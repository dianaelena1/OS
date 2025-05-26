//
// 8. Parent process sends to the child a username, and the child sends back to the parent the dates when the specified user logged in.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  int pipe_parent[2];
  int pipe_child[2];

  if (pipe(pipe_parent) == -1 || pipe(pipe_child) == -1)
  {
    perror("Pipe fail!");
    return 1;
  }

  pid_t pid = fork();

  if (pid == -1)
  {
    perror("Fork fail!");
    return 1;
  }
  else if (pid == 0)
  {
    close(pipe_parent[1]);
    close(pipe_child[0]);

    char user_name[20];
    read(pipe_parent[0], user_name, sizeof(user_name));
    close(pipe_parent[0]);

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
    while (fgets(line, sizeof(line), command_file) != NULL)
    {
      write(pipe_child[1], line, strlen(line));
    }

    pclose(command_file);
    close(pipe_child[1]);
  }
  else
  {
    close(pipe_parent[0]);
    close(pipe_child[1]);

    char user_name[20] = "dragos_trandafir";
    write(pipe_parent[1], user_name, sizeof(user_name));
    close(pipe_parent[1]);

    char dates[1024] = {0};
    int n;
    while ((n = read(pipe_child[0], dates + strlen(dates), sizeof(dates) - strlen(dates) - 1)) > 0)
      ;
    printf("Parent received dates: %s\n", dates);
    close(pipe_child[0]);
  }
  return 0;
}
// gcc dragos_trandafir_h7.c -o dragos_trandafir_h7.exe
// ./dragos_trandafir_h7.exe