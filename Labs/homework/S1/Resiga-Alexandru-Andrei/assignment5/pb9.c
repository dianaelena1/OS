// Write a C Program that receives as command line arguments two file names
// and merges the lines of the two files (that are already sorted).


#include <stdio.h>
#include <string.h>

#define MAX_LINE 500

int main (int argc, char* argv[]) {

    if (argc != 4) {
        printf("Please insert an argument!\n");
        return 1;
    }

    FILE* f1 = fopen(argv[1], "r");
    FILE* f2 = fopen(argv[2], "r"); 
    FILE* f3 = fopen(argv[3], "w");

    if (!f1 || !f2 || !f3) {
        printf("Could not open files!");
        return 1;
    }

    char line1[MAX_LINE], line2[MAX_LINE];
    char *res1, *res2;
    
    res1 = fgets(line1, MAX_LINE, f1);
    res2 = fgets(line2, MAX_LINE, f2);


    while (res1 != NULL && res2 != NULL) {
        if (stricmp(res1, res2) == 0) {
            fputs(res1, f3);
            fputs(res2, f3);
            fputs(res1, stdout);
            fputs(res2, stdout);
            res1 = fgets(line1, MAX_LINE, f1);
            res2 = fgets(line2, MAX_LINE, f2);
        } else if (stricmp(res1, res2) < 0) {
            fputs(res1, f3);
            fputs(res1, stdout);
            res1 = fgets(line1, MAX_LINE, f1);
        } else if (stricmp(res1, res2) > 0) {
            fputs(res2, f3);
            fputs(res2, stdout);
            res2 = fgets(line2, MAX_LINE, f2);
        }
    }


    while (res2 != NULL) {
        fputs(res2, f3);
        fputs(res2, stdout);
        res2 = fgets(line2, MAX_LINE, f2);
    }

    while (res1 != NULL) {
        fputs(res1, f3);
        fputs(res1, stdout);
        res1 = fgets(line1, MAX_LINE, f1);
    }



    fclose(f1);
    fclose(f2);
    fclose(f3);
    return 0;
}