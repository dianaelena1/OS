#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

void process2or3() {
    char buffer[SIZE];
    int n = read(STDIN_FILENO, buffer, SIZE);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (isdigit(buffer[i])) {
            sum += buffer[i] - '0';
        } else if (isalpha(buffer[i])) {
            buffer[i] = 'Z';
        }
    }
    buffer[n] = '\0';
    printf("Process %d transformed: %s, sum of digits = %d\n", getpid(), buffer, sum);
}

void process4() {
    char buffer[SIZE];
    int n = read(STDIN_FILENO, buffer, SIZE);
    buffer[n] = '\0';
    // Simple bubble sort
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (buffer[j] > buffer[j + 1]) {
                char temp = buffer[j];
                buffer[j] = buffer[j + 1];
                buffer[j + 1] = temp;
            }
        }
    }
    printf("Process 4 sorted result: %s\n", buffer);
}

void process5() {
    char buffer[SIZE];
    int n = read(STDIN_FILENO, buffer, SIZE);
    buffer[n] = '\0';
    printf("Process 5 received: %s\n", buffer);
}

int main() {
    int p1to2[2], p1to3[2], p1to4[2];
    int p2to5[2], p3to5[2];

    pipe(p1to2);
    pipe(p1to3);
    pipe(p1to4);
    pipe(p2to5);
    pipe(p3to5);

    char input[SIZE];

    printf("Enter 10 bytes: ");
    fgets(input, 11, stdin); // Read 10 chars + newline

    pid_t pid2, pid3, pid4, pid5;

    // Process 2
    if ((pid2 = fork()) == 0) {
        close(p1to2[1]);
        dup2(p1to2[0], STDIN_FILENO);
        close(p2to5[0]);
        dup2(p2to5[1], STDOUT_FILENO);
        process2or3();
        exit(0);
    }

    // Process 3
    if ((pid3 = fork()) == 0) {
        close(p1to3[1]);
        dup2(p1to3[0], STDIN_FILENO);
        close(p3to5[0]);
        dup2(p3to5[1], STDOUT_FILENO);
        process2or3();
        exit(0);
    }

    // Process 4
    if ((pid4 = fork()) == 0) {
        close(p1to4[1]);
        dup2(p1to4[0], STDIN_FILENO);
        process4();
        exit(0);
    }

    // Process 5
    if ((pid5 = fork()) == 0) {
        close(p2to5[1]);
        close(p3to5[1]);
        char buf1[SIZE], buf2[SIZE];
        int n1 = read(p2to5[0], buf1, SIZE);
        int n2 = read(p3to5[0], buf2, SIZE);
        buf1[n1] = '\0';
        buf2[n2] = '\0';
        printf("Process 5 received from 2: %s\n", buf1);
        printf("Process 5 received from 3: %s\n", buf2);
        exit(0);
    }

    // Parent process sends input
    close(p1to2[0]); write(p1to2[1], input, strlen(input));
    close(p1to3[0]); write(p1to3[1], input, strlen(input));
    close(p1to4[0]); write(p1to4[1], input, strlen(input));

    // Optionally sleep to allow child processes to finish
    sleep(1); // not ideal, but works in absence of wait()

    return 0;
}
