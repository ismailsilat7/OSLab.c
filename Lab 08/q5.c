#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>

#define NUMTHREADS 5
#define NUMELEMENTS 50

typedef struct threadData {
	int startIndex;
	int endIndex;
	int* array;
	int numPrimes;
} threadData;

bool isPrime(int num) {
	if ( num <= 2) {
		return true;
	}
	for (int i = 2; i*i <= num; i++) {
		if ( num % i == 0 ) {
			return false;
		}
	}
	return true;
}

void* findPrimes(void* arg) {
	threadData* data = (threadData *) arg;
	for (int i = data->startIndex; i < data->endIndex; i++) {
		if (isPrime(data->array[i])) {
			data->numPrimes++;
		}
	}
	pthread_exit(NULL);
}


int main() {
	srand(time(NULL));
	int numbers[NUMELEMENTS];
	for (int i = 0; i < NUMELEMENTS; i++) {
		numbers[i] = rand() % 500 + 1;
	}

	pthread_t threads[NUMTHREADS];
	threadData data[NUMTHREADS];
	int size = NUMELEMENTS/NUMTHREADS;
	int remainder = NUMELEMENTS % NUMTHREADS;
	for (int i = 0; i < NUMTHREADS; i++) {
		int startIndex = (i * size);
		int endIndex = ((i + 1) * size);
		if ( i == NUMTHREADS -1 ){
			endIndex += remainder;
		}
		data[i].startIndex = startIndex;
		data[i].endIndex = endIndex;
		data[i].numPrimes = 0;
		data[i].array = numbers;
		pthread_create(&threads[i], NULL, findPrimes, &data[i]);
	}
	int total = 0;
	for (int i = 0; i < NUMTHREADS; i++) {
		pthread_join(threads[i], NULL);
		printf("Thread %d found %d primes\n", i, data[i].numPrimes);
		total += data[i].numPrimes;
	}
	printf("Total primes: %d\n", total);

}

