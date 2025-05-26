#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    FILE *f = fopen(argv[1], "r"), *t = tmpfile();
    int n;
    while (fscanf(f, "%d", &n) == 1)
        if (n % 2) fprintf(t, "%d ", n);
    freopen(argv[1], "w", f);
    rewind(t);
    while (fscanf(t, "%d", &n) == 1)
        fprintf(f, "%d ", n);
    fclose(f), fclose(t);
    return 0;
}
