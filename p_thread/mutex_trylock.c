#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;

void* routine(void* arg) {
    if(pthread_mutex_trylock(&mutex) != 0) {
        printf("Didn't get the lock :(\n");
    } else {
        printf("Locked broski, hehe\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {

    pthread_t threads[4];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, routine, NULL);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}


