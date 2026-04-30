#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <semaphore.h>

#define THREAD_NUM 16
sem_t *semaphore;

void *routine(void* args) {
    int* id = (int* )args;
    printf("Wating in login queue, id: %d\n", *id);
    sem_wait(semaphore);
    printf("Logged in hehe, id: %d\n", *id);
    sleep(rand() % 5 + 1);
    printf("Logged out, id: %d\n", *id);
    sem_post(semaphore);
    free(id);
    return NULL;
}


int main(int argc, char* argv[]){

    pthread_t th[THREAD_NUM];
    semaphore = sem_open("/mysem", O_CREAT | O_TRUNC, 0644, 12);
    if (semaphore == SEM_FAILED) {
        perror("sem_open failed");
        exit(1);
    }
    // unanamed: sem_t semaphore;
    // sem_init(&sem, 0, 1);
    int i;
    for(int i = 0; i < THREAD_NUM; i++) {
        int* a = malloc(sizeof(int));
        *a = i;
        if(pthread_create(&th[i], NULL, routine, a) != 0) {
            perror("Failed to create thread\n");
        }
    }

    for(int i = 0; i < THREAD_NUM; i++) {
        if(pthread_join(th[i], NULL) != 0) {
            perror("Failed to join\n");
        }
    }
    
    sem_close(semaphore);
    sem_unlink("/mysem");
    // sem_destroy(&sem);
    return 0;
}
