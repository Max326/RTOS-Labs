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
			printf("Child pid = %d finished with status = %d\n", getpid(), WEXITSTATUS(status));
			exit(EXIT_SUCCESS);
		} else {
			printf("parent pid = %d\n", getpid());
		}
	}

	for(i = 0; i < 5; i++) {
		waitpid(fork_pid[i], &status, 0);
	}
	printf("parent process pid = %d finished\n", getpid());

	printf("proces pid = %d finished working, status = %d\n", getpid(), status);

	return 0;
}

/*
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
    int i, j, status;

    for(i = 0; i < 5; i++) {
        fork_pid[i] = fork();

        if(fork_pid[i] == -1) {
            perror("forking failed");
            return EXIT_FAILURE;
        } else if(fork_pid[i] == 0) {
            for(j = 0; j < t[i]; j++) {
                printf("\tpid = %d, ppid = %d, process number: %d, step: %d\n", getpid(), getppid(), i, j);
                usleep(100000);
            }
            exit(EXIT_SUCCESS);
        } else {
            printf("parent pid = %d\n", getpid());
        }
    }

    for(i = 0; i < 5; i++) {
        waitpid(fork_pid[i], &status, 0);
        printf("Child with pid = %d finished\n", fork_pid[i]);
    }

    printf("parent process pid = %d finished\n", getpid());

    return 0;
}
*/