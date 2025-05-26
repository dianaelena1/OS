#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int sum_array(int *arr, int start, int end) {
    int sum = 0;
    for (int i = start; i < end; i++) {
        sum += arr[i];
    }
    return sum;
}

int divide_and_conquer(int *arr, int start, int end) {
    if (end - start == 1) {
        return arr[start];
    }

    int mid = (start + end) / 2;

    pid_t pid1 = fork();
    if (pid1 == 0) {
        int left_sum = divide_and_conquer(arr, start, mid);
        exit(left_sum);
    } else {
        pid_t pid2 = fork(); 
        if (pid2 == 0) {
            int right_sum = divide_and_conquer(arr, mid, end);
            exit(right_sum);  
        } else {
            int left_sum, right_sum;
            waitpid(pid1, &left_sum, 0);
            waitpid(pid2, &right_sum, 0);

            left_sum = WEXITSTATUS(left_sum);
            right_sum = WEXITSTATUS(right_sum);

            return left_sum + right_sum;
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    int total_sum = divide_and_conquer(arr, 0, n);

    printf("Total sum of the array: %d\n", total_sum);
    return 0;
}
