// lab5 assignment 1
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 8

typedef struct{
	int cnt;
	int sum;
	const char *msg;
} thread_data; // this way you can initialize struct objects without using the struct keyword

// or
// struct thread_data{
// 	int cnt;
// 	int sum;
// 	const char *msg;
// };

void* start_routine(void *arg){
	thread_data *data = (thread_data *)arg;

	printf("thread %d: %s, sum = %d\n", data->cnt, data->msg, data->sum);

	// usleep(5000); // otherwise the values were overwriting themselves

	int ret = data->cnt;
	free(arg);
	pthread_exit((void*) ret);
}

int main(){
	int i, sum, rc;
	sum = 0;

	pthread_t thread_id[NUM_THREADS];
	
	pthread_attr_t attr;
	struct sched_param param;

	pthread_attr_init(&attr);
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
    pthread_attr_setschedparam(&attr, &param);


	void *status;

	char *msg[NUM_THREADS] = {
		"english",
		"french",
		"spanish",
		"polish",
		"german",
		"russian",
		"turkish",
		"portuguese"
	};
	
	for (i = 0; i < NUM_THREADS; i++){
		thread_data *temp = malloc(sizeof(thread_data));

		*temp = (thread_data){i, sum, msg[i]}; 

		rc = pthread_create(&thread_id[i], &attr, &start_routine, (void *)temp);

		if (rc){
			printf("error, rc= %d\n", rc);
			exit(1);
		}

		sum += 1;

		// thread_data *data = &td[i];
	}

	// joining threads

	for (i = 0; i < NUM_THREADS; i++){
		rc = pthread_join(thread_id[i], &status);
		if (rc){
			printf("joining error, rc= %d\n", rc);
			exit(1);
		}
		printf("thread %d joined main thread with status: %d\n", i, (int)status); 
	}

	printf("main thread finished, exiting...\n");
	pthread_exit(NULL);

	pthread_attr_destroy(&attr);

	return 0;
}

// int num_steps = 100000;


// int main ()
// {
// 	int i;
// 	double x, pi, step, sum = 0.0;

// 	step = 1.0 / (double) num_steps;
// 	for (i=0; i < num_steps; i++)
// 	{
// 		x = (double)(i + 0.5) * step;
// 		sum = sum + 4.0 / (1.0 + x * x);
// 	}
// 	pi = step * sum;

// 	printf("PI = %.15f\n", pi);

// 	return 0;
// }
