#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#define NPAGES (3)

void leef(char *p) {
  p[0] = 0xdd;
}

void mid(void) {
  char *automatic = alloca(0x1000 * NPAGES);
  leef(automatic);
}

int main(int argc, char *argv[]) {
  printf("argv @ %p\n", argv);
  mid();
  return 0;
}

