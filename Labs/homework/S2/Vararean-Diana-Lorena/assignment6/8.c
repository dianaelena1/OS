//Pb 8 - Write a C Program that receives as command line argument
// the name of a file and deletes the even numbers from this file.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int is_even(int n) {
    return n % 2 == 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        return 1;
    } 
    else if (pid == 0) {
        FILE *in = fopen(argv[1], "r");
        if (!in) {
            perror("Failed to open file");
            exit(1);
        }

        FILE *temp = tmpfile();
        int num;

        while (fscanf(in, "%d", &num) == 1) {
            if (!is_even(num)) {
                fprintf(temp, "%d ", num);
            }
        }

        rewind(temp);
        freopen(argv[1], "w", in);

        while (fscanf(temp, "%d", &num) == 1) {
            fprintf(in, "%d ", num);
        }

        fclose(in);
        fclose(temp);
        exit(0);
    } 
    else {
        wait(NULL);
        printf("Even numbers removed by child process.\n");
    }

    return 0;
}
