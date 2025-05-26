//Parent process sends to the child a name of a Unix server, and the child sends back 
//to the parent the list of all usernames that work in that moment on the server. C-pipe.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUF_SIZE 256

int main() {
    int p2c[2];  
    int c2p[2]; 
    pid_t pid;
    char server[BUF_SIZE];

    if (pipe(p2c) == -1 || pipe(c2p) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
      
        close(p2c[1]);        
        close(c2p[0]);        

        
        ssize_t n = read(p2c[0], server, BUF_SIZE-1);
        if (n <= 0) {
            perror("child read");
            exit(EXIT_FAILURE);
        }
        server[n] = '\0';
      
        char *newline = strchr(server, '\n');
        if (newline) *newline = '\0';

        if (dup2(c2p[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(c2p[1]);
        close(p2c[0]);

        execlp("rusers", "rusers", server, (char *)NULL);
        
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent
        close(p2c[0]);          
        close(c2p[1]);          

        printf("Enter Unix server name: ");
        if (!fgets(server, BUF_SIZE, stdin)) {
            fprintf(stderr, "Failed to read server name\n");
            exit(EXIT_FAILURE);
        }
        write(p2c[1], server, strlen(server));
        close(p2c[1]);

        
        char buf[BUF_SIZE];
        ssize_t m;
        printf("Users currently logged in on %s:\n", server);
        while ((m = read(c2p[0], buf, BUF_SIZE-1)) > 0) {
            buf[m] = '\0';
            fputs(buf, stdout);
        }
        if (m < 0) perror("parent read");

        close(c2p[0]);
        wait(NULL); 
    }

    return 0;
}
