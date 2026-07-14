/* ComposeAvatarSprites - 0x004d1500 in the original binary.
 *
 * The in-battle avatar compositor. Called as
 * ComposeAvatarSprites(slot, bodyId, headId, glassesId, flagId) - it builds the
 * four avatar part sprite names and LoadSpriteSet's them into a 32 KB buffer:
 * %cb%05d.img (body, param_2), %ch%05d.img (head, param_3), %cg%05d.img
 * (glasses, param_4), mf%05d.img (flag, param_5), plus their large "...l.img"
 * in-battle variants. The gender char is taken from the player's stored avatar
 * record (g_clientContext + 0x501fe + slot*8, high bit -> 'm'/'f').
 *
 * This is the handler for battle action 0xf00b (an in-battle avatar/costume
 * change); the peer lobby compositor is LoadAvatarSprites (0x4141b0). See
 * FILEFORMATS.md "Avatar.xfs". IMPORTANT: this was previously mis-named
 * "LoadTerrainDeformationFrame" and 0xf00b mis-read as "terrain deformation" -
 * the mf/%cb/%cg/%ch strings are avatar parts, not map/color-channel frames.
 *
 * Function IDENTITY is confirmed; the BODY is a raw/near-verbatim Ghidra port,
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void ComposeAvatarSprites
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined1 *puVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  undefined1 *puVar11;
  undefined4 *puVar12;
  uint uVar13;
  undefined4 *puVar14;
  int local_80b0;
  undefined4 *local_80ac;
  int local_80a8;
  int local_80a0;
  int local_809c;
  int local_808c;
  char local_8088 [128];
  undefined4 local_8008 [63];
  undefined1 local_7f0a [32258];
  undefined1 local_108 [252];
  undefined4 uStack_c;
  
  uStack_c = 0x4d1510;
  _sprintf(local_8088,s_mf_05d_img_0055220c,param_5);
  LoadSpriteSet(&DAT_00ea0e18,100000);
  _sprintf(local_8088,s__cb_05d_img_00552200,
           (int)(char)((-((*(ushort *)(g_clientContext + 0x501fe + param_1 * 8) & 0x8000) != 0) & 7U) +
                      0x66),param_2);
  LoadSpriteSet(&DAT_00ea0e18,0x186a1);
  _sprintf(local_8088,s__cg_05d_img_005521f4,
           (int)(char)((-((*(ushort *)(g_clientContext + 0x50202 + param_1 * 8) & 0x8000) != 0) & 7U) +
                      0x66),param_4);
  LoadSpriteSet(&DAT_00ea0e18,0x186a2);
  _sprintf(local_8088,s__ch_05d_img_005521e8,
           (int)(char)((-((*(ushort *)(g_clientContext + 0x50200 + param_1 * 8) & 0x8000) != 0) & 7U) +
                      0x66),param_3);
  LoadSpriteSet(&DAT_00ea0e18,0x186a3);
  uVar10 = param_1 + 200000;
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar13 = puVar12[1];
  if (uVar13 <= uVar10) {
LAB_004d1648:
    if (uVar13 != uVar10) goto code_r0x004d164a;
    puVar6 = (undefined4 *)puVar12[4];
    while (puVar6 != puVar12) {
      puVar14 = (undefined4 *)*puVar6;
      puVar6 = (undefined4 *)puVar6[4];
      (*(code *)*puVar14)(1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_004d1675:
  local_80b0 = 0;
LAB_004d1680:
  puVar12 = local_8008;
  for (iVar5 = 0x2000; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  FUN_00414070(local_8008);
  FUN_00414070(local_8008);
  FUN_00414070(local_8008);
  FUN_00414070(local_8008);
  iVar5 = 0;
  puVar12 = local_8008;
  do {
    iVar2 = 0;
    puVar6 = puVar12;
    do {
      if ((*(byte *)((int)puVar6 + 1) & 0xf0) != 0) {
        iVar2 = 0x7f;
        puVar11 = local_108;
        goto LAB_004d1810;
      }
      iVar2 = iVar2 + 1;
      puVar6 = (undefined4 *)((int)puVar6 + 2);
    } while (iVar2 < 0x80);
    iVar5 = iVar5 + 1;
    puVar12 = puVar12 + 0x40;
  } while (iVar5 < 0x80);
  goto LAB_004d1a01;
code_r0x004d164a:
  puVar12 = (undefined4 *)puVar12[7];
  uVar13 = puVar12[1];
  if (uVar10 < uVar13) goto LAB_004d1675;
  goto LAB_004d1648;
LAB_004d1810:
  do {
    iVar3 = 0;
    puVar7 = puVar11;
    do {
      iVar1 = iVar2;
      if ((puVar7[1] & 0xf0) != 0) goto LAB_004d1836;
      iVar3 = iVar3 + 1;
      puVar7 = puVar7 + 2;
    } while (iVar3 < 0x80);
    iVar2 = iVar2 + -1;
    puVar11 = puVar11 + -0x100;
    iVar1 = local_809c;
  } while (-1 < iVar2);
LAB_004d1836:
  local_809c = iVar1;
  iVar2 = 0;
  puVar12 = local_8008;
  do {
    iVar3 = 0;
    puVar6 = puVar12;
    do {
      iVar1 = iVar2;
      if ((*(byte *)((int)puVar6 + 1) & 0xf0) != 0) goto LAB_004d1870;
      iVar3 = iVar3 + 1;
      puVar6 = puVar6 + 0x40;
    } while (iVar3 < 0x80);
    iVar2 = iVar2 + 1;
    puVar12 = (undefined4 *)((int)puVar12 + 2);
    iVar1 = local_80a8;
  } while (iVar2 < 0x80);
LAB_004d1870:
  local_80a8 = iVar1;
  iVar2 = 0x7f;
  puVar11 = local_7f0a;
  do {
    iVar3 = 0;
    puVar7 = puVar11;
    do {
      iVar1 = iVar2;
      if ((puVar7[1] & 0xf0) != 0) goto LAB_004d18a6;
      iVar3 = iVar3 + 1;
      puVar7 = puVar7 + 0x100;
    } while (iVar3 < 0x80);
    iVar2 = iVar2 + -1;
    puVar11 = puVar11 + -2;
    iVar1 = local_80a0;
  } while (-1 < iVar2);
LAB_004d18a6:
  local_80a0 = iVar1;
  puVar12 = operator_new(0x50);
  if (puVar12 == (undefined4 *)0x0) {
    puVar12 = (undefined4 *)0x0;
  }
  else {
    puVar12[1] = param_1 + 200000;
    puVar12[2] = local_80b0;
    puVar12[3] = 0;
    puVar12[4] = 0;
    *(undefined1 *)(puVar12 + 5) = 0;
    *(undefined1 *)((int)puVar12 + 0x15) = 0;
    *puVar12 = &PTR_FUN_00557524;
    *(undefined1 *)((int)puVar12 + 0x1b) = 0xff;
    *(undefined1 *)((int)puVar12 + 0x1a) = 0;
    *(undefined1 *)((int)puVar12 + 0x19) = 0xff;
    puVar12[8] = 0;
    puVar12[9] = 0;
    puVar12[0xb] = 0;
    puVar12[10] = 0;
    *(undefined1 *)(puVar12 + 0xc) = 0;
    puVar12[0xd] = 0;
    puVar12[0xe] = 0;
  }
  iVar3 = (local_80a0 - local_80a8) + 1;
  iVar2 = (local_809c - iVar5) + 1;
  puVar12[9] = iVar2;
  iVar2 = iVar2 * iVar3;
  puVar12[0xf] = iVar2 * 2;
  *(undefined1 *)(puVar12 + 6) = 2;
  puVar12[8] = iVar3;
  puVar12[10] = local_80a8 + -0x40;
  puVar12[0xb] = iVar5 + -0x40;
  *(undefined1 *)(puVar12 + 0xc) = 0;
  pvVar4 = operator_new(iVar2 * 2);
  puVar12[0xd] = pvVar4;
  uVar10 = 0;
  if (puVar12[9] != 0) {
    local_80ac = (undefined4 *)((int)local_8008 + (iVar5 * 0x80 + local_80a8) * 2);
    do {
      uVar13 = puVar12[8] * 2;
      uVar13 = ((int)uVar13 < 0) - 1 & uVar13;
      puVar6 = local_80ac;
      puVar14 = (undefined4 *)(puVar12[0xd] + puVar12[8] * uVar10 * 2);
      for (uVar8 = uVar13 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *puVar14 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar14 = puVar14 + 1;
      }
      for (uVar13 = uVar13 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
        *(undefined1 *)puVar14 = *(undefined1 *)puVar6;
        puVar6 = (undefined4 *)((int)puVar6 + 1);
        puVar14 = (undefined4 *)((int)puVar14 + 1);
      }
      uVar10 = uVar10 + 1;
      local_80ac = local_80ac + 0x40;
    } while (uVar10 < (uint)puVar12[9]);
  }
  iVar5 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar10 = *(uint *)(iVar5 + 4);
  while (uVar10 <= (uint)puVar12[1]) {
    if (uVar10 == puVar12[1]) goto LAB_004d19cc;
    iVar5 = *(int *)(iVar5 + 0x1c);
    uVar10 = *(uint *)(iVar5 + 4);
  }
  iVar5 = CreateActiveObjectLayer((int)&DAT_00ea0e18);
LAB_004d19cc:
  uVar10 = puVar12[2];
  if (uVar10 != 0xffffffff) {
    iVar5 = *(int *)(iVar5 + 0x10);
    uVar13 = *(uint *)(iVar5 + 8);
    if (uVar13 <= uVar10) {
      do {
        if (uVar13 == uVar10) {
          (**(code **)*puVar12)(1);
          goto LAB_004d1a01;
        }
        iVar5 = *(int *)(iVar5 + 0x10);
        uVar13 = *(uint *)(iVar5 + 8);
      } while (uVar13 <= (uint)puVar12[2]);
    }
  }
  puVar12[4] = iVar5;
  puVar12[3] = *(undefined4 *)(iVar5 + 0xc);
  *(undefined4 **)(*(int *)(iVar5 + 0xc) + 0x10) = puVar12;
  *(undefined4 **)(iVar5 + 0xc) = puVar12;
LAB_004d1a01:
  local_80b0 = local_80b0 + 1;
  if (0x2b < local_80b0) goto code_r0x004d1a13;
  goto LAB_004d1680;
code_r0x004d1a13:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar10 = puVar12[1];
  if (uVar10 < 0x186a1) {
LAB_004d1a25:
    if (uVar10 != 100000) goto code_r0x004d1a27;
    puVar6 = (undefined4 *)puVar12[4];
    while (puVar6 != puVar12) {
      puVar14 = (undefined4 *)*puVar6;
      puVar6 = (undefined4 *)puVar6[4];
      (*(code *)*puVar14)(1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_004d1a5c:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar10 = puVar12[1];
  if (uVar10 < 0x186a2) {
LAB_004d1a6e:
    if (uVar10 != 0x186a1) goto code_r0x004d1a70;
    puVar6 = (undefined4 *)puVar12[4];
    while (puVar6 != puVar12) {
      puVar14 = (undefined4 *)*puVar6;
      puVar6 = (undefined4 *)puVar6[4];
      (*(code *)*puVar14)(1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_004d1a9b:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar10 = puVar12[1];
  if (uVar10 < 0x186a3) {
LAB_004d1aad:
    if (uVar10 != 0x186a2) goto code_r0x004d1aaf;
    puVar6 = (undefined4 *)puVar12[4];
    while (puVar6 != puVar12) {
      puVar14 = (undefined4 *)*puVar6;
      puVar6 = (undefined4 *)puVar6[4];
      (*(code *)*puVar14)(1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_004d1ada:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar10 = puVar12[1];
  if (uVar10 < 0x186a4) {
LAB_004d1aec:
    if (uVar10 != 0x186a3) goto code_r0x004d1aee;
    puVar6 = (undefined4 *)puVar12[4];
    while (puVar6 != puVar12) {
      puVar14 = (undefined4 *)*puVar6;
      puVar6 = (undefined4 *)puVar6[4];
      (*(code *)*puVar14)(1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_004d1b19:
  _sprintf(local_8088,s_mf_05dl_img_005521dc,param_5);
  LoadSpriteSet(&DAT_00ea0e18,100000);
  _sprintf(local_8088,s__cb_05dl_img_005521cc,
           (int)(char)((-((*(ushort *)(g_clientContext + 0x501fe + param_1 * 8) & 0x8000) != 0) & 7U) +
                      0x66),param_2);
  LoadSpriteSet(&DAT_00ea0e18,0x186a1);
  _sprintf(local_8088,s__cg_05dl_img_005521bc,
           (int)(char)((-((*(ushort *)(g_clientContext + 0x50202 + param_1 * 8) & 0x8000) != 0) & 7U) +
                      0x66),param_4);
  LoadSpriteSet(&DAT_00ea0e18,0x186a2);
  _sprintf(local_8088,s__ch_05dl_img_005521ac,
           (int)(char)((-((*(ushort *)(g_clientContext + 0x50200 + param_1 * 8) & 0x8000) != 0) & 7U) +
                      0x66),param_3);
  LoadSpriteSet(&DAT_00ea0e18,0x186a3);
  uVar10 = param_1 + 300000;
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar13 = puVar12[1];
  if (uVar13 <= uVar10) {
LAB_004d1c52:
    if (uVar13 != uVar10) goto code_r0x004d1c54;
    puVar6 = (undefined4 *)puVar12[4];
    while (puVar6 != puVar12) {
      puVar14 = (undefined4 *)*puVar6;
      puVar6 = (undefined4 *)puVar6[4];
      (*(code *)*puVar14)(1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_004d1c7c:
  local_80b0 = 0;
LAB_004d1c82:
  puVar12 = local_8008;
  for (iVar5 = 0x2000; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  FUN_00414070(local_8008);
  FUN_00414070(local_8008);
  FUN_00414070(local_8008);
  FUN_00414070(local_8008);
  iVar5 = 0;
  puVar12 = local_8008;
  do {
    iVar2 = 0;
    puVar6 = puVar12;
    do {
      if ((*(byte *)((int)puVar6 + 1) & 0xf0) != 0) {
        iVar2 = 0x7f;
        puVar11 = local_108;
        goto LAB_004d1e07;
      }
      iVar2 = iVar2 + 1;
      puVar6 = (undefined4 *)((int)puVar6 + 2);
    } while (iVar2 < 0x80);
    iVar5 = iVar5 + 1;
    puVar12 = puVar12 + 0x40;
  } while (iVar5 < 0x80);
  goto LAB_004d2005;
code_r0x004d1a27:
  puVar12 = (undefined4 *)puVar12[7];
  uVar10 = puVar12[1];
  if (100000 < uVar10) goto LAB_004d1a5c;
  goto LAB_004d1a25;
code_r0x004d1a70:
  puVar12 = (undefined4 *)puVar12[7];
  uVar10 = puVar12[1];
  if (0x186a1 < uVar10) goto LAB_004d1a9b;
  goto LAB_004d1a6e;
code_r0x004d1aaf:
  puVar12 = (undefined4 *)puVar12[7];
  uVar10 = puVar12[1];
  if (0x186a2 < uVar10) goto LAB_004d1ada;
  goto LAB_004d1aad;
code_r0x004d1aee:
  puVar12 = (undefined4 *)puVar12[7];
  uVar10 = puVar12[1];
  if (0x186a3 < uVar10) goto LAB_004d1b19;
  goto LAB_004d1aec;
code_r0x004d1c54:
  puVar12 = (undefined4 *)puVar12[7];
  uVar13 = puVar12[1];
  if (uVar10 < uVar13) goto LAB_004d1c7c;
  goto LAB_004d1c52;
LAB_004d1e07:
  do {
    iVar3 = 0;
    puVar7 = puVar11;
    do {
      iVar1 = iVar2;
      if ((puVar7[1] & 0xf0) != 0) goto LAB_004d1e32;
      iVar3 = iVar3 + 1;
      puVar7 = puVar7 + 2;
    } while (iVar3 < 0x80);
    iVar2 = iVar2 + -1;
    puVar11 = puVar11 + -0x100;
    iVar1 = local_808c;
  } while (-1 < iVar2);
LAB_004d1e32:
  local_808c = iVar1;
  iVar2 = 0;
  puVar12 = local_8008;
  do {
    iVar3 = 0;
    puVar6 = puVar12;
    do {
      iVar1 = iVar2;
      if ((*(byte *)((int)puVar6 + 1) & 0xf0) != 0) goto LAB_004d1e6a;
      iVar3 = iVar3 + 1;
      puVar6 = puVar6 + 0x40;
    } while (iVar3 < 0x80);
    iVar2 = iVar2 + 1;
    puVar12 = (undefined4 *)((int)puVar12 + 2);
    iVar1 = local_80a8;
  } while (iVar2 < 0x80);
LAB_004d1e6a:
  local_80a8 = iVar1;
  iVar2 = 0x7f;
  puVar11 = local_7f0a;
  do {
    iVar3 = 0;
    puVar7 = puVar11;
    do {
      iVar1 = iVar2;
      if ((puVar7[1] & 0xf0) != 0) goto LAB_004d1ea2;
      iVar3 = iVar3 + 1;
      puVar7 = puVar7 + 0x100;
    } while (iVar3 < 0x80);
    iVar2 = iVar2 + -1;
    puVar11 = puVar11 + -2;
    iVar1 = local_80a0;
  } while (-1 < iVar2);
LAB_004d1ea2:
  local_80a0 = iVar1;
  puVar12 = operator_new(0x50);
  if (puVar12 == (undefined4 *)0x0) {
    puVar12 = (undefined4 *)0x0;
  }
  else {
    puVar12[1] = uVar10;
    puVar12[2] = local_80b0;
    puVar12[3] = 0;
    puVar12[4] = 0;
    *(undefined1 *)(puVar12 + 5) = 0;
    *(undefined1 *)((int)puVar12 + 0x15) = 0;
    *puVar12 = &PTR_FUN_00557524;
    *(undefined1 *)((int)puVar12 + 0x1b) = 0xff;
    *(undefined1 *)((int)puVar12 + 0x1a) = 0;
    *(undefined1 *)((int)puVar12 + 0x19) = 0xff;
    puVar12[8] = 0;
    puVar12[9] = 0;
    puVar12[0xb] = 0;
    puVar12[10] = 0;
    *(undefined1 *)(puVar12 + 0xc) = 0;
    puVar12[0xd] = 0;
    puVar12[0xe] = 0;
  }
  iVar3 = (local_80a0 - local_80a8) + 1;
  iVar2 = (local_808c - iVar5) + 1;
  puVar12[9] = iVar2;
  iVar2 = iVar2 * iVar3;
  puVar12[0xf] = iVar2 * 2;
  puVar12[10] = local_80a8 + -0x40;
  *(undefined1 *)(puVar12 + 6) = 2;
  puVar12[8] = iVar3;
  puVar12[0xb] = iVar5 + -0x40;
  *(undefined1 *)(puVar12 + 0xc) = 0;
  pvVar4 = operator_new(iVar2 * 2);
  puVar12[0xd] = pvVar4;
  uVar13 = 0;
  if (puVar12[9] != 0) {
    local_80ac = (undefined4 *)((int)local_8008 + (iVar5 * 0x80 + local_80a8) * 2);
    do {
      uVar8 = puVar12[8] * 2;
      uVar8 = ((int)uVar8 < 0) - 1 & uVar8;
      puVar6 = local_80ac;
      puVar14 = (undefined4 *)(puVar12[0xd] + puVar12[8] * uVar13 * 2);
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *puVar14 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar14 = puVar14 + 1;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined1 *)puVar14 = *(undefined1 *)puVar6;
        puVar6 = (undefined4 *)((int)puVar6 + 1);
        puVar14 = (undefined4 *)((int)puVar14 + 1);
      }
      uVar13 = uVar13 + 1;
      local_80ac = local_80ac + 0x40;
    } while (uVar13 < (uint)puVar12[9]);
  }
  iVar5 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar13 = *(uint *)(iVar5 + 4);
  while (uVar13 <= (uint)puVar12[1]) {
    if (uVar13 == puVar12[1]) goto LAB_004d1fca;
    iVar5 = *(int *)(iVar5 + 0x1c);
    uVar13 = *(uint *)(iVar5 + 4);
  }
  iVar5 = CreateActiveObjectLayer((int)&DAT_00ea0e18);
LAB_004d1fca:
  uVar13 = puVar12[2];
  if (uVar13 != 0xffffffff) {
    iVar5 = *(int *)(iVar5 + 0x10);
    uVar8 = *(uint *)(iVar5 + 8);
    if (uVar8 <= uVar13) {
      do {
        if (uVar8 == uVar13) {
          (**(code **)*puVar12)(1);
          goto LAB_004d2005;
        }
        iVar5 = *(int *)(iVar5 + 0x10);
        uVar8 = *(uint *)(iVar5 + 8);
      } while (uVar8 <= (uint)puVar12[2]);
    }
  }
  puVar12[4] = iVar5;
  puVar12[3] = *(undefined4 *)(iVar5 + 0xc);
  *(undefined4 **)(*(int *)(iVar5 + 0xc) + 0x10) = puVar12;
  *(undefined4 **)(iVar5 + 0xc) = puVar12;
LAB_004d2005:
  local_80b0 = local_80b0 + 1;
  if (0x2b < local_80b0) goto code_r0x004d2013;
  goto LAB_004d1c82;
code_r0x004d2027:
  puVar12 = (undefined4 *)puVar12[7];
  uVar10 = puVar12[1];
  if (100000 < uVar10) goto LAB_004d205c;
  goto LAB_004d2025;
code_r0x004d2070:
  puVar12 = (undefined4 *)puVar12[7];
  uVar10 = puVar12[1];
  if (0x186a1 < uVar10) goto LAB_004d209b;
  goto LAB_004d206e;
code_r0x004d2013:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar10 = puVar12[1];
  if (uVar10 < 0x186a1) {
LAB_004d2025:
    if (uVar10 != 100000) goto code_r0x004d2027;
    puVar6 = (undefined4 *)puVar12[4];
    while (puVar6 != puVar12) {
      puVar14 = (undefined4 *)*puVar6;
      puVar6 = (undefined4 *)puVar6[4];
      (*(code *)*puVar14)(1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_004d205c:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar10 = puVar12[1];
  if (uVar10 < 0x186a2) {
LAB_004d206e:
    if (uVar10 != 0x186a1) goto code_r0x004d2070;
    puVar6 = (undefined4 *)puVar12[4];
    while (puVar6 != puVar12) {
      puVar14 = (undefined4 *)*puVar6;
      puVar6 = (undefined4 *)puVar6[4];
      (*(code *)*puVar14)(1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_004d209b:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar10 = puVar12[1];
  while( true ) {
    if (0x186a2 < uVar10) goto LAB_004d20da;
    if (uVar10 == 0x186a2) break;
    puVar12 = (undefined4 *)puVar12[7];
    uVar10 = puVar12[1];
  }
  puVar6 = (undefined4 *)puVar12[4];
  while (puVar6 != puVar12) {
    puVar14 = (undefined4 *)*puVar6;
    puVar6 = (undefined4 *)puVar6[4];
    (*(code *)*puVar14)(1);
  }
  puVar12[3] = puVar12;
  puVar12[4] = puVar12;
LAB_004d20da:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar10 = puVar12[1];
  if (uVar10 < 0x186a4) {
    while (uVar10 != 0x186a3) {
      puVar12 = (undefined4 *)puVar12[7];
      uVar10 = puVar12[1];
      if (0x186a3 < uVar10) {
        return;
      }
    }
    puVar6 = (undefined4 *)puVar12[4];
    while (puVar6 != puVar12) {
      puVar14 = (undefined4 *)*puVar6;
      puVar6 = (undefined4 *)puVar6[4];
      (*(code *)*puVar14)(1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
  return;
}

