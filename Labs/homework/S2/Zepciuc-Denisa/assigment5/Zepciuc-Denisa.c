//Write a C Program that compares the content of two files provided as command line parameters.
//The compariso will be performed on blocks of 1KB each.
//The program will print the total number of blocks from each file and the number of identical blocks found.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *f1 = fopen(argv[1], "rb");
    FILE *f2 = fopen(argv[2], "rb");

    if (!f1 || !f2) {
        perror("Error opening files");
        return EXIT_FAILURE;
    }

    unsigned char buffer1[BLOCK_SIZE];
    unsigned char buffer2[BLOCK_SIZE];
    int blocks_f1 = 0, blocks_f2 = 0, identical_blocks = 0;

    while (1) {
        size_t bytes_read1 = fread(buffer1, 1, BLOCK_SIZE, f1);
        size_t bytes_read2 = fread(buffer2, 1, BLOCK_SIZE, f2);

        if (bytes_read1 > 0) blocks_f1++;
        if (bytes_read2 > 0) blocks_f2++;

        if (bytes_read1 == 0 && bytes_read2 == 0)
            break;

        if (bytes_read1 == bytes_read2 && memcmp(buffer1, buffer2, bytes_read1) == 0)
            identical_blocks++;
    }

    fclose(f1);
    fclose(f2);

    printf("Total blocks in %s: %d\n", argv[1], blocks_f1);
    printf("Total blocks in %s: %d\n", argv[2], blocks_f2);
    printf("Identical blocks: %d\n", identical_blocks);

    return EXIT_SUCCESS;
}
//gcc Zepciuc-Denisa.c -o Zepciuc-Denisa
//./Zepciuc-Denisa file1.txt file2.txt
