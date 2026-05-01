#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void proc_exit(int sig) {
    int status;
    pid_t pid;

    // Handle all terminated children
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("Child %d terminated\n", pid);
    }
}

int main() {
    signal(SIGCHLD, proc_exit);

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            printf("Child %d started\n", getpid());
            sleep(2);
            printf("Child %d exiting\n", getpid());
            exit(0);
        }
    }

    sleep(10);

    printf("Parent exiting\n");
    return 0;
}