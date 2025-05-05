#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("File opening failed");
        return 1;
    }

    int c, count = 0, line = 1;

    while ((c = fgetc(file)) != EOF) {
        if (isdigit(c)) count++;
        if (c == '\n') {
            printf("Line %d: %d digits\n", line++, count);
            count = 0;
        }
    }

    if (count > 0) 
        printf("Line %d: %d digits\n", line, count);

    fclose(file);
    return 0;
}

