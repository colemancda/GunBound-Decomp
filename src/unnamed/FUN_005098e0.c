/* FUN_005098e0 - 0x005098e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_005098e0(int param_1)

{
  int *piVar1;
  void *_Memory;
  int *piVar2;
  int in_EAX;
  
  piVar2 = *(int **)(in_EAX + 4);
  while (piVar1 = piVar2, piVar1 != (int *)0x0) {
    _Memory = (void *)piVar1[2];
    piVar2 = (int *)*piVar1;
    if (*(int *)((int)_Memory + 0x24) < param_1) {
      if (piVar1 == *(int **)(in_EAX + 4)) {
        *(int *)(in_EAX + 4) = *piVar1;
      }
      else {
        *(int *)piVar1[1] = *piVar1;
      }
      if (piVar1 == *(int **)(in_EAX + 8)) {
        *(int *)(in_EAX + 8) = piVar1[1];
      }
      else {
        *(int *)(*piVar1 + 4) = piVar1[1];
      }
      *piVar1 = *(int *)(in_EAX + 0x14);
      *(int **)(in_EAX + 0x14) = piVar1;
      piVar1 = (int *)(in_EAX + 0xc);
      *piVar1 = *piVar1 + -1;
      if (*piVar1 == 0) {
        FUN_00509fd0();
      }
      FUN_0050e560();
      _free(_Memory);
    }
  }
  return;
}

