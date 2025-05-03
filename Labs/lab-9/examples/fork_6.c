//
// fork_6.c
//
// Preventing a child process to become ZOMBIE - Using signal() system call
//
// At the termination of the child, a ‘SIGCHLD’ signal is generated
// and is delivered to the parent by the kernel.
// If the parent call signal(SIGCHLD, SIG_IGN), then the SIGCHLD signal is ignored,
// and the child process entry will be deleted from the process table.
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int pid = fork();
    if (pid == -1)                      // fork() failed
    {
        perror("fork() error: ");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)                       // in child process
    {
        printf("\n[In CHILD] I started ...\n");

        int i;
        for (i = 0; i < 3; i++)
        {
            sleep(5);
            printf("[In CHILD]\tMy PID is %d Parent PID is %d\n", getpid(), getppid());
        }

        printf("[In CHILD] I finished my job.\n");
    }
    else                                // in parent process
    {
        signal(SIGCHLD, SIG_IGN);       // ignore the SIGCHLD signal
        printf("[In PARENT] I started ...\n");
        printf("[In PARENT]\tMy PID is %d Child PID is %d\n", getpid(), pid);
        while(1);
        printf("[In PARENT] I finished.\n");
    }

    return 0;
}
