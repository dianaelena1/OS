#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_line_without_words(char *line, int argc, char *argv[])
{
    char *word = strtok(line, " ");
    int word_printed = 0;
    while (word != NULL)
    {
        int i;
        for (i = 2; i < argc; i++)
        {
            if (strcmp(word, argv[i]) == 0)
            {
                break;
            }
        }
        if (i == argc)
        {
            if (word_printed)
                printf(" ");
            printf("%s", word);
            word_printed = 1;
        }
        word = strtok(NULL, " ");
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <filename> <word1> <word2> ...\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Failed to open file\n");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1)
        print_line_without_words(line, argc, argv);

    fclose(file);
    if (line)
        free(line);

    return 0;
}