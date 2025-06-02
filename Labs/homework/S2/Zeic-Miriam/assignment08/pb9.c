//Parent process sends to the child a name of a Unix server, and the child sends 
//back to the parent the list of all usernames that work in that moment on the server. C-fifo

// user_fifo.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define FIFO_P2C "/tmp/fifo_p2c"
#define FIFO_C2P "/tmp/fifo_c2p"
#define BUF_SIZE 256

int main(void) {
    
    if (mkfifo(FIFO_P2C, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo " FIFO_P2C);
        exit(EXIT_FAILURE);
    }
    if (mkfifo(FIFO_C2P, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo " FIFO_C2P);
        unlink(FIFO_P2C);
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        unlink(FIFO_P2C);
        unlink(FIFO_C2P);
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
      
        int fd_read = open(FIFO_P2C, O_RDONLY);
        if (fd_read < 0) {
            perror("child open P2C");
            exit(EXIT_FAILURE);
        }

    
        char server[BUF_SIZE];
        ssize_t n = read(fd_read, server, sizeof(server)-1);
        close(fd_read);
        if (n <= 0) {
            fprintf(stderr, "child: failed to read server name\n");
            exit(EXIT_FAILURE);
        }
        server[n] = '\0';
        if (server[n-1] == '\n') server[n-1] = '\0';

      
        int fd_write = open(FIFO_C2P, O_WRONLY);
        if (fd_write < 0) {
            perror("child open C2P");
            exit(EXIT_FAILURE);
        }

       
        if (dup2(fd_write, STDOUT_FILENO) < 0) {
            perror("child dup2");
            close(fd_write);
            exit(EXIT_FAILURE);
        }
        close(fd_write);

        
        execlp("rusers", "rusers", server, (char *)NULL);
        
        perror("child execlp");
        exit(EXIT_FAILURE);

    } else {
        
        char server[BUF_SIZE];
        printf("Enter Unix server name: ");
        if (!fgets(server, sizeof(server), stdin)) {
            fprintf(stderr, "parent: failed to read input\n");
            goto cleanup;
        }

        
        int fd_write = open(FIFO_P2C, O_WRONLY);
        if (fd_write < 0) {
            perror("parent open P2C");
            goto cleanup;
        }
        write(fd_write, server, strlen(server));
        close(fd_write);

        
        int fd_read = open(FIFO_C2P, O_RDONLY);
        if (fd_read < 0) {
            perror("parent open C2P");
            goto cleanup;
        }
        printf("Users currently logged in on %s", server);
        char buf[BUF_SIZE];
        ssize_t m;
        while ((m = read(fd_read, buf, sizeof(buf)-1)) > 0) {
            buf[m] = '\0';
            fputs(buf, stdout);
        }
        if (m < 0) perror("parent read");
        close(fd_read);

        
        wait(NULL);
    }

cleanup:
   
    unlink(FIFO_P2C);
    unlink(FIFO_C2P);
    return 0;
}
