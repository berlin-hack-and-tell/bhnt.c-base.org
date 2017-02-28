#include <stdlib.h>
#include <alsa/asoundlib.h>

#include "midi.h"


int lash_netsimmidiInit(lash_netsimmidi_input_midi_t *m, const char *ascid) {
	int e;
	
	m->initialized = 0;
	
	e = snd_rawmidi_status_malloc(&(m->s));
	e = snd_rawmidi_open(&(m->in), NULL, ascid, 0); 
	e = snd_rawmidi_status(m->in, m->s);
	
	m->ch = malloc(sizeof(unsigned char *) * 2);

	lash_netsimmidiStatusClear(&(m->is));
	
	m->initialized = 1;
	
	return e;
}

// return -1 on error

int lash_netsimmidiGet(lash_netsimmidi_input_midi_t *m) {
	unsigned char d1, d2, d3;
	int more = 0;

	if (!snd_rawmidi_read(m->in, m->ch, 2))
		return -1;
		
	m->is.sub_instruction = *(m->ch) >> 4;
	m->is.channel = *m->ch & 0x0f;
	m->is.value = *(m->ch+1);
		
	d3 = 0;
	d1 = *m->ch;
	d2 = *(m->ch+1);
		
	if (m->is.sub_instruction == 0x0f) { //sysex
		unsigned char sysexbyte = d2;
		while (sysexbyte != 0xf7) { // get rid of the data, 0xf7 marks end
			snd_rawmidi_read(m->in, &sysexbyte, 1);
		}
		m->is.instruction = m->is.sub_instruction;
		m->is.sub_instruction = 0;
		m->is.key = 0;
		m->is.value = 0;
		d2 = 0;
		more = 2;
	} else if ((m->is.sub_instruction & 0x0e) != 0x0c) { // if not 110x, we have one more byte of data coming
		m->is.instruction = m->is.sub_instruction;
		m->is.sub_instruction = 0;
		m->is.key = m->is.value;
		snd_rawmidi_read(m->in, m->ch, 1);
		m->is.value = *m->ch;
		d3 = *m->ch;
		more = 1;
	}
	
	m->raw[0] = d1;
	m->raw[1] = d2;
	m->raw[2] = d3;

	return more;
}

void lash_netsimmidiClear(lash_netsimmidi_input_midi_t *m) {
	if (m->initialized) {
		snd_rawmidi_drain(m->in);
		snd_rawmidi_close(m->in);	
	}
}	

void lash_netsimmidiStatusClear(lash_netsimmidi_input_status_t *is) {
	is->channel = 0;
	is->instruction = 0;
	is->key = 0;
	is->value = 0;
	is->sub_instruction = 0;
	is->sub_value = 0;
}
