#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_BUF 1024

int main() {
    int parent_to_child[2];
    int child_to_parent[2];

    if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(2);
    }

    if (pid == 0) {
        
        close(parent_to_child[1]);
        close(child_to_parent[0]);

        char dir_name[MAX_BUF];
        read(parent_to_child[0], dir_name, sizeof(dir_name));
        dir_name[strcspn(dir_name, "\n")] = 0;

        DIR *dir = opendir(dir_name);
        char result[MAX_BUF] = "";

        if (dir == NULL) {
            snprintf(result, sizeof(result), "Error: Directory '%s' not found.\n", dir_name);
        } else {
            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL) {
                if (strstr(entry->d_name, ".txt") != NULL) {
                    strcat(result, entry->d_name);
                    strcat(result, "\n");
                }
            }
            closedir(dir);
            if (strlen(result) == 0)
                strcpy(result, "No .txt files found.\n");
        }

        write(child_to_parent[1], result, strlen(result) + 1);

        close(parent_to_child[0]);
        close(child_to_parent[1]);
        exit(0);

    } else {
    
        close(parent_to_child[0]);
        close(child_to_parent[1]);

        char dir_name[MAX_BUF];
        printf("Enter directory name: ");
        fgets(dir_name, sizeof(dir_name), stdin);

        write(parent_to_child[1], dir_name, strlen(dir_name) + 1);

        char buffer[MAX_BUF];
        read(child_to_parent[0], buffer, sizeof(buffer));
        printf("Child response:\n%s", buffer);

        close(parent_to_child[1]);
        close(child_to_parent[0]);
        wait(NULL);
    }

    return 0;
}
