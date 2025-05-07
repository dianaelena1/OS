#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    size_t read;
    int line_number = 1;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

  
    file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    while ((read = getline(&line, &len, file)) != -1) {
        if (line[read - 1] == '\n') {
            read--;
        }
        printf("Line %d: %zd characters\n", line_number++, read);
    }

    free(line);
    fclose(file);

    return 0;
}
