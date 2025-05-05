//Write a C Program that counts the number of words on each line of a file. Make no assumptions regarding the maxim length of a line.
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>


// Function to count words in a line
int count_words(const char *line) {
    int count = 0;
    int in_word = 0;

    for (; *line; line++) {
        if (isspace((unsigned char)*line)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
    }

    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    int line_num = 1;

    while ((nread = getline(&line, &len, fp)) != -1) {
        int words = count_words(line);
        printf("Line %d: %d word%s\n", line_num++, words, words == 1 ? "" : "s");
    }

    free(line);
    fclose(fp);
    return 0;
}
