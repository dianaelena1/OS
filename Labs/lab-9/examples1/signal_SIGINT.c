#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigintHandler(int signum)
{
    printf("Signal SIGINT received. Exiting...\n");
    exit(EXIT_SUCCESS);
}

int main()
{
    // Atribuirea unui handler personalizat semnalului SIGINT
    signal(SIGINT, sigintHandler);


    printf("Press Ctrl+C to trigger SIGINT signal...\n");

    // Execuție continuă până la primirea semnalului SIGINT
    while (1)
    {
    }

    return 0;
}
