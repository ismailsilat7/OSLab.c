#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>

# define NS 8 // num students = NS
# define NF 3 // num faculty = NF

sem_t read_try;
sem_t rw_mutex;
sem_t mutex;
int read_count = 0;


void* studentFunc(void* arg) {
	// each student comes back 5 times to read
	for (int i = 0; i < 5; i++) {
		sem_wait(&read_try);
		sem_wait(&mutex);
		read_count++;
		if (read_count == 1) {
			sem_wait(&rw_mutex);
		}
		sem_post(&mutex);
		sem_post(&read_try);
		printf("Student is reading...\n");
		sleep(1);
		sem_wait(&mutex);
		read_count--;
		if (read_count == 0) {
			sem_post(&rw_mutex);
		}
		sem_post(&mutex);
	}
	return NULL;
}

void* facultyFunc(void* arg) {
	// each faculty comes back 3 times to update
	for(int i = 0; i < 3; i++) {
		sem_wait(&read_try);
		sem_wait(&rw_mutex);
		printf("Faculty is updating document...\n");
		sleep(1);
		sem_post(&rw_mutex);
		sem_post(&read_try);
	}
	return NULL;
}

int main() {
	sem_init(&mutex, 0, 1);
	sem_init(&read_try, 0, 1);
	sem_init(&rw_mutex, 0, 1);

	pthread_t students[NS];
	pthread_t faculty[NF];
	for(int i = 0; i < NS; i++) {
		pthread_create(&students[i], NULL, studentFunc, NULL);
	}
	for(int i = 0; i < NF; i++) {
		pthread_create(&faculty[i], NULL, facultyFunc, NULL);
	}
	for(int i = 0; i < NS; i++) {
		pthread_join(students[i], NULL);
	}
	for(int i = 0; i < NF; i++) {
		pthread_join(faculty[i], NULL);
	}

	sem_destroy(&read_try);
	sem_destroy(&rw_mutex);
	sem_destroy(&mutex);
}
