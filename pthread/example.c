#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>

void *thread_func(void *);

int main(int argc, char *argv[]) {
  pthread_t tid;
  pthread_create(&tid, NULL, thread_func, NULL);
  pthread_join(tid, NULL);
  return 0;
}

void *thread_func(void *p) {
  printf("[+] Thread 1: Hello!\n");
  return NULL;
}

