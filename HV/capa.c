#include <Hypervisor/hv.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  hv_return_t hvr;
  uint64_t value;

  /*
  hvr = hv_capability(42UL, &value);
  printf("hvr: 0x%08x\n", hvr);
  */

  for (uint32_t u = 0; u <= 0xffffffff; u++) {
    hvr = hv_capability((uint64_t)u, &value);
    if ((hvr & 0xfffffff0) != 0xfae94000) {
      printf("hvr: 0x%08x\n", hvr);
      }
  }

  return 0;
}

