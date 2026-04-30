#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

typedef struct order {
	int id;
	int price;
} order;

typedef struct tData {
	order* orders;
	int startIndex;
	int endIndex;
	int subTotal;
} threadData;

void* subTotal(void *arg) {
	threadData* data = (threadData *)arg;
	for (int i = data->startIndex; i < data->endIndex; i++) {
		data->subTotal += data->orders[i].price;
	}
	pthread_exit(0);
}

#define NUMORDERS 50
#define NUMTHREADS 3
int main() {
	srand(time(NULL));
	order orders[NUMORDERS];
	for (int i = 0; i < NUMORDERS; i++) {
		orders[i].price = rand()%50 + 1;
		orders[i].id = i;
	}
	threadData data[NUMTHREADS];
	pthread_t threads[NUMTHREADS];
	int orderPerThread = NUMORDERS/NUMTHREADS;
	int remainder = NUMORDERS % NUMTHREADS;
	for (int i = 0; i < NUMTHREADS; i++) {
		int startIndex = i * orderPerThread;
		int endIndex = ((i + 1) * orderPerThread) + (i == NUMTHREADS - 1 ? remainder : 0);
		data[i].orders = orders;
		data[i].startIndex = startIndex;
		data[i].endIndex = endIndex;
		data[i].subTotal = 0;
		pthread_create(&threads[i], NULL, subTotal, &data[i]);
	}
	int total = 0;
	for (int i = 0; i < NUMTHREADS; i++) {
		pthread_join(threads[i], NULL);
		printf("Subtotal by thread %d: %d\n", i, data[i].subTotal);
		total += data[i].subTotal;
	}
	printf("Total: %d\n", total);
	printf("Printing orders (to crosscheck):\n");
	int sum = 0;
	for (int i = 0; i < NUMORDERS; i++) {
		printf("%d, ",orders[i].price);
		sum += orders[i].price;
	}
	printf("\nCrosscheck Sum: %d\n", sum);
}

