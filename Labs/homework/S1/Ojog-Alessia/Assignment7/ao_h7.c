#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>

void list_txt_files(const char *dir_name, int write_fd) {
    DIR *dir = opendir(dir_name);
    if (!dir) {
        char error_msg[] = "Error: Directory does not exist.\n";
        write(write_fd, error_msg, strlen(error_msg));
        return;
    }

    struct dirent *entry;
    int found_files = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".txt")) {
            found_files = 1;
            write(write_fd, entry->d_name, strlen(entry->d_name));
            write(write_fd, "\n", 1);
        }
    }

    if (!found_files) {
        write(write_fd, "No .txt files found.\n", 21);
    }

    closedir(dir);
}

int main() {
    int pipe1[2], pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    pid_t pid = fork();

    if (pid == 0) {
        close(pipe1[1]);
        close(pipe2[0]);
        
        char dir_name[256];
        read(pipe1[0], dir_name, sizeof(dir_name));
        list_txt_files(dir_name, pipe2[1]);
        
        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);
    } else {
        close(pipe1[0]);
        close(pipe2[1]);

        char dir_name[] = "/mnt/c/Users/user/.vscode/OS-3/labs/homework/s1/ojog-alessia/assignment7/dir1/";
        write(pipe1[1], dir_name, strlen(dir_name) + 1);
        
        char buffer[1024];
        int bytes_read;
        while ((bytes_read = read(pipe2[0], buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }
        
        close(pipe1[1]);
        close(pipe2[0]);
        wait(NULL);
    }

    return 0;
}
