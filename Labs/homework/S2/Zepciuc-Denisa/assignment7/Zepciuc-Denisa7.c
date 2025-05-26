//Implement the following structure of processes,
//in which the vertices indicate the communication between processes using pipes:
//Process 1: read from stdin and write to 2 lines that are alphanumerical and to 3 lines that do not contain letters
//Process 2: replace digits with ‘_’
//Process 3,4: print to stdout what is read.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1024

// Helper function: check if string contains any letter
int contains_letter(const char *line) {
    for (int i = 0; line[i]; i++) {
        if (isalpha(line[i])) return 1;
    }
    return 0;
}

// Helper function: replace digits with '_'
void replace_digits(char *line) {
    for (int i = 0; line[i]; i++) {
        if (isdigit(line[i])) {
            line[i] = '_';
        }
    }
}

int main() {
    int pipe1[2]; // P1 -> P2
    int pipe2[2]; // P1 -> P3
    int pipe3[2]; // P2 -> P4

    pipe(pipe1);
    pipe(pipe2);
    pipe(pipe3);

    pid_t pid2 = fork();

    if (pid2 == 0) {
        // Process 2
        close(pipe1[1]); // Close write end of P1->P2
        close(pipe2[0]); close(pipe2[1]); // Not used
        close(pipe3[0]); // Close read end of P2->P4

        dup2(pipe1[0], STDIN_FILENO);  // Read from P1
        dup2(pipe3[1], STDOUT_FILENO); // Write to P4

        char line[MAX_LINE];
        while (fgets(line, MAX_LINE, stdin)) {
            replace_digits(line);
            fputs(line, stdout);
            fflush(stdout);
        }
        exit(0);
    }

    pid_t pid3 = fork();

    if (pid3 == 0) {
        // Process 3
        close(pipe2[1]); // Close write end of P1->P3
        close(pipe1[0]); close(pipe1[1]); // Not used
        close(pipe3[0]); close(pipe3[1]); // Not used

        dup2(pipe2[0], STDIN_FILENO);

        char line[MAX_LINE];
        while (fgets(line, MAX_LINE, stdin)) {
            printf("[Process 3] %s", line);
            fflush(stdout);
        }
        exit(0);
    }

    pid_t pid4 = fork();

    if (pid4 == 0) {
        // Process 4
        close(pipe3[1]); // Close write end
        close(pipe1[0]); close(pipe1[1]);
        close(pipe2[0]); close(pipe2[1]);

        dup2(pipe3[0], STDIN_FILENO);

        char line[MAX_LINE];
        while (fgets(line, MAX_LINE, stdin)) {
            printf("[Process 4] %s", line);
            fflush(stdout);
        }
        exit(0);
    }

    // Parent (Process 1)
    close(pipe1[0]); // Close read end P1->P2
    close(pipe2[0]); // Close read end P1->P3
    close(pipe3[0]); close(pipe3[1]); // Not used by P1

    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, stdin)) {
        if (contains_letter(line)) {
            write(pipe1[1], line, strlen(line));
        } else {
            write(pipe2[1], line, strlen(line));
        }
    }

    // Close writing ends
    close(pipe1[1]);
    close(pipe2[1]);

    // Wait for children
    wait(NULL); wait(NULL); wait(NULL);

    return 0;
}
