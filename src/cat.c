#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *file;
    long length = 0;
    for (int i = 1; i < argc; i++)
    {
        file = fopen(argv[i], "r");
        if (file == NULL)
        {
            perror("Error opening file");
            printf("%s\n", argv[i]);
            return 1;
        }

        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);

        char *buffer = malloc(length + 1);
        size_t read_size = fread(buffer, 1, length, file);
        buffer[read_size] = '\0';
        printf("%s", buffer);

        fclose(file);
        free(buffer);
    }
}
