/* BlitSpriteFrameToRayonTextureCell - 0x00497980 in the original
 * binary.
 *
 * Copies frame regEax of sprite set param_2 into a 32x32 16bpp cell at
 * (param_3, pitch param_4), biasing the frame hotspot by (+0x10,+0x18)
 * and clamping to the 0x20-square cell - the small-cell sibling of
 * BlitAnnouncementFrameToYesooriTexture (0x4b3b60), same registry walk
 * over DAT_00ea0e1c, same row-copy core.
 *
 * The cell identity is external.  Both binary call sites, 0x499e83 and
 * 0x499eb6, are in the uncarved function at 0x499930 - slot 9 of the
 * Mine projectile vtable 0x5563f0 (docs/projectile_classes.md; the
 * walking Raon bots) - and both compute the destination as base +
 * (((idx>>3)*pitch + (idx&7)*2) << 5), i.e. cell idx of an
 * 8-cells-per-row 32x32 grid, where base/pitch are
 * g_clientContext+0x227c4/+0x227cc for the first call and
 * +0x227c8/+0x227d0 for the second.  Those four cells are what
 * State11_InBattle_ClearEffectTextures fills from its once-per-frame
 * locks of RayonTexture1 and RayonTexture2 (the original's own
 * s_RayonTexture1/2 strings) - each live mine stamps its current frame
 * (from two sprite sets, mine+0x18 and mine+0x38, frame mine+0x30) into
 * its own cell of the two Rayon atlases.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void __fastcall BlitSpriteFrameToRayonTextureCell(undefined4 param_1,uint param_2,int param_3,int param_4,uint regEax)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  int iVar10;
  undefined4 *puVar11;
  
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar8 = *(uint *)(iVar2 + 4);
  if (uVar8 <= param_2) {
    while (uVar8 != param_2) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar8 = *(uint *)(iVar2 + 4);
      if (param_2 < uVar8) {
        return;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar8 = *(uint *)(iVar2 + 8);
    if (uVar8 <= regEax) {
      while (uVar8 != regEax) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar8 = *(uint *)(iVar2 + 8);
        if (regEax < uVar8) {
          return;
        }
      }
      iVar10 = *(int *)(iVar2 + 0x20);
      iVar5 = *(int *)(iVar2 + 0x28) + 0x10;
      iVar1 = iVar10 + iVar5;
      uVar8 = *(int *)(iVar2 + 0x2c) + 0x18;
      if ((((0 < iVar1) && (iVar5 < 0x20)) && (*(int *)(iVar2 + 0x24) + uVar8 != 0)) &&
         ((int)uVar8 < 0x80)) {
        uVar4 = -uVar8;
        puVar3 = (undefined4 *)
                 (*(int *)(iVar2 + 0x34) + iVar10 * (((int)uVar4 < 0) - 1 & uVar4) * 2);
        iVar7 = *(int *)(iVar2 + 0x24) - (uVar4 & ((int)uVar4 < 0) - 1);
        uVar8 = ((int)uVar8 < 0) - 1 & uVar8;
        if (0x1f < (int)(iVar7 + uVar8)) {
          iVar7 = 0x1f - uVar8;
        }
        if (iVar5 < 0) {
          puVar3 = (undefined4 *)((int)puVar3 + iVar5 * -2);
          iVar5 = 0;
          iVar10 = iVar1;
        }
        if (0x1f < iVar10 + iVar5) {
          iVar10 = 0x1f - iVar5;
        }
        if (0 < iVar7) {
          puVar6 = (undefined4 *)(uVar8 * param_4 + param_3 + iVar5 * 2);
          param_3 = iVar7;
          do {
            uVar4 = (iVar10 * 2 < 0) - 1 & iVar10 * 2;
            puVar9 = puVar3;
            puVar11 = puVar6;
            for (uVar8 = uVar4 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
              *puVar11 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar11 = puVar11 + 1;
            }
            for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
              *(undefined1 *)puVar11 = *(undefined1 *)puVar9;
              puVar9 = (undefined4 *)((int)puVar9 + 1);
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

