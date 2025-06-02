// C program that computes the product of all elements in a fixed-size integer array using two processes.

// - array statically defined in the program (6 elements)
// - parent will create one child process using fork()
// - child process computes the product of the 1st half of the array and return the result using _exit()
// - parent process coputes the product of the 2nd half of the array, waits for the child, and multiply the two partial results
// program prints the final product of all elements in the array.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int array[6] = {1, 2, 3, 4, 5, 6};
int p1=1, p2=1, prod=1;

int main(int argc, char *argv[]) {

    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork failed");
        return 1;
    } 
    else if (pid == 0) {
        for (int i=0;i<=2;i++)
        {
            p1 *= array[i];
        }
        printf("p1 = %d\n", p1);

        _exit(0);
    } 
    else {
        for (int i=3;i<=6;i++)
        {
            p2 *= array[i];
        }
        printf("p2 = %d\n", p2);

        printf("Parent process returned the product of the 2nd half of the array.\n");
        

        wait(NULL);
        printf("Child process returned the product of the 1st half of the array.\n");

        prod = p1 * p2;

        printf("prod = %d\n", prod);
    }

    return 0;
}
