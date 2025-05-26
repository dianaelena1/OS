//Pb 2 - Implement the following structure of processes, in which the vertices
// indicate the communication between processes using pipes:

//![](Aspose.Words.8d0edccb-2f34-4293-95e6-66be4d8c1cbf.002.png)

//Process 1: read from stdin 10 bytes and write to each process 1,2 and 4
//Processes 2, 3: add digits and replace letters with ‘Z’
//Process 4: sort the result and print it
//Process 5: print the information received by pipe


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

void replace_and_sum(char *buf, int *sum) {
    *sum = 0;
    for (int i = 0; i < 10; i++) {
        if (isdigit(buf[i])) {
            *sum += buf[i] - '0';
        } else if (isalpha(buf[i])) {
            buf[i] = 'Z';
        }
    }
}

int main() {
    int p1_to_2[2], p1_to_3[2], p1_to_4[2], p2_to_5[2], p3_to_5[2];
    if (pipe(p1_to_2) < 0 || pipe(p1_to_3) < 0 || pipe(p1_to_4) < 0 || pipe(p2_to_5) < 0 || pipe(p3_to_5) < 0) {
        perror("pipe error");
        exit(1);
    }

    pid_t pids[5];
    for (int i = 0; i < 5; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork error");
            exit(1);
        }
        if (pids[i] == 0) {
            if (i == 0) { // Process 1
                close(p1_to_2[0]); close(p1_to_3[0]); close(p1_to_4[0]);
                char buf[11];
                read(STDIN_FILENO, buf, 10);
                buf[10] = '\0';
                write(p1_to_2[1], buf, 10);
                write(p1_to_3[1], buf, 10);
                write(p1_to_4[1], buf, 10);
            } else if (i == 1) { // Process 2
                close(p1_to_2[1]); close(p2_to_5[0]);
                char buf[11];
                int sum;
                read(p1_to_2[0], buf, 10);
                buf[10] = '\0';
                replace_and_sum(buf, &sum);
                write(p2_to_5[1], buf, 10);
                write(p2_to_5[1], &sum, sizeof(int));
            } else if (i == 2) { // Process 3
                close(p1_to_3[1]); close(p3_to_5[0]);
                char buf[11];
                int sum;
                read(p1_to_3[0], buf, 10);
                buf[10] = '\0';
                replace_and_sum(buf, &sum);
                write(p3_to_5[1], buf, 10);
                write(p3_to_5[1], &sum, sizeof(int));
            } else if (i == 3) { // Process 4
                close(p1_to_4[1]);
                char buf[11];
                read(p1_to_4[0], buf, 10);
                buf[10] = '\0';

                for (int j = 0; j < 9; j++)
                    for (int k = 0; k < 9 - j; k++)
                        if (buf[k] > buf[k + 1]) {
                            char t = buf[k];
                            buf[k] = buf[k + 1];
                            buf[k + 1] = t;
                        }
                printf("Process 4: ");
                for (int j = 0; j < 10; j++) {
                    printf("%c", buf[j]);
                }
                printf("\n");
            } else if (i == 4) { // Process 5
                close(p2_to_5[1]); close(p3_to_5[1]);
                char buf_from_2[11], buf_from_3[11];
                int sum_from_2, sum_from_3;
                read(p2_to_5[0], buf_from_2, 10);
                buf_from_2[10] = '\0';
                read(p2_to_5[0], &sum_from_2, sizeof(int));
                read(p4_to_5[0], buf_from_3, 10);
                buf_from_3[10] = '\0';
                read(p3_to_5[0], &sum_from_3, sizeof(int));
                printf("Received from Process 2: %s, Sum: %d\n", buf_from_2, sum_from_2);
                printf("Received from Process 3: %s, Sum: %d\n", buf_from_3, sum_from_3);
            }
            exit(0);
        }
    }

    for (int i = 0; i < 5; i++)
        wait(NULL);
    return 0;
}