/* FUN_0050dfd0 - 0x0050dfd0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0050dfd0(int param_1)

{
  int iVar1;
  uint uVar2;
  
  if (*(char *)(param_1 + 0x1e) == '\0') {
    iVar1 = 0;
    do {
      if (*(int *)(param_1 + 0x2c) < iVar1) break;
      BlitRLESprite(iVar1 + *(int *)(param_1 + 0x2c),*(undefined2 *)(param_1 + 0x38));
      iVar1 = iVar1 + 0xe;
    } while (iVar1 < 0x8c);
    if (*(char *)(param_1 + 0x1e) == '\0') {
      uVar2 = 0;
      if (*(int *)(param_1 + 0x10) != 0) {
        if (*(int *)(param_1 + 0x10) == 0) {
                    /* WARNING: Subroutine does not return */
          ThrowCxxException(0x80070057);
        }
        do {
          (**(code **)(**(int **)(*(int *)(param_1 + 0xc) + uVar2 * 4) + 0x24))();
          uVar2 = uVar2 + 1;
        } while (uVar2 < *(uint *)(param_1 + 0x10));
      }
    }
  }
  return;
}

