// lab5 assignment 2
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 100
int num_steps = 1000;
double step, pi, sum, range;

typedef struct {
	int x0;
	int x1;
} thread_data;	// this way you can initialize struct objects without using the struct keyword

// or
// struct thread_data{
// 	int x0;
// 	int x1;
// 	const char *msg;
// };

void *start_routine(void *arg) {
	thread_data *data = (thread_data *)arg;

	int i;
	double x;

	for(i = data->x0; i < data->x1; i++) {
		x = (double)(i + 0.5) * step;
		sum = sum + 4.0 / (1.0 + x * x);
	}

	free(arg);
	return NULL;
}

int main() {
	int i, rc;
	sum = 0.0;

	pthread_t thread_id[NUM_THREADS];
	
	// scheduling set here
	pthread_attr_t attr;
	struct sched_param param;
	pthread_attr_init(&attr);
	pthread_attr_setschedpolicy(&attr, SCHED_RR);
	param.sched_priority = sched_get_priority_max(SCHED_RR);
	pthread_attr_setschedparam(&attr, &param);
	// end of schedule setting here

	void *status;

	double threads = NUM_THREADS;

	range = num_steps / threads;

	step = 1.0 / (double)(num_steps);

	double iter;
	iter = 0;

	for(i = 0; i < NUM_THREADS; i++) {
		thread_data *temp = malloc(sizeof(thread_data));

		*temp = (thread_data) {iter, iter + range};

		rc = pthread_create(&thread_id[i], &attr, &start_routine, (void *)temp);

		if(rc) {
			printf("error, rc= %d\n", rc);
			exit(1);
		}

		iter += range;
	}

	// joining threads

	for(i = 0; i < NUM_THREADS; i++) {
		rc = pthread_join(thread_id[i], &status);
		if(rc) {
			printf("joining error, rc= %d\n", rc);
			exit(1);
		}
	}

	pi = step * sum;

	printf("PI = %.15f\n", pi);

	pthread_exit(NULL);

	pthread_attr_destroy(&attr);

	return 0;
}
