/* FUN_0050f770 - 0x0050f770 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __fastcall FUN_0050f770(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int unaff_EBX;
  int iVar3;
  
  uVar1 = *(uint *)(param_1 + 0x28);
  if (((int)uVar1 <= param_2) && (param_2 <= (int)(*(int *)(param_1 + 0x30) + uVar1))) {
    iVar3 = *(int *)(param_1 + 0x2c);
    if (0 < *(int *)(param_1 + 0x38)) {
      uVar1 = (*(int *)(param_1 + 0x40) * *(int *)(param_1 + 0x34)) / *(int *)(param_1 + 0x38);
      iVar3 = iVar3 + uVar1;
    }
    if (iVar3 <= unaff_EBX) {
      iVar2 = FUN_0050e050();
      uVar1 = iVar2 + iVar3;
      if (unaff_EBX <= (int)uVar1) {
        return CONCAT31((int3)(uVar1 >> 8),1);
      }
    }
  }
  return uVar1 & 0xffffff00;
}

