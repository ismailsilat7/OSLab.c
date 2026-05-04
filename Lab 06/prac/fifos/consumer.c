#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO "/tmp/myfifo"
#define BUFSIZE 50

int main() {
    char buffer[BUFSIZE];
    ssize_t n;

    int fd = open(FIFO, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    while(1) {
        n = read(fd, buffer, BUFSIZE);
        if (n > 0) {
            buffer[n] = '\0';
            if (strncmp(buffer, "exit", 4) == 0) {
                break;
            }
            printf("Received: %s\n", buffer);
        }
        if (n == 0) {
            break;
        }
    }

    close(fd);
    return 0;
}
