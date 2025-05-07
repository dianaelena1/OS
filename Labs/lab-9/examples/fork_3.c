//
// fork_3.c
//
// An ORPHAN process
//
// A child process whose parent process no more exists.
// (i.e. either finished or terminated without waiting for its child process to terminate)
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
    int pid = fork();
    if (pid == -1)                  // fork() failed
    {
        perror("fork() error: ");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)                   // in child process
    {
        printf("[In CHILD] I started ...\n");
        printf("[In CHILD]\tMy PID is %d\tParent PID is %d\n", getpid(), getppid());
		
        sleep(5);					// wait for 5 seconds
        
		printf("\n[In CHILD]\tI am an ORPHAN process now ...\n");
        printf("[In CHILD]\tMy PID is %d Parent PID is %d\n", getpid(), getppid());
        printf("[In CHILD] I finished my job.\n");
		
		exit(EXIT_SUCCESS);
    }
    else                            // in parent process
    {
        printf("[In PARENT] I started ...\n");
        printf("[In PARENT]\tMy PID is %d Child PID is %d\n", getpid(), pid);
        printf("[In PARENT] I finished.\n");
    }

    return 0;
}
