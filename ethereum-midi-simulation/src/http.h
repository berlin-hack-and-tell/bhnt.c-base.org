#ifndef LASH_NETSIMMIDI_HTTP_H_
#define LASH_NETSIMMIDI_HTTP_H_

#include <sys/socket.h> 
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "common.h"

#define LASH_NETSIMMIDI_HTTP_DEFAULTHOST "localhost"
#define LASH_NETSIMMIDI_HTTP_DEFAULTPORT "8889"
#define LASH_NETSIMMIDI_HTTP_BODY_MAX 8192
#define LASH_NETSIMMIDI_HTTP_HEADER_MAX 1024
#define LASH_NETSIMMIDI_HTTP_NETWORKNAME_MAX 32
#define LASH_NETSIMMIDI_HTTP_TIMEOUT_NS 900000;

typedef struct {
	int sd;
	int cd;
	struct sockaddr_in s;
	struct sockaddr_storage c;
	struct addrinfo *res;
	struct addrinfo hints;
	//char networkname[LASH_NETSIMMIDI_HTTP_NETWORKNAME_MAX];
	char *header;
	char *body;
	size_t body_cursor;
} lash_netsimmidi_output_http_t;

int lash_netsimmidiHttpInit(lash_netsimmidi_output_http_t *c, char *optaddr, char *optport);
int lash_netsimmidiHttpConnect(lash_netsimmidi_output_http_t *c);
int lash_netsimmidiHttpSend(lash_netsimmidi_output_http_t *c, unsigned char data[], lash_netsimmidi_node_t *node);
int lash_netsimmidiHttpListen(lash_netsimmidi_output_http_t *c);
int lash_netsimmidiHttpGetConnection(lash_netsimmidi_output_http_t *c);
void lash_netsimmidiHttpResponseAdd(lash_netsimmidi_output_http_t *c, unsigned char *d, size_t l);
int lash_netsimmidiHttpFinishConnection(lash_netsimmidi_output_http_t *c);
void lash_netsimmidiHttpClear(lash_netsimmidi_output_http_t *c);

#endif // LASH_NETSIMMIDI_TCP_H_
