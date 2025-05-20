//       1
//      / \
//     2   3

// Process 1: Reads from stdin. Sends input to Process 3 through a pipe

// Process 3: Filters and forwards only alphanumeric lines to Process 2

// Process 2: Replaces all vowels (a e i o u) with digits (1 2 3 4 5). Prints the result to stdout

// => 2 pipes needed:
// pipe13: P1 → P3

// pipe32: P3 → P2

// => 3 processes total:
// P1 (parent)

// P2 and P3 (children from fork())

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

// Helper: is line alphanumeric
int is_alphanumeric(const char *s) {
    for (int i = 0; s[i]; i++) {
        if (!isalnum(s[i]) && !isspace(s[i])) return 0;
    }
    return 1;
}

// Helper: replace vowels
void replace_vowels(char *s) {
    for (int i = 0; s[i]; i++) {
        switch (s[i]) {
            case 'a': s[i] = '1'; break;
            case 'e': s[i] = '2'; break;
            case 'i': s[i] = '3'; break;
            case 'o': s[i] = '4'; break;
            case 'u': s[i] = '5'; break;
        }
    }
}

int main() {
    int pipe13[2], pipe32[2];
    pipe(pipe13);
    pipe(pipe32);

    pid_t pid2 = fork();
    if (pid2 == 0) {
        // Process 2: read from pipe32 and replace vowels (checks if the line is alphanumeric and, if so, sends it to Process 2.)
        close(pipe32[1]);
        char buffer[256];
        int n = read(pipe32[0], buffer, sizeof(buffer));
        buffer[n] = '\0';
        replace_vowels(buffer);
        printf("Process 2: %s\n", buffer);
        close(pipe32[0]);
        exit(0);
    }

    pid_t pid3 = fork();
    if (pid3 == 0) {
        // Process 3: filter alphanumeric lines and send to Process 2 (receives the line, replaces all vowels with digits (a→1, e→2, etc.), and prints it.)
        close(pipe13[1]); // Close write end
        close(pipe32[0]); // Close read end

        char buffer[256];
        int n = read(pipe13[0], buffer, sizeof(buffer));
        buffer[n] = '\0';

        if (is_alphanumeric(buffer)) {
            write(pipe32[1], buffer, strlen(buffer));
        }

        close(pipe13[0]);
        close(pipe32[1]);
        exit(0);
    }

    // Process 1: Parent (reads user input and sends it to Process 3)
    close(pipe13[0]); // Close read end
    close(pipe32[0]); close(pipe32[1]); // Not used here

    char input[256];
    printf("Process 1: Enter a line: ");
    fgets(input, sizeof(input), stdin);
    write(pipe13[1], input, strlen(input));
    close(pipe13[1]);

    wait(NULL); wait(NULL);
    return 0;
}
