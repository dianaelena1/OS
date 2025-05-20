#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork() error: ");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Procesul copil
        printf("[In CHILD] My PID is %d\n", getpid());
        printf("[In CHILD] Child process is doing some work...\n");
        sleep(3);
        printf("[In CHILD] Child process finished its work.\n");
        exit(EXIT_SUCCESS);
    } else {
        // Procesul părinte
        printf("[In PARENT] My PID is %d\n", getpid());
        printf("[In PARENT] Parent process is waiting for child process to finish...\n");
        wait(NULL); // Așteaptă orice proces copil să se încheie
        printf("[In PARENT] Child process has finished.\n");
    }

    return 0;
}
