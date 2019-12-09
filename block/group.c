#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dispatch/dispatch.h>

int main(int argc, char *argv[]) {
  dispatch_group_t grp_greeter = dispatch_group_create();
  dispatch_queue_t q_greeter = dispatch_queue_create("dev.m6m.greeter", DISPATCH_QUEUE_CONCURRENT);
  printf("argc = %d\n", argc);

  for (char **p = &argv[1]; *p != NULL; p++) {
    dispatch_group_async(grp_greeter, q_greeter, ^{
        printf("Hello, %s!\n", *p);
    });
  }

  // Wait for dispatched blocks to complete
  dispatch_group_wait(grp_greeter, DISPATCH_TIME_FOREVER);
  dispatch_sync(q_greeter, ^{ puts("Goodbye!"); });
  return 0;
}

