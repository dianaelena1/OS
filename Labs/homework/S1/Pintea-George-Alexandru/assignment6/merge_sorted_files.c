//Write a C program that recieves as command line arguments two file names and merges the lines of the two files(that are already sorted)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1024

void print_usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s <file1> <file2>\n", prog_name);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        print_usage(argv[0]);
        return 1;
    }

    FILE *file1 = fopen(argv[1], "r");
    FILE *file2 = fopen(argv[2], "r");

    if (!file1 || !file2) {
        perror("Error opening file");
        return 1;
    }

    char line1[MAX_LINE_LEN], line2[MAX_LINE_LEN];
    char *read1 = fgets(line1, MAX_LINE_LEN, file1);
    char *read2 = fgets(line2, MAX_LINE_LEN, file2);

    while (read1 && read2) {
        if (strcmp(line1, line2) <= 0) {
            fputs(line1, stdout);
            read1 = fgets(line1, MAX_LINE_LEN, file1);
        } else {
            fputs(line2, stdout);
            read2 = fgets(line2, MAX_LINE_LEN, file2);
        }
    }

    while (read1) {
        fputs(line1, stdout);
        read1 = fgets(line1, MAX_LINE_LEN, file1);
    }

    while (read2) {
        fputs(line2, stdout);
        read2 = fgets(line2, MAX_LINE_LEN, file2);
    }

    fclose(file1);
    fclose(file2);
    return 0;
}
