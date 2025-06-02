//Write a C program that replaces all punctuation characters in a file with the character *,
//and prints the result.


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, char *argv[]) {
    if (argc != 2 ){
        printf("Usage, %s <filename> \n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL){
        perror("Error opening file");
        return 1;
    }

    int ch;
    while ((ch=fgetc(file)) != EOF){
        if (ispunct(ch)){
            putchar('*');
        }
        else{
            putchar(ch);  
        }
    }
    
    fclose(file);
    return 0;
    
}


