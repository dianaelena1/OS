//Given the Polynomic A=(a0, a1, ...,an). Compute the value of A for an x, using Horner formula and several processes. For example: a0+a1*x+a2*x2

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int a0 = 1, a1 = 2, a2 = 3;
    int x = 4;

    int pipe1[2]; 
    int pipe2[2]; 

    pipe(pipe1);
    pipe(pipe2);

    pid_t pid1 = fork();
    if (pid1 == 0) {
        // Child P1: r1 = a2
        int r1 = a2;
        write(pipe1[1], &r1, sizeof(int));
        close(pipe1[0]); close(pipe1[1]);
        exit(0);
    }

    wait(NULL); // Wait for child 1

    int r1;
    read(pipe1[0], &r1, sizeof(int));
    close(pipe1[0]);

    pid_t pid2 = fork();
    if (pid2 == 0) {
        // Child P2: r2 = a1 + r1 * x
        int r2 = a1 + r1 * x;
        write(pipe2[1], &r2, sizeof(int));
        close(pipe2[0]); close(pipe2[1]);
        exit(0);
    }

    wait(NULL); // Wait for child 2

    int r2;
    read(pipe2[0], &r2, sizeof(int));
    close(pipe2[0]);

    int r3 = a0 + r2 * x;
    printf("Final result: A(%d) = %d\n", x, r3);

    return 0;
}
