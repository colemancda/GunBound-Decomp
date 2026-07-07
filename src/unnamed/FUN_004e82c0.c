/* FUN_004e82c0 - 0x004e82c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined1 __fastcall FUN_004e82c0(int param_1)

{
  undefined1 uVar1;
  char in_AL;
  uint uVar2;
  char unaff_BL;
  int iVar3;
  
  uVar2 = 0;
  uVar1 = 0;
  if (*(uint *)(param_1 + 0x454a8) != 0) {
    iVar3 = 0;
    do {
      if (*(uint *)(param_1 + 0x454a8) <= uVar2) goto LAB_004e8398;
      if (*(char *)(iVar3 + 4 + *(int *)(param_1 + 0x454a4)) == in_AL) {
        if (*(uint *)(param_1 + 0x454a8) <= uVar2) goto LAB_004e8398;
        if (*(short *)(iVar3 + *(int *)(param_1 + 0x454a4)) == -0x3cfe) {
          if (*(uint *)(param_1 + 0x454a8) <= uVar2) goto LAB_004e8398;
          if (*(char *)(iVar3 + 0x26 + *(int *)(param_1 + 0x454a4)) == unaff_BL) {
            uVar1 = 1;
            break;
          }
        }
      }
      uVar2 = uVar2 + 1;
      iVar3 = iVar3 + 0x206;
    } while (uVar2 < *(uint *)(param_1 + 0x454a8));
  }
  uVar2 = 0;
  if (*(uint *)(param_1 + 0x454b8) == 0) {
    return uVar1;
  }
  iVar3 = 0;
  while (uVar2 < *(uint *)(param_1 + 0x454b8)) {
    if (*(char *)(iVar3 + 4 + *(int *)(param_1 + 0x454b4)) == in_AL) {
      if (*(uint *)(param_1 + 0x454b8) <= uVar2) break;
      if (*(short *)(iVar3 + *(int *)(param_1 + 0x454b4)) == -0x3cfe) {
        if (*(uint *)(param_1 + 0x454b8) <= uVar2) break;
        if (*(char *)(iVar3 + 0x26 + *(int *)(param_1 + 0x454b4)) == unaff_BL) {
          return 1;
        }
      }
    }
    uVar2 = uVar2 + 1;
    iVar3 = iVar3 + 0x206;
    if (*(uint *)(param_1 + 0x454b8) <= uVar2) {
      return uVar1;
    }
  }
LAB_004e8398:
                    /* WARNING: Subroutine does not return */
  FUN_004010c0(0x80070057);
}

