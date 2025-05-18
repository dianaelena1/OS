//|2|Write a C Program that deletes from a file the bytes from even offsets. The name of the file is provided as a command line argument. |



#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp_in, *fp_out;
    char *filename_in, *filename_temp = "temp_file.bin";
    int ch;
    int pos = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    filename_in = argv[1];


    fp_in = fopen(filename_in, "rb");
    if (!fp_in) {
        perror("Error opening input file");
        return 1;
    }


    fp_out = fopen(filename_temp, "wb");
    if (!fp_out) {
        perror("Error opening temporary file");
        fclose(fp_in);
        return 1;
    }


    while ((ch = fgetc(fp_in)) != EOF) {
        if (pos % 2 != 0) {
            fputc(ch, fp_out);
        }
        pos++;
    }

    fclose(fp_in);
    fclose(fp_out);

    if (remove(filename_in) != 0) {
        perror("Error deleting original file");
        return 1;
    }

    if (rename(filename_temp, filename_in) != 0) {
        perror("Error renaming temp file");
        return 1;
    }

    printf("Even offset bytes removed successfully.\n");
    return 0;
}
