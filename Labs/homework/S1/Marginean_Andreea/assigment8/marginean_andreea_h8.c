<<<<<<< Updated upstream
=======
// Implement the following structure of processes, in which the vertices indicate thecommunication between processes using pipes:
// Process 1: write to 3 what is read from stdin
// Process 2: read from 3 and replace all vowels with digits (aeiou->12345)
// Process 3: read from 1 and write to 2 only alphanumeric lines
>>>>>>> Stashed changes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FIFO1 "/tmp/fifo_1_3"
#define FIFO2 "/tmp/fifo_3_2"
#define MAXLINE 256

<<<<<<< Updated upstream
// Replace vowels with digits
=======
>>>>>>> Stashed changes
void replace_vowels(char *line) {
    for (int i = 0; line[i]; i++) {
        switch(tolower(line[i])) {
            case 'a': line[i] = '1'; break;
            case 'e': line[i] = '2'; break;
            case 'i': line[i] = '3'; break;
            case 'o': line[i] = '4'; break;
            case 'u': line[i] = '5'; break;
        }
    }
}

<<<<<<< Updated upstream
// Check if line is alphanumeric (letters, digits, spaces allowed)
=======
>>>>>>> Stashed changes
int is_alphanumeric_line(const char *line) {
    for (int i = 0; line[i]; i++) {
        if (!isalnum(line[i]) && !isspace(line[i]))
            return 0;
    }
    return 1;
}

int main() {
<<<<<<< Updated upstream
    // Create FIFOs (named pipes)
=======
>>>>>>> Stashed changes
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    pid_t pid1, pid2, pid3;

<<<<<<< Updated upstream
    // Fork Process 1
    pid1 = fork();
    if (pid1 == 0) {
        // Process 1: read from stdin, write to FIFO1
=======
    pid1 = fork();
    if (pid1 == 0) {
>>>>>>> Stashed changes
        int fd_write = open(FIFO1, O_WRONLY);
        if (fd_write < 0) { perror("Process 1 open FIFO1 write"); exit(1); }

        char buffer[MAXLINE];
        while (fgets(buffer, sizeof(buffer), stdin)) {
            write(fd_write, buffer, strlen(buffer));
        }

        close(fd_write);
        exit(0);
    }

<<<<<<< Updated upstream
    // Fork Process 3
    pid3 = fork();
    if (pid3 == 0) {
        // Process 3: read from FIFO1, filter alphanumeric lines, write to FIFO2
=======
    pid3 = fork();
    if (pid3 == 0) {
>>>>>>> Stashed changes
        int fd_read = open(FIFO1, O_RDONLY);
        int fd_write = open(FIFO2, O_WRONLY);
        if (fd_read < 0 || fd_write < 0) {
            perror("Process 3 open FIFO"); exit(1);
        }

        char buffer[MAXLINE];
        ssize_t n;
        while ((n = read(fd_read, buffer, sizeof(buffer)-1)) > 0) {
            buffer[n] = '\0';

<<<<<<< Updated upstream
            // Since read may read partial lines, we must split by lines:
=======
>>>>>>> Stashed changes
            char *line = strtok(buffer, "\n");
            while (line != NULL) {
                if (is_alphanumeric_line(line)) {
                    char out_line[MAXLINE];
                    snprintf(out_line, MAXLINE, "%s\n", line);
                    write(fd_write, out_line, strlen(out_line));
                }
                line = strtok(NULL, "\n");
            }
        }
        close(fd_read);
        close(fd_write);
        exit(0);
    }

<<<<<<< Updated upstream
    // Fork Process 2
    pid2 = fork();
    if (pid2 == 0) {
        // Process 2: read from FIFO2, replace vowels and print
=======
    pid2 = fork();
    if (pid2 == 0) {
>>>>>>> Stashed changes
        int fd_read = open(FIFO2, O_RDONLY);
        if (fd_read < 0) { perror("Process 2 open FIFO2 read"); exit(1); }

        char buffer[MAXLINE];
        ssize_t n;
        while ((n = read(fd_read, buffer, sizeof(buffer)-1)) > 0) {
            buffer[n] = '\0';
            replace_vowels(buffer);
            printf("Process 2 output: %s", buffer);
            fflush(stdout);
        }

        close(fd_read);
        exit(0);
    }

<<<<<<< Updated upstream
    // Parent waits for children
=======
>>>>>>> Stashed changes
    wait(NULL);
    wait(NULL);
    wait(NULL);

<<<<<<< Updated upstream
    // Cleanup FIFOs
=======
>>>>>>> Stashed changes
    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}