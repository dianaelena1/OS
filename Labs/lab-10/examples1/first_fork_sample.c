#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;  // Variabila pentru a stoca ID-ul procesului

    // Apelul fork() încearcă să creeze un nou proces prin duplicarea procesului curent
    //print-ul asta trebuie sa apara o singura data
    printf("Valoare pid inainte de fork este : %d iar acest print apare o singura data\n",pid);
    pid = fork();
    //acest print se va vedea in ambelel procese
    printf("Am trecut de fork si am pid = %d iar acest print apare de doua ori\n",pid);

    if (pid < 0) {
        // Dacă fork() returnează o valoare negativă, crearea procesului copil a eșuat
        fprintf(stderr, "Eroare la fork()\n");
        return 1;
    } else if (pid == 0) {
        // Dacă fork() returnează 0, suntem în procesul copil
        printf("Sunt procesul copil! PID-ul meu este %d.\n", getpid());
    } else {
        // Dacă fork() returnează o valoare pozitivă, suntem în procesul părinte
        // și valoarea returnată este PID-ul procesului copil
        printf("Sunt procesul părinte! PID-ul meu este %d și PID-ul copilului meu este %d.\n", getpid(), pid);
    }

    // Ambele procese vor executa această linie.
    printf("Aceasta linie este executată de ambele procese.\n");

    return 0;
}


//[Proces Părinte] -> [Apel fork()]
//       |                      |
//       |                      |----> [Proces Copil]
//       |                             |-> [Execuție Cod Copil]
//       |                             '-> [Terminare Copil]
//       |
//       |-> [Continuă Execuția]
//       '-> [Așteaptă Copilul cu wait()]
//            '-> [Continuă după Copil]
