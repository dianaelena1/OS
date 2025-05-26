//Implement the following structure of processes: Process 1: read from stdin and write towards 2 all lines that start with a letter, writes to 3 all lines that start with a digit,
//and to 4 the rest of the lines. Processes 2, 3, 4: print what they read from the pipe
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void child_process(int read_fd, int process_number) {
    char buffer[BUFFER_SIZE];
    int n;
    while ((n = read(read_fd, buffer, BUFFER_SIZE)) > 0) {
        buffer[n] = '\0';
        printf("Process %d received: %s", process_number, buffer);
    }
    close(read_fd);
    exit(0);
}

int main() {
    int pipe2[2], pipe3[2], pipe4[2];

    pipe(pipe2);
    pipe(pipe3);
    pipe(pipe4);

    pid_t pid2 = fork();
    if (pid2 == 0) {
        close(pipe2[1]);
        child_process(pipe2[0], 2);
    }

    pid_t pid3 = fork();
    if (pid3 == 0) {
        close(pipe3[1]);
        child_process(pipe3[0], 3);
    }

    pid_t pid4 = fork();
    if (pid4 == 0) {
        close(pipe4[1]);
        child_process(pipe4[0], 4);
    }

    close(pipe2[0]);
    close(pipe3[0]);
    close(pipe4[0]);

    char line[BUFFER_SIZE];
    while (fgets(line, sizeof(line), stdin)) {
        if (isalpha(line[0])) {
            write(pipe2[1], line, strlen(line));
        } else if (isdigit(line[0])) {
            write(pipe3[1], line, strlen(line));
        } else {
            write(pipe4[1], line, strlen(line));
        }
    }

    close(pipe2[1]);
    close(pipe3[1]);
    close(pipe4[1]);

    wait(NULL); wait(NULL); wait(NULL);
    return 0;
}

