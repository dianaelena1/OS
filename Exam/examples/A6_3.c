#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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

int countLessThanOrEqual(int arr[], int n, int val) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] <= val) {
            count++;
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <k>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int k = atoi(argv[2]);
    int arr[100];

    int count = 0;
    
    while (fscanf(file, "%d", &arr[count]) == 1) {
        count++;
    }
    fclose(file);

    pid_t pid_min, pid_max;
    pid_min = fork();

    if (pid_min < 0) {
        perror("Error forking");
        return 1;
    } else if (pid_min == 0) {
        int min = findMin(arr, 0, count - 1);
        printf("Minimum value: %d\n", min);
        exit(0);
    } else {
        pid_max = fork();
        if (pid_max < 0) {
            perror("Error forking");
            return 1;
        } else if (pid_max == 0) {
            int max = findMax(arr, 0, count - 1);
            printf("Maximum value: %d\n", max);
            exit(0);
        } else {
            int status;
            waitpid(pid_min, &status, 0);
            waitpid(pid_max, &status, 0);

            int min = findMin(arr, 0, count - 1);
            int max = findMax(arr, 0, count - 1);
            int range = max - min + 1;
            int freq[range];
            for (int i = 0; i < range; i++) {
                freq[i] = 0;
            }
            for (int i = 0; i < count; i++) {
                freq[arr[i] - min]++;
            }
            int numLessThanOrEqual = 0;
            int kthSmallest = -1;
            for (int i = 0; i < range; i++) {
                numLessThanOrEqual += freq[i];
                if (numLessThanOrEqual >= k) {
                    kthSmallest = i + min;
                    break;
                }
            }
            printf("Kth smallest element: %d\n", kthSmallest);
        }
    }

    return 0;
}
