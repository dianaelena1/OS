#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_LEN 100

int main() {
    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {

        close(pipe1[1]);
        close(pipe2[0]);

        char username[MAX_LEN];
        read(pipe1[0], username, sizeof(username));
        username[strcspn(username, "\n")] = '\0';


        int exec_pipe[2];
        if (pipe(exec_pipe) == -1) {
            perror("Pipe exec_pipe failed");
            exit(EXIT_FAILURE);
        }

        pid_t exec_pid = fork();

        if (exec_pid == 0) {

            close(exec_pipe[0]);
            dup2(exec_pipe[1], STDOUT_FILENO);
            dup2(exec_pipe[1], STDERR_FILENO);
            close(exec_pipe[1]);

            execlp("ps", "ps", "-u", username, NULL);
            perror("execlp failed");
            exit(EXIT_FAILURE);
        } else {

            close(exec_pipe[1]);

            FILE *stream = fdopen(exec_pipe[0], "r");
            if (!stream) {
                perror("fdopen failed");
                exit(EXIT_FAILURE);
            }

            char line[256];
            int count = -1;

            while (fgets(line, sizeof(line), stream)) {
                count++;
            }

            fclose(stream);
            wait(NULL);


            char buffer[256];
;
            if (count < 0) {
                snprintf(buffer, sizeof(buffer), "User '%s' not found or has no processes.\n", username);
            } else {
                snprintf(buffer, sizeof(buffer), "Number of processes for user '%s': %d\n", username, count);
            }

            write(pipe2[1], buffer, strlen(buffer));

            close(pipe1[0]);
            close(pipe2[1]);
            exit(0);
        }
    } else {

        close(pipe1[0]);
        close(pipe2[1]);

        char username[MAX_LEN];
        printf("Enter username: ");
        fgets(username, sizeof(username), stdin);

        write(pipe1[1], username, strlen(username) + 1);

        char response[256];
        int bytesRead = read(pipe2[0], response, sizeof(response) - 1);
        if (bytesRead > 0) {
            response[bytesRead] = '\0';
            printf("%s", response);
        }

        close(pipe1[1]);
        close(pipe2[0]);
        wait(NULL);
    }

    return 0;
}
