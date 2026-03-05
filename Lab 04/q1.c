# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <sys/wait.h>
int main() {
	pid_t pid1 = fork();

	if (pid1 == 0) {
		printf("PID: %d\n", getpid());
		exit(0);
	}
	pid_t pid2 = fork();
	if (pid2 == 0) {
		printf("Parent PID: %d\n", getppid());
		exit(0);
	}
	int status;
	wait(&status);
}
