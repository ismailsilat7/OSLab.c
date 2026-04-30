#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define NUM_PHILOSOPHERS 5
#define NUM_STICKS 5

pthread_t philosophers[NUM_PHILOSOPHERS];
pthread_mutex_t chopsticks[NUM_STICKS];
sem_t num_eating;

void* dining(void* arg) {
    int* i = (int *)arg;
    while(1) {
    
        sem_wait(&num_eating);
        pthread_mutex_lock(&chopsticks[*i]);
        pthread_mutex_lock(&chopsticks[(*i + 1) % 5]);

        // eating broski

        pthread_mutex_unlock(&chopsticks[(*i + 1) % 5]);
        pthread_mutex_unlock(&chopsticks[*i]);
        sem_post(&num_eating);
    }

    free(i);

}


int main() {


    sem_init(&num_eating, 0, NUM_PHILOSOPHERS - 1);
    for(int i = 0; i < NUM_STICKS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    for(int i = 0; i < NUM_PHILOSOPHERS; i++) {
        int* id = (int *)malloc(sizeof(int));
        *id = i;
        pthread_create(&philosophers[i], NULL, dining, id);
    }

    for(int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for(int i = 0; i < NUM_STICKS; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }
    sem_destroy(&num_eating);


}
