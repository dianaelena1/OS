//Write a C Program that receives as command line arguments two words and the name of a file. The program will print at stdout the content of the file, replacing the occurrences of the first word with the second.  

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *f;
    char line[1024];

    if (argc != 4) {
        printf("Usage: %s oldWord newWord filename\n", argv[0]);
        return 1;
    }

    char *old = argv[1];
    char *new = argv[2];
    char *filename = argv[3];

    f = fopen(filename, "r");
    if (!f) {
        printf("Cannot open file.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), f)) {
        char *pos = line;
        while ((pos = strstr(pos, old))) {
            fwrite(line, 1, pos - line, stdout);
            
            printf("%s", new);
            
            pos += strlen(old);
            
            memmove(line, pos, strlen(pos) + 1);
            pos = line;
        }
        printf("%s", line);
    }

    fclose(f);
    return 0;
}

