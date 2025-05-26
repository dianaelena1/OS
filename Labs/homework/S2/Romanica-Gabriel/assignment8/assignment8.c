#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipe1[2]; // Parent to Child
    int pipe2[2]; // Child to Parent
    pid_t pid;
    char username[100];
    
    // Create pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }

    printf("Enter username: ");
    scanf("%s", username);

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        close(pipe1[1]); // Close write end of pipe1
        close(pipe2[0]); // Close read end of pipe2

        char user[100];
        read(pipe1[0], user, sizeof(user));
        close(pipe1[0]);

        // Prepare shell command: ps -u username | wc -l
        char command[200];
        snprintf(command, sizeof(command), "ps -u %s | wc -l", user);

        FILE *fp = popen(command, "r");
        if (fp == NULL) {
            perror("popen");
            exit(1);
        }

        char count[16];
        fgets(count, sizeof(count), fp);
        pclose(fp);

        write(pipe2[1], count, strlen(count) + 1);
        close(pipe2[1]);
        exit(0);
    } else {
        // Parent process
        close(pipe1[0]); // Close read end of pipe1
        close(pipe2[1]); // Close write end of pipe2

        write(pipe1[1], username, strlen(username) + 1);
        close(pipe1[1]);

        char result[16];
        read(pipe2[0], result, sizeof(result));
        close(pipe2[0]);

        wait(NULL); // Wait for child to finish

        printf("Number of processes run by %s: %s", username, result);
    }

    return 0;
}
