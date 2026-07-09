/* FUN_004141b0 - 0x004141b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void FUN_004141b0(uint param_1,uint param_2,uint param_3,uint param_4,int param_5,uint param_6,
                 uint param_7)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  void *pvVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined1 *puVar9;
  uint uVar10;
  undefined1 *puVar11;
  undefined4 *puVar12;
  code *pcVar13;
  undefined4 *puVar14;
  int local_80b0;
  undefined4 *local_80ac;
  undefined4 local_80a8;
  undefined2 local_80a4;
  ushort local_80a2;
  int local_80a0;
  undefined4 local_809c;
  int local_8098;
  undefined4 local_8094;
  undefined4 local_8090;
  undefined4 local_808c;
  char local_8088 [128];
  undefined4 local_8008 [63];
  undefined1 local_7f0a [32258];
  undefined1 local_108 [252];
  undefined4 uStack_c;
  
  uStack_c = 0x4141c0;
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  if (uVar2 <= param_6) {
LAB_004141d8:
    if (uVar2 != param_6) goto code_r0x004141da;
    puVar8 = (undefined4 *)puVar12[4];
    while (puVar8 != puVar12) {
      puVar14 = (undefined4 *)*puVar8;
      puVar8 = (undefined4 *)puVar8[4];
      (*(code *)*puVar14)(1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_00414205:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  if (uVar2 <= param_7) {
LAB_00414214:
    if (uVar2 != param_7) goto code_r0x00414216;
    puVar8 = (undefined4 *)puVar12[4];
    while (puVar8 != puVar12) {
      puVar14 = (undefined4 *)*puVar8;
      puVar8 = (undefined4 *)puVar8[4];
      (*(code *)*puVar14)(1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_00414245:
  if (param_4 == 0xffffffff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    _sprintf(local_8088,s_mf_05d_img_0055220c,uVar2 & 0x7fff);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  else {
    _sprintf(local_8088,s_mf_05d_img_0055220c,param_4 & 0x7fff);
    uVar2 = param_4;
  }
  local_80a2 = (ushort)uVar2 & 0x7fff;
  local_8090 = LoadSpriteSet(&DAT_00ea0e18,100000);
  if (param_2 == 0xffffffff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    _sprintf(local_8088,s__cb_05d_img_00552200,(int)(char)((-((uVar3 & 0x8000) != 0) & 7U) + 0x66),
             uVar2 & 0x7fff);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  else {
    _sprintf(local_8088,s__cb_05d_img_00552200,(int)(char)((-((param_2 & 0x8000) != 0) & 7U) + 0x66)
             ,param_2 & 0x7fff);
    uVar2 = param_2;
  }
  local_80a8 = CONCAT22(SUBFIELD(local_80a8,2,undefined2),(short)uVar2);
  local_808c = LoadSpriteSet(&DAT_00ea0e18,0x186a1);
  if (param_3 == 0xffffffff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    _sprintf(local_8088,s__cg_05d_img_005521f4,(int)(char)((-((uVar3 & 0x8000) != 0) & 7U) + 0x66),
             uVar2 & 0x7fff);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  else {
    _sprintf(local_8088,s__cg_05d_img_005521f4,(int)(char)((-((param_3 & 0x8000) != 0) & 7U) + 0x66)
             ,param_3 & 0x7fff);
    uVar2 = param_3;
  }
  local_80a4 = (undefined2)uVar2;
  local_809c = LoadSpriteSet(&DAT_00ea0e18,0x186a2);
  if (param_1 == 0xffffffff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    _sprintf(local_8088,s__ch_05d_img_005521e8,(int)(char)((-((uVar3 & 0x8000) != 0) & 7U) + 0x66),
             uVar2 & 0x7fff);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  else {
    _sprintf(local_8088,s__ch_05d_img_005521e8,(int)(char)((-((param_1 & 0x8000) != 0) & 7U) + 0x66)
             ,param_1 & 0x7fff);
    uVar2 = param_1;
  }
  local_80a8 = CONCAT22((short)uVar2,(undefined2)local_80a8);
  local_8094 = LoadSpriteSet(&DAT_00ea0e18,0x186a3);
  if (param_5 != 0) {
    FUN_00424ac0(g_clientContext,&local_80a8,param_5,0);
  }
  local_80b0 = 0;
LAB_00414610:
  puVar12 = local_8008;
  for (iVar7 = 0x2000; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  FUN_00414070(local_8008);
  FUN_00414070(local_8008);
  FUN_00414070(local_8008);
  FUN_00414070(local_8008);
  iVar7 = 0;
  puVar12 = local_8008;
  do {
    iVar4 = 0;
    puVar8 = puVar12;
    do {
      if ((*(byte *)((int)puVar8 + 1) & 0xf0) != 0) {
        iVar4 = 0x7f;
        puVar11 = local_108;
        goto LAB_004147a7;
      }
      iVar4 = iVar4 + 1;
      puVar8 = (undefined4 *)((int)puVar8 + 2);
    } while (iVar4 < 0x80);
    iVar7 = iVar7 + 1;
    puVar12 = puVar12 + 0x40;
  } while (iVar7 < 0x80);
  goto LAB_004149a1;
code_r0x004141da:
  puVar12 = (undefined4 *)puVar12[7];
  uVar2 = puVar12[1];
  if (param_6 < uVar2) goto LAB_00414205;
  goto LAB_004141d8;
code_r0x00414216:
  puVar12 = (undefined4 *)puVar12[7];
  uVar2 = puVar12[1];
  if (param_7 < uVar2) goto LAB_00414245;
  goto LAB_00414214;
LAB_004147a7:
  do {
    iVar5 = 0;
    puVar9 = puVar11;
    do {
      iVar1 = iVar4;
      if ((puVar9[1] & 0xf0) != 0) goto LAB_004147d2;
      iVar5 = iVar5 + 1;
      puVar9 = puVar9 + 2;
    } while (iVar5 < 0x80);
    iVar4 = iVar4 + -1;
    puVar11 = puVar11 + -0x100;
    iVar1 = local_80a8;
  } while (-1 < iVar4);
LAB_004147d2:
  local_80a8 = iVar1;
  iVar4 = 0;
  puVar12 = local_8008;
  do {
    iVar5 = 0;
    puVar8 = puVar12;
    do {
      iVar1 = iVar4;
      if ((*(byte *)((int)puVar8 + 1) & 0xf0) != 0) goto LAB_0041480a;
      iVar5 = iVar5 + 1;
      puVar8 = puVar8 + 0x40;
    } while (iVar5 < 0x80);
    iVar4 = iVar4 + 1;
    puVar12 = (undefined4 *)((int)puVar12 + 2);
    iVar1 = local_80a0;
  } while (iVar4 < 0x80);
LAB_0041480a:
  local_80a0 = iVar1;
  iVar4 = 0x7f;
  puVar11 = local_7f0a;
  do {
    iVar5 = 0;
    puVar9 = puVar11;
    do {
      iVar1 = iVar4;
      if ((puVar9[1] & 0xf0) != 0) goto LAB_00414842;
      iVar5 = iVar5 + 1;
      puVar9 = puVar9 + 0x100;
    } while (iVar5 < 0x80);
    iVar4 = iVar4 + -1;
    puVar11 = puVar11 + -2;
    iVar1 = local_8098;
  } while (-1 < iVar4);
LAB_00414842:
  local_8098 = iVar1;
  puVar12 = operator_new(0x50);
  if (puVar12 == (undefined4 *)0x0) {
    puVar12 = (undefined4 *)0x0;
  }
  else {
    puVar12[1] = param_6;
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
  iVar5 = (local_8098 - local_80a0) + 1;
  iVar4 = (local_80a8 - iVar7) + 1;
  puVar12[9] = iVar4;
  iVar4 = iVar4 * iVar5;
  puVar12[0xf] = iVar4 * 2;
  puVar12[10] = local_80a0 + -0x40;
  *(undefined1 *)(puVar12 + 6) = 2;
  puVar12[8] = iVar5;
  puVar12[0xb] = iVar7 + -0x40;
  *(undefined1 *)(puVar12 + 0xc) = 0;
  pvVar6 = operator_new(iVar4 * 2);
  puVar12[0xd] = pvVar6;
  uVar2 = 0;
  if (puVar12[9] != 0) {
    local_80ac = (undefined4 *)((int)local_8008 + (iVar7 * 0x80 + local_80a0) * 2);
    do {
      uVar3 = puVar12[8] * 2;
      uVar3 = ((int)uVar3 < 0) - 1 & uVar3;
      puVar8 = local_80ac;
      puVar14 = (undefined4 *)(puVar12[0xd] + puVar12[8] * uVar2 * 2);
      for (uVar10 = uVar3 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
        *puVar14 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar14 = puVar14 + 1;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined1 *)puVar14 = *(undefined1 *)puVar8;
        puVar8 = (undefined4 *)((int)puVar8 + 1);
        puVar14 = (undefined4 *)((int)puVar14 + 1);
      }
      uVar2 = uVar2 + 1;
      local_80ac = local_80ac + 0x40;
    } while (uVar2 < (uint)puVar12[9]);
  }
  iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar2 = *(uint *)(iVar7 + 4);
  while (uVar2 <= (uint)puVar12[1]) {
    if (uVar2 == puVar12[1]) goto LAB_0041496a;
    iVar7 = *(int *)(iVar7 + 0x1c);
    uVar2 = *(uint *)(iVar7 + 4);
  }
  iVar7 = FUN_004f2f00(&DAT_00ea0e18);
LAB_0041496a:
  uVar2 = puVar12[2];
  if (uVar2 != 0xffffffff) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar3 = *(uint *)(iVar7 + 8);
    if (uVar3 <= uVar2) {
      do {
        if (uVar3 == uVar2) {
          (**(code **)*puVar12)(1);
          goto LAB_004149a1;
        }
        iVar7 = *(int *)(iVar7 + 0x10);
        uVar3 = *(uint *)(iVar7 + 8);
      } while (uVar3 <= (uint)puVar12[2]);
    }
  }
  puVar12[4] = iVar7;
  puVar12[3] = *(undefined4 *)(iVar7 + 0xc);
  *(undefined4 **)(*(int *)(iVar7 + 0xc) + 0x10) = puVar12;
  *(undefined4 **)(iVar7 + 0xc) = puVar12;
LAB_004149a1:
  local_80b0 = local_80b0 + 1;
  if (0x2b < local_80b0) goto code_r0x004149b3;
  goto LAB_00414610;
code_r0x004149b3:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  if (uVar2 < 0x186a1) {
LAB_004149c5:
    if (uVar2 != 100000) goto code_r0x004149c7;
    puVar8 = (undefined4 *)puVar12[4];
    while (puVar8 != puVar12) {
      puVar14 = (undefined4 *)*puVar8;
      puVar8 = (undefined4 *)puVar8[4];
      (*(code *)*puVar14)(1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_004149fc:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  if (uVar2 < 0x186a2) {
LAB_00414a0e:
    if (uVar2 != 0x186a1) goto code_r0x00414a10;
    puVar8 = (undefined4 *)puVar12[4];
    while (puVar8 != puVar12) {
      puVar14 = (undefined4 *)*puVar8;
      puVar8 = (undefined4 *)puVar8[4];
      (*(code *)*puVar14)(1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_00414a3b:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  if (uVar2 < 0x186a3) {
LAB_00414a4d:
    if (uVar2 != 0x186a2) goto code_r0x00414a4f;
    puVar8 = (undefined4 *)puVar12[4];
    while (puVar8 != puVar12) {
      puVar14 = (undefined4 *)*puVar8;
      puVar8 = (undefined4 *)puVar8[4];
      (*(code *)*puVar14)(1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_00414a7a:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  if (uVar2 < 0x186a4) {
LAB_00414a8c:
    if (uVar2 != 0x186a3) goto code_r0x00414a8e;
    puVar8 = (undefined4 *)puVar12[4];
    while (puVar8 != puVar12) {
      puVar14 = (undefined4 *)*puVar8;
      puVar8 = (undefined4 *)puVar8[4];
      (*(code *)*puVar14)(1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_00414ab9:
  if (param_4 == 0xffffffff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    param_4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  _sprintf(local_8088,s_mf_05dl_img_005521dc,param_4 & 0x7fff);
  local_8090 = LoadSpriteSet(&DAT_00ea0e18,100000);
  pcVar13 = (code *)EnterCriticalSection;
  if (param_2 == 0xffffffff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    _sprintf(local_8088,s__cb_05dl_img_005521cc,(int)(char)((-((uVar3 & 0x8000) != 0) & 7U) + 0x66),
             uVar2 & 0x7fff);
  }
  else {
    _sprintf(local_8088,s__cb_05dl_img_005521cc,
             (int)(char)((-((param_2 & 0x8000) != 0) & 7U) + 0x66),param_2 & 0x7fff);
    pcVar13 = (code *)EnterCriticalSection;
  }
  local_808c = LoadSpriteSet(&DAT_00ea0e18,0x186a1);
  uVar2 = param_3;
  if (param_3 == 0xffffffff) {
    (*pcVar13)(&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    (*pcVar13)(&DAT_005a9068);
    param_3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  _sprintf(local_8088,s__cg_05dl_img_005521bc,(int)(char)((-((param_3 & 0x8000) != 0) & 7U) + 0x66),
           uVar2 & 0x7fff);
  local_809c = LoadSpriteSet(&DAT_00ea0e18,0x186a2);
  uVar2 = param_1;
  if (param_1 == 0xffffffff) {
    (*pcVar13)(&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    (*pcVar13)(&DAT_005a9068);
    param_1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  _sprintf(local_8088,s__ch_05dl_img_005521ac,(int)(char)((-((param_1 & 0x8000) != 0) & 7U) + 0x66),
           uVar2 & 0x7fff);
  local_8094 = LoadSpriteSet(&DAT_00ea0e18,0x186a3);
  local_80b0 = 0;
LAB_00414d80:
  puVar12 = local_8008;
  for (iVar7 = 0x2000; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  FUN_00414070(local_8008);
  FUN_00414070(local_8008);
  FUN_00414070(local_8008);
  FUN_00414070(local_8008);
  iVar7 = 0;
  puVar12 = local_8008;
  do {
    iVar4 = 0;
    puVar8 = puVar12;
    do {
      if ((*(byte *)((int)puVar8 + 1) & 0xf0) != 0) {
        iVar4 = 0x7f;
        puVar11 = local_108;
        goto LAB_00414f07;
      }
      iVar4 = iVar4 + 1;
      puVar8 = (undefined4 *)((int)puVar8 + 2);
    } while (iVar4 < 0x80);
    iVar7 = iVar7 + 1;
    puVar12 = puVar12 + 0x40;
  } while (iVar7 < 0x80);
  goto LAB_00415105;
code_r0x004149c7:
  puVar12 = (undefined4 *)puVar12[7];
  uVar2 = puVar12[1];
  if (100000 < uVar2) goto LAB_004149fc;
  goto LAB_004149c5;
code_r0x00414a10:
  puVar12 = (undefined4 *)puVar12[7];
  uVar2 = puVar12[1];
  if (0x186a1 < uVar2) goto LAB_00414a3b;
  goto LAB_00414a0e;
code_r0x00414a4f:
  puVar12 = (undefined4 *)puVar12[7];
  uVar2 = puVar12[1];
  if (0x186a2 < uVar2) goto LAB_00414a7a;
  goto LAB_00414a4d;
code_r0x00414a8e:
  puVar12 = (undefined4 *)puVar12[7];
  uVar2 = puVar12[1];
  if (0x186a3 < uVar2) goto LAB_00414ab9;
  goto LAB_00414a8c;
LAB_00414f07:
  do {
    iVar5 = 0;
    puVar9 = puVar11;
    do {
      iVar1 = iVar4;
      if ((puVar9[1] & 0xf0) != 0) goto LAB_00414f32;
      iVar5 = iVar5 + 1;
      puVar9 = puVar9 + 2;
    } while (iVar5 < 0x80);
    iVar4 = iVar4 + -1;
    puVar11 = puVar11 + -0x100;
    iVar1 = local_8098;
  } while (-1 < iVar4);
LAB_00414f32:
  local_8098 = iVar1;
  iVar4 = 0;
  puVar12 = local_8008;
  do {
    iVar5 = 0;
    puVar8 = puVar12;
    do {
      iVar1 = iVar4;
      if ((*(byte *)((int)puVar8 + 1) & 0xf0) != 0) goto LAB_00414f6a;
      iVar5 = iVar5 + 1;
      puVar8 = puVar8 + 0x40;
    } while (iVar5 < 0x80);
    iVar4 = iVar4 + 1;
    puVar12 = (undefined4 *)((int)puVar12 + 2);
    iVar1 = local_80a0;
  } while (iVar4 < 0x80);
LAB_00414f6a:
  local_80a0 = iVar1;
  iVar4 = 0x7f;
  puVar11 = local_7f0a;
  do {
    iVar5 = 0;
    puVar9 = puVar11;
    do {
      iVar1 = iVar4;
      if ((puVar9[1] & 0xf0) != 0) goto LAB_00414fa2;
      iVar5 = iVar5 + 1;
      puVar9 = puVar9 + 0x100;
    } while (iVar5 < 0x80);
    iVar4 = iVar4 + -1;
    puVar11 = puVar11 + -2;
    iVar1 = local_80a8;
  } while (-1 < iVar4);
LAB_00414fa2:
  local_80a8 = iVar1;
  puVar12 = operator_new(0x50);
  if (puVar12 == (undefined4 *)0x0) {
    puVar12 = (undefined4 *)0x0;
  }
  else {
    puVar12[1] = param_7;
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
  iVar5 = (local_80a8 - local_80a0) + 1;
  iVar4 = (local_8098 - iVar7) + 1;
  puVar12[9] = iVar4;
  iVar4 = iVar4 * iVar5;
  puVar12[0xf] = iVar4 * 2;
  puVar12[10] = local_80a0 + -0x40;
  *(undefined1 *)(puVar12 + 6) = 2;
  puVar12[8] = iVar5;
  puVar12[0xb] = iVar7 + -0x40;
  *(undefined1 *)(puVar12 + 0xc) = 0;
  pvVar6 = operator_new(iVar4 * 2);
  puVar12[0xd] = pvVar6;
  uVar2 = 0;
  if (puVar12[9] != 0) {
    local_80ac = (undefined4 *)((int)local_8008 + (iVar7 * 0x80 + local_80a0) * 2);
    do {
      uVar3 = puVar12[8] * 2;
      uVar3 = ((int)uVar3 < 0) - 1 & uVar3;
      puVar8 = local_80ac;
      puVar14 = (undefined4 *)(puVar12[0xd] + puVar12[8] * uVar2 * 2);
      for (uVar10 = uVar3 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
        *puVar14 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar14 = puVar14 + 1;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined1 *)puVar14 = *(undefined1 *)puVar8;
        puVar8 = (undefined4 *)((int)puVar8 + 1);
        puVar14 = (undefined4 *)((int)puVar14 + 1);
      }
      uVar2 = uVar2 + 1;
      local_80ac = local_80ac + 0x40;
    } while (uVar2 < (uint)puVar12[9]);
  }
  iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar2 = *(uint *)(iVar7 + 4);
  while (uVar2 <= (uint)puVar12[1]) {
    if (uVar2 == puVar12[1]) goto LAB_004150ca;
    iVar7 = *(int *)(iVar7 + 0x1c);
    uVar2 = *(uint *)(iVar7 + 4);
  }
  iVar7 = FUN_004f2f00(&DAT_00ea0e18);
LAB_004150ca:
  uVar2 = puVar12[2];
  if (uVar2 != 0xffffffff) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar3 = *(uint *)(iVar7 + 8);
    if (uVar3 <= uVar2) {
      do {
        if (uVar3 == uVar2) {
          (**(code **)*puVar12)(1);
          goto LAB_00415105;
        }
        iVar7 = *(int *)(iVar7 + 0x10);
        uVar3 = *(uint *)(iVar7 + 8);
      } while (uVar3 <= (uint)puVar12[2]);
    }
  }
  puVar12[4] = iVar7;
  puVar12[3] = *(undefined4 *)(iVar7 + 0xc);
  *(undefined4 **)(*(int *)(iVar7 + 0xc) + 0x10) = puVar12;
  *(undefined4 **)(iVar7 + 0xc) = puVar12;
LAB_00415105:
  local_80b0 = local_80b0 + 1;
  if (0x2b < local_80b0) goto code_r0x00415113;
  goto LAB_00414d80;
code_r0x00415127:
  puVar12 = (undefined4 *)puVar12[7];
  uVar2 = puVar12[1];
  if (100000 < uVar2) goto LAB_0041515c;
  goto LAB_00415125;
code_r0x00415170:
  puVar12 = (undefined4 *)puVar12[7];
  uVar2 = puVar12[1];
  if (0x186a1 < uVar2) goto LAB_0041519b;
  goto LAB_0041516e;
code_r0x00415113:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  if (uVar2 < 0x186a1) {
LAB_00415125:
    if (uVar2 != 100000) goto code_r0x00415127;
    puVar8 = (undefined4 *)puVar12[4];
    while (puVar8 != puVar12) {
      puVar14 = (undefined4 *)*puVar8;
      puVar8 = (undefined4 *)puVar8[4];
      (*(code *)*puVar14)(1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_0041515c:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  if (uVar2 < 0x186a2) {
LAB_0041516e:
    if (uVar2 != 0x186a1) goto code_r0x00415170;
    puVar8 = (undefined4 *)puVar12[4];
    while (puVar8 != puVar12) {
      puVar14 = (undefined4 *)*puVar8;
      puVar8 = (undefined4 *)puVar8[4];
      (*(code *)*puVar14)(1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_0041519b:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  while( true ) {
    if (0x186a2 < uVar2) goto LAB_004151da;
    if (uVar2 == 0x186a2) break;
    puVar12 = (undefined4 *)puVar12[7];
    uVar2 = puVar12[1];
  }
  puVar8 = (undefined4 *)puVar12[4];
  while (puVar8 != puVar12) {
    puVar14 = (undefined4 *)*puVar8;
    puVar8 = (undefined4 *)puVar8[4];
    (*(code *)*puVar14)(1);
  }
  puVar12[3] = puVar12;
  puVar12[4] = puVar12;
LAB_004151da:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  if (uVar2 < 0x186a4) {
    while (uVar2 != 0x186a3) {
      puVar12 = (undefined4 *)puVar12[7];
      uVar2 = puVar12[1];
      if (0x186a3 < uVar2) {
        return;
      }
    }
    puVar8 = (undefined4 *)puVar12[4];
    while (puVar8 != puVar12) {
      puVar14 = (undefined4 *)*puVar8;
      puVar8 = (undefined4 *)puVar8[4];
      (*(code *)*puVar14)(1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
  return;
}

