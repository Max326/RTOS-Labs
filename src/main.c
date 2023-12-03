// lab4 assignment 1

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int fork_pid, fork_pid2, fork_pid3, fork_pid4;
	int i, j;
	int status, status2, status3, status4;

	fork_pid = fork();

	if(fork_pid == -1) {
		perror("P: sie nie udao\n");
	} else if(fork_pid == 0) {
		printf("\tR1: potomny pid = %d, macierzysty - P = %d\n", getpid(), getppid());
		fork_pid2 = fork();

		if(fork_pid2 == -1) {
			perror("\tR1: sie nie udao\n");
		} else if(fork_pid2 == 0) {
			printf("\t\tS1: potomny pid = %d, macierzysty - R1 = %d\n", getpid(), getppid());
		} else {
			fork_pid2 = wait(&status2);
		}
	} else {
		printf("P: proces macierzysty pid = %d\n", getpid());

		fork_pid3 = fork();

		if(fork_pid3 == -1) {
			perror("P: sie nie udalo stworzyc R2\n");
		} else if(fork_pid3 == 0) {
			printf("\tR2: potomny pid = %d, macierzysty - P %d\n", getpid(), getppid());

			fork_pid4 = fork();

			if(fork_pid4 == -1) {
				perror("R2: sie nie udalo stworzyc S2\n");
			} else if(fork_pid4 == 0) {
				printf("\t\tS2: potomny pid = %d, macierzysty - R2 = %d\n", getpid(), getppid());
			} else{
				fork_pid4 = wait(&status4);
			}
		} else{
			fork_pid3 = wait(&status3);
		}

		printf("P: Czekam na potomny ...\n");
		fork_pid = wait(&status);

		printf("P: Proces potomny PID = %d zakonczony; status : %d\n", fork_pid, WEXITSTATUS(status));
	}
	printf(" Proces PID = %d konczy prace \n", getpid());

	return 0;
}