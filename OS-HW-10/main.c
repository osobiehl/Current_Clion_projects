#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
 #include <stdlib.h>
#include <dirent.h>
#include <limits.h>
#include <fnmatch.h>
#include <string.h>
//defining flags
#define FILE_FLAG 1
#define DIRECTORY_FLAG 1<<1
#define SYMBOLIC_FLAG 1<<2
#define EXEC_FLAG 1<<3
#define EMPTY_FLAG 1<<4
#define PATTERN_FLAG 1<<5
#define LOCAL_DOMAIN_FLAG 1<<6
#define PIPE_FLAG 1<<7


static inline int is_file(struct dirent* e){
	return e->d_type == DT_REG;
}
static inline int is_directory(struct dirent* e){
	return e->d_type == DT_DIR;
}
static inline int  is_link(struct dirent* e){
	return e->d_type == DT_LNK;
}
static inline int is_local_domain(struct dirent* e){
	return e->d_type == DT_SOCK;
}
static inline int is_pipe(struct dirent* e){
	return e->d_type == DT_FIFO;
}


//global variable b/c I'm lazy
static char* fd_pattern;

int fd( const char* directory, unsigned flags ){

	DIR* d;
	struct dirent *e;
	char next_path[PATH_MAX]; // in case a next path is needed
	d = opendir(directory);

	if (!d){
		printf("error occurred on directory %s\n", directory);
		perror("d: ");
		return -1;
	}
	int count = 0;
	while ((e = readdir(d))){
		count++;
		//for now print everything
		if (e->d_name[0] != '.'){

			//check if it is a directory, avoid infinite recursion (kinda)
			if (flags == 0)
				puts(e->d_name);
			else{
				//this is what happens when you don't plan ahead, juergen would publicly humiliate this garbage
				if ((flags & PATTERN_FLAG)){
					if (fnmatch(fd_pattern, e->d_name, 0) == 0){
						//if the name matches, and pattern flag is the only flag, then we print
						if ( (flags ^ PATTERN_FLAG) == 0)
							puts(e->d_name);
						//else we need to do all of this again
						else{
							//this is bad code but idc
							if ((flags & FILE_FLAG) && is_file(e))
								puts(e->d_name);
							else if ((flags & DIRECTORY_FLAG) && is_directory(e))
								puts(e->d_name);
							else if ((flags & SYMBOLIC_FLAG) && is_link(e))
								puts(e->d_name);
							else if ((flags & EXEC_FLAG)){
								char file_name[PATH_MAX];
								snprintf(file_name, sizeof(file_name), "%s/%s", directory, e->d_name);
								struct stat st;
								if (stat(file_name, &st) == 0 && st.st_mode & S_IXUSR)
									puts(e->d_name);
							}
							else if ((flags & LOCAL_DOMAIN_FLAG) && is_local_domain(e))
								puts(e->d_name);
							else if ((flags & PIPE_FLAG) && is_pipe(e))
								puts(e->d_name);

							else if ((flags & EMPTY_FLAG)){
								char file_name[PATH_MAX];
								snprintf(file_name, sizeof(file_name), "%s/%s", directory, e->d_name);
								struct stat st;
								if (stat(file_name, &st) == 0 && st.st_size < 1)
									puts(e->d_name);
							}
							//try to match all given patterns
						}
					}
				}
				// let the flag games begin!
				else if ((flags & FILE_FLAG) && is_file(e))
					puts(e->d_name);
				else if ((flags & DIRECTORY_FLAG) && is_directory(e))
					puts(e->d_name);
				else if ((flags & SYMBOLIC_FLAG) && is_link(e))
					puts(e->d_name);
				else if ((flags & EXEC_FLAG)){
					char file_name[PATH_MAX];
					snprintf(file_name, sizeof(file_name), "%s/%s", directory, e->d_name);
					struct stat st;
					if (stat(file_name, &st) == 0 && st.st_mode & S_IXUSR)
						puts(e->d_name);
				}
				else if ((flags & LOCAL_DOMAIN_FLAG) && is_local_domain(e))
					puts(e->d_name);
				else if ((flags & PIPE_FLAG) && is_pipe(e))
					puts(e->d_name);

				else if ((flags & EMPTY_FLAG)){
					char file_name[PATH_MAX];
					snprintf(file_name, sizeof(file_name), "%s/%s", directory, e->d_name);
					struct stat st;
					if (stat(file_name, &st) == 0 && st.st_size < 1)
						puts(e->d_name);
				}
				//try to match all given patterns

			}
			if (e->d_type == DT_DIR) {
				//append absolute path
				snprintf(next_path, sizeof(next_path), "%s/%s", directory, e->d_name);
				fd(next_path, flags);
			}

		}
	}
	closedir(d);
	return count;
}

int main(int argc, char* argv[]) {
	char cwd[PATH_MAX];
	int c;
	int flags = 0;

	if (getcwd(cwd, sizeof(cwd)) == NULL){
		perror("unable to get working directory: ");
		return(EXIT_FAILURE);
	}

	while ((c = getopt(argc, argv, "t:")) != -1){
		//printf("%c\n", c);
		char* ptr;
		switch(c) {
			int val;
			case 't':
				printf("optarg is: %s\n", optarg);

				val = optarg[0];
				if (val == 0){
					perror("unknown argument given");
					exit(EXIT_FAILURE);

				}
				switch (val) {
					case 'f':
						flags |= FILE_FLAG;
						break;
					case 'd':
						flags |= DIRECTORY_FLAG;
						break;
					case 'l':
						flags |= SYMBOLIC_FLAG;
						break;
					case 'x':
						flags |= EXEC_FLAG;
					case 'e':
						flags |= EMPTY_FLAG;
						break;
					case 's':
						flags |= LOCAL_DOMAIN_FLAG;
						break;
					case 'p':
						flags |= PIPE_FLAG;
						break;
					default:
						fprintf(stderr, "unknown argument: %c\n", val);
						exit(EXIT_FAILURE);
				}
				break;
			case '?':
				abort();
				break;
			default:
				perror("optarg");
				exit(EXIT_FAILURE);
				break;
		}
	}
	if (optind < argc){
		printf("optind is %d, string is %s\n", optind, argv[optind]);
		char* inp = argv[optind];
		if (inp[0] == '\'')
		{
			flags |= PATTERN_FLAG;
			//ignore the ' character
			fd_pattern = &inp[1];
			if ( fd_pattern[strlen(fd_pattern)-1] == '\'')
				fd_pattern[strlen(fd_pattern)-1] = '\0';

			printf("fd_pattern is: %s\n", fd_pattern);
			//the holy grail of bad practices
			if (optind + 1 < argc){
				inp = argv[optind + 1];
			}
		}
		if (strcmp(inp, "../") ==0){
			fprintf(stderr, "invalid argument %s, please call from parent directory\n", inp);
			exit(EXIT_FAILURE);
		}
			//this is an absolute directory
		if (inp[0] == '/'){
			strcpy(cwd, inp);
			printf("new absolute path given: %s", inp);
		}
		else if (inp[0] != '\''){
			// this is a relative directory
			strcat(cwd, "/\0");
			strcat(cwd, inp);
		}



	}
	printf("cwd is: %s\n", cwd);
	fd(cwd, flags);
	return 0;
}
