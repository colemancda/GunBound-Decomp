/* FUN_004ede20 - 0x004ede20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004ede20(int param_1)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 4);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x20))(piVar1);
    *(undefined1 *)(param_1 + 0x54) = 0;
    (**(code **)(**(int **)(param_1 + 4) + 8))(*(int **)(param_1 + 4));
    *(undefined4 *)(param_1 + 4) = 0;
  }
  return;
}

