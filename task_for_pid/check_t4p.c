#include <stdio.h>
#include <dlfcn.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>

int (*fn)(int) = NULL;

typedef struct threadarg {
  int begin;
  int end;
} threadarg_t;

void *thread_func(void *arg) {
  if (fn == NULL) return NULL;
  
  threadarg_t targ = (threadarg_t)arg;
  int res;
  for (int i = targ->begin; i < targ->end; i++) {
    res = fn(i);

  



int main(int argc, char *argv[]) {
  void *addr = dlsym(RTLD_DEFAULT, "rootless_allows_task_for_pid");
  if (addr == NULL) {
    return 1;
  }

  fn = (int (*)(int))addr;
  int res = -9;
  res = fn(0);
  printf("res = %d\n", res);
  return 0;
}

