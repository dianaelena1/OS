//Pb 2 - Implement the following structure of processes, in which the vertices
// indicate the communication between processes using pipes:

//![](Aspose.Words.8d0edccb-2f34-4293-95e6-66be4d8c1cbf.002.png)

//Process 1: read from stdin 10 bytes and write to each process 1,2 and 4
//Processes 2, 3: add digits and replace letters with ‘Z’
//Process 4: sort the result and print it
//Process 5: print the information received by pipe


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUF_SIZE 100

void error(const char *msg) {
    perror(msg);
    exit(1);
}

void replace_and_sum(char *buf, char *out_buf) {
    int sum = 0;
    for (int i = 0; buf[i]; i++) {
        if (isdigit(buf[i])) {
            sum += buf[i] - '0';
        } else if (isalpha(buf[i])) {
            buf[i] = 'Z';
        }
    }
    snprintf(out_buf, BUF_SIZE, "%s\nSum: %d", buf, sum);
}

void sort_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len - 1; i++)
        for (int j = i + 1; j < len; j++)
            if (str[i] > str[j]) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
}

int main() {
    int p1_to_2[2], p1_to_4[2], p1_to_5[2], p2_to_3[2], p3_to_4[2];
    char buffer[BUF_SIZE];

    pipe(p1_to_2);
    pipe(p1_to_4);
    pipe(p1_to_5);
    pipe(p2_to_3);
    pipe(p3_to_4);

    // Process 1
    pid_t pid1 = fork();
    if (pid1 == 0) {
        close(p1_to_2[0]); close(p1_to_4[0]); close(p1_to_5[0]);
        printf("Process 1: Enter 10 characters:\n");
        fgets(buffer, 11, stdin); // read 10 chars

        write(p1_to_2[1], buffer, strlen(buffer) + 1);
        write(p1_to_4[1], buffer, strlen(buffer) + 1);
        write(p1_to_5[1], buffer, strlen(buffer) + 1);

        exit(0);
    }

    // Process 2
    pid_t pid2 = fork();
    if (pid2 == 0) {
        close(p1_to_2[1]); close(p2_to_3[0]);

        read(p1_to_2[0], buffer, BUF_SIZE);
        char modified[BUF_SIZE];
        replace_and_sum(buffer, modified);
        write(p2_to_3[1], modified, strlen(modified) + 1);

        exit(0);
    }

    // Process 3
    pid_t pid3 = fork();
    if (pid3 == 0) {
        close(p2_to_3[1]); close(p3_to_4[0]);

        read(p2_to_3[0], buffer, BUF_SIZE);
        write(p3_to_4[1], buffer, strlen(buffer) + 1);

        exit(0);
    }

    // Process 4
    pid_t pid4 = fork();
    if (pid4 == 0) {
        close(p1_to_4[1]); close(p3_to_4[1]);

        char from_p1[BUF_SIZE], from_p3[BUF_SIZE];
        read(p1_to_4[0], from_p1, BUF_SIZE);
        read(p3_to_4[0], from_p3, BUF_SIZE);

        strcat(from_p1, from_p3);
        sort_string(from_p1);

        printf("Process 4 (sorted result): %s\n", from_p1);
        exit(0);
    }

    // Process 5
    pid_t pid5 = fork();
    if (pid5 == 0) {
        close(p1_to_5[1]);
        read(p1_to_5[0], buffer, BUF_SIZE);
        printf("Process 5 received: %s\n", buffer);
        exit(0);
    }

    close(p1_to_2[0]); close(p1_to_2[1]);
    close(p1_to_4[0]); close(p1_to_4[1]);
    close(p1_to_5[0]); close(p1_to_5[1]);
    close(p2_to_3[0]); close(p2_to_3[1]);
    close(p3_to_4[0]); close(p3_to_4[1]);

    for (int i = 0; i < 5; i++) wait(NULL);

    return 0;
}
