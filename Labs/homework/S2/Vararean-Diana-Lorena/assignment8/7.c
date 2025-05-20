//Pb 7 - Implement the following structure of processes,
// in which the vertices indicate the communication between processes using pipes.

// Process 1: read from stdin and write to 2 lines that are alphanumerical and to 3 lines that do not contain letters
// Process 2: replace digits with ‘_’
// Process 3 & 4: print to stdout what is read


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <errno.h>

#define FIFO_1_2 "fifo_1_2"
#define FIFO_1_3 "fifo_1_3"
#define FIFO_2_4 "fifo_2_4"

#define MAX_LINE 256


int contains_letter(const char *line) {
    while (*line) {
        if (isalpha((unsigned char)*line))
            return 1;
        line++;
    }
    return 0;
}

void replace_digits(char *line) {
    while (*line) {
        if (isdigit((unsigned char)*line))
            *line = '_';
        line++;
    }
}

int main() {
    mkfifo(FIFO_1_2, 0666);
    mkfifo(FIFO_1_3, 0666);
    mkfifo(FIFO_2_4, 0666);

    pid_t pids[4];
    for (int i = 0; i < 4; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork");
            exit(1);
        }
        if (pids[i] == 0) {
            if (i == 0) { // Process 1
                int fd_1_2 = open(FIFO_1_2, O_WRONLY);
                int fd_1_3 = open(FIFO_1_3, O_WRONLY);
                if (fd_1_2 < 0 || fd_1_3 < 0) {
                    perror("Process 1: open FIFO");
                    exit(1);
                }

                char line[MAX_LINE];
                while (fgets(line, MAX_LINE, stdin)) {
                    if (contains_letter(line)) {
                        write(fd_1_2, line, strlen(line));
                    } else {
                        write(fd_1_3, line, strlen(line));
                    }
                }
                close(fd_1_2);
                close(fd_1_3);
                exit(0);
            } else if (i == 1) { // Process 2
                int fd_1_2 = open(FIFO_1_2, O_RDONLY);
                int fd_2_4 = open(FIFO_2_4, O_WRONLY);
                if (fd_1_2 < 0 || fd_2_4 < 0) {
                    perror("Process 2: open FIFO");
                    exit(1);
                }

                char buf[MAX_LINE];
                ssize_t n;
                while ((n = read(fd_1_2, buf, MAX_LINE)) > 0) {
                    buf[n] = '\0';
                    replace_digits(buf);
                    write(fd_2_4, buf, strlen(buf));
                }
                close(fd_1_2);
                close(fd_2_4);
                exit(0);
            } else if (i == 2) { // Process 3
                int fd_1_3 = open(FIFO_1_3, O_RDONLY);
                if (fd_1_3 < 0) {
                    perror("Process 3: open FIFO");
                    exit(1);
                }

                char buf[MAX_LINE];
                ssize_t n;
                while ((n = read(fd_1_3, buf, MAX_LINE)) > 0) {
                    buf[n] = '\0';
                    printf("From Process 3: %s", buf);
                    fflush(stdout);
                }

                close(fd_1_3);
                exit(0);

            } else if (i == 3) { // Process 4
                int fd_2_4 = open(FIFO_2_4, O_RDONLY);
                if (fd_2_4 < 0) {
                    perror("Process 4: open FIFO");
                    exit(1);
                }

                char buf[MAX_LINE];
                ssize_t n;

                while ((n = read(fd_2_4, buf, MAX_LINE - 1)) > 0) {
                    buf[n] = '\0';
                    printf("From Process 2: %s", buf);
                    fflush(stdout);
                }

                close(fd_2_4);
                exit(0);

            }
        }
    }
    
    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }

    unlink(FIFO_1_2);
    unlink(FIFO_1_3);
    unlink(FIFO_2_4);

    return 0;
}

/* Example Input:

abc123
456
hello42
7890

*/