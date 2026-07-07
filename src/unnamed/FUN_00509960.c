/* FUN_00509960 - 0x00509960 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00509960(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 4);
  if (piVar1 != (int *)0x0) {
    while (piVar1[2] != param_2) {
      piVar1 = (int *)*piVar1;
      if (piVar1 == (int *)0x0) {
        return;
      }
    }
    if (piVar1 != *(int **)(param_1 + 4)) {
      if (*piVar1 == 0) {
        *(int *)(param_1 + 8) = piVar1[1];
      }
      else {
        *(int *)(*piVar1 + 4) = piVar1[1];
      }
      *(int *)piVar1[1] = *piVar1;
      *(int **)(*(int *)(param_1 + 4) + 4) = piVar1;
      *piVar1 = *(int *)(param_1 + 4);
      piVar1[1] = 0;
      *(int **)(param_1 + 4) = piVar1;
    }
  }
  return;
}

