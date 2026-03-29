#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_FILE "/tmp/myfifo"
#define BUFSIZE 50

int main() {

	int fd;
	char buffer[BUFSIZE];
	ssize_t num_bytes;

	fd = open(FIFO_FILE, O_RDONLY);
	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	printf("Consumer has successfully established a connection!\n");
	while(1) {
		num_bytes = read(fd, buffer, BUFSIZE - 1);
		if (num_bytes > 0) {
			buffer[num_bytes] = '\0';
			if (strncmp(buffer, "exit", 4) == 0) {
				break;
			}
			printf("Consumer received: %s\n", buffer);
		}
		if(num_bytes == 0) {
			printf("Consumer closed the connection\n");
			break;
		}
	}
	close(fd);

}

