#include <stdio.h>

FILE* file;

int main() {
    file = fopen("filename.txt", "w");
    file = fopen("filename.txt", "a");
    file = fopen("filename.txt", "r");

    if (file == NULL) {
        perror("fopen");
        exit(1);
    } 

    int i = 6, score = 18;
    fprintf(file, "Student %d score: %d\n", i, score);
    fputs("some string\n", file);

    char buffer[256];
    fgets(buffer, sizeof(buffer), file);
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
}
