//Write a C Program that receives as command line argument a name of a file. 
//The program duplicates the bytes from even offsets in the file
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void duplicate_even_offsets(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        free(buffer);
        exit(EXIT_FAILURE);
    } else if (pid == 0) {  // Child process
        // Open the file again for writing (truncate)
        file = fopen(filename, "wb");
        if (!file) {
            perror("Error reopening file");
            free(buffer);
            exit(EXIT_FAILURE);
        }
        for (long i = 0; i < file_size; i++) {
            if (i % 2 == 0) {  // Even offset
                fputc(buffer[i], file);
                fputc(buffer[i], file);
            } else {  // Odd offset
                fputc(buffer[i], file);
            }
        }
        fclose(file);
        free(buffer);
        exit(EXIT_SUCCESS);
    } else {  // Parent process
        wait(NULL);  // Wait for the child to complete
    }

    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    duplicate_even_offsets(argv[1]);
    return EXIT_SUCCESS;
}
