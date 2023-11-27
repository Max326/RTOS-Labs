#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define NUM_THREADS 1

double x, pi, step, sum = 0.0;

double num_steps = 1000;

pthread_mutex_t mutex_pi = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;

typedef struct
{
	int start_step;
	int end_step;
} thread_data;

void *pi_approx(void *arg)
{
	thread_data *data = (thread_data *)arg;
	double x, partial_sum = 0.0;

	for (int i = data->start_step; i < data->end_step; i++)
	{
		x = (double)(i + 0.5) * step;
		partial_sum += 4.0 / (1.0 + x * x);
	}

	pthread_mutex_lock(&mutex_pi);
	sum += partial_sum;
	pthread_mutex_unlock(&mutex_pi);

	pthread_barrier_wait(&barrier);
	return NULL;
}

int main(int argc, char *argv[])
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();

	pthread_t thread_id[NUM_THREADS];
	thread_data thread_args[NUM_THREADS];

	int steps_per_thread = num_steps / NUM_THREADS;

	step = 1.0 / num_steps;

	pthread_barrier_init(&barrier, NULL, NUM_THREADS);

	int i;
	void *status;

	for (i = 0; i < NUM_THREADS; i++)
	{
		thread_args[i].start_step = i * steps_per_thread;
		thread_args[i].end_step = (i + 1) * steps_per_thread;
		pthread_create(&thread_id[i], NULL, pi_approx, (void *)&thread_args[i]);
	}

	for (i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(thread_id[i], NULL);
	}

	pi = step * sum;
	printf("Calculated value of PI = %.15f\n", pi);

	pthread_barrier_destroy(&barrier);

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

	printf("Program executed in: %f seconds\n", cpu_time_used);

	return 0;
}