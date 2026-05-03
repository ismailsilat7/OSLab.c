#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/stat.h>
#define NUM_THREADS 50
pthread_mutex_t lock;


void* thread_func(void* arg) {
   int id = *((int *)arg);
   pthread_mutex_lock(&lock);
   printf("%d accessed criticial section\n", id);
   sleep(1);
   pthread_mutex_unlock(&lock);
   return NULL;
}


int main() {
   pthread_mutex_init(&lock, NULL);


   int ids[NUM_THREADS];
   pthread_t threads[NUM_THREADS];
   for(int i = 0; i < NUM_THREADS; i++) {
       ids[i] = i;
       pthread_create(&threads[i], NULL, thread_func, &ids[i]);
   }


   for(int i = 0; i < NUM_THREADS; i++) {
       pthread_join(threads[i], NULL);
   }


   pthread_mutex_destroy(&lock);
}

