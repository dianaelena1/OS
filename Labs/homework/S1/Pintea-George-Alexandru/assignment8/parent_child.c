#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LEN 256

int main() {
    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pipe1[1]);
        close(pipe2[0]);

        char server[MAX_LEN];
        read(pipe1[0], server, MAX_LEN);
        printf("[Child] Received server name: %s\n", server);

        FILE *fp = popen("who", "r");
        if (!fp) {
            perror("popen");
            exit(EXIT_FAILURE);
        }

        char output[1024] = "";
        char buffer[128];
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            strcat(output, buffer);
        }
        pclose(fp);

        write(pipe2[1], output, strlen(output) + 1);

        close(pipe1[0]);
        close(pipe2[1]);

    } else {
        close(pipe1[0]);
        close(pipe2[1]);

        char server_name[MAX_LEN] = "localhost";
        write(pipe1[1], server_name, strlen(server_name) + 1);

        char result[1024];
        read(pipe2[0], result, sizeof(result));

        printf("[Parent] Logged-in users on %s:\n%s", server_name, result);

        close(pipe1[1]);
        close(pipe2[0]);

        wait(NULL);
    }

    return 0;
}
