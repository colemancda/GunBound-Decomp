/* FUN_0044c310 - 0x0044c310 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_0044c310(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = -1;
  uVar1 = 0;
  if (0 < *(int *)(g_clientContext + 0x44e24)) {
    iVar2 = 0;
    do {
      if (*(uint *)(g_clientContext + 0x44e24) <= uVar1) {
LAB_0044c364:
                    /* WARNING: Subroutine does not return */
        FUN_004010c0(0x80070057);
      }
      if (iVar3 < *(int *)(*(int *)(g_clientContext + 0x44e20) + 4 + iVar2)) {
        if (*(uint *)(g_clientContext + 0x44e24) <= uVar1) goto LAB_0044c364;
        iVar3 = *(int *)(iVar2 + 4 + *(int *)(g_clientContext + 0x44e20));
      }
      uVar1 = uVar1 + 1;
      iVar2 = iVar2 + 0x450;
    } while ((int)uVar1 < *(int *)(g_clientContext + 0x44e24));
  }
  return iVar3 + 1;
}

