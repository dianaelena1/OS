#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>


#define MAX_LEN 256

int is_alphanum_line(const char *line) {
    for (int i = 0; line[i]; i++)
        if (isalnum(line[i])) return 1;
    return 0;
}

int is_no_letters_line(const char *line) {
    for (int i = 0; line[i]; i++)
        if (isalpha(line[i])) return 0;
    return 1;
}

void replace_digits_with_underscore(char *line) {
    for (int i = 0; line[i]; i++)
        if (isdigit(line[i])) line[i] = '_';
}

int main() {
    int pipe1[2], pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    if (fork() == 0) {
        // Child Process 2
        close(pipe1[1]);
        dup2(pipe1[0], STDIN_FILENO); close(pipe1[0]);

        char line[MAX_LEN];
        while (fgets(line, MAX_LEN, stdin)) {
            replace_digits_with_underscore(line);
            printf("Process 2: %s", line);
        }
        exit(0);
    }

    if (fork() == 0) {
        // Child Process 3
        close(pipe2[1]);
        dup2(pipe2[0], STDIN_FILENO); close(pipe2[0]);

        char line[MAX_LEN];
        while (fgets(line, MAX_LEN, stdin))
            printf("Process 3: %s", line);
        exit(0);
    }

    // Parent Process 1
    close(pipe1[0]); close(pipe2[0]);
    char line[MAX_LEN];
    while (fgets(line, MAX_LEN, stdin)) {
        if (is_alphanum_line(line))
            write(pipe1[1], line, strlen(line));
        if (is_no_letters_line(line))
            write(pipe2[1], line, strlen(line));
    }
    close(pipe1[1]); close(pipe2[1]);

    wait(NULL); wait(NULL); // wait for children
    return 0;
}
