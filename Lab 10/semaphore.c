#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#define N 4
#define NUMTHREADS 50
sem_t sem;


void *thread_func(void* arg) {
   int id = *((int *)arg);
   sem_wait(&sem);
   printf("thread %d accessed critical section\n", id);
   sleep(1);
   sem_post(&sem);
   return NULL;
}


int main() {
   sem_init(&sem, 0, N);


   int ids[NUMTHREADS];
   pthread_t threads[NUMTHREADS];
   for(int i = 0; i < NUMTHREADS; i++) {
       ids[i] = i;
       pthread_create(&threads[i], NULL, thread_func, &ids[i]);
   }
   for(int i = 0; i < NUMTHREADS; i++) {
       pthread_join(threads[i], NULL);
   }


   sem_destroy(&sem);
}









