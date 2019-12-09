#include <stdio.h>

int main(void) {
  int x = 123;

  void (^print_X_Y)(int) = ^(int y) {
    printf("%d %d\n", x, y);
    puts("Done");
  };

  void (^none)(void) = ^(void) {
    puts("Nothing");
  };

  print_X_Y(42);
  none();
  return 0;
}

