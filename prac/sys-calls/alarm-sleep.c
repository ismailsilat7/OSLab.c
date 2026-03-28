#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

void handle_alarm(int sig) {
	printf("Alarm received, terminating gracefully!\n");
	exit(0);
}

int main() {

	signal(SIGALRM, handle_alarm);
	printf("Setting alarm for 5 secs\n");
	alarm(5);

	int seconds_passed = 0;
	while(1) {
		sleep(1);
		seconds_passed++;
		printf("Seconds Elapsed: %d\n", seconds_passed);
	}

	return 0;
}
