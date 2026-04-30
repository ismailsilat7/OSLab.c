#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

// 0 = square, 1 = cube, 2 = factorial
typedef struct task {
    int input;
    int type;
} task;

typedef struct result {
    long value;
} result;

typedef struct threadData {
    task* tasks;
    result* results;
    int startIndex;
    int endIndex;
} threadData;

long calcFact(int n) {
    if (n <= 1) return 1;
    long res = 1;
    for (int i = 2; i <= n; i++) res *= i;
    return res;
}

void* processTasks(void *arg) {
    threadData* data = (threadData *)arg;
    for (int i = data->startIndex; i < data->endIndex; i++) {
        int val = data->tasks[i].input;
        int type = data->tasks[i].type;
        if (type == 0) {
            data->results[i].value = (long)val * val; // square
        } else if (type == 1) {
            data->results[i].value = (long)val * val * val; // cube
        } else if (type == 2) {
            data->results[i].value = calcFact(val); // factorial
        }
    }
    pthread_exit(0);
}

#define NUMTASKS 10
#define NUMTHREADS 3

int main() {
    srand(time(NULL));

    task tasks[NUMTASKS];
    result results[NUMTASKS];
    printf("Server Received Tasks\n");
    for (int i = 0; i < NUMTASKS; i++) {
        tasks[i].input = rand() % 10 + 1;
        tasks[i].type = rand() % 3;
        char* typeStr = (tasks[i].type == 0) ? "Square" : (tasks[i].type == 1 ? "Cube" : "Factorial");
        printf("Task %d: %s of %d\n", i, typeStr, tasks[i].input);
    }

    threadData data[NUMTHREADS];
    pthread_t threads[NUMTHREADS];

    int tasksPerThread = NUMTASKS / NUMTHREADS;
    int remainder = NUMTASKS % NUMTHREADS;
    for (int i = 0; i < NUMTHREADS; i++) {
        int startIndex = i * tasksPerThread;
        int endIndex = (i + 1) * tasksPerThread;
        if (i == NUMTHREADS - 1) {
            endIndex += remainder;
        }
        data[i].tasks = tasks;
        data[i].results = results;
        data[i].startIndex = startIndex;
        data[i].endIndex = endIndex;
        pthread_create(&threads[i], NULL, processTasks, &data[i]);
    }

    for (int i = 0; i < NUMTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Final Processed Results\n");
    for (int i = 0; i < NUMTASKS; i++) {
        char* typeStr = (tasks[i].type == 0) ? "Square" : (tasks[i].type == 1 ? "Cube" : "Factorial");
        printf("Task %d [%s of %d]: %ld\n", i, typeStr, tasks[i].input, results[i].value);
    }

    return 0;
}
