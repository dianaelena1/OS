#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

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

        DIR *dir = opendir(dir_name);
        if (dir == NULL) {
            perror("opendir");
            int error = -1;
            write(pipe2[1], &error, sizeof(int));
            exit(1);
        }

        struct dirent *entry;
        struct stat file_stat;
        char filepath[512];
        int total_bytes = 0;

        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            snprintf(filepath, sizeof(filepath), "%s/%s", dir_name, entry->d_name);

            if (stat(filepath, &file_stat) == 0 && S_ISREG(file_stat.st_mode)) {
                total_bytes += file_stat.st_size;
            }
        }

        closedir(dir);
        write(pipe2[1], &total_bytes, sizeof(int));
        close(pipe1[0]);
        close(pipe2[1]);
    } else {
        close(pipe1[0]); 
        close(pipe2[1]); 

        char dir_name[256];
        printf("Enter directory name: ");
        scanf("%s", dir_name);

        write(pipe1[1], dir_name, sizeof(dir_name));

        int result;
        read(pipe2[0], &result, sizeof(int));

        if (result >= 0)
            printf("Total bytes in regular files: %d\n", result);
        else
            printf("Error occurred in child process.\n");

        close(pipe1[1]);
        close(pipe2[0]);
        wait(NULL);
    }

    return 0;
}

