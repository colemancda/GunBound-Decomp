/* FUN_004e3aa0 - 0x004e3aa0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e3aa0(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  g_nCompositorLayer = 1;
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  iVar3 = iVar2;
  while (uVar1 < 0xea61) {
    if (uVar1 == 60000) {
      iVar3 = *(int *)(iVar3 + 0x10);
      uVar1 = *(uint *)(iVar3 + 8);
      goto joined_r0x004e3ae4;
    }
    iVar3 = *(int *)(iVar3 + 0x1c);
    uVar1 = *(uint *)(iVar3 + 4);
  }
  iVar3 = 0;
LAB_004e3af8:
  uVar1 = *(uint *)(iVar2 + 4);
  if (uVar1 < 0xea61) {
    while (uVar1 != 60000) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar1 = *(uint *)(iVar2 + 4);
      if (60000 < uVar1) {
        FUN_00450860();
        return;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar1 = *(uint *)(iVar2 + 8);
    if (uVar1 < 2) {
      while (uVar1 != 1) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar1 = *(uint *)(iVar2 + 8);
        if (1 < uVar1) {
          FUN_00450860();
          return;
        }
      }
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans();
      }
      else {
        QueueTextureRegionSpans(-(((*(int *)(iVar3 + 0x20) + -800) * (*(int *)(param_1 + 8) + -400)) /
                      (*(int *)(param_1 + 0x18) + -800)));
      }
    }
  }
  FUN_00450860();
  return;
joined_r0x004e3ae4:
  if (1 < uVar1) goto LAB_004e3af2;
  if (uVar1 == 1) goto LAB_004e3af8;
  iVar3 = *(int *)(iVar3 + 0x10);
  uVar1 = *(uint *)(iVar3 + 8);
  goto joined_r0x004e3ae4;
LAB_004e3af2:
  iVar3 = 0;
  goto LAB_004e3af8;
}

