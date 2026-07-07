/* FUN_0043e150 - 0x0043e150 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_0043e150(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *unaff_ESI;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00537a95;
  *unaff_FS_OFFSET = &local_c;
  if (unaff_ESI[2] == 0) {
    if (unaff_ESI[5] == 0) {
      puVar1 = _malloc(0x18);
      unaff_ESI[5] = puVar1;
      if (puVar1 == (undefined4 *)0x0) goto LAB_0043e189;
      *puVar1 = 0;
      puVar1[1] = 0;
      puVar1[2] = 0;
      puVar1[3] = 0;
      puVar1[4] = 0;
      puVar1[5] = 0;
      *(undefined4 *)(unaff_ESI[5] + 8) = 1;
      *(undefined4 *)(unaff_ESI[5] + 0x10) = unaff_ESI[5];
      *(undefined4 *)(unaff_ESI[5] + 0xc) = *(undefined4 *)(unaff_ESI[5] + 0x10);
      *(undefined4 *)(unaff_ESI[5] + 0x14) = *(undefined4 *)(unaff_ESI[5] + 0xc);
      *unaff_ESI = unaff_ESI[5];
    }
    puVar1 = _malloc(unaff_ESI[4] * 0x18 + 4);
    if (puVar1 == (undefined4 *)0x0) {
LAB_0043e189:
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x8007000e);
    }
    *puVar1 = unaff_ESI[3];
    unaff_ESI[3] = puVar1;
    iVar2 = unaff_ESI[4];
    puVar1 = puVar1 + iVar2 * 6 + -5;
    if (-1 < iVar2 + -1) {
      do {
        puVar1[3] = unaff_ESI[2];
        unaff_ESI[2] = puVar1;
        puVar1 = puVar1 + -6;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  puVar1 = (undefined4 *)unaff_ESI[2];
  local_4 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = param_1;
    FUN_00405510(puVar1 + 1);
    puVar1[2] = 1;
    puVar1[5] = 0;
  }
  unaff_ESI[2] = *(undefined4 *)(unaff_ESI[2] + 0xc);
  puVar1[2] = 0;
  puVar1[3] = unaff_ESI[5];
  puVar1[4] = unaff_ESI[5];
  puVar1[5] = unaff_ESI[5];
  unaff_ESI[1] = unaff_ESI[1] + 1;
  *unaff_FS_OFFSET = local_c;
  return puVar1;
}

