#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUMTHREADS 5

typedef struct threadData {
	int transactionType;
	int amount;
	int* balance;
} threadData;

void* processTransaction(void* arg) {

	threadData* data = (threadData*)arg;
	int temp = *(data->balance);
	if (data->transactionType == 0) {
		printf("Deposit: %d\n", data->amount);
		temp += data->amount;
	} else {
		printf("Withdraw: %d\n", data->amount);
		temp -= data->amount;
	}
	usleep(1000);
	*(data->balance) = temp;
	pthread_exit(NULL);
}

int main() {
	int balance = 1000;
	printf("Initial balance: %d\n", balance);
	threadData data[NUMTHREADS];
	pthread_t threads[NUMTHREADS];
	for (int i = 0; i < NUMTHREADS; i++) {
		data[i].balance = &balance;
		data[i].amount = rand() % 200 + 1;
		data[i].transactionType = rand() % 2;

		pthread_create(&threads[i], NULL, processTransaction, &data[i]);
	}

	for (int i = 0; i < NUMTHREADS; i++) {
		pthread_join(threads[i], NULL);
	}
	printf("Final Balance: %d\n", balance);

}
