#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>

# define NR 4
# define NW 3

sem_t rw_mutex;
sem_t mutex;
sem_t read_try;
int read_count = 0;

void* readFunc(void* arg) {
	sem_wait(&read_try);
	sem_wait(&mutex);
	read_count++;
	if(read_count == 1) {
		sem_wait(&rw_mutex);
	}
	sem_post(&mutex);
	sem_post(&read_try);
	printf("Reader is reading...\n");
	sem_wait(&mutex);
	read_count--;
	if(read_count == 0) {
		sem_post(&rw_mutex);
	}
	sem_post(&mutex);

	return NULL;
}

void* writeFunc(void* arg) {
	sem_wait(&read_try);
	sem_wait(&rw_mutex);
	printf("Write is writing...\n");
	sleep(1);
	sem_post(&rw_mutex);
	sem_post(&read_try);
	return NULL;
}


int main() {
	sem_init(&rw_mutex, 0, 1);
	sem_init(&read_try, 0, 1);
	sem_init(&mutex, 0, 1);

	pthread_t readers[NR];
	pthread_t writers[NW];
	for(int i = 0; i < NR; i++) {
		pthread_create(&readers[i], NULL, readFunc, NULL);
	}
	for(int i = 0; i < NW; i++) {
		pthread_create(&writers[i], NULL, writeFunc, NULL);
	}
	for(int i = 0; i < NR; i++) {
		pthread_join(readers[i],NULL);
	}
	for(int i = 0; i < NW; i++) {
		pthread_join(writers[i], NULL);
	}

	sem_destroy(&rw_mutex);
	sem_destroy(&mutex);
	sem_destroy(&read_try);
}
