//Write a C Program that counts all the digits on each line of a text file.  Make no assumptions regarding the maximum 
//length of a line. 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int line_number = 1;

    while ((read = getline(&line, &len, file)) != -1) {
        int digit_count = 0;

        for (ssize_t i = 0; i < read; i++) {
            if (isdigit((unsigned char)line[i])) {
                digit_count++;
            }
        }

        printf("Line %d: %d digit(s)\n", line_number++, digit_count);
    }

    free(line);
    fclose(file);

    return 0;
}
