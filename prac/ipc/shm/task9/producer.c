#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {

	const int SIZE = 4096;
	const char* name = "my_segment";

	int fd;
	char* ptr;

	pid_t pid = fork();
	if (pid < 0) {
		perror("Fork failed\n");
		return 1;
	} else if (pid == 0) {
		fd = shm_open(name,O_CREAT | O_RDWR, 0666);
		ftruncate(fd, SIZE);
		ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

		char* message = "Hello from child";
		sprintf(ptr, "%s\n", message);
		ptr += strlen(message) + 1;
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
	fd = shm_open(name, O_RDONLY, 0666);
	ptr = (char *)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
	printf("Message receieved: %s\n", (char *)ptr);
	shm_unlink(name);
	return 0;

}
