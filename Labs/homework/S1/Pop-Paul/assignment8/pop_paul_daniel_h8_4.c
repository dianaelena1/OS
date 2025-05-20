//Implement the following structure of processes, in which the vertices indicate the communication between processes using pipes:

//![](Aspose.Words.8d0edccb-2f34-4293-95e6-66be4d8c1cbf.004.png)

//Process 1: read from stdin lines of at most 30 chars and write alternatively one line to each processes 2 and 3

//Process 2: replace digits with 9 and write result to process 4

//Process 3: replace letters with G and write result to process 4

//Process 4: print sorted what it receives
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

#define MAX_LINE 32
#define MAX_LINES 1000

// Compare function for qsort
int cmpfunc(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Process 2: Replace digits with '9'
void process2() {
    char buffer[MAX_LINE];
    fprintf(stderr, "[DEBUG] Process 2 started\n");
    while (fgets(buffer, MAX_LINE, stdin)) {
        fprintf(stderr, "[DEBUG] Process 2: Read line: %s", buffer);
        for (int i = 0; buffer[i]; i++) {
            if (isdigit(buffer[i])) buffer[i] = '9';
        }
        fprintf(stderr, "[DEBUG] Process 2: Modified line: %s", buffer);
        printf("%s", buffer);
        fflush(stdout);
        fprintf(stderr, "[DEBUG] Process 2: Sent modified line\n");
    }
    fprintf(stderr, "[DEBUG] Process 2 exiting\n");
}

// Process 3: Replace letters with 'G'
void process3() {
    char buffer[MAX_LINE];
    fprintf(stderr, "[DEBUG] Process 3 started\n");
    while (fgets(buffer, MAX_LINE, stdin)) {
        fprintf(stderr, "[DEBUG] Process 3: Read line: %s", buffer);
        for (int i = 0; buffer[i]; i++) {
            if (isalpha(buffer[i])) buffer[i] = 'G';
        }
        fprintf(stderr, "[DEBUG] Process 3: Modified line: %s", buffer);
        printf("%s", buffer);
        fflush(stdout);
        fprintf(stderr, "[DEBUG] Process 3: Sent modified line\n");
    }
    fprintf(stderr, "[DEBUG] Process 3 exiting\n");
}

// Process 4: Read from two pipes, sort, and print lines
void process4(int fd1, int fd2) {
    fprintf(stderr, "[DEBUG] Process 4 started\n");
    FILE *in1 = fdopen(fd1, "r");
    FILE *in2 = fdopen(fd2, "r");
    if (!in1 || !in2) {
        perror("fdopen failed in Process 4");
        exit(EXIT_FAILURE);
    }

    char *lines[MAX_LINES];
    int count = 0;
    char buffer[MAX_LINE];

    // Read all lines from pipe 1
    while (fgets(buffer, MAX_LINE, in1)) {
        lines[count] = strdup(buffer);
        if (!lines[count]) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        fprintf(stderr, "[DEBUG] Process 4: Read from pipe 1: %s", buffer);
        count++;
    }
    // Read all lines from pipe 2
    while (fgets(buffer, MAX_LINE, in2)) {
        lines[count] = strdup(buffer);
        if (!lines[count]) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        fprintf(stderr, "[DEBUG] Process 4: Read from pipe 2: %s", buffer);
        count++;
    }

    fprintf(stderr, "[DEBUG] Process 4: Total lines read: %d\n", count);

    // Sort lines alphabetically
    qsort(lines, count, sizeof(char *), cmpfunc);

    fprintf(stderr, "[DEBUG] Process 4: Sorted lines:\n");
    for (int i = 0; i < count; i++) {
        fprintf(stderr, "[DEBUG] %s", lines[i]);
        printf("%s", lines[i]);
        free(lines[i]);
    }
    fflush(stdout);
    fprintf(stderr, "[DEBUG] Process 4 exiting\n");
}

int main() {
    fprintf(stderr, "[DEBUG] Main process started\n");

    int p1_to_p2[2], p1_to_p3[2], p2_to_p4[2], p3_to_p4[2];

    if (pipe(p1_to_p2) == -1 || pipe(p1_to_p3) == -1 ||
        pipe(p2_to_p4) == -1 || pipe(p3_to_p4) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    // Fork Process 2
    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid2 == 0) {
        // Child Process 2
        dup2(p1_to_p2[0], STDIN_FILENO);
        dup2(p2_to_p4[1], STDOUT_FILENO);

        // Close unused pipe ends
        close(p1_to_p2[1]);
        close(p2_to_p4[0]);
        close(p1_to_p3[0]); close(p1_to_p3[1]);
        close(p3_to_p4[0]); close(p3_to_p4[1]);

        process2();
        exit(0);
    }
    fprintf(stderr, "[DEBUG] Forked Process 2\n");

    // Fork Process 3
    pid_t pid3 = fork();
    if (pid3 < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid3 == 0) {
        // Child Process 3
        dup2(p1_to_p3[0], STDIN_FILENO);
        dup2(p3_to_p4[1], STDOUT_FILENO);

        // Close unused pipe ends
        close(p1_to_p3[1]);
        close(p3_to_p4[0]);
        close(p1_to_p2[0]); close(p1_to_p2[1]);
        close(p2_to_p4[0]); close(p2_to_p4[1]);

        process3();
        exit(0);
    }
    fprintf(stderr, "[DEBUG] Forked Process 3\n");

    // Fork Process 4
    pid_t pid4 = fork();
    if (pid4 < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid4 == 0) {
        // Child Process 4
        close(p2_to_p4[1]);
        close(p3_to_p4[1]);

        // Close pipes unused by Process 4
        close(p1_to_p2[0]); close(p1_to_p2[1]);
        close(p1_to_p3[0]); close(p1_to_p3[1]);

        process4(p2_to_p4[0], p3_to_p4[0]);
        exit(0);
    }
    fprintf(stderr, "[DEBUG] Forked Process 4\n");

    // Parent (Process 1)
    close(p1_to_p2[0]);
    close(p1_to_p3[0]);
    close(p2_to_p4[0]); close(p2_to_p4[1]);
    close(p3_to_p4[0]); close(p3_to_p4[1]);

    FILE *out2 = fdopen(p1_to_p2[1], "w");
    FILE *out3 = fdopen(p1_to_p3[1], "w");

    if (!out2 || !out3) {
        perror("fdopen failed");
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "[DEBUG] Main process distributing lines\n");

    char line[MAX_LINE];
    int toggle = 0;
    while (fgets(line, MAX_LINE, stdin)) {
        fprintf(stderr, "[DEBUG] Main: Read line from stdin: %s", line);
        if (toggle) {
            fputs(line, out2);
            fprintf(stderr, "[DEBUG] Main: Sent line to Process 2\n");
        } else {
            fputs(line, out3);
            fprintf(stderr, "[DEBUG] Main: Sent line to Process 3\n");
        }
        fflush(out2);
        fflush(out3);
        toggle = 1 - toggle;
    }

    fclose(out2);
    fclose(out3);

    fprintf(stderr, "[DEBUG] Main: Waiting for child processes\n");

    // Wait for all child processes
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);
    waitpid(pid4, NULL, 0);

    fprintf(stderr, "[DEBUG] Main process exiting\n");
    return 0;
}
