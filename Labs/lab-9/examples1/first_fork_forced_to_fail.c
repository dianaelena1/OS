#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    int num_children = 0;

    while(1) {
        pid = fork();

        if (pid < 0) {
            perror("!!!! Eșec la fork \n");
            printf("Numărul total de procese copil create: %d\n", num_children);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Proces copil iese imediat pentru a nu continua loop-ul
	    printf("processul copil nr %d \n",num_children);
            exit(EXIT_SUCCESS);
        } else {
            // Proces părinte contorizează fiecare proces copil creat cu succes
            num_children++;
        }
    }

    return 0;
}
