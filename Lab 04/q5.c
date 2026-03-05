# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>

int main() {

	int fd1 = open("input.txt", O_RDONLY);
	if (fd1 == -1) {
		printf("Failed to open input.txt\n");
		return 1;
	}

	int fd2 = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if(fd2 == -1) {
		printf("Failed to open output.txt\n");
		return 1;
	}

	char buffer[9];
	read(fd1, buffer, 9);
	write(fd2, buffer, 9);

	close(fd1);
	close(fd2);

}
