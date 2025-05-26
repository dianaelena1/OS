#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2); 

    if (fork() == 0) {
        
        char filename[100];
        read(p1[0], filename, sizeof(filename));

        FILE *f = fopen(filename, "r");
        if (!f) {
            char *error = "error\n";
            write(p2[1], error, strlen(error));
        } else {
            char buf[100];
            size_t n;
            while ((n = fread(buf, 1, sizeof(buf), f)) > 0)
                write(p2[1], buf, n);
            fclose(f);
        }
            
	close(p1[1]);
	close(p2[0]);
	close(p1[0]);
	close(p2[1]);
        
    } else {
    
        char filename[100];
        printf("Enter filename: ");
        scanf("%s", filename);
        write(p1[1], filename, sizeof(filename));

        char buf[100];
        ssize_t n;
        while ((n = read(p2[0], buf, sizeof(buf))) > 0)
            write(1, buf, n);
            
	close(p1[1]);
	close(p2[0]);
	close(p1[0]);
	close(p2[1]);

    }
    

    return 0;
}

