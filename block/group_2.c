#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dispatch/dispatch.h>

int main(int argc, char *argv[]) {
  int i;

  dispatch_group_t grp_greeter = dispatch_group_create();
  dispatch_queue_t q_greeter1 = dispatch_queue_create("dev.m6m.greeter1", DISPATCH_QUEUE_CONCURRENT);
  dispatch_queue_t q_greeter2 = dispatch_queue_create("dev.m6m.greeter2", DISPATCH_QUEUE_CONCURRENT);
  printf("argc = %d\n", argc);

  for (i = 1; i < argc; i++) {
    if (i % 2) {
      dispatch_group_async(grp_greeter, q_greeter1, ^{
          printf("(greeter_1) Hi, %s!\n", argv[i]);
      });
    } else {
      dispatch_group_async(grp_greeter, q_greeter2, ^{
          printf("(greeter_2) Hello, %s!\n", argv[i]);
      });
    }
  }

  // Wait for dispatched blocks to complete
  dispatch_group_wait(grp_greeter, DISPATCH_TIME_FOREVER);
  dispatch_sync(q_greeter1, ^{ puts("Goodbye!"); });
  return 0;
}

