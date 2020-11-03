#include <stdio.h>
#include <stdio.h>
 #include <string.h>
 #include <unistd.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netdb.h>
/*
 * Creates a TCP socket
 *
 *
 *
 */
int tcp_listen(const char *host, const char *port)
	 {
	 struct addrinfo hints, *ai_list, *ai;
	 int rc, fd = 0, on = 1;

	 memset(&hints, 0, sizeof(hints));
	 hints.ai_flags = AI_PASSIVE;
	 hints.ai_family = AF_UNSPEC;
	 hints.ai_socktype = SOCK_STREAM;
	 rc = getaddrinfo(host, port, &hints, &ai_list);
	 if (rc) {
	 fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rc));
	 return -1;
	 }

	 for (ai = ai_list; ai; ai = ai->ai_next) {
		 fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
		 if (fd < 0) {
		 continue;
		 }
		 #ifdef IPV6_V6ONLY
		 if (ai->ai_family == AF_INET6) {
			(void) setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, &on, sizeof(on));
		 }
		 #endif
		 setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
		 if (bind(fd, ai->ai_addr, ai->ai_addrlen) == 0) {
			break;
		 }
		 (void) close(fd);
	 }
	 freeaddrinfo(ai_list);
	 if (ai == NULL) {
		 fprintf(stderr, "failed to bind to '%s' port %s\n", host, port);
		 return -1;
	 }
	/*
	 * listen( int sockfd, int backlog):
	 * 	sockfd: file descriptor that refers to a type of SOCK_STREAM or SOCK_SEQPACKET
	 * 	backlog: maximum  length to which the pending connections to sockfd might grow
	 */
	 if (listen(fd, 42) < 0) {
		 perror("listen");
		 (void) close(fd);
		 return -1;
		 }
		 return fd;
 }

int main() {
	printf("Hello, World!\n");
	return 0;
}
