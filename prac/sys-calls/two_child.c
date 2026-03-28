#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main() {

	pid_t pid1 = fork();
	if(pid1 < 0) {
		printf("Fork faoled\n");
		return 1;
	} else if (pid1 == 0) {
		printf("Child Process tasked with printing it's pid - PID: %d\n", getpid());
		exit(EXIT_SUCCESS);
	}
	pid_t pid2 = fork();
	if (pid2 < 0) {
		printf("Fork failed!");
		return 1;
	} else if (pid2 == 0) {
		printf("Child Process tasked with printing parent's pid - PID: %d\n", getppid());
		exit(EXIT_SUCCESS);
	}

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	printf("Parent waited for both child processes - both of which have returned/finished executing\n");
	return 0;
}

