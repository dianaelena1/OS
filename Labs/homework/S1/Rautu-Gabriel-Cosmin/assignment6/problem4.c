#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    int N = atoi(argv[1]);
    for (int i = 2; i <= N; i++) {
        pid_t pid = fork();
        if (pid < 0) exit(1);
        if (pid == 0) {
            int x = N, count = 0;
            while (x % i == 0) {
                count++;
                x /= i;
            }
            if (count)
                printf("Prime factor %d with multiplicity %d\n", i, count);
            exit(0);
        }
    }
    while (wait(NULL) > 0);
    return 0;
}

