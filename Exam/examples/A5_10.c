#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        return 1;
    }
    
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    
    while ((read = getline(&line, &len, file)) != -1) 
    {
        size_t start = 0;
        while (start < read && (line[start] == ' ' || line[start] == '\t' || line[start] == '\n'))
        {
            start++;
        }

        size_t end = read - 1;
        while (end > start && (line[end] == ' ' || line[end] == '\t' || line[end] == '\n')) 
        {
            end--;
        }
        
        if (start <= end) 
        {
            for (size_t i = start; i <= end; i++) 
            {
                putchar(line[i]);
            }
            putchar('\n');
        }
    }

    if (ferror(file)) 
    {
        perror("Error reading file");
    }

    fclose(file);
    free(line);

    return 0;
}
