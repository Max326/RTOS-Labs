// lab4 assignment 1

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define CHILD  4
#define PARENT 8

int main(int argc, char *argv[]) {
	int fork_pid;
	int i, j;

	fork_pid = fork();

	if(fork_pid == 1) {
		perror("M: sie nie udao\n");
	} else if(fork_pid == 0) {
		printf("\tP: potomny pid= %d\n", getpid());
		for(j = 0; j < CHILD; j++) {
			printf("\tP: pracuje %d sekund ...\n", j);
			sleep(1);
		}
		printf("loop ended");
	} else {
		printf("M: proces macierzysty pid = %d\n", getpid());
		printf("M: moj potomny pid = %d\n", fork_pid);
		for(i = 0; i < PARENT; i++) {
			printf("M: pracuje %d sek ...\n", i);
			sleep(1);
		}
		printf("qniec lupa\n");
	}
	printf(" Proces PID = %d konczy prace \n", getpid());

	return 0;
}