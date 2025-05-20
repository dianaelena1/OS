// An array of numbers is given.
//  Calculate the sum of the cubes of thesenumbers such that the cube of each number is calculated by a separateprocess.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int numbers[] = {1, 2, 3,4};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int total_sum = 0;

    for (int i = 0; i < size; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            
            int cube = numbers[i] * numbers[i] * numbers[i];
            if (cube > 255) cube = 255;
            exit(cube);
        } else {
            
            int status;
            wait(&status);
            if (WIFEXITED(status)) {
                total_sum += WEXITSTATUS(status);
            }
        }
    }

    printf("The sum of the cubes is: %d\n", total_sum);
    return 0;
}
