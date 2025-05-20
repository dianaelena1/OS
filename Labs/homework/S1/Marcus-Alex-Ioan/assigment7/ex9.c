#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_OUTPUT 4096
#define MAX_SERVER 256

// Parent process sends to the child a name of a Unix server, and the child sends back to the 
// parent the list of all usernames that work in that moment on the server.

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
        exit(1);
    }

    if (pid == 0) {
        close(parent_to_child[1]);
        close(child_to_parent[0]);

        char server[MAX_SERVER];
        read(parent_to_child[0], server, sizeof(server));
        server[strcspn(server, "\n")] = '\0'; 

        char command[MAX_SERVER + 32];
        if (strcmp(server, "localhost") == 0 || strcmp(server, "127.0.0.1") == 0) {
            snprintf(command, sizeof(command), "who");
        } else {
            snprintf(command, sizeof(command), "ssh %s who", server);
        }

        FILE *fp = popen(command, "r");
        if (!fp) {
            perror("popen");
            exit(1);
        }

        char output[MAX_OUTPUT] = {0};
        char line[256];

        while (fgets(line, sizeof(line), fp)) {
            char username[64];
            if (sscanf(line, "%63s", username) == 1) {
                strcat(output, username);
                strcat(output, "\n");
            }
        }

        pclose(fp);
        write(child_to_parent[1], output, strlen(output) + 1);

        close(parent_to_child[0]);
        close(child_to_parent[1]);
        exit(0);
    } else {
        close(parent_to_child[0]);
        close(child_to_parent[1]);

        char server[MAX_SERVER];
        printf("Enter server name (e.g., localhost): ");
        fgets(server, sizeof(server), stdin);

        write(parent_to_child[1], server, strlen(server) + 1);
        char result[MAX_OUTPUT];
        read(child_to_parent[0], result, sizeof(result));
        printf("Logged-in users on %s:\n%s\n", server, result);
        close(parent_to_child[1]);
        close(child_to_parent[0]);
        wait(NULL);
    }

    return 0;
}
