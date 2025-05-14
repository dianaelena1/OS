/*
Implement the following structure of processes, in which the vertices indicate the communication between processes using pipes:
Process 1: write to 3 what is read from stdin
Process 2: read from 3 and replace all vowels with digits (aeiou->12345)
Process 3: read from 1 and write to 2 only alphanumeric lines
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_LINE 1000 


static int is_alnum_line(const char *s, size_t len) {
    for (size_t i = 0; i < len && s[i] != '\n'; ++i)
        if (!isalnum(s[i]))
            return 0;
    return 1;
}


static void replace_vowels(char *buf, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        switch (buf[i]) {
            case 'a': case 'A': buf[i] = '1'; break;
            case 'e': case 'E': buf[i] = '2'; break;
            case 'i': case 'I': buf[i] = '3'; break;
            case 'o': case 'O': buf[i] = '4'; break;
            case 'u': case 'U': buf[i] = '5'; break;
        }
    }
}

int main(void) {
    int pipe13[2], pipe32[2];

    if (pipe(pipe13) == -1 || pipe(pipe32) == -1) {
        perror("pipe error!");
        return 1;
    }

    pid_t p1 = fork();
    if (p1 < 0) { 
        perror("fork error!"); 
        return 1; 
    }
    /* p1 */
    if (p1 == 0) {                   
        close(pipe13[0]);            
        close(pipe32[0]); 
        close(pipe32[1]);

        char buf[1000];
        ssize_t n;
        while ((n = read(0, buf, sizeof buf)) > 0) {
            write(pipe13[1], buf, n);
        }

        close(pipe13[1]);
        exit(EXIT_SUCCESS);
    }


    close(pipe13[1]);

    /* p3 */
    pid_t p3 = fork();
    if (p3 < 0) {
        perror("fork"); 
        return 1; 
    }

    if (p3 == 0) {                   
        close(pipe32[0]);           
        close(pipe13[1]);
        
        char line[MAX_LINE];
        int len = 0;
        char ch;

        while (read(pipe13[0], &ch, 1) == 1) {
            line[len++] = ch;

            if (ch == '\n' || len == MAX_LINE) {
                if (is_alnum_line(line, len))
                    write(pipe32[1], line, len);
                len = 0;
            }
        }

        if (len && is_alnum_line(line, len))
            write(pipe32[1], line, len);

        close(pipe13[0]);
        close(pipe32[1]); 
        exit(EXIT_SUCCESS);
    }

    /* p2 */
    pid_t p2 = fork();
    if (p2 < 0) { 
        perror("fork"); 
        return 1; 
    }

    if (p2 == 0) {                   
        close(pipe13[0]);            
        close(pipe13[1]);
        close(pipe32[1]);

        char buf[1000];
        ssize_t n;
        while ((n = read(pipe32[0], buf, sizeof buf)) > 0) {
            replace_vowels(buf, n);
            write(1, buf, n);
        }

        close(pipe32[0]);
        exit(EXIT_SUCCESS);
    }

    
    close(pipe13[0]); close(pipe13[1]);
    close(pipe32[0]); close(pipe32[1]);

    
    while (wait(NULL) > 0);

    return 0;
}
