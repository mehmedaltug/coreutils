#include <stdio.h>

const char *space = " ";

int main(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    printf("%s%s", ++space, argv[i]);
    space -= 2;
  }
  printf("\n");
}
