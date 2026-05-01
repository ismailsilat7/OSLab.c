#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

// key insight: it doesn't matter which thread registers the handler, it applies process-wide. The runtime will find whichever thread has the handler registered and use it.

pthread_t threads[3];

void handler(int sig) {
    printf("Signal %d handled by thread %lu\n", sig, pthread_self());
}

void* worker(void* arg) {
    int id = *(int*)arg;
    signal(SIGUSR1, handler); // uncommented as req by c)
    printf("Thread %d started (TID: %lu)\n", id, pthread_self());
    while (1) {
        sleep(1);
    }
    return NULL;
}

int main() {
    int ids[3] = {1, 2, 3};

    // signal(SIGUSR1, handler); // commented as req by c)
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, worker, &ids[i]);
    }
    sleep(2);

    printf("\nSending signal to PROCESS\n");
    kill(getpid(), SIGUSR1);
    sleep(2);
    printf("\nSending signal to THREAD 3\n");
    pthread_kill(threads[2], SIGUSR1);
    sleep(2);
    return 0;
}