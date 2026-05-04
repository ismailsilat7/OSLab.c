#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    const int SIZE = 4096;
    const char *name = "OS";

    int fd = shm_open(name, O_RDONLY, 0666);
    char* ptr = (char *) mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);

    printf("%s\n", ptr);
    ptr += strlen(ptr) + 1;
    printf("%s\n", ptr);

    shm_unlink(name);
    return 0;
}