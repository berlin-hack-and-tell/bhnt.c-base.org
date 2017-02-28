#include <alsa/asoundlib.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/shm.h>

#include "midi.h"
//#include "debug.h"
//#include "common.h"
#include "http.h"
#include "instruction.h"

#include "liblash/lash_debug_log.h"

//#define BUFFER_SIZE 12288 // (4096 * 3)
#define BUFFER_SIZE 512
#define NODES_MAX 1024

// demo for echoing midi signal inputs using libasound2
// using midi reference as described here https://www.midi.org/specifications/item/table-1-summary-of-midi-message
// tested with akai mpd24 and hercules dj console rmx (requires kernel module hdj_mod)

// program execution
int run = 1;
pid_t pid;

// midi specifics
lash_netsimmidi_input_midi_t midi;

// memory related	
key_t thekey;
int memid;
unsigned char *thesegment;

// debug
lash_debug_log_t logger;
char loggermsg[1024];

void reap(int s) {
	if (!pid)
		return;
	kill(pid, SIGINT);
	wait(&s);
}

void shutdown_main(int s) {
	reap(s);
	lash_netsimmidiClear(&midi);	
	if (thesegment != (void*)0) {
		shmdt(thesegment);
		shmctl(memid, IPC_RMID, NULL);
	}
	lash_debugLogFree(&logger);
	exit(s);
}

void sig_child(int s) {
	shutdown_main(s);
}

void sig_abort(int s) {
 	shutdown_main(s);
}

void sig_interrupt_main(int s) {
	shutdown_main(s);
	exit(1);
}

void sig_interrupt_child(int s) {
	exit(s);	
}

unsigned short getCursor() {
	if (thesegment == (void*)0)
		return 0;
		
	return *((unsigned short*)thesegment);
}

unsigned short truncateAtCursor(unsigned short cursor) {
	unsigned short currentcursor = getCursor();
	memmove(thesegment + sizeof(unsigned short), thesegment + currentcursor + sizeof(unsigned short), currentcursor - cursor);
	currentcursor -= cursor;
	memcpy(thesegment, &currentcursor, sizeof(unsigned short));
	return currentcursor;
}

