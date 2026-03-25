#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"

int validate(char* username) {

	int status = 0;
	FILE* readF = fopen("users.txt", "r");
	if (!readF) {
		printf("Coudln't access users.txt\n");
		return -1;
	}

	char storedUser[50];
	while(fscanf(readF, "%s", storedUser) != EOF) {
		if (strcmp(username, storedUser) == 0) {
			status = 1;
			break;
		}
	}

	fclose(readF);
	return status;
}
