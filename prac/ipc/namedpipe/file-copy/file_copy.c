#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_FILE "file-copy"
#define SIGNAL "signal"
#define BUFSIZE 10

int main() {

	char* input = "input.txt";
	char* output = "output.txt";

	mkfifo(FIFO_FILE, 0777);
	int fd;
	char buffer[BUFSIZE];
	pid_t pid = fork();
	if (pid < 0) {
		printf("fork failed\n");
		return 1;
	} else if(pid == 0) {
		fd = open(FIFO_FILE, O_RDONLY);
		int wFd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		int num_bytes;
		while( (num_bytes = read(fd, buffer, BUFSIZE)) > 0) {
			write(wFd, buffer, num_bytes);
		}
		close(wFd);
		exit(EXIT_SUCCESS);
	}

	fd = open(FIFO_FILE, O_WRONLY);
	int rFd = open(input, O_RDONLY);
	int num_bytes;
	while( (num_bytes = read(rFd, buffer, BUFSIZE)) > 0) {
		write(fd, buffer, num_bytes);
	}
	close(rFd);

	unlink(FIFO_FILE);

}