int main(int argc, char **argv) {
	
	lash_debugLogInit(&logger, 1);
	
	signal(SIGABRT, sig_abort);
	signal(SIGCHLD, sig_child);
	
	char tokenfile[15] = "/tmp/shmXXXXXX\0";
	int tmpfd;
	
	tmpfd = mkstemp(tokenfile);
	
	if (tmpfd == -1) {
		lash_debugLogAdd(&logger, "main", LASH_DEBUG_LOG_LEVEL_CRITICAL, "cant create shared mem token file");
		raise(SIGABRT);
	}
	
	sprintf(loggermsg, "tmpfilename %s is fd %i", tokenfile, tmpfd);	
	lash_debugLogAdd(&logger, "main", LASH_DEBUG_LOG_LEVEL_DEBUG, loggermsg);
	
	thekey =  ftok(tokenfile, 0x0A);
	sprintf(loggermsg, "Have token %i", thekey);	
	lash_debugLogAdd(&logger, "main", LASH_DEBUG_LOG_LEVEL_DEBUG, loggermsg);
	
	memid = shmget(thekey, BUFFER_SIZE + sizeof(unsigned short), 0600 | IPC_CREAT);
	if (memid == -1) {
		sprintf(loggermsg, "Couldnt generate shared memory: %s", strerror(errno));	
		lash_debugLogAdd(&logger, "main", LASH_DEBUG_LOG_LEVEL_CRITICAL, loggermsg);
		raise(SIGABRT);
	}
	sprintf(loggermsg, "Have memid %i\n", memid);	
	lash_debugLogAdd(&logger, "main", LASH_DEBUG_LOG_LEVEL_DEBUG, loggermsg);
	
	thesegment = shmat(memid, (void*)0, 0);
	if (thesegment == (unsigned char*)(-1)) {
		sprintf(loggermsg, "Couldnt get memptr: %s", strerror(errno));	
		lash_debugLogAdd(&logger, "main", LASH_DEBUG_LOG_LEVEL_CRITICAL, loggermsg);
		raise(SIGABRT);
	}
	
	if (lash_netsimmidiInit(&midi, *(argv+1)) != 0)
		raise(SIGABRT);
	
	switch (pid = fork()) {
		
		case -1:	
			raise(SIGABRT);
			break;
			
		// child is the tcp client
		case 0:
		
			signal(SIGINT, sig_interrupt_child);
			
			lash_netsimmidi_output_http_t httpclient;
			
			/*
			lash_netsimmidi_node_t nodes[NODES_MAX];
			unsigned short nodes_cursor = 0;
			*/
			
			if (lash_netsimmidiHttpInit(&httpclient, 0, 0) < 0)
				raise(SIGINT);
			
			if (lash_netsimmidiHttpListen(&httpclient) < 0)
				raise(SIGINT);
			
			while (run) {

				unsigned short data_cursor;
				unsigned short out_cursor;
				unsigned short out_threshold;
				
				if (lash_netsimmidiHttpGetConnection(&httpclient) > 0) {
					sprintf(loggermsg, "connect fd: %d", httpclient.cd);	
					lash_debugLogAdd(&logger, "http", LASH_DEBUG_LOG_LEVEL_DEBUG, loggermsg);
					data_cursor = getCursor();
					out_cursor = 0;
					out_threshold = data_cursor;
					
					while (out_cursor < out_threshold) {
						lash_netsimmidiHttpResponseAdd(&httpclient, thesegment + out_cursor + sizeof(unsigned short), 3);
						out_cursor += 3;
						
						// keep around in case we want to revert to http send instead
						/*
						unsigned char *outdata = thesegment + out_cursor + sizeof(unsigned short);
						fprintf(stderr, "data in cursor pos %u: %02x %02x %02x ... ", out_cursor, *outdata, *(outdata+1), *(outdata+2));
						
						if (lash_netsimmidiHttpSend(&httpclient, outdata, &nodes[nodes_cursor]) < 0) {
							fprintf(stderr, "discarded\n");
						} else {
							fprintf(stderr, "sent!\n");
						}*/
					}
					
					out_threshold = out_cursor;
					
					if (out_cursor > 0 ) {
						sprintf(loggermsg, "sent %d triplets to fd %d", (int)out_cursor / 3, httpclient.cd);	
						lash_debugLogAdd(&logger, "http", LASH_DEBUG_LOG_LEVEL_DEBUG, loggermsg);
					}
					
				} else {
					sprintf(loggermsg, "noconnnection: %s", strerror(errno));	
					lash_debugLogAdd(&logger, "http", LASH_DEBUG_LOG_LEVEL_DEBUG, loggermsg);
					out_threshold = getCursor(); // flush buffer
				}
				
				lash_netsimmidiHttpFinishConnection(&httpclient);
				data_cursor = truncateAtCursor(out_threshold);

			}
			
			break;
	}

	signal(SIGINT, sig_interrupt_main);
	
	lash_netsimmidi_instruction_t ins;
	lash_netsimmidiInstructionReset(&ins);
	struct timespec ns, nsr;
	ns.tv_sec = 0;
	ns.tv_nsec = 500000;
	
	while (run) {
		
		int more = 0;
		unsigned short data_cursor = getCursor();
		
		more = lash_netsimmidiGet(&midi);
		
		if (more < 0) {
			run = 0;
		} else {
			if (data_cursor < BUFFER_SIZE) {
				/*sprintf(loggermsg, "raw: %x %x %x", midi.raw[0], midi.raw[1], midi.raw[2]);	
				lash_debugLogAdd(&logger, "midi", LASH_DEBUG_LOG_LEVEL_DEBUG, loggermsg);
				sprintf(loggermsg, "instr %x subinstr %x", midi.is.instruction, midi.is.sub_instruction);	
				lash_debugLogAdd(&logger, "midi", LASH_DEBUG_LOG_LEVEL_DEBUG, loggermsg);*/
				if (!lash_netsimmidiInstructionTranslate(&ins, &(midi.is))) {
					if (ins.state == LASH_NETSIMMIDI_COMPLETED) {
						memcpy(thesegment + data_cursor + sizeof(unsigned short), ins.result, 3);
						data_cursor += 3;
						memcpy(thesegment, &data_cursor, sizeof(unsigned short));
						sprintf(loggermsg, "success translate %x %x %x", ins.result[0], ins.result[1], ins.result[2]);	
						lash_debugLogAdd(&logger, "midi", LASH_DEBUG_LOG_LEVEL_DEBUG, loggermsg);
						lash_netsimmidiInstructionReset(&ins);
						nanosleep(&ns, &nsr);
					}
				}
			} else {
				sprintf(loggermsg, "data buffer full :/");	
				lash_debugLogAdd(&logger, "midi", LASH_DEBUG_LOG_LEVEL_WARNING, loggermsg);
			}			
		}
	}
	
	shutdown_main(0);
	
	return 0;
}
