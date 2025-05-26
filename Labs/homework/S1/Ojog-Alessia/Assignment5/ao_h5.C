#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Write a C Program that counts the number of characters on each line of a text file.
// Make no assumptions regarding the maximum length of a line.

int main(int argc, char *argv[]) {
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    size_t read;
    int line_number = 1;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

  
    file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    while ((read = getline(&line, &len, file)) != -1) {
        if (read > 0 && line[read - 1] == '\n') {
            line[--read] = '\0';
        }
        printf("Line %d: %zd characters\n", line_number++, read);
    }

    free(line);
    fclose(file);

    return 0;
}
