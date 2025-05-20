// Write a C Program that receives as command line argument a name of a file.
//  The program prints at stdout the content of this file, erasing all empty lines from the file.
//  Make no assumptions regarding the maximum length of a line.
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int is_empty(const char *line) {
    while (*line) {
        if (!isspace((unsigned char)*line)) {
            return 0;
        }
        line++;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Cannot open file");
        return 1;
    }

    char *line = NULL;
    size_t size = 0;

    while (getline(&line, &size, file) != -1) {
        if (!is_empty(line)) {
            printf("%s", line);
        }
    }

    free(line);
    fclose(file);
    return 0;
}

