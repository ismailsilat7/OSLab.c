#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

typedef struct review {
	int id;
	int rating;
} review;

typedef struct tData {
	review* reviews;
	int startIndex;
	int endIndex;
	float avg;
} threadData;

void* calcAvg(void *arg) {
	int sum = 0;
	threadData* data = (threadData *)arg;
	for (int i = data->startIndex; i < data->endIndex; i++) {
		sum += data->reviews[i].rating;
	}
	data->avg = (float)sum/(data->endIndex-data->startIndex);
	pthread_exit(0);
}

#define NUMREVIEWS 13
#define NUMTHREADS 3

int main() {
	srand(time(NULL));

	review reviews[NUMREVIEWS];
	for (int i = 0; i < NUMREVIEWS; i++) {
		reviews[i].rating = rand() % 5 + 1;
		reviews[i].id = i;
	}
	printf("Reviews arr:\n");
	for (int i = 0; i < NUMREVIEWS; i++) {
		printf("Review %d: %d\n", reviews[i].id, reviews[i].rating);
	}
	threadData data[NUMTHREADS];
	pthread_t threads[NUMTHREADS];
	int reviewsPerThread = NUMREVIEWS / NUMTHREADS;
	int remainder = NUMREVIEWS % NUMTHREADS;
	for (int i = 0; i < NUMTHREADS; i++) {
		int startIndex = i * reviewsPerThread;
		int endIndex = (i + 1) * reviewsPerThread;
		if (i == NUMTHREADS - 1) {
			endIndex += remainder;
		}
		data[i].reviews = reviews;
		data[i].startIndex = startIndex;
		data[i].endIndex = endIndex;
		data[i].avg = 0;
		pthread_create(&threads[i], NULL, calcAvg, &data[i]);
	}

	float combinedSum = 0;
	for (int i = 0; i < NUMTHREADS; i++) {
		pthread_join(threads[i], NULL);
		printf("Thread %d avg: %.2f\n", i, data[i].avg);
		int count = data[i].endIndex - data[i].startIndex;
		combinedSum += (data[i].avg * count);
	}
	float finalAvg = combinedSum / NUMREVIEWS;
	printf("Overall Average Rating: %.2f\n", finalAvg);
}
