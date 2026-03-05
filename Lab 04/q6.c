# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>

int main() {

	pid_t pid1 = fork();
	if (pid1 == 0) {
		printf("Creating test_folder...\n");
		execlp("mkdir", "mkdir", "test_folder", NULL);
	}
	wait(NULL);

	pid_t pid2 = fork();
	if (pid2 == 0) {
		printf("Creating q5_copy.c...\n");
		execlp("cp", "cp", "q5.c", "q5_copy.c", NULL);
	}
	wait(NULL);

	pid_t pid3 = fork();
	if (pid3 == 0) {
		printf("Executing whoami...\n");
		execlp("whoami", "whoami", NULL);
	}
	wait(NULL);

	pid_t pid4 = fork();
	if (pid4 == 0) {
		printf("Executing pwd...\n");
		execlp("pwd", "pwd", NULL);
	}
	wait(NULL);

}
