#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // For isalpha()

int main(int argc, char *argv[], char *env[]) {
    if (argc == 1) {
        printf("Error: Insufficient number of arguments.\nPlease enter the name of the file.\n");
        return 1;
    }

    // Open the file
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // Read the file line by line
    int i = 1;
    while ((read = getline(&line, &len, file)) != -1) {

        int count = 0;
        for (int i = 0; i < read; i++) {
            if (isalpha(line[i])) { // Check if the character is a letter
                count++;
            }
        }
        printf("Number of letters in line %d: %d\n", i, count);
        i++;
    }

    // Clean up: free the allocated buffer and close the file
    free(line);
    fclose(file);

    return 0;
}
