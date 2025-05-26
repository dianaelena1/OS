//|Write a C Program that receives a command line argument a filename, and prints to standard output the content of this text file, printing also an empty line after each line of text. Make no assumption regarding the maximum length of a line.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;

    // getline dynamically allocates enough memory for each line
    while (getline(&line, &len, file) != -1) {
        printf("%s\n", line); // print line
    }

    free(line);
    fclose(file);
    return 0;
}
