#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

#define fifo_file "task3"
#define BUFSIZE 50

int main() {
	mkfifo(fifo_file, 0666);
	int fd;
	pid_t pid = fork();

	if (pid < 0) {
		perror("Fork failed\n");
		return 1;
	} else if (pid == 0) {
		int secret_key = 765;
		fd = open(fifo_file, O_WRONLY);
		printf("fd (child) = %d\n", fd);
		write(fd, &secret_key, sizeof(int));
		close(fd);
		exit(EXIT_SUCCESS);
	}
	int secret_key;
	fd = open(fifo_file, O_RDONLY);
	printf("fd (parent) = %d\n", fd);
	read(fd, &secret_key, sizeof(int));
	printf("Secret key received from child: %d\n", secret_key);
	close(fd);

	unlink(fifo_file);

	return 0;

}
