#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUF_SIZE 1024

// Send stdin to both processes
void duplicator(int write_fd1, int write_fd2) {
    char buf[BUF_SIZE];
    while (fgets(buf, BUF_SIZE, stdin)) {
        write(write_fd1, buf, strlen(buf));
        write(write_fd2, buf, strlen(buf));
    }
    close(write_fd1);
    close(write_fd2);
}

// Send input to sorting process
void process1(int read_fd, int write_fd) {
    char buf[BUF_SIZE];
    FILE *in = fdopen(read_fd, "r");
    while (fgets(buf, BUF_SIZE, in)) {
        write(write_fd, buf, strlen(buf));
    }
    fclose(in);
    close(write_fd);
}

// Sort input lines and send them
void process2(int read_fd, int write_fd) {
    char *lines[1000];
    int count = 0;
    char buf[BUF_SIZE];
    FILE *in = fdopen(read_fd, "r");

    while (fgets(buf, BUF_SIZE, in)) {
        lines[count++] = strdup(buf);
    }
    fclose(in);

    // Sort lines alphabetically
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(lines[i], lines[j]) > 0) {
                char *tmp = lines[i];
                lines[i] = lines[j];
                lines[j] = tmp;
            }
        }
    }

    for (int i = 0; i < count; i++) {
        write(write_fd, lines[i], strlen(lines[i]));
        free(lines[i]);
    }

    close(write_fd);
}

// Replace 'X' with '0' and send
void process3(int read_fd, int write_fd) {
    char buf[BUF_SIZE];
    FILE *in = fdopen(read_fd, "r");
    while (fgets(buf, BUF_SIZE, in)) {
        for (int i = 0; buf[i]; i++) {
            if (buf[i] == 'X') buf[i] = '0';
        }
        write(write_fd, buf, strlen(buf));
    }
    fclose(in);
    close(write_fd);
}

// Final process prints lines > 10 chars from both inputs
void process4(int read_fd1, int read_fd2) {
    char buf[BUF_SIZE];
    FILE *in1 = fdopen(read_fd1, "r");
    FILE *in2 = fdopen(read_fd2, "r");

    // Read from both inputs until finished
    while (fgets(buf, BUF_SIZE, in1)) {
        buf[strcspn(buf, "\n")] = 0;
        if (strlen(buf) > 10)
            printf("%s\n", buf);
    }

    while (fgets(buf, BUF_SIZE, in2)) {
        buf[strcspn(buf, "\n")] = 0;
        if (strlen(buf) > 10)
            printf("%s\n", buf);
    }

    fclose(in1);
    fclose(in2);
}

int main() {
    int dupToP1[2], dupToP3[2];
    int pipe1to2[2], pipe2to4[2], pipe3to4[2];

    // Set up all pipes
    pipe(dupToP1);  // duplicator to P1
    pipe(dupToP3);  // duplicator to P3
    pipe(pipe1to2); // P1 to P2
    pipe(pipe2to4); // P2 to P4
    pipe(pipe3to4); // P3 to P4

    // Start Process 1
    if (fork() == 0) {
        close(dupToP1[1]);
        close(pipe1to2[0]);
        close(dupToP3[0]); close(dupToP3[1]);
        close(pipe2to4[0]); close(pipe2to4[1]);
        close(pipe3to4[0]); close(pipe3to4[1]);
        process1(dupToP1[0], pipe1to2[1]);
        exit(0);
    }

    // Start Process 2
    if (fork() == 0) {
        close(pipe1to2[1]);
        close(pipe2to4[0]);
        close(dupToP1[0]); close(dupToP1[1]);
        close(dupToP3[0]); close(dupToP3[1]);
        close(pipe3to4[0]); close(pipe3to4[1]);
        process2(pipe1to2[0], pipe2to4[1]);
        exit(0);
    }

    // Start Process 3
    if (fork() == 0) {
        close(dupToP3[1]);
        close(pipe3to4[0]);
        close(dupToP1[0]); close(dupToP1[1]);
        close(pipe1to2[0]); close(pipe1to2[1]);
        close(pipe2to4[0]); close(pipe2to4[1]);
        process3(dupToP3[0], pipe3to4[1]);
        exit(0);
    }

    // Start duplicator
    if (fork() == 0) {
        close(dupToP1[0]);
        close(dupToP3[0]);
        close(pipe1to2[0]); close(pipe1to2[1]);
        close(pipe2to4[0]); close(pipe2to4[1]);
        close(pipe3to4[0]); close(pipe3to4[1]);
        duplicator(dupToP1[1], dupToP3[1]);
        exit(0);
    }

    // Parent: Process 4
    close(dupToP1[0]); close(dupToP1[1]);
    close(dupToP3[0]); close(dupToP3[1]);
    close(pipe1to2[0]); close(pipe1to2[1]);
    close(pipe2to4[1]);
    close(pipe3to4[1]);

    process4(pipe2to4[0], pipe3to4[0]);

    // Wait for all children
    while (wait(NULL) > 0);

    return 0;
}
