// 13.Calculate the product of an array n of numbers using divide et impera method: a process splits the array in two sub-arrays and gives them to // two other chid processes to compute their product, then multiplies the results obtained from the two. The two child processes apply the same //technique (split, etc…).

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int product_impera(int *arr, int left, int right)
{
  if (left == right)
  {
    return arr[left];
  }
  else
  {
    int middle = (left + right) / 2;

    int status1, status2;
    pid_t pid1 = fork();

    if (pid1 < 0)
    {
      perror("fork failed");
      exit(EXIT_FAILURE);
    }

    if (pid1 == 0)
    {
      int left_product = product_impera(arr, left, middle);
      if (left_product > 255)
        printf("The product exceeds 0-255! \n");
      exit(left_product);
    }
    else
    {
      pid_t pid2 = fork();

      if (pid2 < 0)
      {
        perror("fork failed");
        exit(EXIT_FAILURE);
      }

      if (pid2 == 0)
      {
        int right_product = product_impera(arr, middle + 1, right);
        if (right_product > 255)
          printf("The product exceeds 0-255! \n");
        exit(right_product);
      }
      else
      {
        waitpid(pid1, &status1, 0);
        waitpid(pid2, &status2, 0);
        return WEXITSTATUS(status1) * WEXITSTATUS(status2);
      }
    }
  }
}

int main(int argc, char *argv[])
{

  int n;
  scanf("%d", &n);

  int *numbers = (int *)malloc(n * sizeof(int));
  if (numbers == NULL)
  {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }

  int i;
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &numbers[i]);
  }
  int product = product_impera(numbers, 0, n - 1);
  printf("%d", product);

  free(numbers);
}
// gcc dragos_trandafir_h6.c -o dragos_trandafir_h6.exe
// ./dragos_trandafir_h6.exe