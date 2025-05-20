#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// Implement the following structure of processes, in which the vertices indicate the communication between processes using pipes: Process 1: read from stdin and write towards 2 all lines that start with a letter, writes to 3 all that start with a digit and to 4 the rest of the lines Processes 2, 3, 4: print what they read from pipe

#define BUF_SIZE 1024

void child_process(int read_fd, const char *proc_name) {
    char buffer[BUF_SIZE];
    ssize_t n;
    while ((n = read(read_fd, buffer, BUF_SIZE)) > 0) {
        printf("[%s] %.*s", proc_name, (int)n, buffer);
        fflush(stdout);
    }
    close(read_fd);
    exit(0);
}


int main() {
    int pipe12[2], pipe13[2], pipe14[2];

    pipe(pipe12);
    pipe(pipe13);
    pipe(pipe14);

    pid_t pid2 = fork();
    if (pid2 == 0) {
        close(pipe12[1]);
        close(pipe13[0]); close(pipe13[1]);
        close(pipe14[0]); close(pipe14[1]);
        child_process(pipe12[0], "Proc2");

    }

    pid_t pid3 = fork();
    if (pid3 == 0) {
        close(pipe13[1]);
        close(pipe12[0]); close(pipe12[1]);
        close(pipe14[0]); close(pipe14[1]);
        child_process(pipe13[0], "Proc3");

    }

    pid_t pid4 = fork();
    if (pid4 == 0) {
        close(pipe14[1]);
        close(pipe12[0]); close(pipe12[1]);
        close(pipe13[0]); close(pipe13[1]);
        child_process(pipe14[0], "Proc4");

    }

    close(pipe12[0]);
    close(pipe13[0]);
    close(pipe14[0]);

    char line[BUF_SIZE];
    while (fgets(line, BUF_SIZE, stdin) != NULL) {
        if (isalpha(line[0])) {
            write(pipe12[1], line, strlen(line));
        } else if (isdigit(line[0])) {
            write(pipe13[1], line, strlen(line));
        } else {
            write(pipe14[1], line, strlen(line));
        }
    }

    close(pipe12[1]);
    close(pipe13[1]);
    close(pipe14[1]);

    wait(NULL); wait(NULL); wait(NULL);
    return 0;
}
