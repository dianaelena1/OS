#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/wait.h>

int main() {
    const char *f2 = "/tmp/fifo2";
    const char *f3 = "/tmp/fifo3";

    /* create or recreate the FIFOs */
    unlink(f2); unlink(f3);
    if (mkfifo(f2, 0666) == -1 || mkfifo(f3, 0666) == -1) {
        perror("mkfifo");
        return 1;
    }

    /* fork Process 2: read digits and print */
    if (fork() == 0) {
        int fd = open(f2, O_RDONLY);
        if (fd < 0) { perror("open f2"); exit(1); }
        char c;
        while (read(fd, &c, 1) > 0) putchar(c);
        close(fd);
        return 0;
    }

    /* fork Process 3: read letters, uppercase, print */
    if (fork() == 0) {
        int fd = open(f3, O_RDONLY);
        if (fd < 0) { perror("open f3"); exit(1); }
        char c;
        while (read(fd, &c, 1) > 0) {
            if (islower((unsigned char)c)) c = toupper(c);
            putchar(c);
        }
        close(fd);
        return 0;
    }

    /* Process 1: read stdin, dispatch to the two FIFOs */
    int w2 = open(f2, O_WRONLY);
    int w3 = open(f3, O_WRONLY);
    if (w2 < 0 || w3 < 0) { perror("open for write"); return 1; }

    char buf[31];
    while (fgets(buf, sizeof(buf), stdin)) {
        for (int i = 0; buf[i]; i++) {
            if (isdigit((unsigned char)buf[i]))
                write(w2, &buf[i], 1);
            else if (isalpha((unsigned char)buf[i]))
                write(w3, &buf[i], 1);
        }
    }

    close(w2);
    close(w3);

    /* wait for children and clean up FIFOs */
    wait(NULL);
    wait(NULL);
    unlink(f2);
    unlink(f3);
    return 0;
}
