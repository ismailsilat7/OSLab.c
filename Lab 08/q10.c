#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define NUM_REGIONS 5
#define NUM_PARTIES 10
#define REGIONSIZE 12
typedef struct threadData {
	int region[REGIONSIZE];
	int votesCount;
	int votesPerParty[NUM_PARTIES];
} threadData;


void* countVotes(void* arg) {
	threadData* data = (threadData *)arg;
	for (int i = 0; i < NUM_PARTIES; i++) {
		data->votesPerParty[i] = 0;
	}
	data->votesCount = 0;
	for (int i = 0; i < REGIONSIZE; i++) {
		int partyId = data->region[i];
		if (partyId >= 0 && partyId < NUM_PARTIES) { // consider correct votes only
			data->votesCount++;
			data->votesPerParty[partyId]++;
		}
	}
	pthread_exit(0);
}


int main() {
	srand(time(NULL));
	pthread_t threads[NUM_REGIONS];
	threadData data[NUM_REGIONS];
	for (int i = 0; i < NUM_REGIONS; i++) {
		for (int j = 0; j < REGIONSIZE; j++) {
	    		data[i].region[j] = (rand() % (NUM_PARTIES + 3)) - 2; // waste incorrect votes
		}
		pthread_create(&threads[i], NULL, countVotes, &data[i]);
	}
	int totalCorrectVotes = 0;
	int globalPartyVotes[NUM_PARTIES] = {0};
	for (int i = 0; i < NUM_REGIONS; i++) {
		pthread_join(threads[i], NULL);
		printf("Region %d results collected. Correct votes: %d/%d\n", i, data[i].votesCount, REGIONSIZE);
		for (int p = 0; p < NUM_PARTIES; p++) {
			globalPartyVotes[p] += data[i].votesPerParty[p];
		}
	}
	printf("Final Election Results\n");
	for (int i = 0; i < NUM_PARTIES; i++) {
		printf("Party %d: %d votes\n", i, globalPartyVotes[i]);
	}
	return 0;
}

