#include <stdio.h>
#include <stdio.h>
 #include <string.h>
 #include <unistd.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netdb.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <event.h>
#define SIZE 256
#include "client.c"
void ewrite(int fd, char* str, ssize_t n){
	if (write(fd, str, n ) < 0){
		perror("write");
		exit(EXIT_FAILURE);
	}
}
int eread(int fd, char* str, ssize_t n){
	int res;
	if ( (res = read(fd, str, n )) < 0){
		perror("read");
		exit(EXIT_FAILURE);
	}
	return res;
}

static clnt_t* clients = NULL;
clnt_t* clnt_new() {
	clnt_t * clnt;
	clnt = calloc(1, sizeof(clnt_t));
	if (!clnt){
		perror("calloc");
		return NULL;
	}
	clnt->next = clients;
	clients = clnt;
	clnt->answered_correctly = clnt->games_played = 0;
	printf("user joined\n");
	return clnt;

}
void func(evutil_socket_t sockfd, short evwhat, void *evarg);

void clnt_del(clnt_t *me)
	{
	clnt_t *clnt;
	int cfd = me->fd;

	event_del(me->event);
	(void) close(me->fd);
	if (me == clients) {
	clients = me->next;
	(void) free(me);
	} else {
		for (clnt = clients; clnt && clnt->next != me; clnt = clnt->next) ;
		if (clnt->next == me) {
		clnt->next = me->next;
		(void) free(me);
		}
	}
	printf("user left\n");
}

void clnt_join(evutil_socket_t evfd, short evwhat, void *evarg)
{
	clnt_t* me = evarg;
	struct sockaddr_in clt;
	socklen_t clen = sizeof(clt);
	int sockfd = accept(evfd, (struct sockaddr*)&clt, &clen);
	if (sockfd < 0){
		perror("broken pipe");
		return;
	}

	clnt_t *clnt;
	struct event_base *evb = evarg;
    // not sure if I need to do anything using this

	(void) fcntl(sockfd, F_SETFL, O_NONBLOCK);
	clnt = clnt_new();
	if (! clnt) {
		return;
	}
	clnt->event = event_new(evb, sockfd, EV_READ|EV_PERSIST, func, clnt);
	(void) event_add(clnt->event, NULL);
	char* msg = "M: Guess the missing ____!\nSend your answer in the form R: word\\r\\n,\n";

	ewrite(sockfd, msg, strlen(msg));
	printf("server: clnt-%d joined\n", sockfd);
}

char* readall(int fd){

	char buf[SIZE+1];
	int res;
	char* str_res = NULL;
	int str_size = 0;
	do {
		res = read(fd, buf, SIZE);
		if (!str_res){
			//thanks, valgrind!
			str_res = (char*) malloc( sizeof(char) * res +1);
			if (!str_res){
				perror("malloc failed: ");
				exit(EXIT_FAILURE);
			}
			buf[res] = '\0';
			strcpy(str_res, buf);
			str_size = res;
		}
		else {
			str_size += res;
			str_res = (char *) realloc(str_res, sizeof(char) * str_size + 2);
			if (!str_res) {
				perror("realloc failed: ");
				exit(EXIT_FAILURE);
			}
			buf[res] = '\0';
			strcat(str_res, buf);
		}
	} while(res == SIZE);
	if (res < 0){
		perror("error using read in readall: ");
		exit(EXIT_FAILURE);
	}
	return str_res;
}

