//Parent process sends to the child a username, and the child sends back to the parent the number of processes run by the user.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main() {
    // Create FIFOs (ignore error if already exist)
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) {
        // Parent process
        int fd1 = open(FIFO1, O_WRONLY);
        if (fd1 < 0) {
            perror("open fifo1");
            exit(1);
        }

        char username[100];
        printf("Enter username: ");
        scanf("%s", username);

        write(fd1, username, strlen(username) + 1);
        close(fd1);

        // Receive result
        int fd2 = open(FIFO2, O_RDONLY);
        if (fd2 < 0) {
            perror("open fifo2");
            exit(1);
        }

        char buffer[100];
        read(fd2, buffer, sizeof(buffer));
        printf("Number of processes for user %s: %s\n", username, buffer);
        close(fd2);

        // Clean up
        unlink(FIFO1);
        unlink(FIFO2);
    } else {
        // Child process
        int fd1 = open(FIFO1, O_RDONLY);
        if (fd1 < 0) {
            perror("open fifo1");
            exit(1);
        }

        char username[100];
        read(fd1, username, sizeof(username));
        close(fd1);

        // Build shell command
        char command[200];
        snprintf(command, sizeof(command), "ps -u %s | wc -l", username);

        FILE *fp = popen(command, "r");
        if (!fp) {
            perror("popen");
            exit(1);
        }

        char result[100];
        fgets(result, sizeof(result), fp);
        pclose(fp);

        // Send back result
        int fd2 = open(FIFO2, O_WRONLY);
        if (fd2 < 0) {
            perror("open fifo2");
            exit(1);
        }

        write(fd2, result, strlen(result) + 1);
        close(fd2);
    }

    return 0;
}

