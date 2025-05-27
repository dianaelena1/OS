//|13|Parent process sends to the child a directory name, and the child sends back to the parent the total number of bytes from all files from that directory. |

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s dirname\n", argv[0]);
        return 1;
    }

    int p2c[2], c2p[2];
    if (pipe(p2c) == -1 || pipe(c2p) == -1) {
        perror("pipe");
        return 1;
    }



    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }



    if (pid > 0) {
        // parent
        close(p2c[0]);
        write(p2c[1], argv[1], strlen(argv[1]) + 1);
        close(p2c[1]);

        close(c2p[1]);
        long total = 0;
        read(c2p[0], &total, sizeof(total));
        close(c2p[0]);

        printf("Total bytes in '%s': %ld\n", argv[1], total);
    }


    else {
        // child
        close(p2c[1]);
        char dirname[256];
        read(p2c[0], dirname, sizeof(dirname));
        close(p2c[0]);

        DIR *d = opendir(dirname);
        if (!d) {
            perror("opendir");
            exit(1);
        }

        
        struct dirent *entry;
        struct stat st;
        long total = 0;
        char path[512];

        while ((entry = readdir(d))) {
            if (strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);
            if (stat(path, &st)==0 && S_ISREG(st.st_mode))
                total += st.st_size;
        }
        closedir(d);

        close(c2p[0]);
        write(c2p[1], &total, sizeof(total));
        close(c2p[1]);
    }

    return 0;
}
