//  three processes communicating as follows:

// markdown
// Copy
// Edit
//            1
//          /   \
//         2     3

// Process 1: Reads a line (max 30 characters) from stdin
// → Sends digits to process 2
// → Sends letters to process 3

// Process 2: Prints received digits to stdout

// Process 3: Converts received letters to uppercase and prints to stdout



// =>Create 2 pipes:

// pipe1: between Process 1 → Process 2

// pipe2: between Process 1 → Process 3

// fork() twice to create 2 child processes (for 2 and 3).

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int main() {
    int pipe1[2]; // Pipe for digits to Process 2
    int pipe2[2]; // Pipe for letters to Process 3

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid_t p2 = fork();
    if (p2 == -1) {
        perror("Fork for process 2 failed");
        exit(EXIT_FAILURE);
    }

    if (p2 == 0) {
        // Process 2 - receive digits and print
        close(pipe1[1]); // Close write end
        char buffer[100];
        int n = read(pipe1[0], buffer, sizeof(buffer));
        buffer[n] = '\0';
        printf("Process 2 received digits: %s\n", buffer);
        close(pipe1[0]);
        exit(0);
    }

    pid_t p3 = fork();
    if (p3 == -1) {
        perror("Fork for process 3 failed");
        exit(EXIT_FAILURE);
    }

    if (p3 == 0) {
        // Process 3 - receive letters, convert to uppercase, print
        close(pipe2[1]); // Close write end
        char buffer[100];
        int n = read(pipe2[0], buffer, sizeof(buffer));
        buffer[n] = '\0';
        for (int i = 0; i < n; i++) {
            buffer[i] = toupper(buffer[i]);
        }
        printf("Process 3 received letters: %s\n", buffer);
        close(pipe2[0]);
        exit(0);
    }

    // Parent - Process 1
    close(pipe1[0]);
    close(pipe2[0]);

    char input[100];
    printf("Enter a line (max 30 chars): ");
    fgets(input, sizeof(input), stdin);

    char digits[100] = "", letters[100] = "";
    for (int i = 0; i < strlen(input); i++) {
        if (isdigit(input[i]))
            strncat(digits, &input[i], 1);
        else if (isalpha(input[i]))
            strncat(letters, &input[i], 1);
    }

    write(pipe1[1], digits, strlen(digits));
    write(pipe2[1], letters, strlen(letters));

    close(pipe1[1]);
    close(pipe2[1]);

    wait(NULL); wait(NULL); // Wait for both children
    return 0;
}
