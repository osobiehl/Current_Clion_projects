#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>

int debug = 0;
int COpen() {

        char c;
        while ((c = getc(stdin)) != EOF) {
            putc(c, stdout);
        }
        return 0;
}

int SysOpen()
{
    char buf[1];
    while (read(STDIN_FILENO, &buf[0], 1))
        write(STDOUT_FILENO, &buf[0], 1);
    return 0;
}
int LinuxOpen(){
	off_t bytesCopied = 0;
	struct stat fileinfo = {0};
	fstat(STDIN_FILENO, &fileinfo);
	size_t size_left = fileinfo.st_size;
	size_t count = 4096;
	while (size_left > 0){

		if (size_left < count){
			count = size_left;
		}
		if (sendfile(STDOUT_FILENO,STDIN_FILENO, &bytesCopied, count) < 0)
			exit(-1);
		size_left -= count;
	}

	return 0;
}
int main(int argc, char *argv[])
{
    int opt;
    int lastopt = 'd';
    int new_file_desc;
    int idx = 0;
        while (idx < argc)
        {
            if ((opt = getopt(argc, argv, "slp") )!= -1 )
            {
                switch (opt) {
                    case 'l':
                        lastopt = opt;
                        break;
                    case 's':
                        lastopt=opt;
                        break;
                	case'p':
                		lastopt=opt;
                    default:
                        break;
                    case '?':
                        break;
                }

            }
            else
            {
                if (debug){
                    printf("char is: %c\n", argv[idx][0]);
                }

                if (strlen(argv[idx]) == 1 && idx < argc-1){

                    switch(argv[idx][0]) {
                        case '<':
                            new_file_desc = open(argv[idx+1], O_RDONLY);

                            if (debug) {
                                printf("new file descriptor found!");
                                printf("file name is: %s\n", argv[idx+1]);
                            }
                            if (new_file_desc < 0) {
                                perror("input file descriptor error");
                                exit(-1);
                            }
                            dup2(new_file_desc, STDIN_FILENO);
                            if (debug) printf("new STDIN_FILENO is: %d\n", STDIN_FILENO);
                            break;
                        case '>':
                            new_file_desc = open(argv[idx+1], O_CREAT | O_WRONLY);
                            if (debug) {
                                printf("new file descriptor found!\n");
                                printf("file name is: %s\n", argv[idx+1]);
                            }
                            if (new_file_desc < 0) {
                                perror("output file descriptor error");
                                exit(-1);
                            }
                            dup2(new_file_desc, STDOUT_FILENO);
                            if (debug) printf("new STDOUT_FILENO is: %d\n", STDOUT_FILENO);
                            break;
                        default:
                            break;
                    }
                }
            }
            idx++;
        }
    //handle which library call to use
    switch(lastopt){
        case 's':
            if (debug)
                puts("s is the last command!");
            SysOpen();
            break;
        case 'p':
        	LinuxOpen();
        	break;
        case 'd':
        case 'l':
            if (debug)
                puts("l is the last command! / default!");
            COpen();
            break;
    }



    return 0;
}

