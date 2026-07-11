/* SpawnPrimaryShot - 0x0042bbb0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x0042cb86) */

void SpawnPrimaryShot(undefined1 param_1,uint param_2,uint param_3,uint param_4,int param_5,int param_6,
                 int param_7,int param_8,undefined4 param_9,undefined4 param_10,undefined4 param_11,
                 int param_12)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffff734;
  undefined stack0xfffff740;
  byte *pbVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  char cVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  char *pcVar10;
  undefined4 uVar11;
  byte bVar12;
  byte bVar13;
  undefined4 unaff_ESI;
  char *pcVar14;
  code *pcVar15;
  int unaff_EDI;
  undefined4 *unaff_FS_OFFSET;
  bool bVar16;
  byte unaff_retaddr;
  undefined *puVar17;
  undefined *puVar18;
  undefined *puVar19;
  int *local_8bc; /* was undefined4; compared/indexed as int * throughout */
  int *local_8b8;
  uint uStack_8b4;
  uint uStack_8b0;
  float fStack_8ac;
  undefined4 uStack_8a8;
  undefined *puStack_8a4;
  undefined1 auStack_8a0 [8];
  int iStack_898;
  uint uStack_88c;
  undefined1 auStack_68c [12];
  undefined *puStack_680;
  undefined1 auStack_67c [8];
  int iStack_674;
  uint uStack_668;
  undefined1 auStack_478 [52];
  int iStack_444;
  undefined1 auStack_250 [48];
  int iStack_220;
  undefined1 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined1 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  uStack_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ddcf;
  *unaff_FS_OFFSET = &uStack_c;
  FUN_004e51f0();
  switch(param_3) {
  case 0:
    if ((char)param_4 == '\0') {
      local_8bc = operator_new(0x3f9c);
      local_4 = 0;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)InitProjectile(local_8bc,0x186a2);
      }
      local_4 = 0xffffffff;
      local_8b8[0x794] = 3;
      iVar6 = FindPreloadedTextureByName(s_bullet1n_00553f80);
      local_8b8[7] = iVar6;
      local_8b8[0xfe4] = 2;
    }
    else {
      local_8bc = operator_new(0x3fa0);
      local_4 = 1;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
        uRam00001e50 = 5;
        pcVar14 = s_bullet1s_00553f74;
      }
      else {
        local_8b8 = (int *)FUN_00468860();
        local_8b8[0x794] = 5;
        pcVar14 = s_bullet1s_00553f74;
      }
