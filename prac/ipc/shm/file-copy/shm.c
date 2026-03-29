#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFSIZE 10

int main(int argc, char* argv[]) {

	if (argc != 3) {
		printf("Correct usage: %s input.txt copy.txt\n", argv[0]);
		return 1;
	}

	const char* name = "file_copy";
	const int SIZE = 4096;

	int fd;
	char* ptr;
	char buffer[BUFSIZE];
	char* input = argv[1];
	char* output = argv[2];



	int rFd = open(input, O_RDONLY, 0777);
	fd = shm_open(name, O_RDWR | O_CREAT, 0777);
	ftruncate(fd, SIZE);
	ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	int total = 0;
	char* base = ptr;
	char* data_ptr = ptr + sizeof(int);
	int bytes_read;
	while((bytes_read = read(rFd, buffer, sizeof(buffer))) > 0) {
		memcpy(data_ptr, buffer, bytes_read);
		data_ptr+= bytes_read;
		total += bytes_read;
	}
	memcpy(base, &total, sizeof(int));
	close(rFd);


	pid_t pid = fork();
	if (pid < 0) {
		printf("Fork failed\n");
		return 1;
	} else if (pid == 0) {
		int wFd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		fd = shm_open(name, O_RDONLY, 0777);
		ptr = (char *)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
		int total;
		memcpy(&total, ptr, sizeof(int));
		ptr += sizeof(int);
		int remaining = total;
		while(remaining > 0) {
			int bytes_to_read = remaining > BUFSIZE ? BUFSIZE : remaining;
			memcpy(buffer, ptr, bytes_to_read);
			write(wFd, buffer, bytes_to_read);
			ptr += bytes_to_read;
			remaining -= bytes_to_read;
		}
		close(wFd);
		exit(EXIT_SUCCESS);
	}

	wait(NULL);
	shm_unlink(name);
	return 0;

}
