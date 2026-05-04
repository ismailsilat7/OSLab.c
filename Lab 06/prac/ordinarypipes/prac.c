#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    int fd[2];
    pid_t pid;
    char write_msg[] = "Hello from parent";
    char read_msg[50];

    pipe(fd);// bfr fork

    pid = fork();
    if (pid < 0) {
        perror("Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        close(fd[1]);
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child received: %s\n", read_msg);
    } else {
        close(fd[0]);
        write(fd[1], write_msg, strlen(write_msg) + 1); // include '\0'
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}

