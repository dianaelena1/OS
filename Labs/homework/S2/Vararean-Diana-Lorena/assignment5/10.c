//Pb 10 - Write a C Program that receives as command line argument a name of a file.
// The program prints at stdout the content of this file, erasing all empty lines
// from the file. Make no assumptions regarding the maximum length of a line.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int is_empty_line(const char *line) {
    for (int i = 0; line[i] != '\0'; ++i) {
        if (!isspace((unsigned char)line[i])) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while ((nread = getline(&line, &len, fp)) != -1) {
        if (!is_empty_line(line)) {
            printf("%s", line);
        }
    }

    free(line);
    fclose(fp);
    return EXIT_SUCCESS;
}