/* GetPlayerRecordBySlot - 0x004206f0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


int GetPlayerRecordBySlot(int param_1)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  int iVar4;
  char unaff_BL;
  uint unaff_EDI;
  
  iVar4 = *(int *)(*(int *)(&DAT_006a7f8c + param_1) + 0x1c);
  uVar1 = *(uint *)(iVar4 + 4);
  while (uVar1 < 0x186a2) {
    if (uVar1 == 0x186a1) {
      iVar4 = *(int *)(iVar4 + 0x10);
      uVar1 = *(uint *)(iVar4 + 8);
      if (uVar1 <= unaff_EDI) goto LAB_00420726;
      break;
    }
    iVar4 = *(int *)(iVar4 + 0x1c);
    uVar1 = *(uint *)(iVar4 + 4);
  }
  goto LAB_00420748;
  while( true ) {
    iVar4 = *(int *)(iVar4 + 0x10);
    uVar1 = *(uint *)(iVar4 + 8);
    if (unaff_EDI < uVar1) break;
LAB_00420726:
    if (uVar1 == unaff_EDI) {
      cVar3 = FUN_004065a0();
      if ((bool)cVar3 != (unaff_BL == '\0')) {
        return iVar4;
      }
      break;
    }
  }
LAB_00420748:
  iVar4 = *(int *)(*(int *)(&DAT_006a7f8c + param_1) + 0x1c);
  uVar2 = *(uint *)(iVar4 + 4);
  uVar1 = unaff_EDI + 8;
  if (uVar2 < 0x186a2) {
    while (uVar2 != 0x186a1) {
      iVar4 = *(int *)(iVar4 + 0x1c);
      uVar2 = *(uint *)(iVar4 + 4);
      if (0x186a1 < uVar2) {
        return 0;
      }
    }
    iVar4 = *(int *)(iVar4 + 0x10);
    uVar2 = *(uint *)(iVar4 + 8);
    if (uVar2 <= uVar1) {
      while (uVar2 != uVar1) {
        iVar4 = *(int *)(iVar4 + 0x10);
        uVar2 = *(uint *)(iVar4 + 8);
        if (uVar1 < uVar2) {
          return 0;
        }
      }
      cVar3 = FUN_004065a0();
      if ((bool)cVar3 != (unaff_BL == '\0')) {
        return iVar4;
      }
    }
  }
  return 0;
}

