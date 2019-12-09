#include <stdio.h>
#include <dispatch/dispatch.h>
#include <unistd.h>

int main(int argc, char **argv) {
  dispatch_queue_t q_main = dispatch_get_main_queue();

  for (char **p = &argv[1]; *p != NULL; p++) {
    dispatch_async(q_main, ^{
        sleep(1);
        printf("[*] Hello, %s!\n", *p);
    });
  }

  dispatch_main();
}


