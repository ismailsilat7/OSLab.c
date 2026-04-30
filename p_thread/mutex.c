#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMREADERS 4
#define NUMSTRINGS 3
#define BUFLENGTH 1024

char buffer[BUFLENGTH] = {0};

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

char *strings[NUMSTRINGS] = {
    "Hey wassup broski",
    "La-lalala, :)",
    "stay away dear"
};

void *readerthreadfunc(void* arg) {
    long threadID = (long)arg;

    while(1) {
        pthread_mutex_lock(&lock);
        printf("%ld: %s\n", threadID, buffer);
        pthread_mutex_unlock(&lock);
        usleep(5000000);
    }
    return NULL;
}

void slow_copy(char* dest, char* src, size_t maxlength) {
    for(size_t i = 0; i < maxlength; i++) {
        dest[i] = src[i];
        if (dest[i] == 0) break;
        if (i + 1 == maxlength) {
            dest[i] = 0;
            break;
        }
        usleep(50000);
    }
}

int main(int argc, char* argv[]) {
    
    pthread_t readers[NUMREADERS];

    for(long i = 0; i < NUMREADERS; i++) {
        pthread_create(&readers[i], NULL, readerthreadfunc, (void*)i);
    }

    int i = 0;
    while(1) {
        pthread_mutex_lock(&lock);
        slow_copy(buffer, strings[i], BUFLENGTH);
        i = (i+1) % NUMSTRINGS;
        pthread_mutex_unlock(&lock);
        sleep(2);
    }

    return 0;
}


