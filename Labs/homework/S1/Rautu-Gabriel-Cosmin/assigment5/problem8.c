#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fin, *fout;
    char *inname, tmpname[FILENAME_MAX];
    int num;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input-file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    inname = argv[1];
   
   snprintf(tmpname, sizeof(tmpname), "%s.tmp", inname);

    fin = fopen(inname, "r");
    if (!fin) {
        perror("fopen input");
        return EXIT_FAILURE;
    }

    fout = fopen(tmpname, "w");
    if (!fout) {
        perror("fopen output");
        fclose(fin);
        return EXIT_FAILURE;
    }

    while (fscanf(fin, "%d", &num) == 1) {
        if (num % 2 != 0) {
            fprintf(fout, "%d ", num);
        }
    }

    fclose(fin);
    fclose(fout);

    if (remove(inname) != 0) {
        perror("remove original");
        return EXIT_FAILURE;
    }
    if (rename(tmpname, inname) != 0) {
        perror("rename temp");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
