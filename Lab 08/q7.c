#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>

#define NUMTHREADS 4

typedef struct threadData {
	char* filename;
	char* keyword;
	int instances;
} threadData;

void* findInstances(void* arg) {

	threadData* data = (threadData *)arg;
	int fd = open(data->filename, O_RDONLY);
	if ( fd < 0 ) {
		perror("file open failed\n");
		pthread_exit(NULL);
	}

	int endByte = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	char* ch = malloc(sizeof(char));
	int inword = 0;
	for(int i = 0; i <= endByte; i++) {
		read(fd, ch, 1);
		if (!(*ch == ' ' || *ch == ',' || *ch == '.' || *ch == '\n' || *ch == '.'
			|| *ch == '!' || *ch == '?' || *ch == ';' || *ch == ':')) {
			if (inword == 0) {
				data->instances++; // word beginss
				inword = 1;
			}
		} else {
			inword = 0; // word ends
		}
	}
	close(fd);
	free(ch);
	pthread_exit(NULL);
}

int main() {

	char* filenames[NUMTHREADS] = {
		"file1.txt", "file2.txt", "file3.txt", "file4.txt"
	};

	threadData data[NUMTHREADS];
	pthread_t threads[NUMTHREADS];
	for(int i = 0; i < NUMTHREADS; i++) {
		data[i].filename = filenames[i];
		data[i].instances = 0;
		pthread_create(&threads[i], NULL, findInstances, &data[i]);
	}
	int total = 0;
	for (int i = 0; i < NUMTHREADS; i++) {
		pthread_join(threads[i], NULL);
		printf("Thread %d found %d words from %s\n", i, data[i].instances, data[i].filename);
		total += data[i].instances;
	}
	printf("Total words: %d\n", total);
}
