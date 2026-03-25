#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("Incorrect Usage! Pass atleast 2 ints as arguments to sum\n");
		return 0;
	}
	int sum = 0;
	for (int i = 1; i <= argc-1; i++) {
		sum += atoi(argv[i]);
	}
	printf("Sum: %d\n", sum);
	return 0;
}
