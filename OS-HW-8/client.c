//
// Created by osobiehl on 05.11.20.
//
#include <event2/event.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
struct clnt_t{
	struct clnt_t* next;
	int fd;
	struct event* event;

}typedef clnt_t;
clnt_t* clnt_new() {
	clnt_t * clnt;
	clnt = calloc(1, sizeof(clnt_t));
	if (!clnt){
		perror("calloc");
		return NULL;
	}

}
void clnt_join(evutil_socket_t evfd, short evwhat, void *evarg)
 {
 int cfd;
 clnt_t *clnt;
struct event_base *evb = evarg;

 cfd = tcp_accept(evfd);
 if (cfd == -1) {
 return;
 }
 (void) fcntl(cfd, F_SETFL, O_NONBLOCK);
clnt = clnt_new();
 if (! clnt) {
return;
 }

clnt->fd = cfd;
 clnt->event = event_new(evb, cfd, EV_READ|EV_PERSIST, clnt_read, clnt);
 (void) event_add(clnt->event, NULL);

 clnt_bcast("server: clnt-%d joined\n", cfd);
 }
