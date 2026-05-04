#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIFO "/tmp/myfifo"
#define BUFSIZE 50

int main() {
    char buffer[BUFSIZE];

    mkfifo(FIFO, 0666);

    int fd = open(FIFO, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    while(1) {
        printf("Enter nessage (exit to quit): ");
        fgets(buffer, BUFSIZE, stdin);
        write(fd, buffer, strlen(buffer));
        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }
    }

    close(fd);
    unlink(FIFO);
    return 0;
}

