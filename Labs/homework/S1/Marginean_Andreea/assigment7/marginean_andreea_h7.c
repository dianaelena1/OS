// Implement the following structure of processes, in which the vertices indicate the communication between processes using pipes:
// Process 1: read from stdin and write to 2
// Process 2: read from 1, sort and send to 4
// Process 3: read from stdin, replace character X with 0 and write to 4
// Process 4: print only lines with more than 10 chars
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 1024

int cmp(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    int pipe1[2], pipe2[2], pipe3[2];
    pid_t pid1, pid2, pid3;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1 || pipe(pipe3) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == 0) {
        close(pipe1[0]);
        close(pipe2[0]); close(pipe2[1]);
        close(pipe3[0]); close(pipe3[1]);

        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), stdin)) {
            if (strncmp(line, "STOP", 4) == 0)
                break;
            write(pipe1[1], line, strlen(line));
        }

        close(pipe1[1]);
        exit(EXIT_SUCCESS);
    }

    pid2 = fork();
    if (pid2 == 0) {
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe3[0]); close(pipe3[1]);

        FILE *in = fdopen(pipe1[0], "r");
        if (!in) {
            perror("fdopen");
            exit(EXIT_FAILURE);
        }

        char *lines[MAX_LINES];
        char buffer[MAX_LINE_LENGTH];
        int count = 0;

        while (fgets(buffer, sizeof(buffer), in) && count < MAX_LINES) {
            lines[count++] = strdup(buffer);
        }
        fclose(in);

        qsort(lines, count, sizeof(char *), cmp);

        for (int i = 0; i < count; i++) {
            write(pipe2[1], lines[i], strlen(lines[i]));
            free(lines[i]);
        }

        close(pipe2[1]);
        exit(EXIT_SUCCESS);
    }

    pid3 = fork();
    if (pid3 == 0) {
        close(pipe1[0]); close(pipe1[1]);
        close(pipe2[1]);
        close(pipe3[0]);

        FILE *in = fdopen(pipe2[0], "r");
        if (!in) {
            perror("fdopen");
            exit(EXIT_FAILURE);
        }

        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), in)) {
            for (int i = 0; line[i]; i++) {
                if (line[i] == 'X') line[i] = '0';
            }
            write(pipe3[1], line, strlen(line));
        }

        fclose(in);
        close(pipe3[1]);
        exit(EXIT_SUCCESS);
    }

    close(pipe1[0]); close(pipe1[1]);
    close(pipe2[0]); close(pipe2[1]);
    close(pipe3[1]);

    FILE *in = fdopen(pipe3[0], "r");
    if (!in) {
        perror("fdopen");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), in)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[--len] = '\0';
        }

        if (len > 10) {
            printf("%s\n", line);
        }
    }

    fclose(in);
    wait(NULL); wait(NULL); wait(NULL);
    return 0;
}
