//An array of numbers is given x1, x2, ..., xn. Compute the partial 
//sums x1, x1+x2, x1+x2+x3,..., x1+x2+...+xn, using a separate 
//process for each partial sum.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Usage: enter a positive integer n\n");
        return EXIT_FAILURE;
    }

    int *x = malloc(n * sizeof(int));
    if (!x) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &x[i]) != 1) {
            fprintf(stderr, "Failed to read x[%d]\n", i);
            free(x);
            return EXIT_FAILURE;
        }
    }

    for (int i = 1; i <= n; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            free(x);
            return EXIT_FAILURE;
        }
        if (pid == 0) {
            
            int sum = 0;
            for (int j = 0; j < i; j++) {
                sum += x[j];
            }
            printf("Sum of first %d element%s: %d\n",
                   i, (i>1 ? "s" : ""), sum);
            free(x);
            _exit(EXIT_SUCCESS);
        }
        
    }

    
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    free(x);
    return EXIT_SUCCESS;
}
