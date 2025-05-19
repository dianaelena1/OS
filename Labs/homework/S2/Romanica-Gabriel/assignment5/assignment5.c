//Write a C Program that counts all the digits on each line of a text file.  Make no assumptions regarding the maximum 
//length of a line. 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define INITIAL_BUFFER 128

char *read_line(FILE *fp) {
    int ch;
    size_t size = INITIAL_BUFFER;
    size_t len = 0;
    char *buffer = malloc(size);

    if (!buffer) return NULL;

    while ((ch = fgetc(fp)) != EOF) {
        if (len + 1 >= size) {
            size *= 2;
            char *new_buffer = realloc(buffer, size);
            if (!new_buffer) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
        }
        buffer[len++] = ch;
        if (ch == '\n') break;
    }

    if (len == 0 && ch == EOF) {
        free(buffer);
        return NULL;
    }

    buffer[len] = '\0';
    return buffer;
}

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

    int line_number = 1;
    char *line;

    while ((line = read_line(fp)) != NULL) {
        int digit_count = 0;
        for (size_t i = 0; line[i] != '\0'; i++) {
            if (isdigit((unsigned char)line[i])) {
                digit_count++;
            }
        }
        printf("Line %d: %d digit(s)\n", line_number++, digit_count);
        free(line);
    }

    fclose(fp);
    return 0;
}
