#include <stdio.h>
#include <stdlib.h>

// Function to reverse a file's bytes
int reverse_file_bytes(const char *filename) {
    FILE *file = fopen(filename, "rb+");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Move to end to get file size
    if (fseek(file, 0, SEEK_END) != 0) {
        perror("Error seeking to end of file");
        fclose(file);
        return 1;
    }

    long size = ftell(file);
    if (size < 0) {
        perror("Error getting file size");
        fclose(file);
        return 1;
    }

    // Allocate buffer
    unsigned char *buffer = (unsigned char *)malloc(size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return 1;
    }

    // Read file into buffer
    rewind(file);
    if (fread(buffer, 1, size, file) != size) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return 1;
    }

    // Reverse buffer
    for (long i = 0; i < size / 2; ++i) {
        unsigned char temp = buffer[i];
        buffer[i] = buffer[size - 1 - i];
        buffer[size - 1 - i] = temp;
    }

    // Write reversed buffer back to file
    rewind(file);
    if (fwrite(buffer, 1, size, file) != size) {
        perror("Error writing to file");
        free(buffer);
        fclose(file);
        return 1;
    }

    // Cleanup
    free(buffer);
    fclose(file);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    if (reverse_file_bytes(argv[1]) != 0) {
        fprintf(stderr, "Failed to reverse file contents.\n");
        return 1;
    }

    printf("File contents reversed successfully.\n");
    return 0;
}

// cd /Users/zepciucdenisa/IdeaProjects/OS/Labs/homework/S2/Zepciuc-Denisa/assignment6
// gcc Zepciuc-Denisa.c -o Zepciuc-Denisa
//./Zepciuc-Denisa file.txt