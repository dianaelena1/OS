#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();
    int seconds=30;

    if (pid < 0) {
        perror("fork() error");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Procesul copil
        while(seconds >=0){
        	sleep(1); // Procesul copil rulează timp de 30 de secunde
        	printf("Procesul copil  mai are de rulat %d secunde.\n",seconds);
		seconds --;
	}
	printf("Procesul copil este gata");
    } else {
        // Procesul parinte
        while(seconds >=0){
                sleep(1); // Procesul copil rulează timp de 30 de secunde
                printf("Procesul parinte  mai are de rulat %d secunde.\n",seconds);
                seconds --;
        }
        printf("Procesul parinte  este gata");
    }

    return 0;
}
