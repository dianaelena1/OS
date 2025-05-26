#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    char *name = argv[1], tmp[FILENAME_MAX];
    sprintf(tmp, "%s.tmp", name);
    FILE *in = fopen(name, "r"), *out = fopen(tmp, "w");
    if (!in || !out) return 1;
    int x;
    while (fscanf(in, "%d", &x) == 1)
        if (x % 2) fprintf(out, "%d ", x);
    fclose(in);
    fclose(out);
    remove(name);
    rename(tmp, name);
    return 0;
}
