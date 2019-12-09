#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>

void f_callee(char *p) {
  p[0] = 0x41;
}


int main(int argc, char *argv[]) {
  char *automatic = alloca(0x10);
  f_callee(automatic);
  return 0;
}


