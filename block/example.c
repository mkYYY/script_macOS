#include <stdio.h>

int main(void) {
  int multiplier = 7;
  int (^my_block)(int) = ^(int num) {
    return num * multiplier;
  };

  printf("%d\n", my_block(4));
  printf("%d\n", my_block(5));
  return 0;
}


