#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define NUM_READERS 9
#define NUM_WRITERS 3

sem_t rw_mutex;
sem_t mutex;
int read_count = 0;

void* readFunc(void* arg) {

    while(1) {
        sem_wait(&mutex); // update read_count
        read_count++;
        if (read_count == 1) {
            sem_wait(&rw_mutex); // indicate there r readers
        }
        sem_post(&mutex); // exit CS for read_count
        printf("Broski, I'm reading, %d\n", (int*)arg);
        sem_wait(&mutex); // enter CS for read_count
        read_count--; 
        if (read_count == 0) { // if no more readers
            sem_post(&rw_mutex); // allow writers
        }
        sem_post(&mutex);
    }

    return NULL;
}


void* writeFunc(void* arg) {

    while(1) {
        sem_wait(&rw_mutex);
        printf("Broski, I'm writing, %d\n", (int *)arg);
        sem_post(&rw_mutex);
    }

    return NULL;
}



