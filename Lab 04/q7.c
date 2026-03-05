# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>

int main() {
	pid_t pid1 = fork();
	if (pid1 == 0) {
		execlp("ls", "ls", NULL);
		exit(1);
	}
	wait(NULL);
}
