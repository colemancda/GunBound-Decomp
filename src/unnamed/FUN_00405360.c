/* FUN_00405360 - 0x00405360 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_00405360(undefined4 param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *unaff_EBX;
  undefined4 *puVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00537a95;
  *unaff_FS_OFFSET = &local_c;
  if (unaff_EBX[2] == 0) {
    if (unaff_EBX[5] == 0) {
      puVar1 = _malloc(0x114);
      unaff_EBX[5] = puVar1;
      if (puVar1 == (undefined4 *)0x0) goto LAB_004053a0;
      for (iVar2 = 0x45; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar1 = 0;
        puVar1 = puVar1 + 1;
      }
      *(undefined4 *)(unaff_EBX[5] + 0x104) = 1;
      *(undefined4 *)(unaff_EBX[5] + 0x10c) = unaff_EBX[5];
      *(undefined4 *)(unaff_EBX[5] + 0x108) = *(undefined4 *)(unaff_EBX[5] + 0x10c);
      *(undefined4 *)(unaff_EBX[5] + 0x110) = *(undefined4 *)(unaff_EBX[5] + 0x108);
      *unaff_EBX = unaff_EBX[5];
    }
    puVar1 = _malloc(unaff_EBX[4] * 0x114 + 4);
    if (puVar1 == (undefined4 *)0x0) {
LAB_004053a0:
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x8007000e);
    }
    *puVar1 = unaff_EBX[3];
    unaff_EBX[3] = puVar1;
    iVar2 = unaff_EBX[4];
    puVar1 = puVar1 + iVar2 * 0x45 + -0x44;
    if (-1 < iVar2 + -1) {
      do {
        puVar1[0x42] = unaff_EBX[2];
        unaff_EBX[2] = puVar1;
        puVar1 = puVar1 + -0x45;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  puVar1 = (undefined4 *)unaff_EBX[2];
  local_4 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    FUN_00405510(puVar1);
    puVar3 = puVar1;
    for (iVar2 = 0x40; puVar3 = puVar3 + 1, iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *param_2;
      param_2 = param_2 + 1;
    }
    puVar1[0x41] = 1;
    puVar1[0x44] = 0;
  }
  unaff_EBX[2] = *(undefined4 *)(unaff_EBX[2] + 0x108);
  puVar1[0x41] = 0;
  puVar1[0x42] = unaff_EBX[5];
  puVar1[0x43] = unaff_EBX[5];
  puVar1[0x44] = unaff_EBX[5];
  unaff_EBX[1] = unaff_EBX[1] + 1;
  *unaff_FS_OFFSET = local_c;
  return puVar1;
}

