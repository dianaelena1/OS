#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/file.h>

//An array of letters is given. Using a separate process for each vowel, delete all vowels from the array.

#define TEMP_FILE "temp_string.txt"
#define MAX_LEN 1000

void remove_vowel_from_file(char vowel) {
    FILE *file = fopen(TEMP_FILE, "r+");
    if (!file) {
        perror("fopen");
        exit(1);
    }

    int fd = fileno(file);
    if (flock(fd, LOCK_EX) < 0) {
        perror("flock");
        fclose(file);
        exit(1);
    }

    char buffer[MAX_LEN];
    int i = 0, c;
    while ((c = fgetc(file)) != EOF && i < MAX_LEN - 1) {
        if (tolower(c) != vowel) {
            buffer[i++] = c;
        }
    }
    buffer[i] = '\0';

    rewind(file);
    ftruncate(fd, 0); 
    fputs(buffer, file);
    fflush(file);

    flock(fd, LOCK_UN);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s \"your input string\"\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(TEMP_FILE, "w");
    if (!file) {
        perror("fopen");
        return 1;
    }
    fputs(argv[1], file);
    fclose(file);

    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    for (int i = 0; i < 5; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            remove_vowel_from_file(vowels[i]);
            exit(0);
        } else if (pid < 0) {
            perror("fork");
            return 1;
        }
    }

    for (int i = 0; i < 5; i++) {
        wait(NULL);
    }

    file = fopen(TEMP_FILE, "r");
    if (!file) {
        perror("fopen");
        return 1;
    }

    char result[MAX_LEN];
    fgets(result, MAX_LEN, file);
    fclose(file);

    printf("Final string without vowels: \"%s\"\n", result);
    remove(TEMP_FILE);
    return 0;
}
