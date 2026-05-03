#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <time.h>
#define N 4
#define NP 8
#define NC 8

int buffer[N] = {0};
int k = 0;
int j = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;


void* producerFunc(void* arg) {
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	printf("Producer trying to write...\n");
	int d = rand() % 10;
	buffer[k] = d;
	printf("Producer wrote %d at %d\n", d, k);
	k = (k + 1) % N;
	sleep(1);
	pthread_mutex_unlock(&mutex);
	sem_post(&full);
	return NULL;
}

void* consumerFunc(void* arg) {
	sem_wait(&full);
	pthread_mutex_lock(&mutex);
	printf("Consumer about to consume...\n");
	int d = buffer[j];
	printf("Consumer consumed %d at %d\n", d, j);
	j = (j + 1) % N;
	sleep(1);
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
	return NULL;
}



int main() {
	srand(time(NULL));
	sem_init(&empty,0, N);
	sem_init(&full, 0, 0);
	pthread_mutex_init(&mutex, NULL);

	pthread_t consumers[NC];
	pthread_t producers[NP];
	for(int i = 0; i < NC; i++) {
		pthread_create(&consumers[i], NULL, consumerFunc, NULL);
	}
	for(int i = 0; i < NP; i++) {
		pthread_create(&producers[i], NULL, producerFunc, NULL);
	}
	for(int i = 0; i < NC; i++) {
		pthread_join(consumers[i], NULL);
	}
	for(int i = 0; i < NP; i++) {
		pthread_join(producers[i], NULL);
	}
	sem_destroy(&empty);
	sem_destroy(&full);
	pthread_mutex_destroy(&mutex);
	return 0;
}
