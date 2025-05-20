

/*Write a C Program that compares the content of two files provided as command line parameters.
The comparison will be performed on blocks of 1KB each. 
The program will print the total number of blocks from each file 
and the number of identical blocks found.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOCK_SIZE 1024

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE* f1 = fopen(argv[1], "rb");
    if (f1 == NULL) {
        perror("Error opening first file");
        exit(EXIT_FAILURE);
    }

    FILE* f2 = fopen(argv[2], "rb");
    if (f2 == NULL) {
        perror("Error opening second file");
        fclose(f1);
        exit(EXIT_FAILURE);
    }

    unsigned char buf1[BLOCK_SIZE], buf2[BLOCK_SIZE];
    int blocks1 = 0, blocks2 = 0, identicalBlocks = 0;

    while (!feof(f1) || !feof(f2)) {
        size_t r1 = fread(buf1, 1, BLOCK_SIZE, f1);
        size_t r2 = fread(buf2, 1, BLOCK_SIZE, f2);

        if (r1 > 0) blocks1++;
        if (r2 > 0) blocks2++;

        if (r1 > 0 && r2 > 0 && r1 == r2 && memcmp(buf1, buf2, r1) == 0) {
            identicalBlocks++;
        }
    }

    fclose(f1);
    fclose(f2);

    printf("Total blocks in %s: %d\n", argv[1], blocks1);
    printf("Total blocks in %s: %d\n", argv[2], blocks2);
    printf("Identical blocks: %d\n", identicalBlocks);

    return 0;
}
