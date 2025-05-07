#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1024

// Function to check if a token starts with the word followed by punctuation
int starts_with_word_and_punct(const char *token, const char *word) {
    size_t word_len = strlen(word);
    return strncmp(token, word, word_len) == 0 &&
           token[word_len] != '\0' &&
           !isalnum((unsigned char)token[word_len]);
}

// Function to check if a token is exactly the word
int is_exact_word(const char *token, const char *word) {
    return strcmp(token, word) == 0;
}

void remove_word(char *line, const char *word) {
    char result[MAX_LINE] = "";
    char temp[MAX_LINE];
    strcpy(temp, line);

    char *token = strtok(temp, " \t\n");
    while (token != NULL) {
        if (is_exact_word(token, word)) {
            // Skip the word
        } else if (starts_with_word_and_punct(token, word)) {
            // Strip the word, keep punctuation
            strcat(result, token + strlen(word));
            strcat(result, " ");
        } else {
            // Keep the token as-is
            strcat(result, token);
            strcat(result, " ");
        }
        token = strtok(NULL, " \t\n");
    }

    // Remove trailing space
    size_t len = strlen(result);
    if (len > 0 && result[len - 1] == ' ')
        result[len - 1] = '\0';

    strcpy(line, result);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <word> <filename>\n", argv[0]);
        return 1;
    }

    const char *word = argv[1];
    const char *filename = argv[2];

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    FILE *temp = tmpfile();
    if (!temp) {
        perror("Error creating temp file");
        fclose(file);
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        remove_word(line, word);
        fputs(line, temp);
        fputs("\n", temp);
    }

    rewind(temp);
    file = freopen(filename, "w", file);
    if (!file) {
        perror("Error reopening file for writing");
        fclose(temp);
        return 1;
    }

    while (fgets(line, sizeof(line), temp)) {
        fputs(line, file);
    }

    fclose(file);
    fclose(temp);

    return 0;
}
