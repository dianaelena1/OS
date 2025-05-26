//Write a C Program that deletes from a file the bytes from even offsets. 
//The name of the file is provided as a command line argument.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "rb");

    if (!file) {
        perror("Error opening file for reading");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return 1;
    }

    if (fread(buffer, 1, size, file) != size) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return 1;
    }

    fclose(file);

    file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file for writing");
        free(buffer);
        return 1;
    }

    for (long i = 1; i < size; i += 2) {
        fputc(buffer[i], file);
    }

    fclose(file);
    free(buffer);

    printf("Bytes at even offsets removed successfully.\n");
    return 0;
}

