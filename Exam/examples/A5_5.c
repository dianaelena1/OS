#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char *env[]){

    if (argc != 4)
    {
        printf("Error: Insufficient number of arguments.\n");
        printf("Usage: tema5 file_name word1 word2\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", argv[1]);
        return 2;
    }

    char word1[100], word2[100];
    strcpy(word1, argv[2]);
    strcpy(word2, argv[3]);

    char buffer[100];


    // read the entire file and replace word1 with word2
    while (fscanf(file, "%s", buffer) != EOF)
    {
        if (strcmp(buffer, word1) == 0)
        {
            printf("%s ", word2);
        }
        else
        {
            printf("%s ", buffer);
        }
    }

    fclose(file);


    return 0;
}