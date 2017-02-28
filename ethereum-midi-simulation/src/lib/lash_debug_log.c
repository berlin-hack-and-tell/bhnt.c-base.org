#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "liblash/lash_debug_log.h"

struct timespec _timecontainer;

int lash_debugLogInit(lash_debug_log_t *log, int autoflush) {

	log->capacity = 0;
	log->items = (lash_debug_log_item_t*)malloc(sizeof(lash_debug_log_item_t) * LASH_DEBUG_LOG_CAPACITY_CHUNK);
	
	if (log->items == NULL) {
		log = NULL;
		return 1;
	}
	
	log->error_string_buffer = (char*)calloc(LASH_DEBUG_LOG_CAPACITY_DESCRIPTION, sizeof(char));
	
	if (log->error_string_buffer == NULL) {
		log = NULL;
		return 1;
	}
	
	log->capacity = LASH_DEBUG_LOG_CAPACITY_CHUNK;
	log->count = 0;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &_timecontainer);
	log->ns_start = _timecontainer.tv_nsec;
	log->autoflush = autoflush != 0 ? 1 : 0;
		
	return 0;
}

/**
 * TODO Auto extend memory for log if capacity runs out
 */
 
int lash_debugLogAdd(lash_debug_log_t *log, char *origin, char level, char *description) {
	if (log->count == log->capacity || log->capacity == 0)
		return 1;
	
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &_timecontainer);
	(log->items+log->count)->ns = _timecontainer.tv_nsec;
	(log->items+log->count)->level = level;
	
	if (description == NULL)
		(log->items+log->count)->description = log->error_string_buffer;
	else
		(log->items+log->count)->description = description;
	
	
	if (origin == NULL)
		(log->items+log->count)->origin = log->origin_string_buffer;
	else
		(log->items+log->count)->origin = origin;
		

	if (log->autoflush > 0)
		fprintf(stderr, "%s: %s\n", (log->items+log->count)->origin, (log->items+log->count)->description);

	//*(log->error_string_buffer) = NULL;
	//*(log->origin_string_buffer) = NULL;
	log->error_string_buffer = NULL;
	log->origin_string_buffer = NULL;
	
	log->count++;
		
	return 0;
}

void lash_debugLogSetDescription(lash_debug_log_t *log, char *d) {
	log->error_string_buffer = d;
}

void lash_debugLogSetOrigin(lash_debug_log_t *log, char *o) {
	log->origin_string_buffer = o;
}

void lash_debugLogFree(lash_debug_log_t *log) {
	if (log->error_string_buffer != NULL)
		free(log->error_string_buffer);
		
	if (log->items != NULL)
		free(log->error_string_buffer);
}
