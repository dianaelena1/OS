#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void process1(int write_fd, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen process1");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, fp)) {
        write(write_fd, buffer, strlen(buffer));
    }

    fclose(fp);
    close(write_fd);
}

void process2(int read_fd, int write_fd) {
    char *lines[1000];
    int count = 0;
    char buffer[BUFFER_SIZE];

    FILE *input = fdopen(read_fd, "r");
    if (!input) {
        perror("fdopen process2");
        exit(1);
    }

    while (fgets(buffer, BUFFER_SIZE, input)) {
        lines[count] = strdup(buffer);
        count++;
    }
    fclose(input);

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

void process3(int write_fd, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen process3");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, fp)) {
        for (int i = 0; buffer[i]; i++) {
            if (buffer[i] == 'X') {
                buffer[i] = '0';
            }
        }
        write(write_fd, buffer, strlen(buffer));
    }

    fclose(fp);
    close(write_fd);
}

void process4(int read_fd1, int read_fd2) {
    char buffer[BUFFER_SIZE];

    FILE *input1 = fdopen(read_fd1, "r");
    FILE *input2 = fdopen(read_fd2, "r");
    if (!input1 || !input2) {
        perror("fdopen process4");
        exit(1);
    }

    while (fgets(buffer, BUFFER_SIZE, input1)) {
        if (strlen(buffer) > 10) {
            fputs(buffer, stdout);
        }
    }

    while (fgets(buffer, BUFFER_SIZE, input2)) {
        if (strlen(buffer) > 10) {
            fputs(buffer, stdout);
        }
    }

    fclose(input1);
    fclose(input2);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s input.txt\n", argv[0]);
        exit(1);
    }

    const char *filename = argv[1];
    int pipe12[2], pipe24[2], pipe34[2];

    pipe(pipe12);
    pipe(pipe24);
    pipe(pipe34);

    if (fork() == 0) {
        close(pipe12[0]);
        close(pipe24[0]); close(pipe24[1]);
        close(pipe34[0]); close(pipe34[1]);
        process1(pipe12[1], filename);
        exit(0);
    }

    if (fork() == 0) {
        close(pipe12[1]);
        close(pipe24[0]);
        close(pipe34[0]); close(pipe34[1]);
        process2(pipe12[0], pipe24[1]);
        exit(0);
    }

    if (fork() == 0) {
        close(pipe34[0]);
        close(pipe12[0]); close(pipe12[1]);
        close(pipe24[0]); close(pipe24[1]);
        process3(pipe34[1], filename);
        exit(0);
    }

    if (fork() == 0) {
        close(pipe12[0]); close(pipe12[1]);
        close(pipe24[1]);
        close(pipe34[1]);
        process4(pipe24[0], pipe34[0]);
        exit(0);
    }

    close(pipe12[0]); close(pipe12[1]);
    close(pipe24[0]); close(pipe24[1]);
    close(pipe34[0]); close(pipe34[1]);

    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }

    return 0;
}