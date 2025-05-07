#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int divide_sum(int* array, int start, int end) {
    if (start > end) return 0;
    if (start == end) return array[start];

    int mid = (start + end) / 2;
    int pipe1[2], pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    if (fork() == 0) {
        int left = divide_sum(array, start, mid);
        write(pipe1[1], &left, sizeof(int));
        close(pipe1[1]);
        exit(0);
    }

    if (fork() == 0) {
        int right = divide_sum(array, mid + 1, end);
        write(pipe2[1], &right, sizeof(int));
        close(pipe2[1]);
        exit(0);
    }

    int sum1, sum2;
    close(pipe1[1]); close(pipe2[1]);
    read(pipe1[0], &sum1, sizeof(int));
    read(pipe2[0], &sum2, sizeof(int));
    close(pipe1[0]); close(pipe2[0]);

    wait(NULL); wait(NULL);
    return sum1 + sum2;
}

int main() {
    int array[] = {1, 4, 5, 9, 12, 18};
    int n = sizeof(array) / sizeof(array[0]);

    int sum = divide_sum(array, 0, n - 1);
    printf("Total sum: %d\n", sum);
    return 0;
}
