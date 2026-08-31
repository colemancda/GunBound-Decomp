/* DrawStageDecorationParallax - 0x004e3aa0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void DrawStageDecorationParallax(int param_1)

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
        DrawActiveObjectLayers(param_1 + 0x85c);
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
          DrawActiveObjectLayers(param_1 + 0x85c);
          return;
        }
      }
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        /* One argument-setup block feeds both twins (0x4e3b98..0x4e3ba3
         * reaches 0x4e3ba5 and 0x4e3bac alike): ECX=1 (index, set once at
         * 0x4e3aa6), EDX=0xea60 (group), the value PUSHED at 0x4e3b9b is
         * x, and EAX at the call is EDI (loaded 0x4e3ba1) = 0xffffff9a -
         * (the FIRST division, over +0x24 / +0xc / +0x1c) = y, which
         * Ghidra dropped from this decompile entirely. */
        QueueSpriteFrameSpans(1,
                      -(((*(int *)(iVar3 + 0x20) + -800) * (*(int *)(param_1 + 8) + -400)) /
                      (*(int *)(param_1 + 0x18) + -800)),
                      -102 - (((*(int *)(iVar3 + 0x24) + -800) *
                               (*(int *)(param_1 + 0xc) + -260)) /
                              (*(int *)(param_1 + 0x1c) + -800)),0xea60);
      }
      else {
        /* Corrected 2026-08-28 alongside the QueueSpriteFrameSpans twin
         * above, completed 2026-08-31 when QueueTextureRegionSpans was
         * recovered: ECX=1 (index, set once at 0x4e3aa6) and EDX=0xea60
         * (group, the same constant as the uVar1<0xea61/60000 tree
         * searches) are the two __fastcall register slots; the neg'd
         * division is the value PUSHED at 0x4e3b9b, i.e. the x. EAX at
         * the call is EDI (`mov eax,edi` at 0x4e3ba1) = the OTHER
         * division, -102 minus the +0x24/+0xc/+0x1c quotient - the y,
         * now passed as regEax exactly as the twin above spells it. */
        QueueTextureRegionSpans(1,0xea60,
                      -(((*(int *)(iVar3 + 0x20) + -800) * (*(int *)(param_1 + 8) + -400)) /
                      (*(int *)(param_1 + 0x18) + -800)),
                      -102 - (((*(int *)(iVar3 + 0x24) + -800) *
                               (*(int *)(param_1 + 0xc) + -260)) /
                              (*(int *)(param_1 + 0x1c) + -800)));
      }
    }
  }
  DrawActiveObjectLayers(param_1 + 0x85c);
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

