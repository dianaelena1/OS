#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Funcție de tratare a semnalului SIGTERM
void sigtermHandler(int signum)
{
    printf("Received SIGTERM signal. Terminating...\n");
    exit(EXIT_SUCCESS);
}

int main()
{
    // Atribuirea unui handler personalizat semnalului SIGTERM
    signal(SIGTERM, sigtermHandler);

    printf("Running. Press Ctrl+C or send SIGTERM signal to terminate.\n");

    // Execuție continuă până la primirea semnalului SIGTERM
    while (1)
    {
        // Câteva operații simulate
        printf("Program is running...\n");
        sleep(1);
    }

    return 0;
}
