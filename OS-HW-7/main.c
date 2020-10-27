#include <stdio.h>
#include <regex.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#define SIZE 256
char* readall(int fd){
	char buf[SIZE+1];
	int res;
	char* str_res = NULL;
	int str_size = 0;
	while ((res = read(fd, buf, SIZE)) > 0 ){
		if (!str_res){
			str_res = (char*) malloc( sizeof(char) * res);
			if (!str_res){
				perror("malloc failed: ");
				exit(EXIT_FAILURE);
			}
			strcpy(str_res, buf);
			str_size = res;
		}
		else {
			str_size += res;
			str_res = (char *) realloc(str_res, sizeof(char) * str_size + 1);
			if (!str_res) {
				perror("realloc failed: ");
				exit(EXIT_FAILURE);
			}
			buf[res] = '\0';
			strcat(str_res, buf);
		}
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
		execlp("curl", "curl", "-s", "http://numbersapi.com/random/math?min=1&max=100&fragment&json", (char*)NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else {
		(void) close(fdes[1]);
		char* res = readall(fdes[0]);
		return res;
	}
}

char* RegexParse( char* input, char* Search){

		regex_t regex;
		regmatch_t match;
		//put quotes around string
		char reg_match[] = "\\\":\\s*(.+),";
		char cur_string[strlen(Search) + strlen(reg_match) + 6];
		strcpy(cur_string, Search);
		strcat(cur_string, reg_match);
		puts(cur_string);
		int reti = regcomp(&regex, cur_string, 0);
		/*execute regex*/
		reti = regexec(&regex, input, 1,&match, 0 );
		char* res = NULL;
		if (reti == 0){
			int start = (int)match.rm_so;
			int end = (int)match.rm_eo;
			if (input[start] == '\"'){
				start++;
				end--;
			}
			res = (char*) malloc( sizeof(char*)* (end-start + 1) );
			if (!res) {
				perror("malloc");
				exit(-1);
			}
			for (int i = 0; i < end - start; i++ ){
				res[i] = input[start+i];
			}
		}
		return res;




	return NULL;

}

int main() {
	char* inp = readall(STDIN_FILENO);
	char* rparsed = RegexParse(inp, "text");
	puts(rparsed);

	/*
	char* res = fetch();
	if (!res)
		puts("NULL POINTER!");
	else puts(res);

	return 0;
	 */
}
