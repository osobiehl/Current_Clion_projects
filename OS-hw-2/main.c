#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>

int main(int argc, char* argv[]){
	int max_input_lines = 1;
	int print_before_executing = 0;
	int executed_command_index=0;
	max_input_lines = 512;
	int a;
	while ((a = getopt(argc,argv, "n:t")) != -1){
		switch(a){
			case 'n':
				//corner case: no number is specified for n
				for (int i = 0; i < strlen(argv[optind-1]); i++){
					if (!isdigit(argv[optind-1][i]))
					{
						fprintf(stderr, "error, \"%s\" is not a number\n", argv[optind-1]);
						return EXIT_FAILURE;
					}
				}
				max_input_lines = atoi(argv[optind -1]);
				if (max_input_lines < 1){
					fprintf(stderr, "error: n cannot be less than 1");
					return EXIT_FAILURE;
				}
				break;
			case 't':
				print_before_executing = 1;
				break;
			case '?':
				perror("invalid argument");
				return EXIT_FAILURE;
				break;
			default:
				break;
		}
	}
	//creating our command execution string
	int command_line_execution_max = max_input_lines+ argc- optind + (optind == argc? 1 : 0);
	// add 1 for null termination
	char* command_line_execution_string[max_input_lines + argc - optind + 1];

	int remaining_commands = optind;
	if (optind == argc) {
		command_line_execution_string[0] = "/bin/echo";
		executed_command_index = 1;

	}
	else{
		while (remaining_commands < argc){

			command_line_execution_string[executed_command_index] = argv[remaining_commands];
			executed_command_index++;
			remaining_commands++;
		}
	}
	pid_t pid;
	/*
	 * idea: load up using a "while" loop using fgets, using two iterative layers, the first one parses the input, the second one
	 * will "load up" the correct amount of inputs, and then do a system call
	 */

		char* line = NULL;
		size_t len = 0;
		ssize_t nread = 0;
		int while_loop_exec_counter = executed_command_index;

		while (-1 != (nread = getline(&line, &len, stdin))) {
			//get rid of new line character
			if (line[strlen(line)-1] == '\n'){ line[strlen(line)-1] = '\0';}


			command_line_execution_string[while_loop_exec_counter] = malloc(strlen(line)+1);
			if (!command_line_execution_string[while_loop_exec_counter])
				perror("null pointer in malloc call");
			strcpy(command_line_execution_string[while_loop_exec_counter++], line);
			if (while_loop_exec_counter >= command_line_execution_max){
				while_loop_exec_counter = executed_command_index;
				// print out execution string:
				if (print_before_executing){
					for (int i = 0; i < command_line_execution_max; i++){
						if (fprintf(stderr, "%s ", command_line_execution_string[i]) < 0)
							perror("fprintf call failed");
					}
					 if (fprintf(stderr, "\n") < 0)
					 	perror("printf call failed");
					 if (fflush(stderr) == EOF)
					 	perror("could not perform fflush on stderr\n");
				}
				//fork, then execute command
				pid = fork();
				if (pid < 0)
				{
					perror("fork system call failed");
					return EXIT_FAILURE;
				}
				if (pid == 0){
					//execute command in child process
					command_line_execution_string[command_line_execution_max] = NULL;
					if (execvp(command_line_execution_string[0], command_line_execution_string) < 0) {
						perror("error executing execvp");
						exit(-1);
					}

				}
				else {
					int status ;
					if (waitpid(pid, &status, 0) == -1){
						perror("waitpid system call failed");
						return EXIT_FAILURE;
					}
					if(WIFEXITED(status)){
						exit(-1);
					}
					printf("status is: %d\n", status);
					//free allocated memory in parent process
					for (int i = executed_command_index; i < command_line_execution_max; i++){
						 free(command_line_execution_string[i]);
					}
					//reset our execution counter
					while_loop_exec_counter = executed_command_index;
				}


			}

		}
		int status =0;
		//corner case: no more new characters are inputted, but our buffer still contains something

		//no need to free extra memory since program terminates
		if (while_loop_exec_counter != executed_command_index){
			pid = fork();
			if (pid < 0){
				perror("fork failed");
			}
			else if (pid == 0){
				command_line_execution_string[while_loop_exec_counter] = NULL;
				if (print_before_executing) {
					for (int i = 0; i < while_loop_exec_counter; i++) {
						if (fprintf(stderr, "%s ", command_line_execution_string[i]) < 0)
							perror("fprintf call failed");
					}
					if (fprintf(stderr, "\n") < 0)
						perror("fprintf call failed");
				}
				if (execvp(command_line_execution_string[0], command_line_execution_string) < 0)
				{
					perror("error executing execvp");
				}
			}
			else {
				if (waitpid(pid, &status, 0) == -1){
					perror("waitpid system call failed");
				}
			}
		}
	return 0;
}
