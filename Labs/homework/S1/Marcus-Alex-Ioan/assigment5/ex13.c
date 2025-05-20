#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Write a C Program that receives as command line arguments a name of a file and several words. 
// The program will print at stdout the content of the file, deleting the occurrences of all words provided as arguments.
#define MAX_LINE_LENGTH 1024
void remove_word(char *line, const char *word) {
    char *pos, temp[MAX_LINE_LENGTH];
    int index = 0;
    int len = strlen(word);

    while ((pos = strstr(line, word)) != NULL) {
        strncpy(temp, line, pos - line);
        temp[pos - line] = '\0';
        strcat(temp, pos + len);
        strcpy(line, temp);
    }
}
int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <filename> <word1> [word2] ...\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        for (int i = 2; i < argc; i++) {
            remove_word(line, argv[i]);
        }
        printf("%s", line);
    }
    fclose(file);
    return 0;
}
