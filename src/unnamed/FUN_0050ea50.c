/* FUN_0050ea50 - 0x0050ea50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined1 __thiscall FUN_0050ea50(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 uVar2;
  uint uVar3;
  
  if (*(char *)(param_1 + 0x1e) != '\0') {
    return 0;
  }
  uVar2 = 0;
  uVar3 = 0;
  if (*(int *)(param_1 + 0x10) != 0) {
    if (*(int *)(param_1 + 0x10) == 0) {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x80070057);
    }
    while( true ) {
      (**(code **)(**(int **)(*(int *)(param_1 + 0xc) + uVar3 * 4) + 0x14))(param_2);
      if (cVar1 != '\0') break;
      uVar3 = uVar3 + 1;
      if (*(uint *)(param_1 + 0x10) <= uVar3) {
        return 0;
      }
    }
    uVar2 = 1;
  }
  return uVar2;
}

