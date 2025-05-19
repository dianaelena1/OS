
 //Write a C Program that receives as command line arguments  a word and the name of a file. The program will delete 
//from the file the occurrences of the provided word. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1024

// Check if character is a word boundary
int is_word_boundary(char c) {
    return isspace(c) || ispunct(c) || c == '\0';
}

// Function to remove whole-word occurrences of `word` from `str`
void removeWholeWord(char *str, const char *word) {
    char result[MAX_LINE] = "";
    char *ptr = str;
    int wordLen = strlen(word);

    while (*ptr) {
        // Check for whole-word match
        if (strncmp(ptr, word, wordLen) == 0 &&
            (ptr == str || is_word_boundary(*(ptr - 1))) &&
            is_word_boundary(*(ptr + wordLen))) {
            
            ptr += wordLen; // Skip the word
        } else {
            // Copy character to result
            int len = strlen(result);
            result[len] = *ptr;
            result[len + 1] = '\0';
            ptr++;
        }
    }

    strcpy(str, result);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <word> <filename>\n", argv[0]);
        return 1;
    }

    const char *word = argv[1];
    const char *filename = argv[2];
    const char *tempFilename = "temp.txt";

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening input file");
        return 1;
    }

    FILE *temp = fopen(tempFilename, "w");
    if (!temp) {
        perror("Error creating temporary file");
        fclose(fp);
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fp)) {
        removeWholeWord(line, word);
        fputs(line, temp);
    }

    fclose(fp);
    fclose(temp);

    if (remove(filename) != 0) {
        perror("Error deleting original file");
        return 1;
    }

    if (rename(tempFilename, filename) != 0) {
        perror("Error renaming temporary file");
        return 1;
    }

    printf("Whole-word occurrences of \"%s\" removed from %s\n", word, filename);
    return 0;
}
