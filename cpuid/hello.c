#include <stdio.h>

char *g_uninitialized;
char blank[8];

int main(void) {
  g_uninitialized = "HELLO";
  blank[0] = 'A';
  puts(g_uninitialized);
  return 0;
}
