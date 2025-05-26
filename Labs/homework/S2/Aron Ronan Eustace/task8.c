#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <ctype.h>

/*3 Implement the following structure of processes, in which the vertices indicate the communication between processes using FIFO: 
Process 1: write to 3 what is read from stdin Process 2: read from 3 and replace all vowels with digits (aeiou->12345) Process 3: read from 1 and write to 2 only alphanumeric lines.*/

int main() {
    mkfifo("fifo13", 0666);
    mkfifo("fifo32", 0666);

    if (fork() == 0) {
        // Process 1: read from stdin, send to 3
        FILE *f = fopen("fifo13", "w");
        char line[200];
        if (fgets(line, sizeof(line), stdin)) fputs(line, f);
        fclose(f);
        exit(0);
    }

    if (fork() == 0) {
        // Process 2: read from 3, replace vowels
        FILE *f = fopen("fifo32", "r");
        char c;
        while ((c = fgetc(f)) != EOF) {
            if (c == 'a' || c == 'A') c = '1';
            else if (c == 'e' || c == 'E') c = '2';
            else if (c == 'i' || c == 'I') c = '3';
            else if (c == 'o' || c == 'O') c = '4';
            else if (c == 'u' || c == 'U') c = '5';
            putchar(c);
        }
        fclose(f);
        exit(0);
    }

    if (fork() == 0) {
        // Process 3: filter alphanumeric lines
        FILE *in = fopen("fifo13", "r");
        FILE *out = fopen("fifo32", "w");
        char line[200];
        if (fgets(line, sizeof(line), in)) {
            int ok = 1;
            for (int i = 0; line[i] && line[i] != '\n'; i++) {
                if (!isalnum(line[i])) {
                    ok = 0;
                    break;
                }
            }
            if (ok) fputs(line, out);
        }
        fclose(in);
        fclose(out);
        exit(0);
    }

    // Parent
    wait(NULL);
    wait(NULL);
    wait(NULL);
    unlink("fifo13");
    unlink("fifo32");
    return 0;
}
FFđ
