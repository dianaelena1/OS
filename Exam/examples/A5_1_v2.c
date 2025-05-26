#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "You have to pass the filename as an argument");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

  char c;
  char previous;

    while ((c = fgetc(file)) != EOF) {
        if (c != '\n') {
            printf("%c", c);
        } else {
            if (previous != '\n') { // Print an extra newline only if the line is not empty
                printf("\n\n");
        }
        }
        previous = c;
    }
    fclose(file);
    return 0;
}