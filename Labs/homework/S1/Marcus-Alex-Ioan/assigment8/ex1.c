#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 31 

// Implement the following structure of processes, in which the vertices indicate the communication between processes using pipes:
// Process 1: reads from stdin lines of at most 30 chars and writes to process 2 the digits and to process 3 the letters
// Process 2: prints the received input at stdout 
// Process 3: transforms to uppercase all receives letters and prints them to stdout

int main() {
    int pipe1[2]; 
    int pipe2[2]; 

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid2 = fork(); 
    if (pid2 < 0) {
        perror("fork");
        exit(1);
    }

    if (pid2 == 0) {
        close(pipe1[1]); 
        close(pipe2[0]); close(pipe2[1]); 

        char buffer[MAX_LINE];
        int n;
        while ((n = read(pipe1[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[n] = '\0';
            printf("Process 2 (digits): %s\n", buffer);
        }

        close(pipe1[0]);
        exit(0);
    }

    pid_t pid3 = fork();
    if (pid3 < 0) {
        perror("fork");
        exit(1);
    }

    if (pid3 == 0) {
        close(pipe2[1]); 
        close(pipe1[0]); close(pipe1[1]); 

        char buffer[MAX_LINE];
        int n;
        while ((n = read(pipe2[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[n] = '\0';
            for (int i = 0; buffer[i]; i++) {
                buffer[i] = toupper((unsigned char)buffer[i]);
            }
            printf("Process 3 (letters uppercased): %s\n", buffer);
        }

        close(pipe2[0]);
        exit(0);
    }

    close(pipe1[0]); 
    close(pipe2[0]); 

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), stdin)) {
        char digits[MAX_LINE] = "";
        char letters[MAX_LINE] = "";

        for (int i = 0; line[i] != '\0'; i++) {
            if (isdigit((unsigned char)line[i])) {
                strncat(digits, &line[i], 1);
            } else if (isalpha((unsigned char)line[i])) {
                strncat(letters, &line[i], 1);
            }
        }

        write(pipe1[1], digits, strlen(digits));
        write(pipe2[1], letters, strlen(letters));
    }

    close(pipe1[1]);
    close(pipe2[1]);

    wait(NULL); 
    wait(NULL); 

    return 0;
}
