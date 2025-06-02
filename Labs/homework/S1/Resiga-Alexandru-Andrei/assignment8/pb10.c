/* 
Pb. 10: 
Parent process sends to the child a username, and the child 
sends back to the parent the number of processes run by the user.
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

#define MAX 100

int main() {
   
    mkfifo("fifoPC", 0666);
    mkfifo("fifoCP", 0666);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid > 0) {
        
        char username[MAX];
        printf("Enter username: ");  
        fgets(username, MAX, stdin);
        username[strcspn(username, "\n")] = '\0'; 

        int fd1 = open("fifoPC", O_WRONLY); 
        write(fd1, username, strlen(username)+1);
        close(fd1);

        int fd2 = open("fifoCP", O_RDONLY);
        int count;
        read(fd2, &count, sizeof(int));
        printf("Number of processes run by '%s': %d\n", username, count);
        close(fd2);

        wait(NULL); 
        unlink("fifoPC"); unlink("fifoCP");  
    } else {
      
        char username[MAX];
        int fd1 = open("fifoPC", O_RDONLY);
        read(fd1, username, MAX);
        close(fd1);

  
        char command[MAX + 50];
        snprintf(command, sizeof(command), "ps --no-headers -u %s | wc -l", username);

        FILE *fp = popen(command, "r");
        if (!fp) {
            perror("popen failed");
            exit(1);
        }

        int count;
        fscanf(fp, "%d", &count);
        pclose(fp);

        int fd2 = open("fifoCP", O_WRONLY);
        write(fd2, &count, sizeof(int));
        close(fd2);

        exit(0);
    }

    return 0;
}
