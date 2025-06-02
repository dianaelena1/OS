#include <stdio.h>
#include <string.h>
// Write a C Program that receives as command line arguments a name of a file and several words. 
// The program will print at stdout the content of the file, deleting the occurrences of all words provided as arguments.
#define MAX_LINE_LENGTH 1024
void remove_word(char *line, const char *word) {
    char *pos, temp[MAX_LINE_LENGTH];
    int index = 0;
    int len = strlen(word);

    while ((pos = strstr(line, word)) != NULL) {
        
        strncpy(temp, line, pos - line);
        temp[pos - line] = '*';
        strcat(temp, pos +  strlen(word));
        strcpy(line, temp);
    }
}
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }
    char line[MAX_LINE_LENGTH];
    
    while (fgets(line, sizeof(line), file)) {
        const char word1 = '.';
        const char word2 = '?';
        const char word3 = ',';
        const char word4 = '\'';
        const char word5 = '\"';
        const char word6 = '!';
        remove_word(line, &word1);
        remove_word(line, &word2);
        remove_word(line, &word3);
        remove_word(line, &word4);
        remove_word(line, &word5);
        remove_word(line, &word6);
        
        printf("%s", line);
    }
    fclose(file);
    return 0;
}
