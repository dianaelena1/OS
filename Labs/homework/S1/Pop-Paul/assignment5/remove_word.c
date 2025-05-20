#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

// Function to remove all occurrences of a word from a line
void remove_word_from_line(char *line, const char *word) {
    char *pos, temp[MAX_LINE];
    int index = 0;
    int word_len = strlen(word);

    while ((pos = strstr(line, word)) != NULL) {
        // Copy characters before the found word
        strncpy(temp, line, pos - line);
        temp[pos - line] = '\0';

        // Append the rest of the string after the word
        strcat(temp, pos + word_len);

        // Copy modified temp back to line
        strcpy(line, temp);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <word_to_remove> <filename>\n", argv[0]);
        return 1;
    }

    const char *word = argv[1];
    const char *filename = argv[2];

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open input file");
        return 1;
    }

    FILE *temp_file = tmpfile();
    if (!temp_file) {
        perror("Could not open temporary file");
        fclose(file);
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        remove_word_from_line(line, word);
        fputs(line, temp_file);
    }

    // Rewrite the original file with the new content
    freopen(filename, "w", file);
    rewind(temp_file);
    while (fgets(line, sizeof(line), temp_file)) {
        fputs(line, file);
    }

    fclose(file);
    fclose(temp_file);

    printf("All occurrences of \"%s\" removed from %s.\n", word, filename);
    return 0;
}

