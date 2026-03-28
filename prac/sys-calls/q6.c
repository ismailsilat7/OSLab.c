#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


int main() {

	pid_t c1,c2,c3,c4;

	c1 = fork();
	if (c1 == 0) {
		execlp("cp", "cp", "output.txt", "input.txt", NULL);
		printf("C1 failed to execute\n");
		exit(EXIT_FAILURE);
	}
	wait(NULL);
	c2 = fork();
	if (c2 == 0) {
		execlp("mkdir", "mkdir", "test", NULL);
		printf("C2 failed to execute\n");
		exit(EXIT_FAILURE);
	}
	wait(NULL);
	c3 = fork();
	if (c3 == 0) {
		execlp("ls", "ls", NULL);
		printf("C3 failed to execute\n");
		exit(EXIT_FAILURE);
	}
	wait(NULL);
	c4 = fork();
	if (c4 == 0) {
		execlp("rmdir", "rmdir", "test", NULL);
		printf("C4 failed to execute\n");
		exit(EXIT_FAILURE);
	}
	wait(NULL);

}
