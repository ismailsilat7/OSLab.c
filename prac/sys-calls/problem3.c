#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]) {

	if (argc!=3) {
		printf("Incorrect arguments count\n");
		printf("Usage: %s input.txt output.txt\n", argv[0]);
		return 1;
	}

	char* inFile = argv[1];
	char* outFile = argv[2];
	int rd = open(inFile, O_RDONLY);
	if (rd == -1) {perror("Couldn't open file for read"); return 1;}
	int wd = open(outFile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (wd == -1) {perror("Couldn't open file for write"); return 1;}

	char buffer[50];
	while(1) {
		int bytes = read(rd, buffer, 50);
		if (bytes == 0) {
			break;
		}
		write(wd, buffer, bytes);
	}
	close(rd);
	close(wd);

}