LAB_0042c334:
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(pcVar14);
      local_8b8[7] = iVar6;
      local_8b8[0xfe4] = 3;
    }
    break;
  case 1:
    if ((char)param_4 == '\0') {
      local_8bc = operator_new(0x40a8);
      local_4 = 2;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_0047eb60();
      }
      iVar6 = g_clientContext;
      local_4 = 0xffffffff;
      local_8b8[0x1029] = 0xf80ffff;
      if (*(char *)(iVar6 + 0x45578) != '\0') {
        SetGuardedBool(0);
      }
      local_8b8[0xfe4] = 6;
    }
    else {
      local_8bc = operator_new(0x4940);
      local_4 = 3;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_004a46f0(local_8bc);
      }
      iVar6 = g_clientContext;
      uVar7 = param_2 & 0x80000001;
      local_4 = 0xffffffff;
      if ((int)uVar7 < 0) {
        uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
      }
      local_8b8[0x102a] = uVar7 * 0xb4;
      local_8b8[0x1029] = (-(uint)(uVar7 != 0) & 0x7e8100) + 0xf80ffff;
      local_8b8[0x102b] = 10;
      if (*(char *)(iVar6 + 0x45578) != '\0') {
        SetGuardedBool(0);
      }
      local_8b8[0xfe4] = 7;
    }
    break;
  case 2:
    if ((char)param_4 == '\0') {
      local_8bc = operator_new(0x3f9c);
      local_4 = 4;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)InitProjectile(local_8bc,0x186a2);
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet3n_00553f68);
      local_8b8[7] = iVar6;
      local_8b8[0xfe4] = 0;
    }
    else {
      local_8bc = operator_new(0x3fa0);
      local_4 = 5;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_00493340();
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet3s_00553f5c);
      local_8b8[7] = iVar6;
      local_8b8[0xfe4] = 1;
    }
    break;
  case 3:
    if ((char)param_4 != '\0') {
      if ((param_2 == 2) || (param_2 == 10)) {
        local_8bc = operator_new(0x3f9c);
        local_4 = 7;
        if (local_8bc == (int *)0x0) {
          local_8b8 = (int *)0x0;
          pcVar14 = s_bullet4s_00553f44;
        }
        else {
          local_8b8 = (int *)InitProjectile(local_8bc,0x186a2);
          pcVar14 = s_bullet4s_00553f44;
        }
      }
      else {
        local_8bc = operator_new(0x4838);
        local_4 = 8;
        if (local_8bc == (int *)0x0) {
          local_8b8 = (int *)0x0;
        }
        else {
          local_8b8 = (int *)FUN_004a2a70(local_8bc);
        }
        uVar7 = param_2 & 0x80000007;
        if ((int)uVar7 < 0) {
          uVar7 = (uVar7 - 1 | 0xfffffff8) + 1;
        }
        local_8b8[0xfe7] = uVar7 * 0xb4 + param_8;
        pcVar14 = s_bullet4s_00553f44;
        local_8b8[0xfe8] = ((param_8 < 0x5b) - 1 & 0x10) - 8;
      }
      goto LAB_0042c334;
    }
    local_8bc = operator_new(0x3f9c);
    local_4 = 6;
    if (local_8bc == (int *)0x0) {
      local_8b8 = (int *)0x0;
    }
    else {
      local_8b8 = (int *)InitProjectile(local_8bc,0x186a2);
    }
    local_4 = 0xffffffff;
    iVar6 = FindPreloadedTextureByName(s_bullet4n_00553f50);
    local_8b8[7] = iVar6;
    local_8b8[0xfe4] = 2;
    break;
  case 4:
    if ((char)param_4 == '\0') {
      local_8bc = operator_new(0x3f9c);
      local_4 = 9;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)InitProjectile(local_8bc,0x186a2);
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet5n_00553f38);
      local_8b8[7] = iVar6;
      local_8b8[0xfe4] = 0xff;
    }
    else {
      local_8bc = operator_new(0x3f9c);
      local_4 = 10;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)InitProjectile(local_8bc,0x186a2);
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet5s_00553f2c);
      local_8b8[7] = iVar6;
      local_8b8[0xfe4] = 0xff;
    }
    break;
  case 5:
    if ((char)param_4 == '\0') {
      local_8bc = operator_new(0x3fa8);
      local_4 = 0xb;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_00451270(local_8bc);
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet6n_00553f20);
      local_8b8[0xfe4] = 0;
    }
    else {
      local_8bc = operator_new(0x3fa8);
      local_4 = 0xc;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_00451270(local_8bc);
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet6s_00553f14);
      local_8b8[0xfe4] = 1;
    }
    local_8b8[7] = iVar6;
    SetGuardedBool(0);
    break;
  case 6:
    if ((char)param_4 != '\0') {
      local_8bc = operator_new(0x3f9c);
      local_4 = 0xf;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_0044c900();
      }
      pcVar14 = s_bullet7s_00553efc;
      goto LAB_0042c334;
    }
    uVar7 = param_2 & 0x80000007;
    bVar16 = uVar7 == 0;
    if ((int)uVar7 < 0) {
      bVar16 = (uVar7 - 1 | 0xfffffff8) == 0xffffffff;
    }
    if (bVar16) {
      local_8bc = operator_new(0x3f9c);
      local_4 = 0xd;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)InitProjectile(local_8bc,0x186a2);
      }
    }
    else {
      local_8bc = operator_new(0x4834);
      local_4 = 0xe;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_00495c20(local_8bc);
      }
      uVar7 = param_2 & 0x80000001;
      if ((int)uVar7 < 0) {
        uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
      }
      local_8b8[0xfe7] = uVar7 * 0xb4;
    }
    local_4 = 0xffffffff;
    iVar6 = FindPreloadedTextureByName(s_bullet7n_00553f08);
    local_8b8[7] = iVar6;
    SetGuardedBool(0);
    local_8b8[0xfe4] = 0xff;
    break;
  case 7:
    if ((char)param_4 == '\0') {
      local_8bc = operator_new(0x3f9c);
      local_4 = 0x10;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_00482500();
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet8n_00553ef0);
      local_8b8[7] = iVar6;
      local_8b8[0xfe4] = 4;
    }
    else {
      local_8bc = operator_new(0x3f9c);
      local_4 = 0x11;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_004a7000();
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet8s_00553ee4);
      local_8b8[7] = iVar6;
      local_8b8[0xfe4] = 5;
    }
    break;
  case 8:
    if ((char)param_4 == '\0') {
      local_8bc = operator_new(0x3f9c);
      local_4 = 0x12;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_0046e550();
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet9n_00553ed8);
      local_8b8[7] = iVar6;
      local_8b8[0xfe4] = 4;
    }
    else {
      local_8bc = operator_new(0x3f9c);
      local_4 = 0x13;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_004654b0();
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet9s_00553ecc);
      local_8b8[7] = iVar6;
      local_8b8[0xfe4] = 0xff;
    }
    break;
  case 9:
    if ((char)param_4 == '\0') {
      local_8bc = operator_new(0x3fa0);
      local_4 = 0x14;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_004812d0();
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet10n_00553ec0);
      local_8b8[7] = iVar6;
      *(undefined1 *)(local_8b8 + 0xfe7) = 0;
      local_8b8[0xfe4] = 6;
    }
    else {
      local_8bc = operator_new(0x3fa0);
      local_4 = 0x15;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_004812d0();
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet10s_00553eb4);
      local_8b8[7] = iVar6;
      *(undefined1 *)(local_8b8 + 0xfe7) = 1;
      local_8b8[0xfe4] = 7;
    }
    break;
  case 10:
    if ((char)param_4 == '\0') {
      local_8bc = operator_new(0x3f9c);
      local_4 = 0x16;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)InitProjectile(local_8bc,0x186a2);
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet11n_00553ea8);
      local_8b8[7] = iVar6;
      local_8b8[0xfe4] = 0xff;
    }
    else {
      local_8bc = operator_new(0x3f9c);
      local_4 = 0x17;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_00473160();
      }
      local_4 = 0xffffffff;
      local_8b8[0x794] = 5;
      iVar6 = FindPreloadedTextureByName(s_bullet11s_00553e9c);
      local_8b8[7] = iVar6;
      local_8b8[0xfe4] = 0xff;
    }
    break;
  case 0xb:
    if ((char)param_4 == '\0') {
      local_8bc = operator_new(0x40a8);
      local_4 = 0x18;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_004b17b0();
      }
      iVar6 = g_clientContext;
      local_4 = 0xffffffff;
      local_8b8[0x1029] = 0xfffffff;
      if (*(char *)(iVar6 + 0x45578) != '\0') {
        SetGuardedBool(0);
      }
      local_8b8[0xfe4] = 0;
    }
    else {
      local_8bc = operator_new(0x494c);
      local_4 = 0x19;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_004af530(local_8bc);
      }
      iVar6 = g_clientContext;
      uVar7 = param_2 & 0x80000001;
      local_4 = 0xffffffff;
      if ((int)uVar7 < 0) {
        uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
      }
      local_8b8[0x102c] = uVar7 * 0xb4;
      local_8b8[0x1029] = 0xfffffff;
      local_8b8[0x102d] = 10;
      if (*(char *)(iVar6 + 0x45578) != '\0') {
        SetGuardedBool(0);
      }
      local_8b8[0xfe4] = 1;
    }
    break;
  case 0xc:
    if ((char)param_4 == '\0') {
      local_8bc = operator_new(0x3f9c);
      local_4 = 0x1a;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)InitProjectile(local_8bc,0x186a2);
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet13n_00553e90);
      local_8b8[7] = iVar6;
      local_8b8[0xfe4] = 6;
    }
    else {
      local_8bc = operator_new(0x41cc);
      local_4 = 0x1b;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_0049e540(local_8bc);
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet13s_00553e84);
      local_8b8[7] = iVar6;
      local_8b8[0xfe4] = 7;
    }
    break;
  case 0xd:
    local_8bc = operator_new(0x3fa0);
    local_4 = 0x1c;
    if (local_8bc == (int *)0x0) {
      local_8b8 = (int *)0x0;
    }
    else {
      local_8b8 = (int *)FUN_0046fad0();
    }
    local_4 = 0xffffffff;
    local_8b8[0x794] = 5;
    local_8b8[0xfe4] = 0xff;
    break;
  case 0xe:
    if ((char)param_4 == '\0') {
      local_8bc = operator_new(0x3fa0);
      local_4 = 0x1d;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_0047b2a0();
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet15n_00553e78);
      local_8b8[7] = iVar6;
      *(undefined1 *)(local_8b8 + 0xfe7) = 0;
      local_8b8[0xfe4] = 0;
    }
    else {
      local_8bc = operator_new(0x3fa0);
      local_4 = 0x1e;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_0047b2a0();
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet15s_00553e6c);
      local_8b8[7] = iVar6;
      *(undefined1 *)(local_8b8 + 0xfe7) = 1;
      local_8b8[0xfe4] = 1;
    }
    break;
  case 0xf:
    if ((char)param_4 == '\0') {
      local_8bc = operator_new(0x3f9c);
      local_4 = 0x1f;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_0046e550();
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet16n_00553e60);
      local_8b8[7] = iVar6;
      local_8b8[0xfe4] = 4;
    }
    else {
      local_8bc = operator_new(0x3fa0);
      local_4 = 0x20;
      if (local_8bc == (int *)0x0) {
        local_8b8 = (int *)0x0;
      }
      else {
        local_8b8 = (int *)FUN_004aaf80();
      }
      local_4 = 0xffffffff;
      iVar6 = FindPreloadedTextureByName(s_bullet16s_00553e54);
      local_8b8[7] = iVar6;
      local_8b8[0xfe4] = 1;
    }
  }
  piVar3 = local_8bc;
  if (*(char *)(g_clientContext + 0x45578) == '\0') {
    local_8b8[0xe25] = (param_4 & 0xff) + 8000 + param_3 * 2;
    local_8b8[6] = (param_4 & 0xff) + 6000 + param_3 * 2;
    _sprintf((char *)(local_8b8 + 0xe26),s_flame_d_d_00553e48,param_3 + 1,
             ((char)param_4 != '\0') + 1);
  }
  else if (*(char *)(g_clientContext + 0x45578) == '\x01') {
    local_8b8[6] = 6000;
    local_8b8[0xe25] = 8000;
    iVar6 = FindPreloadedTextureByName(s_bulletevent1_00553e38);
    local_8b8[7] = iVar6;
    local_8b8[0xe26] = SUBFIELD(s_flameevent1_00553e2c,0,undefined4);
    local_8b8[0xe27] = SUBFIELD(s_flameevent1_00553e2c,4,undefined4);
    local_8b8[0xe28] = SUBFIELD(s_flameevent1_00553e2c,8,undefined4);
  }
  (**(code **)(*local_8b8 + 4))(s_normal_00552230);
  uVar7 = (uint)unaff_retaddr;
  *(byte *)(local_8b8 + 0xf) = unaff_retaddr & 7;
  local_8b8[0xe] = local_8b8[6] + 100;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_6);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_5 << 8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_6 << 8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = (param_7 + 0x5a) % 0x168;
  if (iVar6 < 0) {
    iVar6 = iVar6 + 0x168;
  }
  uStack_8a8 = *(undefined4 *)(&g_sineTable360 + iVar6 * 4);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uStack_8b4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  fStack_8ac = (float)param_8;
  iVar6 = FloatToInt64();
  EncodeOutgoingPacketField((iVar6 << 8) / (int)uStack_8b4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = param_7 % 0x168;
  if (iVar6 < 0) {
    iVar6 = iVar6 + 0x168;
  }
  uStack_8b4 = *(uint *)(&g_sineTable360 + iVar6 * 4);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar9 = FloatToInt64();
  EncodeOutgoingPacketField(-((iVar9 << 8) / iVar6));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = (iVar6 + 0x5a) % 0x168;
  if (iVar6 < 0) {
    iVar6 = iVar6 + 0x168;
  }
  uStack_8a8 = *(undefined4 *)(&g_sineTable360 + iVar6 * 4);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uStack_8b4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = FloatToInt64();
  EncodeOutgoingPacketField(uVar8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uStack_8a8 = FUN_0040b090(local_8b8 + 0x2bd,auStack_8a0,8);
  puStack_8 = (undefined1 *)0x21;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uStack_8b4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uStack_8b4 = EncodeChecksumDeltaDiv(uStack_8a8,auStack_67c,uStack_8b4);
  SUBFIELD(puStack_8,0,undefined1) = 0x22;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = uStack_668;
  puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),0x21);
  if (uStack_668 != 0) {
    ScrambleChecksumGuardBytes();
    uStack_8b4 = uVar4;
    FUN_0040b540(&uStack_8a8);
    local_8b8 = local_8bc;
  }
  uVar4 = uStack_88c;
  puStack_8 = (undefined1 *)0xffffffff;
  if (uStack_88c != 0) {
    ScrambleChecksumGuardBytes();
    uStack_8b4 = uVar4;
    FUN_0040b540(&uStack_8a8);
    local_8b8 = local_8bc;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = iVar6 % 0x168;
  if (iVar6 < 0) {
    iVar6 = iVar6 + 0x168;
  }
  uStack_8a8 = *(undefined4 *)(&g_sineTable360 + iVar6 * 4);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uStack_8b4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  iVar9 = FloatToInt64();
  EncodeOutgoingPacketField(iVar6 - iVar9);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = FUN_0040b090(local_8b8 + 0x346,auStack_67c,8);
  puStack_8 = (undefined1 *)0x23;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uStack_8b4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaDiv(uVar8,auStack_8a0,uStack_8b4);
  SUBFIELD(puStack_8,0,undefined1) = 0x24;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = uStack_88c;
  puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),0x23);
  if (uStack_88c != 0) {
    ScrambleChecksumGuardBytes();
    uStack_8b4 = uVar4;
    FUN_0040b540(&uStack_8a8);
  }
  uVar4 = uStack_668;
  puStack_8 = (undefined1 *)0xffffffff;
  if (uStack_668 != 0) {
    ScrambleChecksumGuardBytes();
    uStack_8b4 = uVar4;
    FUN_0040b540(&uStack_8a8);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  *(char *)((int)local_8bc + 0xf3f) = (char)iVar6;
  iVar6 = _rand();
  *(byte *)(local_8bc + 0x3d0) = (byte)iVar6;
  bVar12 = *(byte *)((int)local_8bc + 0xf3f) & 7;
  bVar12 = ~('\x01' << bVar12) & (byte)iVar6 | '\0' << bVar12;
  *(byte *)(local_8bc + 0x3d0) = bVar12;
  *(byte *)((int)local_8bc + 0xf41) = bVar12 + *(char *)((int)local_8bc + 0xf3f) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  *(char *)((int)local_8bc + 0xf45) = (char)iVar6;
  iVar6 = _rand();
  *(byte *)((int)local_8bc + 0xf46) = (byte)iVar6;
  bVar12 = *(byte *)((int)local_8bc + 0xf45) & 7;
  bVar12 = ~('\x01' << bVar12) & (byte)iVar6 | '\0' << bVar12;
  *(byte *)((int)local_8bc + 0xf46) = bVar12;
  *(byte *)((int)local_8bc + 0xf47) = bVar12 + *(char *)((int)local_8bc + 0xf45) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool(param_10);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_9);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool(param_4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_11);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8bc[0xfe5] = param_12;
  if (param_7 < 0x46) {
LAB_0042d20d:
    fStack_8ac = (float)((uint)fStack_8ac & 0xffffff00);
  }
  else {
    fStack_8ac = (float)CONCAT31(SUBFIELD(fStack_8ac,1,undefined3),1);
    if (0x6e < param_7) goto LAB_0042d20d;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool(fStack_8ac);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  pcVar10 = (&PTR_s_11blast_xes_0056d290)[(param_3 & 0xff) * 0x10 + param_2];
  pcVar14 = (char *)((int)local_8bc + 0x3813);
  do {
    cVar5 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *pcVar14 = cVar5;
    pcVar14 = pcVar14 + 1;
  } while (cVar5 != '\0');
  pcVar15 = (code *)LeaveCriticalSection;
  if (DAT_0079352a != '\0') {
    Replay_AppendEvent(0xf000);
    (&g_replayEventBuffer)[g_replayEventCursor] = 1;
    pbVar1 = &DAT_00e9aacd + g_replayEventCursor;
    g_replayEventCursor = g_replayEventCursor + 1;
    *pbVar1 = unaff_retaddr;
    puVar18 = &DAT_00e9aacd + g_replayEventCursor;
    g_replayEventCursor = g_replayEventCursor + 1;
    *puVar18 = param_1;
    puVar18 = &DAT_00e9aacd + g_replayEventCursor;
    g_replayEventCursor = g_replayEventCursor + 1;
    *puVar18 = (undefined1)param_2;
    puVar18 = &DAT_00e9aacd + g_replayEventCursor;
    g_replayEventCursor = g_replayEventCursor + 1;
    *puVar18 = (undefined1)param_3;
    piVar2 = (int *)(&DAT_00e9aacd + g_replayEventCursor);
    g_replayEventCursor = g_replayEventCursor + 1;
    *piVar2 = param_5;
    piVar2 = (int *)(&DAT_00e9aad0 + g_replayEventCursor);
    g_replayEventCursor = g_replayEventCursor + 4;
    *piVar2 = param_6;
    piVar2 = (int *)(&DAT_00e9aad0 + g_replayEventCursor);
    g_replayEventCursor = g_replayEventCursor + 4;
    *piVar2 = param_7;
    piVar2 = (int *)(&DAT_00e9aad0 + g_replayEventCursor);
    g_replayEventCursor = g_replayEventCursor + 4;
    *piVar2 = param_8;
    puVar18 = &DAT_00e9aad0 + g_replayEventCursor;
    g_replayEventCursor = g_replayEventCursor + 4;
    *puVar18 = (undefined1)param_9;
    puVar18 = &DAT_00e9aacd + g_replayEventCursor;
    g_replayEventCursor = g_replayEventCursor + 1;
    *puVar18 = (undefined1)param_10;
    g_replayEventCursor = g_replayEventCursor + 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    pcVar15 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar8;
    g_replayEventCursor = g_replayEventCursor + 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar8;
    g_replayEventCursor = g_replayEventCursor + 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar8;
    g_replayEventCursor = g_replayEventCursor + 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar8;
    g_replayEventCursor = g_replayEventCursor + 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar8;
    g_replayEventCursor = g_replayEventCursor + 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar8;
    g_replayEventCursor = g_replayEventCursor + 4;
    Replay_FlushEvent();
  }
  if (param_2 != 5) goto LAB_0042d667;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar15)(&DAT_005a9068);
  if (SUBFIELD(local_8bc,3,undefined1) == '\0') {
LAB_0042d56e:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    local_8bc = (int *)CONCAT13(-1 < iVar6,(undefined3)local_8bc);
    (*pcVar15)(&DAT_005a9068);
    if (-1 < iVar6) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      local_8bc = (int *)CONCAT13(0 < iVar6,(undefined3)local_8bc);
      (*pcVar15)(&DAT_005a9068);
      if (0 < iVar6) goto LAB_0042d5ba;
    }
    uStack_8b0 = CONCAT31(SUBFIELD(uStack_8b0,1,undefined3),1);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    local_8bc = (int *)CONCAT13(iVar6 < 0,(undefined3)local_8bc);
    (*pcVar15)(&DAT_005a9068);
    if (iVar6 >= 0) goto LAB_0042d56e;
