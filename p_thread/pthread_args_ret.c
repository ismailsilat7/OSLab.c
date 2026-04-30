
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define BIG 1000000000UL
uint32_t count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* count_to_big(void * arg) {
    for (u_int32_t i = 0; i < BIG; i++) {
        pthread_mutex_lock(&lock);
        count++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void yourturn() {
    for(int i = 0; i < 5; i++) {
        sleep(1);
        printf("Your turn: %d\n", i);
    }
}

int main() {
    pthread_t newthread1, newthread2;

    pthread_create(&newthread1, NULL, count_to_big, NULL);
    pthread_create(&newthread2, NULL, count_to_big, NULL);

    // for thread to complete even when main ends
    pthread_join(newthread1, NULL);
    pthread_join(newthread2, NULL);

    printf("Result: %d\n", count);
}