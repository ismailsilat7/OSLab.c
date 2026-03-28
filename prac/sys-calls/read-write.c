#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main() {

	int fd1 = open("input.txt", O_RDONLY);
	if (fd1 < 0) {
		perror("Error opening file input.txt");
		return 1;
	}

	int fd2 = open("output.txt", O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd2 < 0) {
		perror("error opening file output.txt");
		return 1;
	}

	char buffer[9];
	int read_bytes = read(fd1, buffer, 9);
	if (read_bytes == 9) {
		printf("Read 9 bytes successfully\n");
	}

	int write_bytes = write(fd2, buffer, 9);
	if (write_bytes == 9) {
		printf("Wrote 9 bytes successfully\n");
	}

	close(fd1);
	close(fd2);
}
