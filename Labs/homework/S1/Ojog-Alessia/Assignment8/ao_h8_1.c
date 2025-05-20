#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

//PB 2
//Implement the following structure of processes, in which the vertices indicate the communication between processes using pipes: 
//Process 1: read from stdin 10 bytes and write to each process 1,2 and 4
// Processes 2, 3: add digits and replace letters with ‘Z’
// Process 4: sort the result and print it 
//Process 5: print the information received by pipe

#define SIZE 11

void transform(char *data) {
    for (int i = 0; i < strlen(data); i++) {
        if (isdigit(data[i]))
            data[i] = ((data[i] - '0' + 1) % 10) + '0';
        else if (isalpha(data[i]))
            data[i] = 'Z';
    }
}

void sort_string(char *data) {
    int len = strlen(data);
    for (int i = 0; i < len-1; i++) {
        for (int j = i+1; j < len; j++) {
            if (data[i] > data[j]) {
                char tmp = data[i];
                data[i] = data[j];
                data[j] = tmp;
            }
        }
    }
}

int main() {
    char input[SIZE];
    printf("Enter 10 characters: ");
    fgets(input, SIZE, stdin);
    input[strcspn(input, "\n")] = '\0';

    int p1_to_p2[2], p1_to_p3[2], p1_to_p4[2], p4_to_p5[2];
    pipe(p1_to_p2);
    pipe(p1_to_p3);
    pipe(p1_to_p4);
    pipe(p4_to_p5);

    pid_t pid2 = fork();
    if (pid2 == 0) {
        close(p1_to_p2[1]);
        char buffer[SIZE];
        read(p1_to_p2[0], buffer, SIZE);
        transform(buffer);
        printf("Process 2 Output: %s\n", buffer);
        exit(0);
    }

    pid_t pid3 = fork();
    if (pid3 == 0) {
        
        close(p1_to_p3[1]);
        char buffer[SIZE];
        read(p1_to_p3[0], buffer, SIZE);
        transform(buffer);
        printf("Process 3 Output: %s\n", buffer);
        exit(0);
    }

    pid_t pid4 = fork();
    if (pid4 == 0) {
        
        close(p1_to_p4[1]);
        close(p4_to_p5[0]);
        char buffer[SIZE];
        read(p1_to_p4[0], buffer, SIZE);
        sort_string(buffer);
        printf("Process 4 Sorted Output: %s\n", buffer);
        write(p4_to_p5[1], buffer, SIZE);
        exit(0);
    }

    pid_t pid5 = fork();
    if (pid5 == 0) {
        
        close(p4_to_p5[1]);
        char buffer[SIZE];
        read(p4_to_p5[0], buffer, SIZE);
        printf("Process 5 Final Output: %s\n", buffer);
        exit(0);
    }

    close(p1_to_p2[0]);
    close(p1_to_p3[0]);
    close(p1_to_p4[0]);
    close(p4_to_p5[0]);
    close(p4_to_p5[1]);

    write(p1_to_p2[1], input, SIZE);
    write(p1_to_p3[1], input, SIZE);
    write(p1_to_p4[1], input, SIZE);

    for (int i = 0; i < 4; i++) wait(NULL);

    return 0;
}
