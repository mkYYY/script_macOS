#include <dlfcn.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
  void *addr_pthread_create_from_mach_thread = dlsym(RTLD_DEFAULT, "pthread_create_from_mach_thread");
  if (addr_pthread_create_from_mach_thread == NULL) {
    fprintf(stderr, "%s", dlerror());
    return 1;
  }
  printf("[+] pthread_create_from_mach_thread: %p\n", addr_pthread_create_from_mach_thread);
  printf("[+] printf: %p\n", printf);
  return 0;
}

