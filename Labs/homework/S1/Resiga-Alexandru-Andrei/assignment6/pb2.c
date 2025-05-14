// pb2: Write a C Program that deletes from a file the bytes from even offsets.
// The name of the file is provided as a command line argument. 

#include <stdio.h>
#include <string.h>

int main (int argc, char* argv[]) {

    if (argc != 2) {
        printf("Please insert an argument!\n");
        return 1;
    }


    FILE* argfile = fopen(argv[1], "rb"); 
    if (!argfile) {
        printf("Couldn't open file!\n");
        return 1;
    } 

    FILE* temp = fopen("tmp.txt", "wb+");
    if (!temp) {
        printf("Couldn't create temporary file!\n");
        return 1;
    }   

    int byte;
    int offset = 0;

    while ((byte = fgetc(argfile)) != EOF) {
        if (offset % 2 == 1) {
            fputc(byte, temp);
        }
        ++offset;
    }

    fclose(argfile);

    rewind(temp);

    argfile = fopen(argv[1], "wb");
    if (!argfile) {
        printf("Couldn't open file for writing!\n");
        fclose(temp);
        return 1;
    }

    while ((byte = fgetc(temp)) != EOF) {
        fputc(byte, argfile);
    }

    fclose(argfile);
    fclose(temp);
    
    return 0;
}


