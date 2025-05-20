    // Process structure
    //        1
    //     /  |  \
    //   2   3    4
    //     \  |  /
    //        5

// Process 1: Reads 10 bytes from stdin. Sends that data to processes 2, 3, and 4

// Processes 2 & 3:

// 2: Adds all digits (e.g., 1+2+3)

// 3: Replaces all letters with 'Z'

// Process 4: Sorts the result and passes it to process 5

// Process 5: Displays the final received output

// => 4 Pipes:

// pipe12: 1 → 2

// pipe13: 1 → 3

// pipe14: 1 → 4

// pipe45: 4 → 5

// use 4 child processes from the parent (Process 1).

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void sort_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len-1; i++) {
        for (int j = i+1; j < len; j++) {
            if (str[i] > str[j]) {
                char t = str[i];
                str[i] = str[j];
                str[j] = t;
            }
        }
    }
}

int main() {
    int pipe12[2], pipe13[2], pipe14[2], pipe45[2];

    pipe(pipe12); // sets up communication between parent and children.
    pipe(pipe13); // sets up communication between parent and children.
    pipe(pipe14); // sets up communication between parent and children.
    pipe(pipe45); // sets up communication between parent and children.

    char input[11];
    printf("Enter 10 characters: ");
    fgets(input, sizeof(input), stdin);

    // Fork for Process 2 (adds digits from the input.)
    if (fork() == 0) {
        close(pipe12[1]);
        char buffer[100];
        read(pipe12[0], buffer, sizeof(buffer));
        int sum = 0;
        for (int i = 0; buffer[i]; i++) {
            if (isdigit(buffer[i])) {
                sum += buffer[i] - '0';
            }
        }
        printf("Process 2: Sum of digits = %d\n", sum);
        exit(0);
    }

    // Fork for Process 3 ( replaces all letters with 'Z'.)
    if (fork() == 0) {
        close(pipe13[1]);
        char buffer[100];
        read(pipe13[0], buffer, sizeof(buffer));
        for (int i = 0; buffer[i]; i++) {
            if (isalpha(buffer[i]))
                buffer[i] = 'Z';
        }
        printf("Process 3: Letters replaced = %s\n", buffer);
        exit(0);
    }

    // Fork for Process 4 (receives the string, sorts it, and sends to Process 5.)
    if (fork() == 0) {
        close(pipe14[1]);
        close(pipe45[0]);

        char buffer[100];
        read(pipe14[0], buffer, sizeof(buffer));
        sort_string(buffer);
        write(pipe45[1], buffer, strlen(buffer));
        close(pipe45[1]);
        exit(0);
    }

    // Fork for Process 5 (prints the final sorted string.)
    if (fork() == 0) {
        close(pipe45[1]);
        char buffer[100];
        int n = read(pipe45[0], buffer, sizeof(buffer));
        buffer[n] = '\0';
        printf("Process 5: Sorted result = %s\n", buffer);
        exit(0);
    }

    // Back to Parent (Process 1)
    close(pipe12[0]); close(pipe13[0]); close(pipe14[0]);
    write(pipe12[1], input, strlen(input));
    write(pipe13[1], input, strlen(input));
    write(pipe14[1], input, strlen(input));

    close(pipe12[1]); close(pipe13[1]); close(pipe14[1]);

    wait(NULL); wait(NULL); wait(NULL); wait(NULL);
    return 0;
}
