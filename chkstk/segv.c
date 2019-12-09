#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#define FORBIDDENSZ (0x1000 * 0x800)

void f_callee(char *p) {
  p[0] = 0xdd;
}

int main(int argc, char *argv[]) {
  char *automatic = alloca(FORBIDDENSZ);
  f_callee(automatic);

  return 0;
}

