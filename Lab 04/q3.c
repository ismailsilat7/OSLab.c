# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>

int main() {
	printf("PPID: %d, PID: %d, UID: %d\n",
		getppid(), getpid(), getuid());
}
