// Ex1
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return 0;
}

//Ex2
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s filename text\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "a");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "%s\n", argv[2]);
    fclose(file);
    return 0;
}
//Ex3
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int ch, inWord = 0;
    int chars = 0, words = 0, lines = 0;

    while ((ch = fgetc(file)) != EOF) {
        chars++;
        if (ch == '\n') lines++;

        if (isspace(ch)) {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            words++;
        }
    }

    printf("Characters: %d\nWords: %d\nLines: %d\n", chars, words, lines);
    fclose(file);
    return 0;
}
//Ex4
#include <stdio.h>

int main() {
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }

    char buffer[100];
    for (int i = 0; i < 3; i++) {
        printf("Enter line %d: ", i + 1);
        fgets(buffer, sizeof(buffer), stdin);
        fputs(buffer, file);
    }

    fclose(file);
    return 0;
}
//Ex5
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s source.txt destination.txt\n", argv[0]);
        return 1;
    }

    FILE *src = fopen(argv[1], "r");
    FILE *dest = fopen(argv[2], "w");

    if (src == NULL || dest == NULL) {
        perror("Error opening file");
        return 1;
    }

    int ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);
    return 0;
}



/* fork_1.c
Create a child process using fork()
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
int a = 5;
int pid = fork(); // try to create a child process
if (pid == -1) // fork() has failed
{
perror("fork() error\n");
exit(EXIT_FAILURE); //exit(1);
}
if (pid == 0) // in the child process
{
printf("[In CHILD] My PID is %d. My parent PID is %d.\n", getpid(), getppid());
exit(EXIT_SUCCESS); //exit(0);
}
else // in the parent process
{
printf("[In PARENT] My PID is %d. My child PID is %d.\n", getpid(), pid);
int status;
wait(&status); // wait(0);
}
return 0;
}







