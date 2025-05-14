#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



void error_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int run_op(int op, int a, int b) {
    int p[2];
    if (pipe(p) == -1) error_exit("pipe");
    pid_t pid = fork();
    if (pid < 0) error_exit("fork");
    if (pid == 0) {

        close(p[0]);
        int r;
        switch (op) {
            case 0: r = a + b; break;
            case 1: r = a - b; break;
            case 2: r = a * b; break;
            case 3:
                if (b == 0) {
                    fprintf(stderr, "Division by zero\n");
                    _exit(EXIT_FAILURE);
                }
                r = a / b;
                break;
            default:
                fprintf(stderr, "Unknown operation\n");
                _exit(EXIT_FAILURE);
        }
        dprintf(p[1], "%d\n", r);
        close(p[1]);
        _exit(EXIT_SUCCESS);
    }

    close(p[1]);
    FILE *fp = fdopen(p[0], "r");
    if (!fp) error_exit("fdopen");
    char buf[64];
    if (!fgets(buf, sizeof(buf), fp)) error_exit("fgets");
    int result = atoi(buf);
    fclose(fp);
    wait(NULL);
    return result;
}

int main(void) {
    int a, b, c, d;

    printf("Enter a b c d:\n");
    fflush(stdout);
    if (scanf("%d %d %d %d", &a, &b, &c, &d) != 4) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }


    int bc = run_op(2, b, c);
    int numerator = run_op(0, a, bc);


    int ab = run_op(1, a, b);
    int abd = run_op(0, ab, d);
    int denom = run_op(1, abd, c);

    int div_res = run_op(3, numerator, denom);


    int abc = run_op(2, a, bc);
    int abcd = run_op(2, abc, d);

    int final = run_op(0, div_res, abcd);

    printf("Result: %d\n", final);
    return EXIT_SUCCESS;
}
