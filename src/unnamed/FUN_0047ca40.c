/* FUN_0047ca40 - 0x0047ca40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0047ca40(int *param_1)

{
  int *piVar1;
  byte bVar2;
  undefined1 uVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  int iVar13;
  int unaff_EBX;
  code *pcVar14;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  uint uVar18;
  undefined4 uVar19;
  undefined *puVar20;
  undefined *puVar21;
  uint uVar22;
  undefined *puVar23;
  undefined *puVar24;
  undefined4 uVar25;
  undefined *puVar26;
  int iStack_ad4;
  uint local_acc;
  undefined1 auStack_ac8 [4];
  undefined1 auStack_ac4 [20];
  int iStack_ab0;
  undefined1 auStack_89c [20];
  int iStack_888;
  undefined1 auStack_67c [552];
  undefined1 auStack_454 [20];
  int iStack_440;
  undefined1 auStack_234 [548];
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053d1fe;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_acc = 0;
  FUN_0047bfd0();
  FUN_00450730();
  if ((char)param_1[0xd] != '\0') {
    (**(code **)(*param_1 + 4))(s_normal_00552230);
  }
  param_1[0xfec] = (param_1[0xfec] + 1) % 0x16;
  iVar5 = GetPlayerRecordBySlot(g_clientContext);
  if (param_1[9] == 0) {
    uVar3 = PeekPacketChecksumBool();
    *(undefined1 *)(param_1 + 0xfe8) = uVar3;
  }
  if (iVar5 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar6 != 1) {
      *(undefined1 *)(param_1 + 5) = 1;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    param_1[0xfed] = iVar6;
    FUN_0040a5f0(iVar5 + 0xb30,auStack_454,
                 (-(uint)((char)param_1[0xfe8] != '\0') & 0xffffff38) - 200);
    uStack_4 = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iStack_ad4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (*(int *)(&DAT_006a7724 + g_clientContext) + iStack_ad4 < iVar6) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = *(int *)(&DAT_006a7724 + g_clientContext) + iVar6;
    }
    else {
      FUN_0040a5f0(iVar5 + 0xb30,auStack_89c,
                   (-(uint)((char)param_1[0xfe8] != '\0') & 0xffffff38) - 200);
      uStack_4 = CONCAT31(SUBFIELD(uStack_4,1,undefined3),1);
      local_acc = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    param_1[0xfee] = iVar6;
    uStack_4 = 0;
    if (((local_acc & 1) != 0) && (iStack_888 != 0)) {
      FUN_0040a240();
      FUN_0040b540(auStack_ac8);
    }
    uStack_4 = 0xffffffff;
    if (iStack_440 != 0) {
      FUN_0040a240();
      FUN_0040b540(auStack_ac8);
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  pcVar14 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (param_1[0xfee] != iVar6) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = param_1[0xfee] - iVar6;
    if ((param_1[0xfef] == 0) && (param_1[9] != 3)) {
      if (0 < iVar6) {
        iVar6 = iVar6 + 7;
      }
      if (iVar6 < 0) {
        iVar6 = iVar6 + -7;
      }
      iVar6 = (int)(iVar6 + (iVar6 >> 0x1f & 7U)) >> 3;
    }
    else {
      if (0 < iVar6) {
        iVar6 = iVar6 + 1;
      }
      if (iVar6 < 0) {
        iVar6 = iVar6 + -1;
      }
      iVar6 = iVar6 / 2;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar7 + iVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    pcVar14 = (code *)LeaveCriticalSection;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  puVar26 = &DAT_005a9068;
  (*pcVar14)(&DAT_005a9068);
  if (param_1[0xfed] != unaff_EBX) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    (*pcVar14)(&DAT_005a9068);
    iVar6 = param_1[0xfed] - iVar6;
    if ((param_1[0xfef] == 0) && (param_1[9] != 3)) {
      if (0 < iVar6) {
        iVar6 = iVar6 + 7;
      }
      if (iVar6 < 0) {
        iVar6 = iVar6 + -7;
      }
      iVar6 = (int)(iVar6 + (iVar6 >> 0x1f & 7U)) >> 3;
    }
    else {
      if (0 < iVar6) {
        iVar6 = iVar6 + 1;
      }
      if (iVar6 < 0) {
        iVar6 = iVar6 + -1;
      }
      iVar6 = iVar6 / 2;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar7 + iVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    pcVar14 = (code *)LeaveCriticalSection;
  }
  if (param_1[9] == 3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    (*pcVar14)(&DAT_005a9068);
    if (param_1[0xfed] == iVar6) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      (*pcVar14)(&DAT_005a9068);
      if (param_1[0xfee] == iVar6) {
        switch(param_1[0xfef]) {
        case 0:
          (**(code **)(*param_1 + 4))(s_normal_00552230);
          break;
        case 1:
        case 3:
          (**(code **)(*param_1 + 4))(&DAT_00553b68);
          break;
        case 2:
          (**(code **)(*param_1 + 4))(&DAT_00553b70);
        }
        param_1[0xfef] = 0;
      }
    }
  }
  if (param_1[9] == 1) {
    if ((char)param_1[0xff2] != '\0') {
      FUN_0040a6e0(iStack_ad4 + 0xb30,auStack_67c,400);
      puStack_8 = (undefined1 *)0x2;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar8 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      param_1[0xfee] = iVar5;
      puStack_8 = (undefined1 *)0xffffffff;
      FUN_0040a2a0();
      if (param_1[0xb] == 1) {
        iVar5 = 0;
        do {
          if (*(char *)(iStack_ad4 + 0x651c) == '\0') {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_acc = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          else {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_acc = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          uVar22 = local_acc;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_acc = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar8 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar16 = 1;
          uVar15 = 8;
          iVar9 = iVar5 * 2;
          uVar11 = PeekPacketChecksumBool(iVar9,uVar22,8,1);
          iVar6 = param_1[0xff7];
          iVar7 = param_1[0xff5];
          uVar18 = local_acc;
          uVar12 = PeekPacketChecksumBool(iVar7,uVar8,iVar6,local_acc,uVar11);
          FUN_004305c0(*(byte *)(param_1 + 2) & 7,iVar5,0,uVar12,iVar7,uVar8,iVar6,uVar18,uVar11,
                       iVar9,uVar22,uVar15,uVar16);
          if (iVar5 == 3) {
            param_1[0xff8] = -param_1[0xff8];
            param_1[0xff6] = -param_1[0xff6];
          }
          else {
            param_1[0xff7] = param_1[0xff7] + param_1[0xff8];
            param_1[0xff5] = param_1[0xff5] + param_1[0xff6];
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < 8);
        cVar4 = FUN_0043a530();
        if (cVar4 == '\0') {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar8 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
      }
      goto LAB_0047dbc9;
    }
    FUN_0040a6e0(iStack_ad4 + 0xb30,auStack_234,200);
    puStack_8 = (undefined1 *)0x3;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    param_1[0xfee] = iVar5;
    puStack_8 = (undefined1 *)0xffffffff;
    FUN_0040a2a0();
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    param_1[0xfed] = iVar5;
    FUN_0047bfd0();
    if (param_1[0xb] != 2) goto LAB_0047dbc9;
    QueueOutgoingPacketField(0xffffffff);
    iVar7 = FUN_0040a4d0(param_1 + 0x10);
    iVar5 = param_1[0xfea];
    iVar6 = param_1[0xfeb];
    iVar9 = FUN_0040a4d0(param_1 + 0x99);
    iVar9 = iVar6 - iVar9;
    local_acc = iVar9 * iVar9 + (iVar5 - iVar7) * (iVar5 - iVar7);
    iVar5 = FUN_0053753c();
    param_1[0xff1] = iVar5;
    iVar5 = FUN_0053753c();
    iVar5 = iVar5 + param_1[0xfea];
    iVar7 = FUN_0053753c();
    iVar6 = iVar6 - iVar7;
    if (*(char *)(iStack_ad4 + 0x651c) == '\0') {
      puVar26 = &DAT_00794e48;
    }
    else {
      puVar26 = &DAT_00796aa0;
    }
    uVar8 = FUN_0040a4d0(puVar26);
    uVar17 = 0;
    uVar19 = 3;
    uVar16 = 3;
    piVar1 = param_1 + 0x4e7;
    uVar11 = PeekPacketChecksumBool(3,uVar8,3,0);
    uVar12 = FUN_0040a4d0(piVar1);
    iVar7 = param_1[0xfe7];
    uVar15 = PeekPacketChecksumBool(iVar5,iVar6,iVar7,uVar12,uVar11);
    FUN_004305c0(*(byte *)(param_1 + 2) & 7,param_1[0xfe9] + 1,0,uVar15,iVar5,iVar6,iVar7,uVar12,
                 uVar11,uVar16,uVar8,uVar19,uVar17);
    iVar5 = FUN_0053753c();
    iVar5 = iVar5 + param_1[0xfea];
    iVar6 = FUN_0053753c();
    iVar6 = param_1[0xfeb] - iVar6;
    if (*(char *)(iStack_ad4 + 0x651c) == '\0') {
      puVar26 = &DAT_00794e48;
    }
    else {
      puVar26 = &DAT_00796aa0;
    }
    uVar8 = FUN_0040a4d0(puVar26);
    uVar17 = 0;
    uVar19 = 3;
    uVar16 = 7;
    uVar11 = PeekPacketChecksumBool(7,uVar8,3,0);
    uVar12 = FUN_0040a4d0(piVar1);
    iVar7 = param_1[0xfe7] + 4;
    uVar15 = PeekPacketChecksumBool(iVar5,iVar6,iVar7,uVar12,uVar11);
    FUN_004305c0(*(byte *)(param_1 + 2) & 7,param_1[0xfe9] + 2,0,uVar15,iVar5,iVar6,iVar7,uVar12,
                 uVar11,uVar16,uVar8,uVar19,uVar17);
    iVar6 = FUN_0053753c();
    iVar6 = iVar6 + param_1[0xfea];
    iVar5 = FUN_0053753c();
    iVar5 = param_1[0xfeb] - iVar5;
    if (*(char *)(iStack_ad4 + 0x651c) == '\0') {
      puVar26 = &DAT_00794e48;
    }
    else {
      puVar26 = &DAT_00796aa0;
    }
    uVar8 = FUN_0040a4d0(puVar26);
    uVar25 = 0;
    uVar17 = 3;
    uVar19 = 7;
    uVar12 = PeekPacketChecksumBool(7,uVar8,3,0);
    uVar11 = FUN_0040a4d0(piVar1);
    iVar7 = param_1[0xfe7] + -4;
    uVar15 = PeekPacketChecksumBool(iVar6,iVar5,iVar7,uVar11,uVar12);
    bVar2 = *(byte *)(param_1 + 2);
    iVar9 = param_1[0xfe9] + 3;
    uVar16 = 0;
  }
  else {
    if (param_1[9] != 2) goto LAB_0047dbc9;
    FUN_0040a6e0(iStack_ad4 + 0xb30,auStack_ac4,400);
    puStack_8 = (undefined1 *)0x4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar8);
    pcVar14 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0xffffffff;
    param_1[0xfee] = iVar6;
    if (iStack_ab0 != 0) {
      FUN_0040a240();
      FUN_0040b540(&local_acc);
      pcVar14 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar8);
    (*pcVar14)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    (*pcVar14)(&DAT_005a9068);
    param_1[0xfed] = iVar6;
    FUN_0047bfd0();
    if (param_1[0xb] != 2) goto LAB_0047dbc9;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0xffffffff);
    puVar24 = &DAT_005a9068;
    (*pcVar14)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar9 = PeekPacketChecksumState();
    puVar23 = &DAT_005a9068;
    (*pcVar14)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    puVar21 = &DAT_005a9068;
    (*pcVar14)(&DAT_005a9068);
    iVar7 = param_1[0xfeb];
    iVar6 = FUN_0053753c();
    param_1[0xff1] = iVar6;
    iVar10 = FUN_0053753c();
    iVar10 = iVar10 + param_1[0xfea];
    iVar6 = FUN_0053753c();
    iVar7 = iVar7 - iVar6;
    if (*(char *)(iVar9 + 0x651c) == '\0') {
      puVar20 = &DAT_00794e48;
    }
    else {
      puVar20 = &DAT_00796aa0;
    }
    uVar8 = FUN_0040a4d0(puVar20);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    (*pcVar14)(&DAT_005a9068);
    uVar19 = 0;
    uVar16 = 5;
    uVar15 = 3;
    uVar11 = PeekPacketChecksumBool(3,puVar26,5,0);
    iVar13 = param_1[0xfe7];
    uVar12 = PeekPacketChecksumBool(uVar8,iVar9,iVar13,iVar7,uVar11);
    FUN_004305c0(*(byte *)(param_1 + 2) & 7,param_1[0xfe9] + 1,1,uVar12,uVar8,iVar9,iVar13,iVar7,
                 uVar11,uVar15,puVar26,uVar16,uVar19);
    iVar7 = FUN_0053753c();
    iVar7 = iVar7 + param_1[0xfea];
    iVar9 = FUN_0053753c();
    iVar9 = param_1[0xfeb] - iVar9;
    if (*(char *)(iVar10 + 0x651c) == '\0') {
      puVar26 = &DAT_00794e48;
    }
    else {
      puVar26 = &DAT_00796aa0;
    }
    uVar11 = FUN_0040a4d0(puVar26);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    (*pcVar14)(&DAT_005a9068);
    uVar17 = 0;
    uVar19 = 5;
    uVar16 = 7;
    uVar12 = PeekPacketChecksumBool(7,puVar24,5,0);
    iVar13 = param_1[0xfe7] + 2;
    uVar15 = PeekPacketChecksumBool(uVar11,iVar10,iVar13,iVar9,uVar12);
    FUN_004305c0(*(byte *)(param_1 + 2) & 7,param_1[0xfe9] + 2,1,uVar15,uVar11,iVar10,iVar13,iVar9,
                 uVar12,uVar16,puVar24,uVar19,uVar17);
    iVar9 = FUN_0053753c();
    iVar9 = iVar9 + param_1[0xfea];
    iVar10 = FUN_0053753c();
    iVar10 = param_1[0xfeb] - iVar10;
    if (*(char *)(iVar7 + 0x651c) == '\0') {
      puVar26 = &DAT_00794e48;
    }
    else {
      puVar26 = &DAT_00796aa0;
    }
    uVar11 = FUN_0040a4d0(puVar26);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar14)(&DAT_005a9068);
    uVar17 = 0;
    uVar19 = 5;
    uVar16 = 7;
    uVar12 = PeekPacketChecksumBool(7,puVar23,5,0);
    iVar13 = param_1[0xfe7] + -2;
    uVar15 = PeekPacketChecksumBool(uVar11,iVar7,iVar13,iVar10,uVar12);
    FUN_004305c0(*(byte *)(param_1 + 2) & 7,param_1[0xfe9] + 3,1,uVar15,uVar11,iVar7,iVar13,iVar10,
                 uVar12,uVar16,puVar23,uVar19,uVar17);
    iVar7 = FUN_0053753c();
    iVar7 = iVar7 + param_1[0xfea];
    iVar10 = FUN_0053753c();
    iVar10 = param_1[0xfeb] - iVar10;
    if (*(char *)(iVar9 + 0x651c) == '\0') {
      puVar26 = &DAT_00794e48;
    }
    else {
      puVar26 = &DAT_00796aa0;
    }
    uVar11 = FUN_0040a4d0(puVar26);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar14)(&DAT_005a9068);
    uVar17 = 0;
    uVar19 = 5;
    uVar16 = 0xb;
    uVar12 = PeekPacketChecksumBool(0xb,puVar21,5,0);
    iVar13 = param_1[0xfe7] + 4;
    uVar15 = PeekPacketChecksumBool(uVar11,iVar9,iVar13,iVar10,uVar12);
    FUN_004305c0(*(byte *)(param_1 + 2) & 7,param_1[0xfe9] + 4,1,uVar15,uVar11,iVar9,iVar13,iVar10,
                 uVar12,uVar16,puVar21,uVar19,uVar17);
    FUN_0053753c();
    iVar9 = FUN_0053753c();
    iVar9 = param_1[0xfeb] - iVar9;
    if (*(char *)(iVar7 + 0x651c) == '\0') {
      puVar26 = &DAT_00794e48;
    }
    else {
      puVar26 = &DAT_00796aa0;
    }
    FUN_0040a4d0(puVar26);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = PeekPacketChecksumState();
    (*pcVar14)(&DAT_005a9068);
    uVar25 = 0;
    uVar17 = 5;
    uVar19 = 0xb;
    uVar12 = PeekPacketChecksumBool(0xb,uVar8,5,0,iVar9);
    iVar7 = param_1[0xfe7] + -4;
    uVar15 = PeekPacketChecksumBool(iVar6,iVar5,iVar7,uVar11,uVar12);
    bVar2 = *(byte *)(param_1 + 2);
    uVar16 = 1;
    iVar9 = param_1[0xfe9] + 5;
  }
  FUN_004305c0(bVar2 & 7,iVar9,uVar16,uVar15,iVar6,iVar5,iVar7,uVar11,uVar12,uVar19,uVar8,uVar17,
               uVar25);
  cVar4 = PeekPacketChecksumBool();
  if ((cVar4 == '\0') && (cVar4 = PeekPacketChecksumBool(), cVar4 == '\0')) {
    cVar4 = FUN_0043a530();
    if (cVar4 == '\0') {
      uVar8 = FUN_0040a4d0(&DAT_007949c8);
      QueueOutgoingPacketField(uVar8);
    }
    FUN_00406500(1);
  }
LAB_0047dbc9:
  *unaff_FS_OFFSET = uStack_10;
  return;
}

