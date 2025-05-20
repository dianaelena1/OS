//
// 8. Parent process sends to the child a username, and the child sends back to the parent the dates when the specified user logged in.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"

int main()
{
  int fd1, fd2;
  pid_t pid;

  if (mkfifo(FIFO1, 0666) == -1)
  {
    perror("mkfifo");
    exit(1);
  }
  if (mkfifo(FIFO2, 0666) == -1)
  {
    perror("mkfifo");
    exit(1);
  }

  pid = fork();
  if (pid < 0)
  {
    perror("fork");
    exit(1);
  }

  if (pid > 0)
  {
    char user_name[20];
    printf("Read username:");
    scanf("%s", user_name);

    fd1 = open(FIFO1, O_WRONLY);
    write(fd1, user_name, sizeof(user_name));
    close(fd1);

    fd2 = open(FIFO2, O_RDONLY);

    char dates[1024] = {0};
    int n;
    while ((n = read(fd2, dates + strlen(dates), sizeof(dates) - strlen(dates) - 1)) > 0)
      ;
    printf("Parent received dates: %s\n", dates);
    close(fd2);
  }
  else
  {

    char user_name[20];

    fd1 = open(FIFO1, O_RDONLY);
    read(fd1, user_name, sizeof(user_name));
    close(fd1);

    char command[100] = "last ";
    strcat(command, user_name);
    strcat(command, " | awk '{print $4, $5, $6, $7}' ");

    FILE *command_file = popen(command, "r");
    if (!command_file)
    {
      perror("popen fail");
      return 1;
    }

    char line[50];

    fd2 = open(FIFO2, O_WRONLY);

    while (fgets(line, sizeof(line), command_file) != NULL)
    {
      write(fd2, line, strlen(line));
    }

    pclose(command_file);
    close(fd2);
  }

  unlink(FIFO1);
  unlink(FIFO2);

  return 0;
}
// gcc -o dragos_trandafir_h8 dragos_trandafir_h8.c
//./dragos_trandafir_h8