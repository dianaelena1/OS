#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void replace_and_print(const char *line, const char *word1, const char *word2) {
    const char *pos = line;
    size_t len1 = strlen(word1);
    size_t len2 = strlen(word2);

    while ((pos = strstr(pos, word1)) != NULL) {
        // Print the part before the match
        fwrite(line, 1, pos - line, stdout);
        // Print the replacement word
        fwrite(word2, 1, len2, stdout);
        // Move past the matched word
        pos += len1;
        line = pos;
    }
    // Print the rest of the line
    printf("%s", line);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <word1> <word2> <filename>\n", argv[0]);
        return 1;
    }

    const char *word1 = argv[1];
    const char *word2 = argv[2];
    const char *filename = argv[3];

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, file)) {
        replace_and_print(buffer, word1, word2);
    }

    fclose(file);
    return 0;
}