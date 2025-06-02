// Write a C Program that counts all the digits on each line of a text file. Make no assumptions regarding the maximum length of a line.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1) {
        int digit_count = 0;
        for (ssize_t i = 0; i < read; ++i) {
            if (isdigit((unsigned char)line[i])) {
                digit_count++;
            }
        }
        printf("Digits on this line: %d\n", digit_count);
    }

    free(line);
    fclose(fp);
    return 0;
}