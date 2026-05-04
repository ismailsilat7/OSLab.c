#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/stat.h>

/*
// Create
int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
ftruncate(fd, size)

char * ptr = (char *)mmap(0, size, PROT_READ, PROT_WRITE, MAP_SHARED, fd, 0);



munmap(fd, size);
shm_unlink(name);
*/



