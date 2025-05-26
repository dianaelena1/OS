#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int p2c[2], c2p[2];
    if (argc!=2) return 1;
    pipe(p2c);
    pipe(c2p);
    if (fork()==0) {
        close(p2c[1]);
        close(c2p[0]);
        char user[64];
        read(p2c[0], user, sizeof(user));
        char cmd[128];
        sprintf(cmd, "ps -u %s --no-headers | wc -l", user);
        FILE *f = popen(cmd, "r");
        char buf[32];
        fgets(buf, sizeof(buf), f);
        pclose(f);
        write(c2p[1], buf, strlen(buf)+1);
        exit(0);
    } else {
        close(p2c[0]);
        close(c2p[1]);
        write(p2c[1], argv[1], strlen(argv[1])+1);
        char result[32];
        read(c2p[0], result, sizeof(result));
        printf("%s", result);
        wait(NULL);
    }
    return 0;
}

