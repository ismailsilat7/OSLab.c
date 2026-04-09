#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

// same as bounded buffer problem
#define NUM_PRODUCERS 5
#define NUM_CONSUMERS 3

#define N 8
sem_t empty; // N buffers
sem_t full; // 0 consumables
sem_t mutex; // 1

int buffer[N] = {0};
int i = 0;
int j = 0;

void* producer(void* arg) {
    int* id = (int *)arg;
    while(1) {
        sem_wait(&empty); // waiting for space to add produced
        sem_wait(&mutex);
        buffer[i] = *id;
        printf("Producer added %d at %d\n", *id, i);
        i = (i + 1) % N;
        sem_post(&mutex);
        sem_post(&full); // indicating that there's smthn available to consume
    }
    free(id);
}

void* consumer(void* arg) {
    int id;
    while(1) {
        sem_wait(&full); // waiting for consumable from producer
        sem_wait(&mutex);
        id = buffer[j];
        printf("Producer consumed %d at %d\n",id, j);
        j = (j + 1) % N;
        sem_post(&mutex);
        sem_post(&empty); // indicating that consumer has consumed
    }

}

int main() {

    pthread_t consumers[NUM_CONSUMERS];
    pthread_t producers[NUM_PRODUCERS];

    sem_init(&empty, 0, N);
    sem_init(&mutex, 0, 1);
    sem_init(&mutex, 0, 0);
    
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        if (pthread_create(&consumers[i], NULL, consumer, NULL) != 0) {
            printf("Thread creation failed\n");
        }
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        int* id = (int *)malloc(sizeof(int));
        *id = i;
        if (pthread_create(&producers[i], NULL, producer, id) != 0) {
            printf("Thread creation failed\n");
        }
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        if (pthread_join(consumers[i], NULL) != 0) {
            printf("Join failed\n");
        }
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        if (pthread_join(producers[i], NULL) != 0) {
            printf("Join failed\n");
        }
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    

}

// web servers queue for web servers & application servers
// print spooler, apps produce print jobs, printer consumes them
// streaming, video buffer b/w producer streaming server & consumer viewer
