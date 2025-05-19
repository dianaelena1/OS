#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("fopen");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, f) != -1) {
        if (line[0] != '\n')
            fputs(line, stdout);
    }

    free(line);
    fclose(f);
    return 0;
}
