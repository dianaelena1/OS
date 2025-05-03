//
// fork_4.c
//
// Using wait() system call (man 2 wait)
//
// If the parent process calls wait(), then its execution
// is suspended until the ALL childs are terminated.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


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
        printf("[In CHILD] I started ...\n");
        printf("[In CHILD]\tMy PID is %d Parent PID is %d\n", getpid(), getppid());
        
		sleep(5);						// wait for 5 seconds
        
		printf("[In CHILD]\tI am NOT an ORPHAN process ...\n");
        printf("[In CHILD]\tMy PID is %d Parent PID is %d\n", getpid(), getppid());
        printf("[In CHILD] I finished my job.\n");
		
		exit(EXIT_SUCCESS);
    }
    else                                // in parent process
    {
        printf("[In PARENT] I started ...\n");
        printf("[In PARENT]\tMy PID is %d Child PID is %d\n", getpid(), pid);
		
        int status;
        wait(&status);					// wait for child process to finish
        
		printf("[In PARENT]\tChild has finished with exit status: %d\n", status);
        printf("[In PARENT] I finished.\n");
    }

    return 0;
}
