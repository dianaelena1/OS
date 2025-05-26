#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    int p2c[2], c2p[2];
    pipe(p2c);
    pipe(c2p);
    if (fork() == 0) {
        close(p2c[1]);
        close(c2p[0]);
        char dir[1024];
        read(p2c[0], dir, sizeof(dir));
        DIR *d = opendir(dir);
        struct dirent *e;
        struct stat st;
        long sum = 0;
        while ((e = readdir(d))) {
            if (e->d_name[0] == '.') continue;
            char path[2048];
            snprintf(path, sizeof(path), "%s/%s", dir, e->d_name);
            if (stat(path, &st) == 0 && S_ISREG(st.st_mode))
                sum += st.st_size;
        }
        closedir(d);
        dprintf(c2p[1], "%ld", sum);
        return 0;
    } else {
        close(p2c[0]);
        close(c2p[1]);
        write(p2c[1], argv[1], strlen(argv[1]) + 1);
        long total;
        FILE *f = fdopen(c2p[0], "r");
        fscanf(f, "%ld", &total);
        printf("%ld\n", total);
    }
    return 0;
}
