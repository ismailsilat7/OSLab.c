#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define NUMSTUDENTS 50

void* calcAverage(void* arg) {

	int* students = (int *) arg;
	float* avg = malloc(sizeof(float));
	*avg = 0;
	for (int i = 0; i < NUMSTUDENTS; i++) {
		*avg += students[i];
	}
	*avg /= NUMSTUDENTS;
	pthread_exit(avg);
}

void* findHighest(void* arg) {

	int* students = (int *)arg;
	int* highest = malloc(sizeof(int));
	if (NUMSTUDENTS <= 0) {
		pthread_exit(NULL);
	}
	*highest = students[0];
	for (int i = 1; i < NUMSTUDENTS; i++) {
		if (students[i] > *highest) {
			*highest = students[i];
		}
	}
	pthread_exit(highest);
}

void* findLowest(void* arg) {

	int* students = (int *)arg;
	int* lowest = malloc(sizeof(int));
	if (NUMSTUDENTS <= 0) {
		pthread_exit(NULL);
	}
	*lowest = students[0];
	for (int i = 1; i < NUMSTUDENTS; i++) {
		if (students[i] < *lowest) {
			*lowest = students[i];
		}
	}
	pthread_exit(lowest);

}


void* getPassed(void* arg) {

	int* students = (int *)arg;
	int* num = malloc(sizeof(int));
	*num = 0;
	if (NUMSTUDENTS <= 0) {
		pthread_exit(NULL);
	}
	for (int i = 1; i < NUMSTUDENTS; i++) {
		if (students[i] >= 50) {
			(*num)++;
		}
	}
	pthread_exit(num);
}

int main() {

	srand(time(NULL));
	int students[NUMSTUDENTS];
	for (int i = 0; i < NUMSTUDENTS; i++) {
		students[i] = rand() % 100 + 1;
	}

	pthread_t avg_thread;
	pthread_t highest_thread;
	pthread_t lowest_thread;
	pthread_t passed_thread;

	pthread_create(&avg_thread, NULL, calcAverage, &students);
	pthread_create(&highest_thread, NULL, findHighest, &students);
	pthread_create(&lowest_thread, NULL, findLowest, &students);
	pthread_create(&passed_thread, NULL, getPassed, &students);

	float* avg;
	pthread_join(avg_thread, (void **)&avg);
	int* highest;
	pthread_join(highest_thread,(void **)&highest);
	int* lowest;
	pthread_join(lowest_thread, (void **)&lowest);
	int* passed;
	pthread_join(passed_thread, (void **)&passed);

	printf("Student Marks: ");
	for(int i = 0; i < NUMSTUDENTS; i++) {
		printf("%d, ", students[i]);
	}
	printf("\nAvg: %.2f, Highest: %d, Lowest: %d, NumPassed: %d out of %d\n",
		*avg, *highest, *lowest, *passed, NUMSTUDENTS);

	free(avg); free(highest); free(lowest); free(passed);
}
