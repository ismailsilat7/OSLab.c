#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>


int main() {

	const int SIZE = 4096;
	const char* name = "OS";
	int fd;
	char* ptr;

	fd = shm_open(name, O_RDONLY, 0666);

	ptr = (char *)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);

	printf("%s\n", (char *)ptr);
	ptr += strlen(ptr) + 1;
	printf("%s\n", (char *)ptr);
	ptr += strlen(ptr) + 1;
	shm_unlink(name);
	return 0;

}
