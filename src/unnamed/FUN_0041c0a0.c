/* FUN_0041c0a0 - 0x0041c0a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_0041c0a0(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int unaff_ESI;
  
  iVar2 = *(int *)(DAT_00e9be94 + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  while (uVar1 < 1000000) {
    if (uVar1 == 999999) {
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar1 = *(uint *)(iVar2 + 8);
      if (uVar1 < 0xf4246) goto LAB_0041c0d8;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar1 = *(uint *)(iVar2 + 4);
  }
  goto LAB_0041c10a;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar1 = *(uint *)(iVar2 + 8);
    if (0xf4245 < uVar1) break;
LAB_0041c0d8:
    if (uVar1 == 0xf4245) {
      if ((iVar2 != 0) && (*(int *)(iVar2 + 0x24) == 1)) {
        uVar1 = *(int *)(unaff_ESI + 0x3b97c) - 1;
        *(uint *)(unaff_ESI + 0x3b97c) = uVar1 & ((int)uVar1 < 0) - 1;
      }
      break;
    }
  }
LAB_0041c10a:
  iVar2 = *(int *)(DAT_00e9be94 + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  if (uVar1 < 1000000) {
    while (uVar1 != 999999) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar1 = *(uint *)(iVar2 + 4);
      if (999999 < uVar1) {
        return;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar1 = *(uint *)(iVar2 + 8);
    if (uVar1 < 0xf4247) {
      while (uVar1 != 0xf4246) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar1 = *(uint *)(iVar2 + 8);
        if (0xf4246 < uVar1) {
          return;
        }
      }
      if ((iVar2 != 0) && (*(int *)(iVar2 + 0x24) == 1)) {
        iVar2 = *(int *)(unaff_ESI + 0x3b980) + -0xd;
        iVar3 = *(int *)(unaff_ESI + 0x3b97c) + 1;
        iVar4 = iVar3;
        if (iVar2 <= iVar3) {
          iVar4 = iVar2;
        }
        if (iVar4 < 0) {
          *(undefined4 *)(unaff_ESI + 0x3b97c) = 0;
          return;
        }
        if (iVar3 < iVar2) {
          iVar2 = iVar3;
        }
        *(int *)(unaff_ESI + 0x3b97c) = iVar2;
      }
    }
  }
  return;
}

