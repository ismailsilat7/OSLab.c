#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]){
	if (argc != 2) {
		printf("Invalid command line agrs");
		printf("Usage: %s num1,num2,num3,......,numn\n", argv[0]);
		return 1;
	}
	int arr[50]; // max 50 numbers
	char* str = argv[1];
	int n = strlen(str);
	int nums = 0;
	int number = 0;
	int sign = 1;
	for (int i = 0; i < n; i++) {
		if(str[i] - '0' >= 0 && str[i] - '0' <= 9) {
			number = number*10 + (str[i] - '0');
		} else if(str[i] == ',') {
			arr[nums] = number * sign;
			number = 0;
			sign = 1;
			nums++;
			if (nums > 49) {
				break;
			}
		} else if (str[i] == '-') {
			sign = -1;
		}
	}
	if (nums <= 49) {
		arr[nums++] = number*sign;
	}

	for(int i = 0; i < nums; i++) {
		printf("%d : %d\n", i+1, arr[i]);
	}

	pid_t c1 = fork();
	if (c1 < 0) {
		printf("Fork for c1 failed\n");
		return 1;
	} else if (c1 == 0) {
		printf("Child 1 -- Adding numbers & printing on screen\n");
		int sum  = 0;
		for (int i = 0; i < nums; i++) {
			sum += arr[i];
		}
		printf("Sum (via child 1): %d\n", sum);
		exit(EXIT_SUCCESS);
	}
	pid_t c2 = fork();
	if (c2 < 0) {
		printf("Fork for c2 failed\n");
		return 1;
	} else if (c2 == 0) {
		printf("Child 2 -- Adding numbers & printing on screen\n");
		int sum  = 0;
		for (int i = 0; i < nums; i++) {
			sum += arr[i];
		}
		printf("Avg (via child 2): %.2f\n", (float)sum/nums);
		exit(EXIT_SUCCESS);
	}
	pid_t c3 = fork();
	if (c3 < 0) {
		printf("Fork for c3 failed\n");
		return 1;
	} else if (c3 == 0) {
		printf("Child 3 -- Finding Max\n");
		int max = arr[0];
		for (int i = 0; i < nums; i++) {
			if (arr[i] > max) max = arr[i];
		}
		printf("Max (via child 3): %d\n", max);
		exit(EXIT_SUCCESS);
	}

	waitpid(c1, NULL, 0);
	waitpid(c2, NULL, 0);
	waitpid(c3, NULL, 0);
	printf("All children parent was waiting for has finished executing... Exiting...\n");
}

