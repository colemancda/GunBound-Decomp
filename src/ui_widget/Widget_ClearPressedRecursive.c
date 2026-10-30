/* Widget_ClearPressedRecursive - 0x0050e790 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * RECURSES INTO THE CHILD (2026-10-30): the loop at 0x50e7a5-0x50e7ab is
 * `mov eax,[esi+0xc] / mov ecx,[eax+edi*4] / call 0x50e790`, ESI = this,
 * so each recursive call gets child[i] in ECX. The port passed param_1
 * itself, so any widget with a child recursed until the stack ran out.
 */
#include "ghidra_types.h"


void __fastcall Widget_ClearPressedRecursive(int param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  *(undefined1 *)(param_1 + 4) = 0;
  if (*(int *)(param_1 + 0x10) != 0) {
    if (*(int *)(param_1 + 0x10) == 0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    do {
      /* 0x50e7a5-0x50e7ab: ECX = child[uVar1]. */
      Widget_ClearPressedRecursive(*(int *)(*(int *)(param_1 + 0xc) + uVar1 * 4));
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)(param_1 + 0x10));
  }
  return;
}

