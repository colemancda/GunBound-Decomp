/* FUN_00505ec0 - 0x00505ec0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_00505ec0(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int unaff_ESI;
  
  if ((*(int *)(param_2 + 0x28) + 0xe < param_1) && (param_1 < *(int *)(param_2 + 0x28) + 0xae)) {
    iVar2 = 0;
    iVar1 = *(int *)(param_2 + 0x2c) + 0x4b;
    do {
      if ((iVar1 + -0x1e < unaff_ESI) && (unaff_ESI < iVar1)) {
        iVar2 = DAT_00e54da8 + iVar2;
        *(int *)(param_2 + 0x90) = iVar2;
        return iVar2;
      }
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 0x1d;
    } while (iVar2 < 7);
  }
  return -1;
}

