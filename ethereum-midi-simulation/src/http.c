#include <sys/socket.h> 
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

//#include <arpa/inet.h>

#include "http.h"
#include "common.h"
#include "midi.h"
#include "instruction.h"

int lash_netsimmidiHttpInit(lash_netsimmidi_output_http_t *c, char *optaddr, char *optport) {
	
	int yes = 1;
	struct timeval timeout;
	
	char *addr = LASH_NETSIMMIDI_HTTP_DEFAULTHOST;
	if (optaddr != (void*)0) {
		addr = optaddr;
	}
	
	char *port = LASH_NETSIMMIDI_HTTP_DEFAULTPORT;
	if (optport != (void*)0) {
		port = optport;
	}
	
	memset(&(c->hints), 0, sizeof(c->hints));
	c->hints.ai_family = AF_UNSPEC;
	c->hints.ai_socktype = SOCK_STREAM;
	c->hints.ai_flags = AI_PASSIVE; 
	c->cd = -1;
	c->body_cursor = 0;
	
	getaddrinfo(addr, port, &(c->hints), &(c->res));
	
	//c->sd = socket(AF_INET, SOCK_STREAM, 0);
	c->sd = socket(c->res->ai_family, c->res->ai_socktype, c->res->ai_protocol);
    if (c->sd == -1) {
		return -1;
    }
    
    c->header = malloc(sizeof(char) * LASH_NETSIMMIDI_HTTP_HEADER_MAX);
    c->body = calloc(sizeof(char), LASH_NETSIMMIDI_HTTP_BODY_MAX);
    
    if (c->header == (void*)0 || c->body == (void*)0) {
		lash_netsimmidiHttpClear(c);
		return -1;
	}
    
    //fcntl(c->sd, F_SETFL, O_NONBLOCK);
    
    if (setsockopt(c->sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		lash_netsimmidiHttpClear(c);
		return -1;
	}
	
	timeout.tv_sec = 0;
	timeout.tv_usec = LASH_NETSIMMIDI_HTTP_TIMEOUT_NS;
	
	if (setsockopt(c->sd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(struct timeval)) == -1) {
		lash_netsimmidiHttpClear(c);
		return -1;
	}

	if (bind(c->sd, c->res->ai_addr, c->res->ai_addrlen) == -1) {
		lash_netsimmidiHttpClear(c);
		return -1;
	}
    
    /*c->networkname[0] = 0;
    */
     
    freeaddrinfo(c->res);
    
    return 0;
}

int lash_netsimmidiHttpListen(lash_netsimmidi_output_http_t *c) {
	return listen(c->sd, 1) == -1;
}

int lash_netsimmidiHttpGetConnection(lash_netsimmidi_output_http_t *c) {
	int e = 0;
	socklen_t sin_size;
	c->cd = accept(c->sd, (struct sockaddr *)&(c->c), &sin_size);
	// we're more of a talker than a listener
	if (c->cd > 0) {
		while (e != 0) {
			e = read(c->sd, c->body, 10);
			if (e < 0)
				return -1;
		}
	}
	return c->cd;
}


void lash_netsimmidiHttpResponseAdd(lash_netsimmidi_output_http_t *c, unsigned char *d, size_t l) {
	memcpy(c->body + c->body_cursor, d, l);
	c->body_cursor += l;
}

int lash_netsimmidiHttpFinishConnection(lash_netsimmidi_output_http_t *c) {
	int r;
	char request[LASH_NETSIMMIDI_HTTP_BODY_MAX + LASH_NETSIMMIDI_HTTP_HEADER_MAX];
	
	sprintf(c->header, "HTTP/1.1 200 OK\r\nServer: Midifeeder\r\nAccess-Control-Allow-Origin: *\r\nContent-type: text/plain\r\nContent-Length: %d\r\n\r\n", (int)c->body_cursor);
	strcpy(request, c->header);
	memcpy(request + strlen(c->header), c->body, c->body_cursor);
	
	r = send(c->cd, request, strlen(c->header) + c->body_cursor, 0);
	
	c->body_cursor = 0;
	*(c->body) = 0;
	
	close(c->cd);
	return r;
}

/*
int lash_netsimmidiHttpConnect(lash_netsimmidi_output_http_t *c) {
	//return connect(c->sd, (struct sockaddr*)&(c->s) , sizeof(c->s));
	return connect(c->sd, c->res->ai_addr, c->res->ai_addrlen);
}
*/

/*
int lash_netsimmidiHttpSend(lash_netsimmidi_output_http_t *c, unsigned char data[], lash_netsimmidi_node_t *node) {
	
	int e;
	char instruction[32];
	char *request;
	int connected;

	switch(data[0]) {
		case LASH_NETSIMMIDI_NODEUP:
			strcpy(instruction, "POST /node/\0");
			*(c->body) = 0;
			break;
		default:
			fprintf(stderr, " (not handled)");
			return -2;
	}
	
	connected = lash_netsimmidiHttpConnect(c);
	
	if (connected != 0 && errno != EISCONN) {
		fprintf(stderr, "failed connect: %s", strerror(errno));
		return -1;
	}
	
	sprintf(c->header, "%s HTTP/1.0\r\nContent-Type: application/json\r\nContent-Length: %u\r\n\r\n", instruction, (unsigned int)strlen(c->body));
	request = strcat(c->header, c->body);
	fprintf(stderr, "\n(preparing to send: %s ...", request);
	
	if (send(c->sd, request, strlen(request), 0) < 0)
		return -1;
	
	// discard result for now
	while (e != 0) {
		e = read(c->sd, c->body, LASH_NETSIMMIDI_HTTP_BODY_MAX);
		fprintf(stderr, "\ngot: %s", c->body);
		if (e < 0)
			return -1;
	}
	
	close(c->sd);
	
	return 0;
	
}
*/
void lash_netsimmidiHttpClear(lash_netsimmidi_output_http_t *c) {
	if (c->header != (void*)0)
		free(c->header);
		
	if (c->body != (void*)0)
		free(c->body);
		
	close(c->sd);
}
