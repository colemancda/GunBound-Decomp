/* BlitAnnouncementFrameToYesooriTexture - 0x004b3b60 in the original
 * binary.
 *
 * Copies frame regEax of sprite set 0x1bbc - loaded as "yesoori.img",
 * the battle announcement banner art (READY / SOLO START! / GREAT!!!
 * etc.) - into the 16bpp surface param_1 with pitch param_2, re-centring
 * the frame's hotspot by +0x80 and clamping to the 256x256 canvas.
 *
 * Everything here was already established from outside by
 * src/battle/SpawnBattleAnnouncement.c's naming evidence, which walks
 * through this exact address: the one caller, 0x4b3d8d, is the
 * announcement object's uncarved Draw at 0x4b3d50 (slot 3 of vtable
 * 0x5566c0, the class-id-0x2e635 object SpawnBattleAnnouncement builds
 * via the FUN_004b3b10 ctor), which passes the surface pointer and pitch the
 * once-per-frame State11_InBattle_ClearEffectTextures lock stores at
 * g_clientContext+0x23254/+0x23258 - the cells of the texture the
 * original itself names "YesooriTexture" (s_YesooriTexture_005567d0) -
 * and State11_InBattle_RenderModeIcons then draws that texture as the
 * screen-centre quad while the +0x2325c flag is up.  This function is
 * the only code that reads sprite set 0x1bbc.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


uint BlitAnnouncementFrameToYesooriTexture(int param_1,int param_2,uint regEax)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  uint uVar8;
  undefined4 *puVar9;
  int iVar10;
  undefined4 *puVar11;
  
  uVar4 = *(uint *)(DAT_00ea0e1c + 0x1c);
  uVar5 = *(uint *)(uVar4 + 4);
  if (uVar5 < 0x1bbd) {
    while (uVar5 != 0x1bbc) {
      uVar4 = *(uint *)(uVar4 + 0x1c);
      uVar5 = *(uint *)(uVar4 + 4);
      if (0x1bbc < uVar5) {
        return uVar4 & 0xffffff00;
      }
    }
    iVar1 = *(int *)(uVar4 + 0x10);
    uVar4 = *(uint *)(iVar1 + 8);
    while (uVar4 <= regEax) {
      if (uVar4 == regEax) {
        uVar5 = *(uint *)(iVar1 + 0x20);
        iVar6 = *(int *)(iVar1 + 0x28) + 0x80;
        uVar4 = uVar5 + iVar6;
        uVar8 = *(int *)(iVar1 + 0x2c) + 0x80;
        uVar2 = uVar4;
        if ((0 < (int)uVar4) && (iVar6 < 0x100)) {
          uVar2 = *(int *)(iVar1 + 0x24) + uVar8;
          if ((uVar2 != 0) && ((int)uVar8 < 0x100)) {
            uVar2 = -uVar8;
            puVar3 = (undefined4 *)
                     (*(int *)(iVar1 + 0x34) + uVar5 * (((int)uVar2 < 0) - 1 & uVar2) * 2);
            iVar10 = *(int *)(iVar1 + 0x24) - (((int)uVar2 < 0) - 1 & uVar2);
            uVar8 = ((int)uVar8 < 0) - 1 & uVar8;
            if (0xff < (int)(iVar10 + uVar8)) {
              iVar10 = 0xff - uVar8;
            }
            if (iVar6 < 0) {
              puVar3 = (undefined4 *)((int)puVar3 + iVar6 * -2);
              iVar6 = 0;
              uVar5 = uVar4;
            }
            if (0xff < (int)(uVar5 + iVar6)) {
              uVar5 = 0xff - iVar6;
            }
            if (0 < iVar10) {
              puVar7 = (undefined4 *)(uVar8 * param_2 + param_1 + iVar6 * 2);
              param_1 = iVar10;
              do {
                uVar2 = ((int)(uVar5 * 2) < 0) - 1 & uVar5 * 2;
                puVar9 = puVar3;
                puVar11 = puVar7;
                for (uVar4 = uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                  *puVar11 = *puVar9;
                  puVar9 = puVar9 + 1;
                  puVar11 = puVar11 + 1;
                }
                for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
                  *(undefined1 *)puVar11 = *(undefined1 *)puVar9;
                  puVar9 = (undefined4 *)((int)puVar9 + 1);
                  puVar11 = (undefined4 *)((int)puVar11 + 1);
                }
                puVar3 = (undefined4 *)((int)puVar3 + *(int *)(iVar1 + 0x20) * 2);
                puVar7 = (undefined4 *)((int)puVar7 + param_2);
                param_1 = param_1 + -1;
              } while (param_1 != 0);
            }
            return CONCAT31((int3)((uint)puVar3 >> 8),1);
          }
        }
        return uVar2 & 0xffffff00;
      }
      iVar1 = *(int *)(iVar1 + 0x10);
      uVar4 = *(uint *)(iVar1 + 8);
    }
  }
  return uVar4 & 0xffffff00;
}

