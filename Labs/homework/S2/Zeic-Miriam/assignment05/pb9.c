//A program receives as command line arguments two file names 
//and merges the lines of the two files (that are already sorted).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <sorted_file1> <sorted_file2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *f1 = fopen(argv[1], "r");
    if (!f1) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }
    FILE *f2 = fopen(argv[2], "r");
    if (!f2) {
        perror(argv[2]);
        fclose(f1);
        return EXIT_FAILURE;
    }

    char line1[MAXLINE], line2[MAXLINE];
    char *l1 = fgets(line1, sizeof(line1), f1);
    char *l2 = fgets(line2, sizeof(line2), f2);

    while (l1 && l2) {
        if (strcmp(line1, line2) <= 0) {
            fputs(line1, stdout);
            l1 = fgets(line1, sizeof(line1), f1);
        } else {
            fputs(line2, stdout);
            l2 = fgets(line2, sizeof(line2), f2);
        }
    }

 
    while (l1) {
        fputs(line1, stdout);
        l1 = fgets(line1, sizeof(line1), f1);
    }
    while (l2) {
        fputs(line2, stdout);
        l2 = fgets(line2, sizeof(line2), f2);
    }

    fclose(f1);
    fclose(f2);
    return EXIT_SUCCESS;
}
