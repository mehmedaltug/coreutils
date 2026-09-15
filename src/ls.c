#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Directory not specified!\n");
        return 1;
    }

    const char *dir_path = argv[1];
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    char **entries = NULL;
    int count = 0;
    int capacity = 10;
    entries = malloc(capacity * sizeof(char *));

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (count >= capacity) {
            capacity *= 2;
            char **temp = realloc(entries, capacity * sizeof(char *));
            if (!temp) {
                perror("Memory allocation failed");
                closedir(dir);
                return 1;
            }
            entries = temp;
        }

        entries[count] = strdup(entry->d_name);
        count++;
    }
    closedir(dir);

    qsort(entries, count, sizeof(char *), compare_strings);

    struct stat file_stat;
    char full_path[1024];

    for (int i = 0; i < count; i++) {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entries[i]);

        if (stat(full_path, &file_stat) == -1) {
            perror("Failed to get file information for a file!");
            free(entries[i]);
            continue;
        }

        const char *type_str = "-";
        if (S_ISDIR(file_stat.st_mode))
            type_str = "D";

        long long size = (long long)file_stat.st_size;
        float new_size = size;
        char *size_state = "B";

        if (size >= 1024) {
            new_size = size / 1024.0;
            size /= 1024;
            size_state = "KB";
        }
        if (size >= 1024) {
            new_size = size / 1024.0;
            size /= 1024;
            size_state = "MB";
        }
        if (size >= 1024) {
            new_size = size / 1024.0;
            size_state = "GB";
        }

        int permissions = file_stat.st_mode & 0777; 

        printf("   %s0%o\t%6.2f %s\t%s\n", type_str, permissions, new_size, size_state, entries[i]);

        free(entries[i]);
    }

    free(entries);
    return 0;
}
