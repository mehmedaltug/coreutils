#include <stdio.h>
#include "new_string.h"
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv) {
    if (argc != 2 && argc != 3){
        perror("Invalid number of arguments!\n");
        return 1;
    }
    const String delim = StringCreate("-n", 0);
    const String nl = StringCreate("\n", 0);
    String text = StringCreate("", 0);
    char *num = NULL;
    for(int i = 1; i < argc; i++){
        String temp = StringCreate(argv[i], 0);
        if(StringFind(temp, delim) != -1){
            if (num == NULL)
                num = argv[i]+2;
            else {
                perror("Invalid arguments!\n");
                return 1;
            }
        } else
            StringConcat(&text, StringCreate(argv[i], 0));
    }

    if (text.length != 0){
        FILE *file = fopen(text.start, "r");
        if (file == NULL) {
            printf("Could not open file.\n");
            return 1;
        }
        char buffer[256];
        text = StringCreate("", 0);
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            StringConcatChar(&text, StringGetPrintable(StringCreate(buffer, 0)));
        }
    }
    if (argc == 2 && text.length == 0) {
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;

        while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1)) > 0) {
          buffer[bytes_read] = '\0';
          String tmp = StringCreate(buffer, 0);
          StringConcat(&text, tmp);
        }
        if (bytes_read == -1)
          perror("Reading STDIN failed!");
    } else if (argc == 2 && text.length != 0) {
        perror("Invalid arguments!\n");
        return 1;
    }

    int tail_count = strtol(num, NULL, 10);
    int item_count = -1;
    String *lines = StringSplit(text, nl, &item_count);
    if(item_count == 0 || item_count == 1) {
        printf("%s\n", text.start);
        return 0;
    }
    if (lines[item_count - 1].length == 0) {
        item_count--;
    }

    if(tail_count > item_count)
        tail_count = item_count;

    for (int i = item_count - tail_count; i < item_count; i++){
        printf("%s\n", StringGetPrintable(lines[i]));
    }
}
