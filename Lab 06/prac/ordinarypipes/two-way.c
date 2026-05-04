#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

# define READEND 0
# define WRITEEND 1

int main() {

    int p2c[2];
    int c2p[2];
    pid_t pid;

    char parent_msg[] = "Hello from parent";
    char child_msg[] = "Hello from child";

    char buffer[50];

    pipe(p2c);
    pipe(c2p);

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } 

    if (pid == 0){
        close(p2c[WRITEEND]);
        close(c2p[READEND]);

        read(p2c[READEND], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        write(c2p[WRITEEND], child_msg, strlen(child_msg) + 1);

        close(p2c[READEND]);
        close(c2p[WRITEEND]);
        exit(EXIT_SUCCESS);
    }

    close(c2p[WRITEEND]);
    close(p2c[READEND]);

    write(p2c[WRITEEND], parent_msg, strlen(parent_msg) + 1);

    read(c2p[READEND], buffer, sizeof(buffer));
    printf("Parent received: %s\n", buffer);

    close(c2p[READEND]);
    close(p2c[WRITEEND]);
}
