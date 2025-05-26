//Parent process sends to the child a filename, 
//and the child sends back to the parent the content of the file or an error message if the file does not exist.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

#define MAX 1024
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main() {
    char filename[MAX], buffer[MAX];
    pid_t pid;

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    else if (pid == 0) {
        // === Child Process ===
        int fd1 = open(FIFO1, O_RDONLY);  
        read(fd1, filename, sizeof(filename));
        close(fd1);

        FILE *fp = fopen(filename, "r");
        int fd2 = open(FIFO2, O_WRONLY); 

        if (fp == NULL) {
            strcpy(buffer, "Error: File does not exist.\n");
        } else {
            buffer[0] = '\0';
            char line[MAX];
            while (fgets(line, sizeof(line), fp) != NULL) {
                strcat(buffer, line);
            }
            fclose(fp);
        }

        write(fd2, buffer, strlen(buffer) + 1);
        close(fd2);
    }

    else {
        // === Parent Process ===
        printf("Enter filename: ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = '\0'; 

        int fd1 = open(FIFO1, O_WRONLY);  
        write(fd1, filename, strlen(filename) + 1);
        close(fd1);

        int fd2 = open(FIFO2, O_RDONLY);  
        read(fd2, buffer, sizeof(buffer));
        printf("\n--- File Output or Error ---\n%s", buffer);
        close(fd2);
    }

    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}
