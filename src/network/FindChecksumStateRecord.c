/* FindChecksumStateRecord - 0x0043d640 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __fastcall FindChecksumStateRecord(int param_1,int param_2,undefined2 *param_3,undefined2 *param_4)

{
  uint uVar1;
  uint in_EAX;
  uint uVar2;
  int iVar3;
  
  uVar1 = *(uint *)(param_1 + 0xc);
  if (uVar1 == 0) {
    return in_EAX & 0xffffff00;
  }
  uVar2 = 0;
  if (uVar1 != 0) {
    iVar3 = 0;
    do {
      if (*(uint *)(param_1 + 0xc) <= uVar2) {
LAB_0043d6a5:
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      if (*(char *)(iVar3 + *(int *)(param_1 + 8)) == param_2) {
        if (*(uint *)(param_1 + 0xc) <= uVar2) {
                    /* WARNING: Subroutine does not return */
          ThrowCxxException(0x80070057);
        }
        *param_3 = *(undefined2 *)(uVar2 * 6 + 2 + *(int *)(param_1 + 8));
        if (uVar2 < *(uint *)(param_1 + 0xc)) {
          iVar3 = *(int *)(param_1 + 8);
          *param_4 = *(undefined2 *)(iVar3 + 4 + uVar2 * 6);
          return CONCAT31((int3)((uint)iVar3 >> 8),1);
        }
        goto LAB_0043d6a5;
      }
      uVar2 = uVar2 + 1;
      iVar3 = iVar3 + 6;
    } while (uVar2 < uVar1);
  }
  return uVar2 & 0xffffff00;
}

