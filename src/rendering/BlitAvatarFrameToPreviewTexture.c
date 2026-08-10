/* BlitAvatarFrameToPreviewTexture - 0x0044b5d0 in the original binary.
 *
 * RENAMED (2026-08-09, was FUN_0044b5d0): copies one composed avatar
 * sprite frame into the locked AvataTexture1 preview surface. Walks the
 * sprite registry (DAT_00ea0e1c, the same nested outer+0x1c/inner+0x10
 * list FindSpriteFrame walks) for outerKey/frameKey, then row-copies the
 * frame's 16bpp pixels (max 128x128, clipped against the frame's own
 * x/y/w/h at +0x20..+0x2c and its pixel base at +0x34) into dest at the
 * given byte pitch. Sole callers: State07_AvatarStore_RenderStoreContent's
 * avatar-composite block, once per half - outerKey 200000 (0x30d40) into
 * the left half and 300000 (0x493e0) into the right half - exactly the
 * two sprite-set keys State07_AvatarStore_OnEnter passes to
 * LoadAvatarSprites, tying this to the avatar-part compositor family
 * (LoadAvatarSprites/ComposeAvatarSprites).
 *
 * DROPPED-EAX FIX (2026-08-09): the frame key arrives in EAX - the
 * original's prologue does `mov esi,eax` with no prior write (custom
 * EAX+EDX+2-stack, ECX-dead, ret 8 convention), and both call sites do
 * `mov eax,[ebx+0x30bec]` immediately before the call. Ghidra dropped it
 * as an uninitialised `in_EAX` local; promoted to the explicit `frameKey`
 * parameter (both call sites updated in the same change - the __fastcall
 * decoration changes @16 -> @20, so a partial promotion cannot link).
 * param_1 (ECX) stays a true dead argument, matching the original ABI
 * slot. Raw/near-verbatim port of Ghidra's decompiler output otherwise.
 */
#include "ghidra_types.h"


void __fastcall BlitAvatarFrameToPreviewTexture(undefined4 param_1,uint param_2,int param_3,
                                                int param_4,uint frameKey)

{
  int iVar1;
  uint in_EAX = frameKey;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  undefined4 *puVar8;
  uint uVar9;
  int iVar10;
  undefined4 *puVar11;
  
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar7 = *(uint *)(iVar2 + 4);
  if (uVar7 <= param_2) {
    while (uVar7 != param_2) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar7 = *(uint *)(iVar2 + 4);
      if (param_2 < uVar7) {
        return;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar7 = *(uint *)(iVar2 + 8);
    if (uVar7 <= in_EAX) {
      while (uVar7 != in_EAX) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar7 = *(uint *)(iVar2 + 8);
        if (in_EAX < uVar7) {
          return;
        }
      }
      iVar4 = *(int *)(iVar2 + 0x20);
      iVar5 = *(int *)(iVar2 + 0x28) + 0x40;
      iVar1 = iVar4 + iVar5;
      uVar7 = *(int *)(iVar2 + 0x2c) + 0x40;
      if ((((0 < iVar1) && (iVar5 < 0x80)) && (*(int *)(iVar2 + 0x24) + uVar7 != 0)) &&
         ((int)uVar7 < 0x80)) {
        uVar9 = -uVar7;
        puVar3 = (undefined4 *)(*(int *)(iVar2 + 0x34) + iVar4 * (((int)uVar9 < 0) - 1 & uVar9) * 2)
        ;
        iVar10 = *(int *)(iVar2 + 0x24) - (((int)uVar9 < 0) - 1 & uVar9);
        uVar7 = ((int)uVar7 < 0) - 1 & uVar7;
        if (0x7f < (int)(iVar10 + uVar7)) {
          iVar10 = 0x7f - uVar7;
        }
        if (iVar5 < 0) {
          puVar3 = (undefined4 *)((int)puVar3 + iVar5 * -2);
          iVar5 = 0;
          iVar4 = iVar1;
        }
        if (0x7f < iVar4 + iVar5) {
          iVar4 = 0x7f - iVar5;
        }
        if (0 < iVar10) {
          puVar6 = (undefined4 *)(uVar7 * param_4 + param_3 + iVar5 * 2);
          param_3 = iVar10;
          do {
            uVar9 = (iVar4 * 2 < 0) - 1 & iVar4 * 2;
            puVar8 = puVar3;
            puVar11 = puVar6;
            for (uVar7 = uVar9 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
              *puVar11 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar11 = puVar11 + 1;
            }
            for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
              *(undefined1 *)puVar11 = *(undefined1 *)puVar8;
              puVar8 = (undefined4 *)((int)puVar8 + 1);
              puVar11 = (undefined4 *)((int)puVar11 + 1);
            }
            puVar3 = (undefined4 *)((int)puVar3 + *(int *)(iVar2 + 0x20) * 2);
            puVar6 = (undefined4 *)((int)puVar6 + param_4);
            param_3 = param_3 + -1;
          } while (param_3 != 0);
        }
      }
    }
  }
  return;
}

