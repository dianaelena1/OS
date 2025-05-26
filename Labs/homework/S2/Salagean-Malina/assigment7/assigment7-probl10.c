//Parent process sends to the child a username,
//and the child sends back to the parent the number of processes run by the user.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     
#include <sys/wait.h>   

int main() {
    int to_child[2], to_parent[2];
    char username[100];

    if (pipe(to_child) == -1 || pipe(to_parent) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    // CHILD PROCESS
    else if (pid == 0) {
        close(to_child[1]); 
        close(to_parent[0]); 

        char user[100];
        read(to_child[0], user, sizeof(user));
        close(to_child[0]); 

        char command[150];
        snprintf(command, sizeof(command), "ps -u %s | wc -l", user);

        FILE *fp = popen(command, "r");
        if (fp == NULL) {
            perror("popen failed");
            exit(1);
        }

        char buffer[16];
        fgets(buffer, sizeof(buffer), fp);
        int count = atoi(buffer) - 1;  
        pclose(fp);

        write(to_parent[1], &count, sizeof(int));
        close(to_parent[1]);

        exit(0); 
    }

    // PARENT PROCESS
    else {
        close(to_child[0]);  
        close(to_parent[1]); 

        printf("Enter username: ");
        scanf("%s", username);

        write(to_child[1], username, strlen(username) + 1);
        close(to_child[1]);  

        wait(NULL);

        int count;
        read(to_parent[0], &count, sizeof(int));
        close(to_parent[0]);

        printf("User '%s' is running %d processes.\n", username, count);
    }

    return 0;
}
