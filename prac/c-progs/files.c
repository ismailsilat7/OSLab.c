#include <stdio.h>
int main() {
    // --- WRITING TO A FILE ---
    // "w" mode creates a new file or overwrites an existing one
    FILE *outFile = fopen("data.txt", "w");
    if (outFile != NULL) {
        // fprintf works exactly like printf, but targets the file
        fprintf(outFile, "Score: %d\n", 100);
        fclose(outFile); // Always close to prevent memory leaks!
        printf("Data written successfully.\n");
    }

    // --- READING FROM A FILE ---
    // "r" mode opens an existing file for reading
    FILE *inFile = fopen("data.txt", "r");
    int readScore;

    if (inFile != NULL) {
        // fscanf reads formatted data from the file
        fscanf(inFile, "Score: %d", &readScore);
        fclose(inFile);
        printf("I read the score from the file: %d\n", readScore);
    } else {
        printf("Error opening file for reading.\n");
    }

    return 0;
}

