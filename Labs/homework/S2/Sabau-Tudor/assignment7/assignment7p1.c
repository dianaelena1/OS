#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

int main() {
    int parentToChild[2]; // pipe for parent to send directory name to child
    int childToParent[2]; // pipe for child to send result back to parent

    if (pipe(parentToChild) == -1 || pipe(childToParent) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(2);
    } else if (pid == 0) {
        // Child process
        close(parentToChild[1]); // close write end
        close(childToParent[0]); // close read end

        char dirName[BUFFER_SIZE];
        read(parentToChild[0], dirName, sizeof(dirName));
        close(parentToChild[0]);

        // Remove newline if present
        dirName[strcspn(dirName, "\n")] = '\0';

        DIR *dir = opendir(dirName);
        if (!dir) {
            char *error = "Error: Directory does not exist or can't be opened.\n";
            write(childToParent[1], error, strlen(error));
            close(childToParent[1]);
            exit(1);
        }

        struct dirent *entry;
        char result[BUFFER_SIZE] = "";
        while ((entry = readdir(dir)) != NULL) {
            if (strstr(entry->d_name, ".txt")) {
                strcat(result, entry->d_name);
                strcat(result, "\n");
            }
        }
        closedir(dir);

        if (strlen(result) == 0) {
            strcpy(result, "No .txt files found.\n");
        }

        write(childToParent[1], result, strlen(result));
        close(childToParent[1]);

    } else {
        // Parent process
        close(parentToChild[0]); // close read end
        close(childToParent[1]); // close write end

        char dirName[BUFFER_SIZE];
        printf("Enter directory name: ");
        fgets(dirName, sizeof(dirName), stdin);
        write(parentToChild[1], dirName, strlen(dirName));
        close(parentToChild[1]);

        char buffer[BUFFER_SIZE];
        int bytesRead = read(childToParent[0], buffer, sizeof(buffer) - 1);
        buffer[bytesRead] = '\0';

        printf("Child response:\n%s", buffer);
        close(childToParent[0]);
    }

    return 0;
}
