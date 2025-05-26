//Write a C Program that receives as command line arguments a word and the name of a file. 
//The program will delete from the file the occurrences of the provided word.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *file, *temp;
    char word[100], current[100];
    
    if (argc != 3) {
        printf("Usage: %s <word> <filename>\n", argv[0]);
        return 1;
    }

    strcpy(word, argv[1]);

    file = fopen(argv[2], "r");
    if (file == NULL) {
        printf("Could not open file %s\n", argv[2]);
        return 1;
    }

    temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Could not create temporary file.\n");
        fclose(file);
        return 1;
    }


    while (fscanf(file, "%s", current) == 1) {
        if (strcmp(current, word) != 0) {
            fprintf(temp, "%s ", current);
        }
    }

    fclose(file);
    fclose(temp);

    remove(argv[2]);              
    rename("temp.txt", argv[2]);  

    printf("All occurrences of \"%s\" removed from %s\n", word, argv[2]);
    return 0;
}

