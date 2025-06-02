//write a c program that takes a text filename as a command-line argument. The text file contains a list of integers, one per line
//The program should: Read all the integers from the file and store them in an array. Create a child process. in the child process find and print the minimum
// value in the array. in the parent process, after the child process has finished find and print the maximum value in the array

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


#define array_size 10

int findMin(int arr[], int start, int end) {
    int min = arr[start];
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int findMax(int arr[], int start, int end) {
    int max = arr[start];
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "You have to pass the filename as an argument");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int arr[array_size];
    int n=0;
    while (fscanf(file, "%d", &arr[n]) == 1) {
        n++;
    }
    fclose(file);

    pid_t pid_min;
    pid_min = fork();

    if (pid_min < 0) {
        perror("Error forking");
        return 1;
    } else if (pid_min == 0) {
        int min = findMin(arr, 0, n - 1);
        printf("Minimum value: %d\n", min);
        exit(0);
    } else {
        wait(NULL);
        int max = findMax(arr, 0, n - 1);
        printf("Maximum value: %d\n", max);
    }
}