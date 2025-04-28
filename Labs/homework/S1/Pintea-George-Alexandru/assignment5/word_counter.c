#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int line_number = 1;

    while ((read = getline(&line, &len, file)) != -1) {
        int words = 0;
        int in_word = 0;

        for (ssize_t i = 0; i < read; i++) {
            if (isspace(line[i])) {
                if (in_word) {
                    words++;
                    in_word = 0;
                }
            } else {
                in_word = 1;
            }
        }
        if (in_word) {
            words++; // If the last word isn't followed by space
        }

        printf("Line %d: %d words\n", line_number, words);
        line_number++;
    }

    free(line);
    fclose(file);

    return 0;
}
