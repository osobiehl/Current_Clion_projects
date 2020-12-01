/*
* nssh.c --
*
* A new process identifier namespaces can be created using the
* clone() system call. (The clone() system call is the Linux
* backend of the fork() system call).
*/
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#define STACK_SIZE 1048576
static char stack[STACK_SIZE];
static int child(void *ignored)
{
	printf("child pid is: %d\n"
		"parent pid is %d\n", getpid(), getppid());
	execl("/bin/sh", "sh", NULL);
	perror("execl");
	return 1;
}
int main(void)
{
	pid_t pid;
	pid = clone(child, stack+STACK_SIZE, CLONE_NEWPID | SIGCHLD, NULL);
	if (pid < 0) {
		perror("clone");
		return 1;
	}
	(void) waitpid(pid, NULL, 0);
	return 0;
}