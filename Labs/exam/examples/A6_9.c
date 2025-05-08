#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#define N 5

int main() {

    int x[N] = {1, 2, 3, 4, 5};
   
    int *S = mmap(NULL, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (S == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    pid_t pids[N];

    void compute_partial_sum(int i) {
        int sum = 0;
        for (int j = 0; j <= i; j++) {
            sum += x[j];
        }
        S[i] = sum;
    }

    for (int i = 0; i < N; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork");
            exit(1);
        } else if (pids[i] == 0) {
            compute_partial_sum(i);
	    munmap(S, N * sizeof(int));
            exit(0);
        }
    }

    for (int i = 0; i < N; i++) {
        waitpid(pids[i], NULL, 0);
    }

    printf("Partial sums: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", S[i]);
    }
    printf("\n");
   munmap(S, N * sizeof(int));
    return 0;
}
