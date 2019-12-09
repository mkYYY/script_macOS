#include <Hypervisor/hv.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

int main(int argc, char *argv[]) {
  hv_return_t hvr;
  /* Create a VM instance */
  // hvr = hv_vm_create(HV_VM_DEFAULT);
  // hvr = hv_vm_create(HV_VM_SPECIFY_MITIGATIONS);
  hvr = hv_vm_create(HV_VM_MITIGATION_A_ENABLE);
  assert(hvr == HV_SUCCESS);

  /* Map a virtual address region */
  // hvr = 

  // hvr = hv_vm_destroy();
  // assert(hvr = HV_SUCCESS);
  return 0;
}
  
