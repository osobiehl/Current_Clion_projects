#include <stdio.h>
#include <regex.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#define SIZE 256
char* readall(int fd){
	char buf[SIZE+1];
	int res;
	char* str_res = NULL;
	int str_size = 0;
	while ((res = read(fd, buf, SIZE)) > 0 ){
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

char* RegexParse( char* input, char* Search){

		regex_t regex;
		regmatch_t match[2];
		//put quotes around string
		char reg_match[] = "\":\\s*([^\n]+),\0";
		//add some padding because I'm bad at math
		char cur_string[strlen(Search) + strlen(reg_match) + 2];
		strcpy(cur_string, Search);
		strcat(cur_string, reg_match);
		int reti = regcomp(&regex, cur_string, REG_EXTENDED );
		if (reti){
			perror("could not do regex compilation");
			exit(EXIT_FAILURE);
		}
		/*execute regex*/
		reti = regexec(&regex, input, 2,match, 0 );
		char* res = NULL;
		if (reti == 0){
			int start = (int)match[1].rm_so;
			int end = (int)match[1].rm_eo;
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
		//free regex expression (can be
		regfree(&regex);
		return res;
}
unsigned play(unsigned n, unsigned score, char *text, long answer){
	//	printf("%ld\n", answer);
	int cur_score = 8;
	if ( printf("Q%d: %s?\n", n, text) < 0){
		perror("printf");
		exit(EXIT_FAILURE);
	}

	do{
		long ans;
		char* end;
		if (printf("%d pt>", cur_score) < 0){
			perror("printf");
			exit(EXIT_FAILURE);
		}
		char* inp_str;
		size_t len = 0;
		// don't care about freeing memory unless we are returning
		if (getline(&inp_str, &len, stdin) != -1){
			if ( 0 == (ans = strtol(inp_str, &end, 10))){
				if (puts("unsupported input, try again . . .\n") < 0){
					perror("puts");
					exit(EXIT_FAILURE);
				}
				continue;
			}
			if (ans == answer){
				if (cur_score ==1){
					if (printf("Too large, the correct answer was %ld", answer) < 0){
						perror("printf");
						exit(EXIT_FAILURE);
					}
				}
				if (printf("Congratulations, your answer %ld is correct\n", ans) < 0){
					perror("printf");
					exit(EXIT_FAILURE);
				}
				score += cur_score;
				if (printf("Your total score is %u/%u points.\n", score, 8 * n) < 0 ){
					perror("printf");
					exit(EXIT_FAILURE);
				}
				free(inp_str);
				return (score);
			}
			else if (ans < answer){
				if (cur_score ==1){
					if (printf("Too small, the correct answer was %ld", answer) < 0){
						perror("printf");
						exit(EXIT_FAILURE);
					}
				}
				else if (printf("Too small, try again\n") < 0){
					perror("printf");
					exit(EXIT_FAILURE);
				}
			}
			else{
				if (printf("Too large, try again\n") < 0){
					perror("printf");
					exit(EXIT_FAILURE);
				}
			}
		}
		else{
			if (printf("\nYour total score is %u/%u points.\n", score, 8 * n) < 0 ){
				perror("printf");
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}

		cur_score /= 2;
	}
	while (cur_score > 0);
	if (printf("\nYour total score is %u/%u points.\n", score, 8 * n) < 0 ){
		perror("printf");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int main() {
	if (puts("Answer questions with numbers in the range [1..100].\n"
	     "You score points for each correctly answered question.\n"
	     "If you need multiple attempts to answer a question, the\n"
	     "points you score for a correct answer go down.") == EOF){
		perror("puts ");
	}
	int counter = 0;
	unsigned score = 0;

	while(1){
		counter++;
		char* json = fetch();
		if (!json) {
			puts("NULL POINTER: fetch");
			exit(EXIT_FAILURE);
		}
		char* q = RegexParse(json, "text");
		char* anss = RegexParse(json, "number");
		if (!q || !anss){
			perror("null pointer found!");
			exit(EXIT_FAILURE);
		}
		long ans;
		char* end;
		if ( 0 == (ans = strtol(anss, &end, 10))){
			perror("Error in json\n");
			exit(EXIT_FAILURE);
		}
		score = play(counter, score, q, ans);
		free(anss);
		free(q);

	}
	return 0;
}

