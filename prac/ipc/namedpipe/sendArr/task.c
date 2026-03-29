#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define READ_END 0
#define WRITE_END 1

int get_median(int arr[], int n) {
	int temp;
	for(int i = 0; i <n; i++) {
		int swap = 0;
		for(int j = 0; j < n - 1 - i; j++) {
			if(arr[j] > arr[j+1]) {
				temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
				swap = 1;
			}
		}
		if (swap == 0) {
			break;
		}
	}
	return arr[n/2];
}

int fact(int n) {
	if (n <= 1) {
		return 1;
	}
	return n * fact(n - 1);
}

int main() {

	int lenfd[2];
	pipe(lenfd);
	int arrfd[2];
	pipe(arrfd);
	int medfd[2];
	pipe(medfd);

	pid_t pid = fork();
	if (pid < 0) {
		perror("Fork failed\n");
		return 1;
	} else if (pid == 0) {
		close(lenfd[WRITE_END]);
		close(arrfd[WRITE_END]);
		close(medfd[READ_END]);
		int n;
		read(lenfd[READ_END], &n, sizeof(int));
		int* arr = malloc(sizeof(int) * n);
		printf("N: %d\n", n);
		read(arrfd[READ_END], arr, sizeof(int) * n);
		int median = get_median(arr, n);
		write(medfd[WRITE_END], &median, sizeof(int));
		close(lenfd[READ_END]);
		close(arrfd[READ_END]);
		close(medfd[WRITE_END]);
		free(arr);
		exit(EXIT_SUCCESS);
	}
	close(lenfd[READ_END]);
	close(arrfd[READ_END]);
	close(medfd[WRITE_END]);
	int n = 10;
	int arr[10] = {9,4,5,2,1,3,7,0,6,8};
	write(lenfd[WRITE_END], &n, sizeof(int));
	write(arrfd[WRITE_END], &arr, sizeof(int) * n);

	int median;
	read(medfd[READ_END], &median, sizeof(int));
	int factorial = fact(median);
	printf("Median received: %d\nFactorial calculated: %d\n", median, factorial);
	close(lenfd[WRITE_END]);
	close(arrfd[WRITE_END]);
	close(medfd[READ_END]);
	return 0;
}
