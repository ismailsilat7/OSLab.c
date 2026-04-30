
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>

void* myturn(void * arg) {
    for(int i = 0; i < 8; i++) {
        sleep(1);
        printf("My turn: %d\n", i);
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
    pthread_t newthread;

    pthread_create(&newthread, NULL, myturn, NULL);
    yourturn();

    // for thread to complete even when main ends
    pthread_join(newthread, NULL);

}