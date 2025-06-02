// Write a C Program that receives as command line arguments a word and the name of a file. The program will delete from the file the occurrences of the provided word.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_word_char(char c)
{
  if (c == ';' || c == '.' || c == ',' || c == '?' || c == '!' || c == ':')
  {
    return 1;
  }
  return 0;
}

void remove_word(char *buffer, const char *word)
{
  size_t len = strlen(word);
  char *src = buffer, *dst = buffer;

  while (*src)
  {
    if (strncmp(src, word, len) == 0 &&
        (src == buffer || !is_word_char(*(src - 1))) &&
        !is_word_char(src[len]))
    {
      src += len; // skip the word
      *dst++ = '*';
    }
    else
    {
      *dst++ = *src++;
    }
  }
  *dst = '\0';
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s <word_to_remove> <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char *word = "!";
  const char *word1 = ";";
  const char *word2 = ".";
  const char *word3 = ",";
  const char *word4 = "?";
  const char *word5 = ":";

  const char *filename = argv[2];

  FILE *file = fopen(filename, "r");
  if (!file)
  {
    perror("Could not open file for reading");
    return EXIT_FAILURE;
  }

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  rewind(file);

  char *buffer = malloc(size + 1);
  if (!buffer)
  {
    perror("Memory allocation failed");
    fclose(file);
    return EXIT_FAILURE;
  }
  fread(buffer, 1, size, file);
  buffer[size] = '\0';
  fclose(file);

  remove_word(buffer, word);
  remove_word(buffer, word1);
  remove_word(buffer, word2);
  remove_word(buffer, word3);
  remove_word(buffer, word4);
  remove_word(buffer, word5);

  file = fopen(filename, "w");
  if (!file)
  {
    perror("Could not open file for writing");
    free(buffer);
    return EXIT_FAILURE;
  }

  fputs(buffer, file);
  fclose(file);
  free(buffer);

  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  // Open file
  file = fopen(argv[2], "r");
  if (file == NULL)
  {
    fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
    return 1;
  }

  // Read file line by line using getline
  while ((read = getline(&line, &len, file)) != -1)
  {

    printf("%s", line);
  }

  // Clean up
  free(line);
  fclose(file);

  return EXIT_SUCCESS;
}

// gcc problem3_1.c -o problem3_1
// ./problem3_1 sis file_c_test.txt