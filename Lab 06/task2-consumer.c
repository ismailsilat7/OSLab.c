#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#define FIFO_FILE "/tmp/myfifo"
int main() {
	int fd;
	char buffer [BUFSIZ];
	ssize_t num_bytes;
	printf("Consumer: waiting for producer to connect\n");
	fd = open(FIFO_FILE, O_RDONLY); // Open the named pipe for reading (consumer)
	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	printf("Consumer:  Connected! Waiting for data...\n");
	while (1) { // Producer loop
		num_bytes = read(fd, buffer, BUFSIZ);
		if (num_bytes > 0) {
			buffer[num_bytes] = '\0';
			if (strncmp(buffer, "exit", 4) == 0) {
				break;
			}
			printf("Consumer: Received message: %s", buffer);
		} else if (num_bytes == 0) {
			printf("Consumer: producer closed the connection.\n");
			break;
		}
	}
	close(fd);
	// Close the named pipe
	return 0;
}
