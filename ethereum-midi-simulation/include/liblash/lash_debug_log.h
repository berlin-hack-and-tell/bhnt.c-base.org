#ifndef LASH_DEBUG_LOG_H_
#define LASH_DEBUG_LOG_H_

#define LASH_DEBUG_LOG_CAPACITY_CHUNK 255
#define LASH_DEBUG_LOG_CAPACITY_DESCRIPTION 255

#define LASH_DEBUG_LOG_LEVEL_CRITICAL 127
#define LASH_DEBUG_LOG_LEVEL_WARNING 64
#define LASH_DEBUG_LOG_LEVEL_MESSAGE -1
#define LASH_DEBUG_LOG_LEVEL_DEBUG -64
#define LASH_DEBUG_LOG_LEVEL_ALL -128

typedef struct lash_debug_log_item_t {
	unsigned long ns;
	char level;
	char *origin;
	char *description;
} lash_debug_log_item_t;

 
typedef struct lash_debug_log_t {
	unsigned long ns_start;
	unsigned short int count;
	unsigned short int capacity;
	lash_debug_log_item_t *items;
	char *error_string_buffer; // used for sprintf, if no description in item is set the current error string buffer is used instead
	char *origin_string_buffer; // used for sprintf, if no description in item is set the current error string buffer is used instead
	int autoflush;
} lash_debug_log_t;

#ifndef alog
#define alog 1;
lash_debug_log_t lash_logobj;
#line 31 __FILE__
#define aloglevel(x) lash_debugLogInit(&lash_logobj, 1)
#define alogset(c, s) lash_debugLogSetDescription(&lash_logobj, s); lash_debugLogSetOrigin(&lash_logobj, c);
#define alogadd(l) lash_debugLogAdd(&lash_logobj, NULL, l, NULL);
#endif //lash_log

#ifdef LASH_DEBUG_LOG_GLOBAL
#include <stdio.h>
lash_debug_log_t lash_log_global;
#endif

#ifdef __cplusplus 
extern "C" {
#endif
int lash_debugLogInit(lash_debug_log_t *log, int autoflush);
int lash_debugLogAdd(lash_debug_log_t *log, char *origin, char level, char *description);
void lash_debugLogSetDescription(lash_debug_log_t *log, char *d);
void lash_debugLogSetOrigin(lash_debug_log_t *log, char *o);
void lash_debugLogFree(lash_debug_log_t *log);

#ifdef __cplusplus 
}
#endif

#endif
