# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Error... CLI input not found\n");
		return 1;
	}

	int arr[50]; // max 50 chars
	int numElements = 0;

	char* str = argv[1];
	int num = 0;
	int sign = 1;
	for(int i = 0; str[i] != 0  ; i++) {
		if (str[i] >= '0' && str[i] <= '9') {
			num = (num * 10) + (str[i] - '0');
		} else if (str[i] == '$' || str[i] == '\0') {
			if (numElements < 50) {
				arr[numElements++] = num * sign;
			}
			num = 0;
			sign = 1;
		} else if (str[i] == '-' && (str[i + 1] >= '0' && str[i + 1] <= '9')) {
			sign = -1;
		} else {
			printf("Error... Invalid character encountered\n");
			return 1;
		}
	}
	if (numElements < 50) {
		arr[numElements++] = num * sign;
	}
	pid_t pid1, pid2, pid3;
	pid1 = fork();
	if (pid1 == 0) {
		int sum = 0;
		for (int i = 0; i < numElements; i++) {
			sum += arr[i];
		}
		printf("Sum (by child 1): %d\n", sum);
		exit(0);
	}
	wait(NULL);
	pid2 = fork();
	if (pid2 == 0) {
		int sum = 0;
		for (int i = 0; i < numElements; i++) {
			sum += arr[i];
		}
		printf("Avg (by child 2): %.2f\n", (float)sum/numElements);
		exit(0);
	}
	wait(NULL);
	pid3 = fork();
	if (pid3 == 0) {
		int highest = INT_MIN;
		for (int i = 0; i < numElements; i++) {
			if (arr[i] > highest) {
				highest = arr[i];
			}
		}
		printf("Highest (by child 3): %d\n", highest);
		exit(0);
	}
	wait(NULL);
}