char* fetch() {
	int fdes[2];
	if (pipe(fdes) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid_t pid = fork();
	if (pid == -1){
		perror("pid");
		exit(EXIT_FAILURE);
	}
	if (pid == 0){
		//close input since we don't care about it
		(void) close(fdes[0]);
		// time
		if (dup2(fdes[1], STDOUT_FILENO) == -1){
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		(void) close(fdes[1]);
		char* arg[] = {"fortune", "-n", "32", "-s", NULL};
		execvp("fortune",  arg );
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else {
		int status;
		(void) close(fdes[1]);
		char* res = readall(fdes[0]);
		if (waitpid(pid, &status, 0) == -1) {
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFSIGNALED(status)){
			perror("error occured in child process");
			exit(EXIT_FAILURE);
		}
		return res;

	}
}
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
	 /*
	  *
       int getaddrinfo(const char *node, const char *service,
                       const struct addrinfo *hints,
                       struct addrinfo **res);
       given node and service, which identify an Internet host and a
       service, getaddrinfo() returns one or more addrinfo structures, each
       of which contains an Internet address that can be specified in a call
       to bind(2) or connect(2).


                  struct addrinfo {
               int              ai_flags;
               int              ai_family;
               int              ai_socktype;
               int              ai_protocol;
               socklen_t        ai_addrlen;
               struct sockaddr *ai_addr;
               char            *ai_canonname;
               struct addrinfo *ai_next;
           };
	  */
	 rc = getaddrinfo(host, port, &hints, &ai_list);
	 if (rc) {
	 fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rc));
	 return -1;
	 }

	 for (ai = ai_list; ai; ai = ai->ai_next) {
	 	/*
	 	 * socket() creates an endpoint for communication and returns a file descriptor that
	 	 * refers to that endpoint
	 	 *
	 	 */
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
		 /*
		  * assigns
       the address specified by addr to the socket referred to by the file
       descriptor sockfd.  addrlen specifies the size, in bytes, of the
       address structure pointed to by addr.
		  */
		 // if it works, we break, NOW IT MAKES SENSE
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


 void func(evutil_socket_t fd, short evwhat, void *evarg){
	int BUF = 256;
	char buff[BUF];
	clnt_t* me = evarg;
	me->games_played++;
	int sockfd = me->fd;
	int n;
	bzero(buff, BUF);
	// if the correct thing is given:
	//get question:
	char* fetch_res = fetch();
	printf("printing fetch: %s\n", fetch_res);

	// wastes memory but even the professor doesn't care
	char* tokens[strlen(fetch_res)];
	char* token = strtok(fetch_res, " ");
	int i;
	for (i = 0; token; i++){
		tokens[i] = token;
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;
	srand(time(NULL));
	int rand_idx = rand() % i;
	char underscore_ans[strlen(tokens[rand_idx]) +1];
	strcpy(underscore_ans, tokens[rand_idx]);
	for (char* p = tokens[rand_idx]; *p != '\0'; p++){
		*p = '_';
	}
	for (int j =0; j < i; j++){
		ewrite(sockfd, tokens[j], strlen(tokens[j]) );
		ewrite(sockfd, " ", 1);
		printf("%s", tokens[j]);
		printf(" ");
	}
	ewrite(sockfd, "\n", 1);
	// debug
	printf("%s\n", underscore_ans);

	char q_resp[1024];
	int cont = 0;
	do {
		//read the user's response
		int r = eread(sockfd, q_resp, sizeof(q_resp));
		//cases:

		if (strlen(q_resp) > 1 && q_resp[strlen(q_resp)-1 ] =='\n'){
			q_resp[strlen(q_resp)-1] = '\0';
		}

		if (strncmp(q_resp, "Q:", 2) == 0) {
			//end the loop
			printf("quit received!");
			dprintf(sockfd, "You mastered %d/%d challenges. Good bye!\n", me->answered_correctly, me->games_played);
			clnt_del(me);
			free(fetch_res);
			return;

		} else if (strncmp(q_resp, "R: ", 3) == 0) {
			if (strstr(q_resp, underscore_ans) != NULL) {
				char *O_resp = "O: Congratulation - challenge passed!\n";
				ewrite(sockfd, O_resp, strlen(O_resp) + 1);
				me->answered_correctly++;
			}
			else{
				if ( dprintf(sockfd, "F: Wrong guess, your guess was: %s\n - expected: %s\n",
			  q_resp, underscore_ans) < 0){
					perror("dprintf");
					exit(EXIT_FAILURE);
				}
			}
			cont = 1;
			free(fetch_res);
		}
		else{
			char* M_resp = "Unknown response, send your guess in the form 'R: word\\r\\n'.\n";
			ewrite(sockfd, M_resp, strlen(M_resp)+1);
		}
		memset(q_resp, 0, strlen(q_resp));


	}
	while(cont == 0);

}
int
setnonblock(int fd)
{
	int flags;

	flags = fcntl(fd, F_GETFL);
	if (flags < 0)
		return flags;
	flags |= O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) < 0)
		return -1;

	return EXIT_SUCCESS;
}


int main(int argc, char* argv[]) {
	const char* interfaces[] = { "0.0.0.0", "::", NULL };
	if (argc != 2) {
		fprintf(stderr, "missing arguments, expected 2, received %d\n", argc);
		return EXIT_FAILURE;
	}
	int fd, i;
	struct event_base* evb;
	struct event* ev;
	struct sockaddr_in cli;
	evb = event_base_new();
	if (!evb){
		perror("event_base_new");
		return EXIT_FAILURE;
	}
	for (i=0; interfaces[i]; i++ ) {
		fd = tcp_listen(interfaces[i], argv[1]);
		if (fd == -1) {
			continue;
		}
		if (setnonblock(fd) < 0){
			perror("unable to create non-binding socket!\n");
		}
		/*
		 * event handler : for now just accept a single connection
		 */
		ev = event_new(evb, fd, EV_READ|EV_PERSIST, clnt_join, evb);
		event_add(ev, NULL);
	}
	if (event_base_loop(evb, 0) == -1) {
		 fprintf(stderr, "event_base_loop: failed\n");
		 event_base_free(evb);
		 return EXIT_FAILURE;
		 }
	(void) event_base_free(evb);
	(void) close(fd);
	 return EXIT_SUCCESS;
}
