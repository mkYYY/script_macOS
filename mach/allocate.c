#include <mach/mach.h>
#include <mach/mach_vm.h>

#include <stdio.h>

int main(int argc, char *argv[]) {
  mach_error_t kr = 0;
  mach_vm_address_t address = (mach_vm_address_t)NULL;

  getchar();
  vm_map_t target = mach_task_self();
  printf("target = mach_task_self() = 0x%016x\n", target);
  kr = mach_vm_allocate(target, &address, 0x1000, VM_FLAGS_ANYWHERE);
  if (kr != KERN_SUCCESS) return 1;

  printf("address @ %p\n", (void *)address);
  getchar();

  return 0;

}
