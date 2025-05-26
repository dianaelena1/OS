#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int p2c[2]; // pipe: parent to child
    int c2p[2]; // pipe: child to parent

    pipe(p2c);
    pipe(c2p);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        close(p2c[1]); // close write end of parent-to-child
        close(c2p[0]); // close read end of child-to-parent

        char username[100];
        read(p2c[0], username, sizeof(username));

        char cmd[150];
        snprintf(cmd, sizeof(cmd), "last %s", username);

        FILE *fp = popen(cmd, "r");
        if (!fp) {
            perror("popen failed");
            exit(1);
        }

        char line[256];
        while (fgets(line, sizeof(line), fp)) {
            write(c2p[1], line, strlen(line));
        }

        pclose(fp);
        close(p2c[0]);
        close(c2p[1]);
        exit(0);
    } else {
        // Parent process
        close(p2c[0]); // close read end of parent-to-child
        close(c2p[1]); // close write end of child-to-parent

        char username[100];
        printf("Enter username: ");
        fgets(username, sizeof(username), stdin);
        write(p2c[1], username, strlen(username));

        printf("\nLogin records for %s:\n", username);
        char line[256];
        while (read(c2p[0], line, sizeof(line)) > 0) {
            printf("%s", line);
        }

        close(p2c[1]);
        close(c2p[0]);
        wait(NULL);
    }

    return 0;
}
