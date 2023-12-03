// lab4 assignment 2

#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int fork_pid;
	int i, res, status;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <path_to_executable> [args_for_executable]\n", argv[0]);
        return EXIT_FAILURE;
	}

	fork_pid = fork();

	if(fork_pid == -1) {
		perror("forking failed\n");
		return EXIT_FAILURE;
	} else if(fork_pid == 0) {
		printf("pid = %d, ppid = %d\n", getpid(), getppid());

		// res = spawnl(WNOWAIT, "/home/max/Projects/RTOS-exec-test/build/my_executable_name", "my_executable_name", "10", NULL); this should work during labs

		// here's running it without weird stuff:
		// res = execl("/home/max/Projects/RTOS-exec-test/build/my_executable_name", "my_executable_name", "2", NULL); // except this replaces the whole process with the executable

		printf("Give me the program path and number of steps: ");

		char *program_name = argv[1];
        char *arg1 = argc > 2 ? argv[2] : NULL;  // First argument for the child program, if provided
        res = execl(program_name, program_name, arg1, NULL);

		if(res < 0) {
			printf("error in running the child program\n");
			exit(EXIT_FAILURE);
		}
	} else {
		printf("parent pid = %d\n", getpid());

		for(i = 1; i <= 3; i++) {
			printf("Parent - step %d\n", i);
			sleep(1);
		}

		fork_pid = wait(&status);
		printf("parent process pid = %d finished\n", getpid());
	}
	printf("proces pid = %d finished working, status = %d\n", getpid(), status);

	return 0;
}