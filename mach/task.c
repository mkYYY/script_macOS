#include <mach/mach.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  mach_error_t kr = 0;
  task_t remote_task = 0;
  pid_t pid = getpid();
  printf("remote_task = 0x%08x\n", remote_task);
  kr = task_for_pid(mach_task_self(), pid, &remote_task);
  if (kr != KERN_SUCCESS) {
    return -1;
  }
  printf("remote_task = 0x%08x\n", remote_task);
  return 0;
}

