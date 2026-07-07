/* FUN_004062b0 - 0x004062b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004062b0(int param_1)

{
  int *piVar1;
  char unaff_BL;
  int *piVar2;
  
  piVar2 = (int *)(*(int **)(param_1 + 4))[7];
  if (piVar2 != *(int **)(param_1 + 4)) {
    do {
      piVar1 = (int *)piVar2[4];
      if (unaff_BL == '\0') {
        if (999999 < (uint)piVar1[1]) {
          return;
        }
joined_r0x004062dd:
        for (; piVar1 != piVar2; piVar1 = (int *)piVar1[4]) {
          (**(code **)(*piVar1 + 0xc))();
        }
      }
      else if (999999 < (uint)piVar1[1]) goto joined_r0x004062dd;
      piVar2 = (int *)piVar2[7];
    } while (piVar2 != *(int **)(param_1 + 4));
  }
  return;
}

