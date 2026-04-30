#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define NUM_READERS 9
#define NUM_WRITERS 3

sem_t rw_mutex; // 1
sem_t mutex; // 1
sem_t read_try; // 1
int read_count = 0;

void* readFunc(void* arg) {

    while(1) {
        sem_wait(&read_try); // wait for writers to finish writing
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);
        sem_post(&read_try);
        printf("Broski, I'm reading, %d\n", (int*)arg);
        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);

    }

    return NULL;
}


void* writeFunc(void* arg) {

    while(1) {
        sem_wait(&read_try); // blocks new readers
        sem_wait(&rw_mutex);
        printf("Broski, I'm writing, %d\n", (int *)arg);
        sem_post(&rw_mutex);
        sem_post(&read_try); // allow new readers
    }

    return NULL;
}



