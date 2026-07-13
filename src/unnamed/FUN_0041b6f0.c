/* FUN_0041b6f0 - 0x0041b6f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-13): `unaff_ESI` is a dropped register, not garbage -
 * confirmed via objdump that it arrives unchanged (no MOV to ESI in the
 * function body, used directly as `[esi+0x5f2f3c]`/`[esi+0x41344]`).
 * Sole caller is GameTick at 0x4132b8: `mov esi,[0x5b3484]` - the
 * already-declared `g_clientContext` global (see include/globals.h) -
 * hardcoded here rather than threading a parameter through.
 */
#include "ghidra_types.h"


void FUN_0041b6f0(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  iVar2 = *(int *)(DAT_00e9be94 + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  while (uVar1 < 1000000) {
    if (uVar1 == 999999) {
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar1 = *(uint *)(iVar2 + 8);
      if (uVar1 < 0xf4244) goto LAB_0041b728;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar1 = *(uint *)(iVar2 + 4);
  }
  goto LAB_0041b75a;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar1 = *(uint *)(iVar2 + 8);
    if (0xf4243 < uVar1) break;
LAB_0041b728:
    if (uVar1 == 0xf4243) {
      if ((iVar2 != 0) && (*(int *)(iVar2 + 0x24) == 1)) {
        *(uint *)((char *)g_clientContext + 0x5f2f3c) =
             *(int *)((char *)g_clientContext + 0x5f2f3c) - 1U &
             ((int)(*(int *)((char *)g_clientContext + 0x5f2f3c) - 1U) < 0) - 1;
      }
      break;
    }
  }
LAB_0041b75a:
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
    if (uVar1 < 0xf4245) {
      while (uVar1 != 0xf4244) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar1 = *(uint *)(iVar2 + 8);
        if (0xf4244 < uVar1) {
          return;
        }
      }
      if ((iVar2 != 0) && (*(int *)(iVar2 + 0x24) == 1)) {
        iVar2 = *(byte *)((char *)g_clientContext + 0x41344) - 8;
        iVar3 = *(int *)((char *)g_clientContext + 0x5f2f3c) + 1;
        iVar4 = iVar3;
        if (iVar2 <= iVar3) {
          iVar4 = iVar2;
        }
        if (iVar4 < 0) {
          *(undefined4 *)((char *)g_clientContext + 0x5f2f3c) = 0;
          return;
        }
        if (iVar3 < iVar2) {
          iVar2 = iVar3;
        }
        *(int *)((char *)g_clientContext + 0x5f2f3c) = iVar2;
      }
    }
  }
  return;
}
