#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FIFO_PARENT_TO_CHILD "to_child_fifo"
#define FIFO_CHILD_TO_PARENT "to_parent_fifo"
#define BUFFER_SIZE 256

int main() {
    char filename[BUFFER_SIZE], result[BUFFER_SIZE];

    // Create FIFOs if they don't exist
    mkfifo(FIFO_PARENT_TO_CHILD, 0666);
    mkfifo(FIFO_CHILD_TO_PARENT, 0666);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    else if (pid == 0) {
        // --- Child process ---
        int read_fd = open(FIFO_PARENT_TO_CHILD, O_RDONLY);
        read(read_fd, filename, sizeof(filename));
        close(read_fd);

        struct stat st;
        if (stat(filename, &st) == -1) {
            snprintf(result, sizeof(result), "Error: File '%s' not found.", filename);
        } else if (S_ISREG(st.st_mode)) {
            snprintf(result, sizeof(result), "File '%s' is a regular file.", filename);
        } else if (S_ISDIR(st.st_mode)) {
            snprintf(result, sizeof(result), "File '%s' is a directory.", filename);
        } else {
            snprintf(result, sizeof(result), "File '%s' is another type.", filename);
        }

        int write_fd = open(FIFO_CHILD_TO_PARENT, O_WRONLY);
        write(write_fd, result, strlen(result) + 1);
        close(write_fd);

        exit(EXIT_SUCCESS);
    }

    else {
        // --- Parent process ---
        printf("Enter file name: ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = '\0'; // Remove newline

        int write_fd = open(FIFO_PARENT_TO_CHILD, O_WRONLY);
        write(write_fd, filename, strlen(filename) + 1);
        close(write_fd);

        int read_fd = open(FIFO_CHILD_TO_PARENT, O_RDONLY);
        read(read_fd, result, sizeof(result));
        close(read_fd);

        printf("Child response: %s\n", result);

        wait(NULL); // Wait for child
    }
// Cleanup FIFOs
    unlink(FIFO_PARENT_TO_CHILD);
    unlink(FIFO_CHILD_TO_PARENT);

    return 0;
}