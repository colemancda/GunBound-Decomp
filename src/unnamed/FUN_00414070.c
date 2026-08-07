/* FUN_00414070 - 0x00414070 in the original binary.
 *
 * Blits one sprite frame into the 128x128x16bpp avatar canvas: walks
 * the DAT_00ea0e1c registry for the sprite set whose key is `key`,
 * finds the frame whose index is `frameIdx`, computes the clipped
 * destination rect (the +0x40 offsets centre the part) and per-pixel
 * blends it into `canvas` via FUN_00413ee0. Called 16x by
 * LoadAvatarSprites/ComposeAvatarSprites - 4 parts (flag/head/glasses/
 * body) x small/large x 2 files.
 *
 * DROPPED-EAX FIX (2026-08-06): the original takes the frame index in
 * EAX (custom convention: EAX + EDX + one CALLER-cleaned stack arg -
 * every call site does `mov eax,<frame> / mov edx,<key> / push <canvas>
 * / call`, with a lumped `add esp,0x10` after the block of 4). Ghidra
 * kept EAX as an unassigned `in_EAX` artifact and its callers passed
 * only the canvas. Under our MSVC compile both sides are our own code,
 * so the register carrier is just __fastcall's ECX instead of EAX -
 * self-consistent with the 16 (also fixed) call sites. */
#include "ghidra_types.h"


void __fastcall FUN_00414070(uint frameIdx,uint param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 local_c;
  undefined4 local_4;
  int srcRow;
  int srcPix;
  int frameWidth;
  
  iVar1 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar2 = *(uint *)(iVar1 + 4);
  if (uVar2 <= param_2) {
    while (uVar2 != param_2) {
      iVar1 = *(int *)(iVar1 + 0x1c);
      uVar2 = *(uint *)(iVar1 + 4);
      if (param_2 < uVar2) {
        return;
      }
    }
    iVar1 = *(int *)(iVar1 + 0x10);
    uVar2 = *(uint *)(iVar1 + 8);
    if (uVar2 <= frameIdx) {
      while (uVar2 != frameIdx) {
        iVar1 = *(int *)(iVar1 + 0x10);
        uVar2 = *(uint *)(iVar1 + 8);
        if (frameIdx < uVar2) {
          return;
        }
      }
      /* SRC-WALK RECOVERY (2026-08-06): the whole source-pixel side of
       * this blit was dead code in the raw port (it only fed the
       * dropped-EAX argument of FUN_00413ee0). From orig 0x4140bb-
       * 0x4141a1: the source base is the frame's pixel buffer (+0x34,
       * the same buffer ReadSpriteFrameRecord fills and
       * DestroySpriteFrame frees), skipped ahead by width*clippedTop
       * rows and clippedLeft columns to mirror the dest clip; each
       * inner step advances src by one texel, and each row steps the
       * source by the frame's FULL width (+0x20) while the dest steps
       * by the canvas pitch 0x100. */
      uVar2 = *(int *)(iVar1 + 0x2c) + 0x40;
      iVar4 = *(int *)(iVar1 + 0x28) + 0x40;
      iVar3 = *(int *)(iVar1 + 0x20);
      frameWidth = iVar3;
      local_4 = *(int *)(iVar1 + 0x24) - (((int)-uVar2 < 0) - 1 & -uVar2);
      srcRow = *(int *)(iVar1 + 0x34) +
               frameWidth * ((((int)-uVar2 < 0) - 1 & -uVar2)) * 2;
      uVar2 = uVar2 & ((int)uVar2 < 0) - 1;
      if (0x7f < (int)(local_4 + uVar2)) {
        local_4 = 0x7f - uVar2;
      }
      if (iVar4 < 0) {
        srcRow = srcRow + iVar4 * -2;
        iVar3 = iVar3 + iVar4;
        iVar4 = 0;
      }
      if (0x7f < iVar4 + iVar3) {
        iVar3 = 0x7f - iVar4;
      }
      if (0 < local_4) {
        param_3 = param_3 + (uVar2 * 0x80 + iVar4) * 2;
        do {
          iVar1 = param_3;
          srcPix = srcRow;
          local_c = iVar3;
          if (0 < iVar3) {
            do {
              FUN_00413ee0((ushort *)iVar1,(ushort *)srcPix);
              local_c = local_c + -1;
              iVar1 = iVar1 + 2;
              srcPix = srcPix + 2;
            } while (local_c != 0);
          }
          param_3 = param_3 + 0x100;
          srcRow = srcRow + frameWidth * 2;
          local_4 = local_4 + -1;
        } while (local_4 != 0);
      }
    }
  }
  return;
}

