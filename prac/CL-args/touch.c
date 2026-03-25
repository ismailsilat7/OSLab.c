#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	if (argc != 3) {
		printf("Usage <executable-file> arg1 arg2\n");
		return 0;
	}

	printf("Called: %s %d %d\n", argv[0], atoi(argv[1]), atoi(argv[2]));

}
