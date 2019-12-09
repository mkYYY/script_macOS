#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dispatch/dispatch.h>

int main(int argc, char *argv[]) {
  int i;

  // dispatch_queue_t greeter = dispatch_queue_create("dev.m6m.greeter", NULL);
  // dispatch_queue_t greeter = dispatch_queue_create("dev.m6m.greeter", DISPATCH_QUEUE_SERIAL);
  dispatch_queue_t greeter = dispatch_queue_create("dev.m6m.greeter", DISPATCH_QUEUE_CONCURRENT);

  printf("argc = %d\n", argc);
  for (i = 1; i < argc; i++) {
    dispatch_async(greeter, ^{ printf("Hello %s!\n", argv[i]); });
  }

  dispatch_sync(greeter, ^{ printf("Goodbye!\n"); });
  return 0;
}

