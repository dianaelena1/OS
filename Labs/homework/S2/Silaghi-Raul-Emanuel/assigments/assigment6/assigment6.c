#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <oldWord> <newWord> <filename>\n", argv[0]);
        return 1;
    }

    char *oldWord = argv[1];
    char *newWord = argv[2];
    char *filename = argv[3];

    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("File error");
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), f)) {
        char *pos = line;
        while ((pos = strstr(pos, oldWord)) != NULL) {
            *pos = '\0';
            printf("%s%s", line, newWord);
            pos += strlen(oldWord);
            strcpy(line, pos);
            pos = line;
        }
        printf("%s", line);
    }

    fclose(f);
    return 0;
}
