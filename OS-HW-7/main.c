#include <stdio.h>
#include <regex.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
char* readall(int fd){
	char buf[256];
	int res;
	char* str_res = NULL;
	int str_size = 0;
	while ((res = read(fd, buf, 256)) > 0 ){
		if (!str_res){
			str_res = (char*) malloc( sizeof(char) * res);
			if (!str_res){
				perror("malloc failed: ");
				exit(EXIT_FAILURE);
			}
			strcpy(str_res, buf);
			str_size = res;
		}
		str_size += res;
		str_res = (char*)realloc(str_res, sizeof(char)*str_size +1);
		if (!str_res){
			perror("realloc failed: ");
			exit(EXIT_FAILURE);
		}
		strcat(str_res, buf);
	}
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
		execlp("curl", "curl", "-s", "'http://numbersapi.com/random/math?min=1&max=100&fragment&json\'");
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else {
		(void) close(fdes[1]);
		char* res = readall(fdes[0]);
		if (res)
			puts(res);

	}


	return NULL;
}


int main() {
	char* res = fetch();
	if (!res)
		puts("NULL POINTER!");

	return 0;
}
