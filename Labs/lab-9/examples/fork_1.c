/* fork_1.c
Create a child process using fork()
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
int a = 5;
int pid = fork(); // try to create a child process
if (pid == -1) // fork() has failed
{
perror("fork() error\n");
exit(EXIT_FAILURE); //exit(1);
}
if (pid == 0) // in the child process
{
printf("[In CHILD] My PID is %d. My parent PID is %d.\n", getpid(), getppid());
exit(EXIT_SUCCESS); //exit(0);
}
else // in the parent process
{
printf("[In PARENT] My PID is %d. My child PID is %d.\n", getpid(), pid);
int status;
wait(&status); // wait(0);
}
return 0;
}