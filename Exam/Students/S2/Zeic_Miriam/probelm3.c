//Write a C program that replaces all punctuation characters in a file 
//with the character * and prints the result.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 1024

int main(int argc, char *argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *f = fopen(argv[1], "r");
    if(!f){
        perror(argv[1]);
        return EXIT_FAILURE;
    }
    
    char line[MAXLINE];
    char *l=fgets(line,sizeof(line), f);

    char code[MAXLINE];

    while(l){
        for(int i=0; i<sizeof(line);i++)
        {    
            if(ispunct(line[i])!=0)
            {
                line[i]='*';
            }
        
        }
        fputs(line,stdout);
        l=fgets(line, sizeof(line), f);     
        
    }
    fclose(f);
    return EXIT_SUCCESS;

}
