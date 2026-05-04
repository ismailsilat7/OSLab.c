#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const int SIZE = 4096; 
    const char* name = "OS";

    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);

    char *ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    sprintf(ptr, "%s", "Hello");
    ptr += strlen("Hello") + 1;
    sprintf(ptr, "%s", "World");

    return 0;
}
