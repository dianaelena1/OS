#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1024

void error_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    int pipe2[2], pipe3[2], pipe4[2];
    pid_t p2, p3, p4;

    // Create pipes
    if (pipe(pipe2) == -1) error_exit("pipe2");
    if (pipe(pipe3) == -1) error_exit("pipe3");
    if (pipe(pipe4) == -1) error_exit("pipe4");

    // Create Process 2
    if ((p2 = fork()) == 0) {
        close(pipe2[1]); // close write end
        dup2(pipe2[0], STDIN_FILENO);
        close(pipe2[0]);
        printf("Process 2 received:\n");
        char buffer[MAX_LINE];
        while (fgets(buffer, sizeof(buffer), stdin)) {
            printf("2: %s", buffer);
        }
        exit(0);
    }

    // Create Process 3
    if ((p3 = fork()) == 0) {
        close(pipe3[1]); // close write end
        dup2(pipe3[0], STDIN_FILENO);
        close(pipe3[0]);
        printf("Process 3 received:\n");
        char buffer[MAX_LINE];
        while (fgets(buffer, sizeof(buffer), stdin)) {
            printf("3: %s", buffer);
        }
        exit(0);
    }

    // Create Process 4
    if ((p4 = fork()) == 0) {
        close(pipe4[1]); // close write end
        dup2(pipe4[0], STDIN_FILENO);
        close(pipe4[0]);
        printf("Process 4 received:\n");
        char buffer[MAX_LINE];
        while (fgets(buffer, sizeof(buffer), stdin)) {
            printf("4: %s", buffer);
        }
        exit(0);
    }

    // Process 1 (parent process)
    close(pipe2[0]);
    close(pipe3[0]);
    close(pipe4[0]);

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), stdin)) {
        if (isalpha(line[0])) {
            write(pipe2[1], line, strlen(line));
        } else if (isdigit(line[0])) {
            write(pipe3[1], line, strlen(line));
        } else {
            write(pipe4[1], line, strlen(line));
        }
    }

    // Close write ends so children can finish
    close(pipe2[1]);
    close(pipe3[1]);
    close(pipe4[1]);

    return 0;
}
