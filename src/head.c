#include <stdio.h>
#include <string.h>
#include "new_string.h"

int return_error(char *text){
        perror(text);
        return 1;
}

int main(int argc, char **argv) {
    if (argc != 2 && argc != 3)
        return return_error("Invalid argument count!\n");
    const char delimiter[] = "-n";
    String content;
    char *num;
    int arg_location = -1;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(delimiter, argv[i])) {
            if (num == NULL && i != argc - 1) {
                num = argv[i+1];
                arg_location = i;
            }
            else
                return return_error("Invalid arguments!\n");
        }
    }

    if (argc == 3) {
        if (arg_location == 1)
            content = StringCreate(argv[3]);
        else
            content = StringCreate(argv[1]);
    } else {
        
    }
}
