#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#define FORBIDDENSZ (0x1000 * (0x800 - 1))

void f_callee(char *p) {
  p[0] = 0xdd;
}

int main(int argc, char *argv[]) {
  printf("argv @ %p\n", argv);
  char *automatic = alloca(FORBIDDENSZ);
  f_callee(automatic);

  return 0;
}

