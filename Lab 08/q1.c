#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>

typedef struct fileTrack {
    int tNum;
    long startByte;
    long endByte;
    char* fileName;
    int lines;
} fileTrack;

#define NUMTHREADS 4

void* readFile(void* arg) {
    fileTrack *fData = (fileTrack *)arg;
    int fd = open(fData->fileName, O_RDONLY);
    if (fd < 0) {
        perror("Open failed");
        pthread_exit(NULL);
    }

    lseek(fd, fData->startByte, SEEK_SET);
    char buffer;
    long currentPos = fData->startByte;
    
    while (currentPos < fData->endByte) {
        if (read(fd, &buffer, 1) <= 0) break;
        if (buffer == '\n') {
            fData->lines++;
        }
        currentPos++;
    }
    close(fd);
    pthread_exit(NULL);
}

int main() {
    char* fileName = "data.txt";
    struct stat st;
    
    if (stat(fileName, &st) != 0) {
        perror("Stat failed");
        return 1;
    }

    long fileSize = st.st_size;
    long bytesPerThread = fileSize / NUMTHREADS;
    
    pthread_t threads[NUMTHREADS];
    fileTrack tData[NUMTHREADS];

    printf("File size: %ld bytes. Dividing into %d parts.\n", fileSize, NUMTHREADS);

    for (int i = 0; i < NUMTHREADS; i++) {
        tData[i].tNum = i;
        tData[i].fileName = fileName;
        tData[i].lines = 0;
        tData[i].startByte = i * bytesPerThread;
        if (i == NUMTHREADS - 1) {
            tData[i].endByte = fileSize;
        } else {
            tData[i].endByte = (i + 1) * bytesPerThread;
        }
        pthread_create(&threads[i], NULL, readFile, &tData[i]);
    }

    int total = 0;
    for (int i = 0; i < NUMTHREADS; i++) {
        pthread_join(threads[i], NULL);
        total += tData[i].lines;
        printf("Thread %d counted %d lines\n", 
                i, tData[i].lines);
    }
    printf("Total requests: %d\n", total);
    return 0;
}
