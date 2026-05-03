#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <time.h>

# define NC 6 // NC = num customers
# define ND 3 // ND = num delivery agents
# define N 10 // N = buffer size

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

int k = 0;
int l = 0;
int buffer[N] = {0};

void* custFunc(void* arg) {
	// customer orders 3 times
	for (int i = 0; i < 3; i++) {
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		printf("Customer is ordering...\n");
		int d = rand() % 10;
		buffer[k] = d;
		printf("Order %d placed: data %d\n", k, d);
		k = (k + 1) % N;
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
		usleep((rand() % 500) * 1000); // random to simulate spikess
	}
	return NULL;
}

void* deliverFunc(void* arg) {
	// deliveryAgent picks order 6 times
	for (int i = 0; i < 6; i++) {
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		printf("Delivery agent is picking up order...\n");
		int d = buffer[l];
		printf("Order %d picked: data %d\n", l, d);
		l = (l + 1) % N;
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
		sleep(rand() % 3 + 1); // varying processing time
	}
	return NULL;
}


int main() {
	srand(time(NULL));
	sem_init(&empty, 0, N);
	sem_init(&full, 0, 0);
	pthread_mutex_init(&mutex, NULL);

	pthread_t customers[NC];
	pthread_t deliveryA[ND];

	for(int i = 0; i < NC; i++) {
		pthread_create(&customers[i], NULL, custFunc, NULL);
	}
	for(int i = 0; i < ND; i++) {
		pthread_create(&deliveryA[i], NULL, deliverFunc, NULL);
	}

	for(int i = 0; i < NC; i++) {
		pthread_join(customers[i], NULL);
	}
	for(int i = 0; i < ND; i++) {
		pthread_join(deliveryA[i], NULL);
	}

	pthread_mutex_destroy(&mutex);
	sem_destroy(&full);
	sem_destroy(&empty);
}
