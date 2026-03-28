#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main() {

	pid_t pid = fork();
	if (pid < 0) {
		printf("Fork failed!\n");
		return 1;
	}
	else if (pid > 0){
		// PARENT BLOCK
		printf("This is parent's block\n");
	} else { // pid == 0

		// CHILD BLOCK
		printf("This is child's block\n");
		exit(EXIT_SUCCESS);
	}

}


