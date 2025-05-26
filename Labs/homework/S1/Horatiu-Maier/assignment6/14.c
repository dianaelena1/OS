#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    int line_number = 1;

    while ((nread = getline(&line, &len, fp)) != -1) {
        // Exclude newline from count if present
        if (nread > 0 && line[nread - 1] == '\n') {
            nread--;
        }
        printf("Line %d: %zd characters\n", line_number++, nread);
    }

    free(line);
    fclose(fp);
    return 0;
}
