//Given P a process that calculates the greatest common divisor (gcd) of two numbers. 
//Using a suitable structure of such processes, write a program that determines the gcd of N given numbers.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int gcd(int a, int b) {
    while (b != 0) {
        int tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

int main() {
    int N;
    printf("Enter how many numbers: ");
    scanf("%d", &N);

    if (N < 2) {
        printf("Need at least two numbers.\n");
        return 1;
    }

    int numbers[N];
    printf("Enter %d numbers: ", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &numbers[i]);
    }

    int current_count = N;

    while (current_count > 1) {
        int new_count = 0;
        int new_numbers[(current_count + 1) / 2]; 

        for (int i = 0; i < current_count; i += 2) {
            if (i + 1 == current_count) {
                new_numbers[new_count++] = numbers[i];
                break;
            }

            int pipefd[2];
            pipe(pipefd);

            pid_t pid = fork();

            if (pid == 0) {
                // Child process: compute GCD
                close(pipefd[0]);
                int result = gcd(numbers[i], numbers[i + 1]);
                write(pipefd[1], &result, sizeof(result));
                close(pipefd[1]);
                exit(0); 
            } else {
                // Parent process: read result
                close(pipefd[1]); 
                int result;
                read(pipefd[0], &result, sizeof(result));
                close(pipefd[0]);
                wait(NULL);
                new_numbers[new_count++] = result;
            }
        }

        for (int i = 0; i < new_count; i++) {
            numbers[i] = new_numbers[i];
        }
        current_count = new_count;
    }

    printf("The GCD of the given numbers is: %d\n", numbers[0]);
    return 0;
}
