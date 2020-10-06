#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
	int max = 100;
	int fort = 0;
	int x;
	while((x = getopt(argc, argv,"n:t"))!= -1){
		switch(x){
			case 'n':
				max = atoi(argv[optind-1]);
				break;
			case 't':
				fort = 1;
				break;
		}
	}
	int defaul = 0;
	if (argc == optind)
		defaul = 1;
	int clength = argc - optind + defaul;
	char* command_array[clength];
	int index = 0;
	if (argc == optind)
		command_array[0] = "/bin/echo";
	else{
		for(int i= optind; i < argc; i++){
			command_array[index++] = argv[i];
		}
	}
	for(int i =0; i< clength; i++){
		printf("%s",command_array[i]);
	}
	char * line = NULL;
	size_t leninp = 0;
	char* array2[max];
	char* array3[max + index + 1];
	int index2 = 0;
	while(-1 != getline(&line, &leninp, stdin)){
		if(line[strlen(line)-1] == '\n'){
			line[strlen(line)-1] = '\0';
		}
		array2[index2++] = strdup(line);
		if (index2 == max){
			for(int i = 0; i<index; i++){
				array3[i] = command_array[i];
			}
			for(int i = index; i< max+index; i++){
				array3[i] = array2[i-index];
			}
			index2=0;
			pid_t pid = fork();
			if(pid < 0){
				perror("fork failed\n");
				return EXIT_FAILURE;
			}
			if(pid == 0) {
				array3[index + max] = NULL;
				if (fort) {
					for (int i = 0; i < index + max; i++) {
						if (fprintf(stderr, "%s ", array3[i]) < 0)
							perror("printf failed\n");
					}
					if (execvp(array3[0], array3) < 0) {
						perror("error dude\n");
						exit(-1);
					}
				}
			}
				else{
					int check;
					if(waitpid(pid, &check, 0) == -1){
						perror("error dude\n");
						return EXIT_FAILURE;
					}
					for(int i = 0; i < max; i++){
						free(array2[i]);
					}
				}
			}

		}
		return 0;
	}