#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    size_t read;
    int line_number = 1;

    // Check for proper usage
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open the file
    file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read each line and count characters
    while ((read = getline(&line, &len, file)) != -1) {
        // Remove newline character from count if present
        if (line[read - 1] == '\n') {
            read--;
        }
        printf("Line %d: %zd characters\n", line_number++, read);
    }

    // Clean up
    free(line);
    fclose(file);

    return 0;
}
