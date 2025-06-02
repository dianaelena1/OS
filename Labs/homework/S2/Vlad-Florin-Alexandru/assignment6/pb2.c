//|2|Write a C Program that deletes from a file the bytes from even offsets. The name of the file is provided as a command line argument. |

#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE *in = fopen(argv[1], "rb");
    if (in == NULL) {
        perror("Error opening input file");
        return 1;
    }

    FILE *out = fopen("temp.bin", "wb");
    if (out == NULL) {
        perror("Error creating temporary file");
        fclose(in);
        return 1;
    }

    int ch;
    long offset = 0;
    while ((ch = fgetc(in)) != EOF) {
        if (offset % 2 == 1) {
            fputc(ch, out);
        }
        offset++;
    }

    fclose(in);
    fclose(out);

    /* replace original with filtered file */
    remove(argv[1]);
    rename("temp.bin", argv[1]);

    return 0;
}
