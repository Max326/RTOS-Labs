// lab4 assignment 3

#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int t[] = {10, 5, 3, 8, 9};

	int fork_pid[5];

	int i, j, res, status;

	for(i = 0; i < 5; i++) {
		fork_pid[i] = fork();

		if(fork_pid[i] == -1) {
			perror("forking failed\n");
			return EXIT_FAILURE;
		} else if(fork_pid[i] == 0) {
			for(j = 0; j < t[i]; j++) {
				printf("\tpid = %d, ppid = %d, process number: %d, step: %d\n", getpid(), getppid(), i, j);
				usleep(100000);
			}
			printf("Child pid = %d\n", getpid());
			// exit(EXIT_SUCCESS);
			exit(i);
		}
	}

	for(i = 0; i < 5; i++) {
		waitpid(fork_pid[i], &status, 0);
	}
	printf("proces pid = %d finished working, status = %d\n", getpid(), status);

	return 0;
}