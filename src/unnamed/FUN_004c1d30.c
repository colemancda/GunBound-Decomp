/* FUN_004c1d30 - 0x004c1d30 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004c1d30(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  uint uVar27;
  uint uVar28;
  int iVar29;
  undefined4 *puVar30;
  undefined4 auStack_c08 [4];
  undefined4 uStack_bf8;
  undefined4 uStack_be4;
  undefined4 auStack_b88 [4];
  undefined4 uStack_b78;
  undefined4 uStack_b64;
  undefined4 local_b08 [4];
  undefined4 uStack_af8;
  undefined4 uStack_ae4;
  undefined4 auStack_a88 [4];
  undefined4 uStack_a78;
  undefined4 uStack_a64;
  undefined4 auStack_a08 [4];
  undefined4 uStack_9f8;
  undefined4 uStack_9e4;
  undefined4 auStack_988 [4];
  undefined4 uStack_978;
  undefined4 uStack_964;
  undefined4 local_908 [4];
  undefined4 uStack_8f8;
  undefined4 uStack_8e4;
  undefined4 auStack_888 [4];
  undefined4 uStack_878;
  undefined4 uStack_864;
  undefined4 auStack_808 [4];
  undefined4 uStack_7f8;
  undefined4 uStack_7e4;
  undefined4 auStack_788 [4];
  undefined4 uStack_778;
  undefined4 uStack_764;
  undefined4 auStack_708 [4];
  undefined4 uStack_6f8;
  undefined4 uStack_6e4;
  undefined4 auStack_688 [4];
  undefined4 uStack_678;
  undefined4 uStack_664;
  undefined4 auStack_608 [4];
  undefined4 uStack_5f8;
  undefined4 uStack_5e4;
  undefined4 auStack_588 [4];
  undefined4 uStack_578;
  undefined4 uStack_564;
  undefined4 auStack_508 [4];
  undefined4 uStack_4f8;
  undefined4 uStack_4e4;
  undefined4 auStack_488 [4];
  undefined4 uStack_478;
  undefined4 uStack_464;
  undefined4 auStack_408 [4];
  undefined4 uStack_3f8;
  undefined4 uStack_3e4;
  undefined4 auStack_388 [4];
  undefined4 uStack_378;
  undefined4 uStack_364;
  undefined4 auStack_308 [4];
  undefined4 uStack_2f8;
  undefined4 uStack_2e4;
  undefined4 auStack_288 [4];
  undefined4 uStack_278;
  undefined4 uStack_264;
  undefined4 auStack_208 [4];
  undefined4 uStack_1f8;
  undefined4 uStack_1e4;
  undefined4 auStack_188 [4];
  undefined4 uStack_178;
  undefined4 uStack_164;
  undefined4 auStack_108 [4];
  undefined4 uStack_f8;
  undefined4 uStack_e4;
  undefined4 auStack_88 [4];
  undefined4 uStack_78;
  undefined4 uStack_64;
  
  iVar2 = FindTextureCacheEntryByName(s_AvataTexture1_0055565c);
  iVar3 = FindTextureCacheEntryByName(s_AvataTexture2_00556914);
  iVar4 = FindTextureCacheEntryByName(s_AvataEffectTexture1_00556900);
  iVar5 = FindTextureCacheEntryByName(s_AvataEffectTexture2_005568ec);
  iVar6 = FindTextureCacheEntryByName(s_CharacterTexture1_005568d8);
  iVar7 = FindTextureCacheEntryByName(s_CharacterTexture2_005568c4);
  iVar8 = FindTextureCacheEntryByName(s_TagTexture_005568b8);
  iVar9 = FindTextureCacheEntryByName(s_CharEffectTexture1_005568a4);
  iVar10 = FindTextureCacheEntryByName(s_CharEffectTexture2_00556890);
  iVar11 = FindTextureCacheEntryByName(s_BulletTexture1_00556880);
  iVar12 = FindTextureCacheEntryByName(s_BulletTexture2_00556870);
  iVar13 = FindTextureCacheEntryByName(s_FlameTexture1_00556860);
  iVar14 = FindTextureCacheEntryByName(s_FlameTexture2_00556850);
  iVar15 = FindTextureCacheEntryByName(s_FlameTexture3_00556840);
  iVar16 = FindTextureCacheEntryByName(s_FlameTexture4_00556830);
  iVar17 = FindTextureCacheEntryByName(s_RayonTexture1_00556820);
  iVar18 = FindTextureCacheEntryByName(s_RayonTexture2_00556810);
  iVar19 = FindTextureCacheEntryByName(s_SpecialTexture1_00556800);
  iVar20 = FindTextureCacheEntryByName(s_SpecialTexture2_005567f0);
  iVar21 = FindTextureCacheEntryByName(s_RiderTexture_005567e0);
  iVar22 = FindTextureCacheEntryByName(s_YesooriTexture_005567d0);
  iVar23 = FindTextureCacheEntryByName(s_JewelTexture_005567c0);
  iVar24 = FindTextureCacheEntryByName(s_ThorTexture1_005567b0);
  iVar25 = FindTextureCacheEntryByName(s_ThorTexture2_005567a0);
  if (iVar2 != 0) {
    puVar30 = local_908;
    for (iVar26 = 0x1f; iVar26 != 0; iVar26 = iVar26 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    local_908[0] = 0x7c;
    piVar1 = *(int **)(*(int *)(iVar2 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,local_908,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x1fe44) = uStack_8e4;
    *(undefined4 *)(iVar26 + 0x1fe4c) = uStack_8f8;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x1fe4c);
      puVar30 = (undefined4 *)(uVar28 * iVar29 + *(int *)(iVar26 + 0x1fe44));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar3 != 0) {
    iVar26 = *(int *)(iVar3 + 0x94);
    puVar30 = local_b08;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    local_b08[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,local_b08,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x1fe48) = uStack_ae4;
    *(undefined4 *)(iVar26 + 0x1fe50) = uStack_af8;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x1fe50);
      puVar30 = (undefined4 *)(uVar28 * iVar29 + *(int *)(iVar26 + 0x1fe48));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar4 != 0) {
    iVar26 = *(int *)(iVar4 + 0x94);
    puVar30 = auStack_308;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_308[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_308,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x1fe54) = uStack_2e4;
    *(undefined4 *)(iVar26 + 0x1fe5c) = uStack_2f8;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x1fe5c);
      puVar30 = (undefined4 *)(uVar28 * iVar29 + *(int *)(iVar26 + 0x1fe54));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar5 != 0) {
    iVar26 = *(int *)(iVar5 + 0x94);
    puVar30 = auStack_a08;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_a08[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_a08,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x1fe58) = uStack_9e4;
    *(undefined4 *)(iVar26 + 0x1fe60) = uStack_9f8;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x1fe60);
      puVar30 = (undefined4 *)(uVar28 * iVar29 + *(int *)(iVar26 + 0x1fe58));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar6 != 0) {
    iVar26 = *(int *)(iVar6 + 0x94);
    puVar30 = auStack_508;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_508[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_508,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x1fe1c) = uStack_4e4;
    *(undefined4 *)(iVar26 + 0x1fe24) = uStack_4f8;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x1fe24);
      puVar30 = (undefined4 *)(uVar28 * iVar29 + *(int *)(iVar26 + 0x1fe1c));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar7 != 0) {
    iVar26 = *(int *)(iVar7 + 0x94);
    puVar30 = auStack_c08;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_c08[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_c08,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x1fe20) = uStack_be4;
    *(undefined4 *)(iVar26 + 0x1fe28) = uStack_bf8;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x1fe28);
      puVar30 = (undefined4 *)(uVar28 * iVar29 + *(int *)(iVar26 + 0x1fe20));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar8 != 0) {
    iVar26 = *(int *)(iVar8 + 0x94);
    puVar30 = auStack_108;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_108[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_108,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x1fe2c) = uStack_e4;
    *(undefined4 *)(iVar26 + 0x1fe30) = uStack_f8;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x1fe30);
      puVar30 = (undefined4 *)(uVar28 * iVar29 + *(int *)(iVar26 + 0x1fe2c));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar9 != 0) {
    iVar26 = *(int *)(iVar9 + 0x94);
    puVar30 = auStack_808;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_808[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_808,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x1fe34) = uStack_7e4;
    *(undefined4 *)(iVar26 + 0x1fe3c) = uStack_7f8;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x1fe3c);
      puVar30 = (undefined4 *)(uVar28 * iVar29 + *(int *)(iVar26 + 0x1fe34));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar10 != 0) {
    iVar26 = *(int *)(iVar10 + 0x94);
    puVar30 = auStack_408;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_408[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_408,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x1fe38) = uStack_3e4;
    *(undefined4 *)(iVar26 + 0x1fe40) = uStack_3f8;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x1fe40);
      puVar30 = (undefined4 *)(uVar28 * iVar29 + *(int *)(iVar26 + 0x1fe38));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar11 != 0) {
    iVar26 = *(int *)(iVar11 + 0x94);
    puVar30 = auStack_708;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_708[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_708,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x20b94) = uStack_6e4;
    *(undefined4 *)(iVar26 + 0x20b98) = uStack_6f8;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x20b98);
      puVar30 = (undefined4 *)(uVar28 * iVar29 + *(int *)(iVar26 + 0x20b94));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar12 != 0) {
    iVar26 = *(int *)(iVar12 + 0x94);
    puVar30 = auStack_208;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_208[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_208,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x20b9c) = uStack_1e4;
    *(undefined4 *)(iVar26 + 0x20ba0) = uStack_1f8;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x20ba0);
      puVar30 = (undefined4 *)(uVar28 * iVar29 + *(int *)(iVar26 + 0x20b9c));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar13 != 0) {
    iVar26 = *(int *)(iVar13 + 0x94);
    puVar30 = auStack_608;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_608[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_608,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x21624) = uStack_5e4;
    *(undefined4 *)(iVar26 + 0x21634) = uStack_5f8;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x21634);
      puVar30 = (undefined4 *)(uVar28 * iVar29 + *(int *)(iVar26 + 0x21624));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar14 != 0) {
    iVar26 = *(int *)(iVar14 + 0x94);
    puVar30 = auStack_b88;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_b88[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_b88,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x21628) = uStack_b64;
    *(undefined4 *)(iVar26 + 0x21638) = uStack_b78;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x21638);
      puVar30 = (undefined4 *)(uVar28 * iVar29 + *(int *)(iVar26 + 0x21628));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar15 != 0) {
    iVar26 = *(int *)(iVar15 + 0x94);
    puVar30 = auStack_a88;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_a88[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_a88,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x2162c) = uStack_a64;
    *(undefined4 *)(iVar26 + 0x2163c) = uStack_a78;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x2163c);
      puVar30 = (undefined4 *)(uVar28 * iVar29 + *(int *)(iVar26 + 0x2162c));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar16 != 0) {
    iVar26 = *(int *)(iVar16 + 0x94);
    puVar30 = auStack_988;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_988[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_988,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x21630) = uStack_964;
    *(undefined4 *)(iVar26 + 0x21640) = uStack_978;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x21640);
      puVar30 = (undefined4 *)(uVar28 * iVar29 + *(int *)(iVar26 + 0x21630));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar17 != 0) {
    iVar26 = *(int *)(iVar17 + 0x94);
    puVar30 = auStack_888;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_888[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_888,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x227c4) = uStack_864;
    *(undefined4 *)(iVar26 + 0x227cc) = uStack_878;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x227cc);
      puVar30 = (undefined4 *)(uVar28 * iVar29 + *(int *)(iVar26 + 0x227c4));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar18 != 0) {
    iVar26 = *(int *)(iVar18 + 0x94);
    puVar30 = auStack_788;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_788[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_788,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x227c8) = uStack_764;
    *(undefined4 *)(iVar26 + 0x227d0) = uStack_778;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x227d0);
      puVar30 = (undefined4 *)(iVar29 * uVar28 + *(int *)(iVar26 + 0x227c8));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar19 != 0) {
    iVar26 = *(int *)(iVar19 + 0x94);
    puVar30 = auStack_688;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_688[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_688,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x22d14) = uStack_664;
    *(undefined4 *)(iVar26 + 0x22d1c) = uStack_678;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x22d1c);
      puVar30 = (undefined4 *)(iVar29 * uVar28 + *(int *)(iVar26 + 0x22d14));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar20 != 0) {
    iVar26 = *(int *)(iVar20 + 0x94);
    puVar30 = auStack_588;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_588[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_588,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x22d18) = uStack_564;
    *(undefined4 *)(iVar26 + 0x22d20) = uStack_578;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x22d20);
      puVar30 = (undefined4 *)(iVar29 * uVar28 + *(int *)(iVar26 + 0x22d18));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar21 != 0) {
    iVar26 = *(int *)(iVar21 + 0x94);
    puVar30 = auStack_488;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_488[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_488,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x1fe64) = uStack_464;
    *(undefined4 *)(iVar26 + 0x1fe68) = uStack_478;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x1fe68);
      puVar30 = (undefined4 *)(iVar29 * uVar28 + *(int *)(iVar26 + 0x1fe64));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar22 != 0) {
    iVar26 = *(int *)(iVar22 + 0x94);
    puVar30 = auStack_388;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_388[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_388,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x23254) = uStack_364;
    *(undefined4 *)(iVar26 + 0x23258) = uStack_378;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x23258);
      puVar30 = (undefined4 *)(iVar29 * uVar28 + *(int *)(iVar26 + 0x23254));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar23 != 0) {
    iVar26 = *(int *)(iVar23 + 0x94);
    puVar30 = auStack_288;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_288[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_288,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x23270) = uStack_264;
    *(undefined4 *)(iVar26 + 0x23274) = uStack_278;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x23274);
      puVar30 = (undefined4 *)(iVar29 * uVar28 + *(int *)(iVar26 + 0x23270));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar24 != 0) {
    iVar26 = *(int *)(iVar24 + 0x94);
    puVar30 = auStack_188;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_188[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_188,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x23300) = uStack_164;
    *(undefined4 *)(iVar26 + 0x23308) = uStack_178;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x23308);
      puVar30 = (undefined4 *)(iVar29 * uVar28 + *(int *)(iVar26 + 0x23300));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  if (iVar25 != 0) {
    iVar26 = *(int *)(iVar25 + 0x94);
    puVar30 = auStack_88;
    for (iVar29 = 0x1f; iVar29 != 0; iVar29 = iVar29 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
    auStack_88[0] = 0x7c;
    piVar1 = *(int **)(iVar26 + 0x110);
    (**(code **)(*piVar1 + 100))(piVar1,0,auStack_88,0,0);
    iVar26 = DAT_005b3484;
    *(undefined4 *)(DAT_005b3484 + 0x23304) = uStack_64;
    *(undefined4 *)(iVar26 + 0x2330c) = uStack_78;
    iVar29 = 0;
    do {
      uVar28 = *(uint *)(iVar26 + 0x2330c);
      puVar30 = (undefined4 *)(iVar29 * uVar28 + *(int *)(iVar26 + 0x23304));
      for (uVar27 = uVar28 >> 2; uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar30 = 0;
        puVar30 = puVar30 + 1;
      }
      iVar29 = iVar29 + 1;
      for (uVar28 = uVar28 & 3; uVar28 != 0; uVar28 = uVar28 - 1) {
        *(undefined1 *)puVar30 = 0;
        puVar30 = (undefined4 *)((int)puVar30 + 1);
      }
    } while (iVar29 < 0x100);
  }
  FUN_00450b80();
  FUN_004e93e0(2);
  FUN_00450bd0();
  if (iVar2 != 0) {
    piVar1 = *(int **)(*(int *)(iVar2 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar3 != 0) {
    piVar1 = *(int **)(*(int *)(iVar3 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar4 != 0) {
    piVar1 = *(int **)(*(int *)(iVar4 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar5 != 0) {
    piVar1 = *(int **)(*(int *)(iVar5 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar6 != 0) {
    piVar1 = *(int **)(*(int *)(iVar6 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar7 != 0) {
    piVar1 = *(int **)(*(int *)(iVar7 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar8 != 0) {
    piVar1 = *(int **)(*(int *)(iVar8 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar9 != 0) {
    piVar1 = *(int **)(*(int *)(iVar9 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar10 != 0) {
    piVar1 = *(int **)(*(int *)(iVar10 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar11 != 0) {
    piVar1 = *(int **)(*(int *)(iVar11 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar12 != 0) {
    piVar1 = *(int **)(*(int *)(iVar12 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar13 != 0) {
    piVar1 = *(int **)(*(int *)(iVar13 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar14 != 0) {
    piVar1 = *(int **)(*(int *)(iVar14 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar15 != 0) {
    piVar1 = *(int **)(*(int *)(iVar15 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar16 != 0) {
    piVar1 = *(int **)(*(int *)(iVar16 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar17 != 0) {
    piVar1 = *(int **)(*(int *)(iVar17 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar18 != 0) {
    piVar1 = *(int **)(*(int *)(iVar18 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar19 != 0) {
    piVar1 = *(int **)(*(int *)(iVar19 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar20 != 0) {
    piVar1 = *(int **)(*(int *)(iVar20 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar21 != 0) {
    piVar1 = *(int **)(*(int *)(iVar21 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar22 != 0) {
    piVar1 = *(int **)(*(int *)(iVar22 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar23 != 0) {
    piVar1 = *(int **)(*(int *)(iVar23 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar24 != 0) {
    piVar1 = *(int **)(*(int *)(iVar24 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  if (iVar25 != 0) {
    piVar1 = *(int **)(*(int *)(iVar25 + 0x94) + 0x110);
    (**(code **)(*piVar1 + 0x80))(piVar1,0);
  }
  return;
}

