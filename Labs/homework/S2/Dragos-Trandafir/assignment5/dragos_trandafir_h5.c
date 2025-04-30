// Write a C Program that receives as command line arguments two words and the name of a file. The program will print at stdout
// the content of the file, replacing the occurrences of the first word with the second.

#include <stdio.h> // C library
#include <string.h>

int main(int argc, char *argv[])
{
  if (argc < 4)
  {
    printf("Usage: %s filename\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[3], "r");
  if (file == NULL)
  {
    perror("Error opening file");
    return 1;
  }

  char ch;
  int went_here = 0;
  char current_string[100] = "";
  while ((ch = fgetc(file)) != EOF)
  {

    if (ch == ' ' || ch == '\n')
    {
      if (strcmp(current_string, argv[1]) == 0)
      {
        printf("%s", argv[2]);
        went_here = 0;
      }
      else
        went_here = 1;

      if (went_here == 1)
        printf("%s", current_string);
      putchar(ch);
      current_string[0] = '\0';
    }
    else
    {
      char current_char[2];
      current_char[0] = ch;
      current_char[1] = '\0';

      strcat(current_string, current_char);
    }
  }

  fclose(file);
  return 0;
}

// gcc dragos_trandafir_h5.c -o dragos_trandafir_h5.exe
// ./dragos_trandafir_h5.exe first second file1.txt