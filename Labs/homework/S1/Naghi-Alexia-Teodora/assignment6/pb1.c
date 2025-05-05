#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>
#include <stdbool.h>

#define MAX 1000

void sieve_process(int n, int read_fd) {
    int i;
    read(read_fd, &i, sizeof(int));

    if (i == 0) return;

    printf("Prime: %d\n", i);

    int num;
    int fds[2];
    pipe(fds);

    if (fork() == 0) {
        close(fds[1]);
        sieve_process(n, fds[0]);
        exit(0);
    } else {
        close(fds[0]);
        while (read(read_fd, &num, sizeof(int)) > 0) {
            if (num % i != 0) {
                write(fds[1], &num, sizeof(int));
            }
        }
        close(fds[1]);
        wait(NULL);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int fds[2];
    pipe(fds);

    if (fork() == 0) {
        close(fds[1]);
        sieve_process(N, fds[0]);
        exit(0);
    } else {
        close(fds[0]);
        for (int i = 2; i <= N; ++i) {
            write(fds[1], &i, sizeof(int));
        }
        int zero = 0;
        write(fds[1], &zero, sizeof(int)); 
        close(fds[1]);
        wait(NULL);
    }

    return 0;
}

