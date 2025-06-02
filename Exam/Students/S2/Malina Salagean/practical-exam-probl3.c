// Replace all punctuation with *  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    FILE *file , *temp;
    char sep[10]={'.',',','?','!',';',':'};
    char current[1];

    if (argc != 2) {
        fprintf(stderr, "You have to pass the filename as an argument");
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }

    temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Could not create temporary file.\n");
        fclose(file);
        return 1;
    }


    while (fscanf(file, "%c", current) == 1) {
        if (strcmp(current,sep)!= 0)
        {
            fprintf(temp, "%c ", current);
        }
        else
        {
            fprint(temp,"%c", '*');
        }

    }

    fclose(file);
    fclose(temp);

    remove(argv[2]);              
    rename("temp.txt", argv[2]);  

    printf("Text was updated in: \"%s\"", argv[1]);
}