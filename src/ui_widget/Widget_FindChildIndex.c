/* Widget_FindChildIndex - 0x0050e620 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __fastcall Widget_FindChildIndex(int param_1)

{
  uint uVar1;
  int unaff_ESI;
  int unaff_EDI;
  
  uVar1 = 0;
  if (*(uint *)(param_1 + 0x10) != 0) {
    do {
      if (*(uint *)(param_1 + 0x10) <= uVar1) {
LAB_0050e65a:
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      if (*(int *)(*(int *)(*(int *)(param_1 + 0xc) + uVar1 * 4) + 0x20) == unaff_EDI) {
        if (*(uint *)(param_1 + 0x10) <= uVar1) goto LAB_0050e65a;
        if (*(int *)(*(int *)(*(int *)(param_1 + 0xc) + uVar1 * 4) + 0x24) == unaff_ESI) {
          return uVar1;
        }
      }
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)(param_1 + 0x10));
  }
  return 0xffffffff;
}

