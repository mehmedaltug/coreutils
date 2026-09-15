#include <stdio.h>
#include <limits.h>

#ifdef _WIN32
    #include <direct.h>
    #define getcwd _getcwd
#else
    #include <unistd.h>
#endif

int main (void) {
    char cwd[PATH_MAX];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else {
        perror("Could not get CWD");
        return 1;
    }
    return 0;
}
