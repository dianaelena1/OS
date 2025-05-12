#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("nonexistentfile.txt", O_RDONLY);
    if (fd == -1) {
        perror("Eroare la deschiderea fișierului");
        return 1;
    }

    // Dacă fișierul este deschis cu succes, restul codului ar urma aici
    close(fd);
    return 0;
}
