/* FUN_0050e520 - 0x0050e520 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0050e520(int param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 0x10) != 0) {
    if (*(int *)(param_1 + 0x10) == 0) {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x80070057);
    }
    do {
      (**(code **)(**(int **)(*(int *)(param_1 + 0xc) + uVar1 * 4) + 0x20))();
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)(param_1 + 0x10));
  }
  return;
}

