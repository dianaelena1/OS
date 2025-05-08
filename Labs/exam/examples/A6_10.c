#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define ARRAY_SIZE 10

char* delete_vowel(char array[], char vowel) {
    int i, j;
    char *result = (char *)malloc(ARRAY_SIZE * sizeof(char));
    for (i = 0, j = 0; array[i] != '\0'; i++) {
        if (array[i] != vowel) {
            result[j++] = array[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    char array[ARRAY_SIZE] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    int num_vowels = sizeof(vowels) / sizeof(vowels[0]);

    // Create separate processes for each vowel deletion
    for (int i = 0; i < num_vowels; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            char *result = delete_vowel(array, vowels[i]);
            printf("Process for vowel '%c' completed. Array: %s\n", vowels[i], result);
            strcpy(array, result); // Assign the modified array back to the original array
            free(result); // Free the memory allocated for the result
            exit(0);
        } else if (pid < 0) {
            // Error handling
            perror("fork");
            exit(1);
        }
    }

    // Parent process waits for all child processes to finish
    for (int i = 0; i < num_vowels; i++) {
        wait(NULL);
    }

    return 0;
}