LAB_0042d5ba:
    uStack_8b0 = uStack_8b0 & 0xffffff00;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool(uStack_8b0);
  (*pcVar15)(&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  (*pcVar15)(&DAT_005a9068);
  if (iVar6 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = _rand();
    *(byte *)(piVar3 + 0xfe7) = (byte)iVar6;
    iVar6 = _rand();
    bVar12 = *(byte *)(piVar3 + 0xfe7);
    *(byte *)((int)piVar3 + 0x3f9d) = (byte)iVar6;
    uStack_8b4 = bVar12 & 7;
    bVar13 = ~('\x01' << (sbyte)uStack_8b4) & (byte)iVar6 | '\0' << (sbyte)uStack_8b4;
    *(byte *)((int)piVar3 + 0x3f9d) = bVar13;
    *(byte *)((int)piVar3 + 0x3f9e) = bVar13 + bVar12 + -0x34;
    (*pcVar15)(&DAT_005a9068);
  }
LAB_0042d667:
  FUN_0041da80(g_clientContext,local_8bc,param_3,param_12,0);
  iVar6 = GetPlayerRecordBySlot(g_clientContext);
  if ((iVar6 != 0) && (cVar5 = PeekPacketChecksumBool(), cVar5 != '\0')) {
    uVar8 = EncodeChecksumDeltaDiv(local_8bc + 0x930,auStack_8a0,4);
    puStack_8 = (undefined1 *)0x25;
    EmitChecksumSum(uVar8);
    uVar4 = uStack_88c;
    puStack_8 = (undefined1 *)0xffffffff;
    if (uStack_88c != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&uStack_8b4);
      uVar7 = uVar4;
    }
    uVar8 = EncodeChecksumDeltaDiv(local_8bc + 0x9b9,auStack_8a0,4);
    puStack_8 = (undefined1 *)0x26;
    EmitChecksumSum(uVar8);
    uVar4 = uStack_88c;
    puStack_8 = (undefined1 *)0xffffffff;
    if (uStack_88c != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&uStack_8b4);
      uVar7 = uVar4;
    }
    uVar8 = EncodeChecksumDeltaDiv(local_8bc + 0xa42,auStack_8a0,4);
    puStack_8 = (undefined1 *)0x27;
    EmitChecksumSum(uVar8);
    uVar4 = uStack_88c;
    puStack_8 = (undefined1 *)0xffffffff;
    if (uStack_88c != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&uStack_8b4);
      uVar7 = uVar4;
    }
  }
  cVar5 = PeekPacketChecksumBool();
  pcVar15 = (code *)LeaveCriticalSection;
  if (cVar5 == '\x01') {
    uVar8 = EncodeChecksumDeltaMul(local_8bc + 0x930,auStack_67c,3);
    puStack_8 = (undefined1 *)0x28;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = PeekPacketChecksumState();
    pcVar15 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaDiv(uVar8,auStack_8a0,uVar11);
    SUBFIELD(puStack_8,0,undefined1) = 0x29;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    iVar9 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar9 + iVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),0x28);
    if (uStack_88c != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&uStack_8b4);
    }
    puStack_8 = (undefined1 *)0xffffffff;
    if (uStack_668 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&uStack_8b4);
    }
    uVar8 = EncodeChecksumDeltaMul(local_8bc + 0x9b9,auStack_67c,3);
    puStack_8 = (undefined1 *)0x2a;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaDiv(uVar8,auStack_8a0,uVar11);
    SUBFIELD(puStack_8,0,undefined1) = 0x2b;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    iVar9 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar9 + iVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),0x2a);
    if (uStack_88c != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&uStack_8b4);
    }
    puStack_8 = (undefined1 *)0xffffffff;
    if (uStack_668 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&uStack_8b4);
    }
    uVar8 = EncodeChecksumDeltaMul(local_8bc + 0xa42,auStack_67c,3);
    puStack_8 = (undefined1 *)0x2c;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaDiv(uVar8,auStack_8a0,uVar11);
    SUBFIELD(puStack_8,0,undefined1) = 0x2d;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    iVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar6 + uVar7);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),0x2c);
    if (uStack_88c != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&uStack_8b4);
      uVar7 = uStack_88c;
    }
    puStack_8 = (undefined1 *)0xffffffff;
    if (uStack_668 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&uStack_8b4);
      uVar7 = uStack_668;
    }
  }
  cVar5 = CheckGuardedBoolAnd(*(char *)(g_clientContext + 0x45127) == '\x02');
  if (cVar5 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    puVar19 = &DAT_005a9068;
    (*pcVar15)(&DAT_005a9068);
    uVar8 = EncodeChecksumDeltaMul(uVar7 + 0x24c0,&puStack_680,uVar8);
    uStack_c = 0x2e;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    puVar18 = &DAT_005a9068;
    (*pcVar15)(&DAT_005a9068);
    EncodeChecksumDeltaDiv(uVar8,&uStack_8a8,unaff_ESI);
    uStack_10 = CONCAT31(SUBFIELD(uStack_10,1,undefined3),0x2f);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar8);
    (*pcVar15)(&DAT_005a9068);
    uStack_14 = CONCAT31(SUBFIELD(uStack_14,1,undefined3),0x2e);
    if (iStack_898 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&stack0xfffff740);
      unaff_EDI = iStack_898;
    }
    uStack_14 = 0xffffffff;
    if (iStack_674 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&stack0xfffff740);
      unaff_EDI = iStack_674;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    puVar17 = &DAT_005a9068;
    (*pcVar15)(&DAT_005a9068);
    uVar8 = EncodeChecksumDeltaMul(unaff_EDI + 0x26e4,auStack_68c,uVar8);
    uStack_18 = 0x30;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar15)(&DAT_005a9068);
    EncodeChecksumDeltaDiv(uVar8,&uStack_8b4,puVar19);
    uStack_1c = 0x31;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar8);
    (*pcVar15)(&DAT_005a9068);
    uStack_20 = CONCAT31(SUBFIELD(uStack_20,1,undefined3),0x30);
    if (puStack_8a4 != (undefined *)0x0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&stack0xfffff734);
      puVar18 = puStack_8a4;
    }
    uStack_20 = 0xffffffff;
    if (puStack_680 != (undefined *)0x0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&stack0xfffff734);
      puVar18 = puStack_680;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    (*pcVar15)(&DAT_005a9068);
    uVar8 = EncodeChecksumDeltaMul(puVar18 + 0x2908,auStack_250,uVar8);
    uStack_24 = 0x32;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar15)(&DAT_005a9068);
    EncodeChecksumDeltaDiv(uVar8,auStack_478,puVar17);
    uStack_28 = 0x33;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar8);
    (*pcVar15)(&DAT_005a9068);
    puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),0x32);
    if (iStack_444 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&uStack_8b4);
    }
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_220 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&uStack_8b4);
    }
  }
  RegisterActiveObject();
  *unaff_FS_OFFSET = uStack_10;
  return;
}

