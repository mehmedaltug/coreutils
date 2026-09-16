#include "new_string.h"
#include <regex.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv) {
    if (argc != 2 && argc != 3) {
        perror("Invalid argument count");
        return 1;
    }
    regex_t regex;
    regmatch_t m;
    const char *filter = argv[1];
    regcomp(&regex, filter, REG_EXTENDED);
    String text;
    if (argc == 3)
        text = StringCreate(argv[2]);
    else
        text = StringCreate("");

    if (argc == 2) {
      char buffer[BUFFER_SIZE];
      ssize_t bytes_read;

      while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0';
        String tmp = StringCreate(buffer);
        StringConcat(&text, tmp);
      }
      if (bytes_read == -1)
        perror("Reading STDIN failed!");
    }
    int line_count = 0;
    String *lines = StringSplit(text, StringCreate("\n"), &line_count);
    if (line_count != 0)
        for (int i = 0; i < line_count; i++) {
            if (regexec(&regex, StringGetPrintable(lines[i]), 1, &m, 0) == 0)
                printf("%s\n", StringGetPrintable(lines[i]));
        }
    else {
        if (regexec(&regex, text.start, 1, &m, 0) == 0)
            printf("%s\n", text.start);
    }
}
