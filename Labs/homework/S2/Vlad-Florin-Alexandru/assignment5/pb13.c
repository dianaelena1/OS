// |13|Write a C Program that receives as command line arguments 
// a name of a file and several words. The program will print at stdout the content of the file, deleting the occurrences of all words provided as arguments.   |


#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s filename word1 [word2 ...]\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("Error opening file");
        return 1;
    }

    char buf[256];
    while (fscanf(f, "%255s", buf) == 1) {
        int remove = 0;
        for (int i = 2; i < argc; i++) {
            if (strcmp(buf, argv[i]) == 0) {
                remove = 1;
                break;
            }
        }
        if (!remove) {
            printf("%s ", buf);
        }
    }

    fclose(f);
    return 0;
}
