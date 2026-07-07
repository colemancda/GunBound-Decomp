/* FUN_0050cdb0 - 0x0050cdb0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_0050cdb0(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int unaff_ESI;
  
  iVar2 = *(int *)(param_1 + 0x2c) + 0x68;
  if ((*(int *)(param_1 + 0x28) + 0x13 < param_2) && (param_2 < *(int *)(param_1 + 0x28) + 0xc3)) {
    iVar1 = 0;
    iVar3 = *(int *)(param_1 + 0x2c) + 0x79;
    do {
      if ((iVar2 < unaff_ESI) && (unaff_ESI < iVar3)) {
        return iVar1;
      }
      iVar2 = iVar2 + 0x11;
      iVar3 = iVar3 + 0x11;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0xe);
  }
  return -1;
}

