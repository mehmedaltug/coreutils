#include "new_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int return_error(char *text) {
  printf("%s", text);
  return 1;
}

int main(int argc, char **argv) {
  if (argc != 4 && argc != 3) {
    printf("Invalid number of arguments!\n");
    return 1;
  }

  const String ARGUMENT_START = StringCreate("-", 0);
  const String DELIMITER = StringCreate("-d", 0);
  const String FIELD = StringCreate("-f", 0);
  const String NL = StringCreate("\n", 0);

  String args[2];
  String delim;
  String field;
  String text = StringCreate("", 0);
  int current_index = 0;
  for (int i = 1; i < argc; i++) {
    String tmp = StringCreate(argv[i], 0);
    if (StringFind(tmp, ARGUMENT_START) != -1 && current_index != 2)
      args[current_index++] = tmp;
    else if (argc == 4) {
      if (text.length == 0)
        text = tmp;
      else
        return return_error("Invalid arguments!\n");
    }
  }

  if (argc == 3) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1)) > 0) {
      buffer[bytes_read] = '\0';
      String tmp = StringCreate(buffer, 0);
      StringConcat(&text, tmp);
    }
    if (bytes_read == -1)
      perror("Reading STDIN failed!");
  }
  if (argc == 4) {
    FILE *file = fopen(text.start, "r");
    if (file == NULL) {
      printf("Could not open file.\n");
      return 1;
    }
    char buffer[256];
    text = StringCreate("", 0);
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
      StringConcatChar(&text, buffer);
    }
  }

  if (current_index != 2)
    return_error("Invalid arguments!\n");
  if (StringFind(args[0], DELIMITER) != -1 &&
      StringFind(args[1], FIELD) != -1) {
    delim = args[0];
    field = args[1];
  } else if (StringFind(args[1], DELIMITER) != -1 &&
             StringFind(args[0], FIELD) != -1) {
    delim = args[1];
    field = args[0];
  } else
    return return_error("Invalid arguments!\n");

  int count = -1;
  String *split = StringSplit(delim, DELIMITER, &count);
  if (count != 2)
    return return_error("Invalid delimiter!\n");
  delim = split[1];

  count = -1;
  split = StringSplit(field, FIELD, &count);
  if (count != 2)
    return return_error("Invalid field input!\n");
  field = split[1];
  int index = strtol(StringGetPrintable(field), NULL, 10);

  int line_count = -1;
  String *lines = StringSplit(text, NL, &line_count);

  if (line_count == 0 || line_count == 1){
    int split_count = -1;
    split = StringSplit(text, delim, &split_count);
    if (index <= 0 || index > split_count)
      return return_error("Invalid field number!\n");
    printf("%s\n", StringGetPrintable(split[index - 1]));
    free(split);
    return 0;
  }

  for (int i = 0; i < line_count; i++){
    int split_count = -1;
    split = StringSplit(lines[i], delim, &split_count);
    if (index <= 0 || index > split_count)
      return return_error("Invalid field number!\n");
    printf("%s\n", StringGetPrintable(split[index - 1]));
    free(split);
  }
  return 0;
}
