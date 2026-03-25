#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"

int main(int argc, char* argv[]) {

	if (argc != 3) {
		printf("Invalid Arguments Count\n");
		printf("Usage: %s <username> <action(register or login)>\n", argv[0]);
		return 1;
	}

	if (strcmp(argv[2], "register") == 0) {
		int status = validate(argv[1]);
		if(status == 1) {
			printf("User %s already registered, please login instead\n", argv[1]);
			return 0;
		} else if (status == -1) return -1;
		FILE* writeF = fopen("users.txt", "a");
		if (!writeF) {
			printf("Couldn't access users.txt\n");
			return 1;
		}
		fprintf(writeF, "%s\n", argv[1]);
		fclose(writeF);
		printf("Success: %s Registered!\n", argv[1]);
	} else if (strcmp(argv[2], "login") == 0) {
		int status = validate(argv[1]);
		if (status == 0) {
			printf("User %s not found, please register first to login\n", argv[1]);
		} else if (status == 1) {
			printf("Success: %s Logged In!\n", argv[1]);
		} else {
			return -1;
		}
	}
	return 0;
}
