/* FUN_004a4950 - 0x004a4950 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004a4950(int *param_1)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  char *pcVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  byte bVar17;
  code *pcVar18;
  undefined4 unaff_EBP;
  byte *pbVar19;
  undefined4 *unaff_FS_OFFSET;
  bool bVar20;
  undefined4 uVar21;
  undefined4 uVar22;
  undefined4 uVar23;
  char cVar24;
  undefined *puVar25;
  undefined4 *puVar26;
  undefined4 *puVar27;
  undefined *puVar28;
  int *piVar29;
  int *piVar30;
  undefined *puVar31;
  undefined *puVar32;
  undefined *puVar33;
  undefined1 auStack_d18 [3];
  char local_d15;
  int local_d14;
  undefined4 local_d10 [2];
  undefined4 uStack_d08;
  int local_d04;
  int *local_d00;
  int *local_cf8;
  undefined1 auStack_cf4 [12];
  undefined *puStack_ce8;
  int local_ce4;
  int local_cd0;
  undefined1 uStack_afc;
  undefined1 auStack_af8 [4];
  undefined1 auStack_af4 [16];
  undefined4 uStack_ae4;
  int local_aac;
  undefined1 uStack_8d8;
  undefined1 auStack_8d0 [532];
  undefined1 auStack_6bc [20];
  int iStack_6a8;
  undefined1 auStack_488 [532];
  undefined1 auStack_274 [20];
  int iStack_260;
  undefined4 uStack_50;
  undefined4 uStack_48;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053e9f5;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_d10[0] = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d00 = param_1 + 0x102c;
  iVar4 = PeekPacketChecksumState();
  pcVar18 = (code *)LeaveCriticalSection;
  local_d15 = iVar4 == -1000000;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (local_d15 == '\0') {
LAB_004a4a60:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    EncodeOutgoingPacketField();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_cf8 = param_1 + 0x10b5;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_cf8 = param_1 + 0x10b5;
    iVar4 = PeekPacketChecksumState();
    local_d15 = iVar4 == -1000000;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (local_d15 == '\0') goto LAB_004a4a60;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    EncodeOutgoingPacketField();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    EncodeOutgoingPacketField();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    EncodeOutgoingPacketField();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d14 = PeekPacketChecksumState();
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d14 = PeekPacketChecksumState();
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d14 = PeekPacketChecksumState();
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d14 = PeekPacketChecksumState();
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004585e0();
  FUN_0040a5f0();
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d14 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0040a9c0();
  local_4._0_1_ = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d04 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = (uint)local_4._1_3_ << 8;
  if (local_cd0 != 0) {
    FUN_0040a240();
    local_d14 = local_cd0;
    FUN_0040b540();
    pcVar18 = (code *)LeaveCriticalSection;
  }
  local_4 = 0xffffffff;
  if (local_aac != 0) {
    FUN_0040a240();
    local_d14 = local_aac;
    FUN_0040b540();
    pcVar18 = (code *)LeaveCriticalSection;
  }
  local_d14 = param_1[0x102a] % 0x168;
  FUN_0053753c();
  local_d14 = FUN_0053753c();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  puVar33 = &DAT_005a9068;
  (*pcVar18)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  puVar32 = &DAT_005a9068;
  (*pcVar18)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d04 = PeekPacketChecksumState();
  (*pcVar18)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d10[0] = PeekPacketChecksumState();
  puVar31 = &DAT_005a9068;
  (*pcVar18)();
  uVar5 = FUN_0040aca0(param_1 + 0x10,auStack_cf4,param_1 + 0x113e);
  uStack_14 = 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar6);
  piVar29 = (int *)&DAT_005a9068;
  (*pcVar18)(&DAT_005a9068);
  uStack_18 = 0xffffffff;
  if (local_ce4 != 0) {
    FUN_0040a240();
    FUN_0040b540(&stack0xfffff2e0);
    pcVar18 = (code *)LeaveCriticalSection;
  }
  FUN_0040aca0(param_1 + 0x99,&local_cf8,param_1 + 0x11c7);
  uStack_18 = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar6);
  (*pcVar18)(&DAT_005a9068);
  uStack_1c = 0xffffffff;
  if (puStack_ce8 != (undefined *)0x0) {
    FUN_0040a240();
    FUN_0040b540(&stack0xfffff2dc);
    pcVar18 = (code *)LeaveCriticalSection;
    puVar33 = puStack_ce8;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar6);
  puVar28 = &DAT_005a9068;
  (*pcVar18)(&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar6);
  puVar26 = (undefined4 *)&DAT_005a9068;
  (*pcVar18)(&DAT_005a9068);
  FUN_004585e0();
  (**(code **)(*param_1 + 0x14))();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(unaff_EBP);
  cVar3 = '\0';
  (*pcVar18)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(puVar33);
  puVar25 = &DAT_005a9068;
  (*pcVar18)(&DAT_005a9068);
  cVar2 = FUN_004065a0();
  if (cVar2 == '\0') {
    FUN_0040b180(param_1 + 0x10,local_d10,8);
    uStack_30 = 9;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar5);
    (*pcVar18)(&DAT_005a9068);
    piVar30 = local_d00;
    uStack_34 = 0xffffffff;
    if (local_d00 != (int *)0x0) {
      FUN_0040a240();
      FUN_0040b540(&stack0xfffff2dc);
      pcVar18 = (code *)LeaveCriticalSection;
      piVar29 = piVar30;
    }
    FUN_0040b180(param_1 + 0x99,&local_d14,8);
    uStack_34 = 10;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar5);
    cVar2 = '\0';
    (*pcVar18)();
    uStack_38 = 0xffffffff;
    if (local_d04 != 0) {
      FUN_0040a240();
      FUN_0040b540(&stack0xfffff2d8);
      pcVar18 = (code *)LeaveCriticalSection;
    }
    cVar3 = FUN_00406610(param_1[0x3d2] != 0);
    if (cVar3 == '\0') {
      FUN_0040afb0(param_1 + 0x2bd);
      FUN_0040afb0(param_1 + 0x346);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar14 = PeekPacketChecksumState();
      (*pcVar18)(&DAT_005a9068);
      if ((int)((uVar14 ^ (int)uVar14 >> 0x1f) - ((int)uVar14 >> 0x1f)) < 200) {
        cVar3 = FUN_0040b330(param_1 + 0x122,0);
        if (cVar3 == '\0') {
          uVar5 = 200;
        }
        else {
          uVar5 = 0xffffff38;
        }
        QueueOutgoingPacketField(uVar5);
      }
      uVar5 = FUN_0040a8c0(param_1[0x3d2] + 0x25c,auStack_8d0,4);
      uStack_38 = 0xb;
      uVar5 = FUN_0040aca0(param_1[0x3d2] + 0x38,auStack_488,uVar5);
      uStack_38 = 0xc;
      puVar28 = (undefined *)0x3;
      cVar3 = FUN_0040b490(param_1 + 0x3d5,uVar5);
      if (cVar3 == '\0') {
        uVar5 = FUN_0040a8c0(param_1[0x3d2] + 0x25c,auStack_af4,4);
        uStack_38 = 0xd;
        uVar5 = FUN_0040aba0(param_1[0x3d2] + 0x38,auStack_d18,uVar5);
        uStack_38 = 0xe;
        puVar28 = (undefined *)0xf;
        cVar3 = FUN_0040b490(uVar5,param_1 + 0x3d5);
        bVar20 = false;
        if (cVar3 != '\0') goto LAB_004a5dbf;
      }
      else {
LAB_004a5dbf:
        bVar20 = true;
      }
      uStack_38 = 0xd;
      if (((uint)puVar28 & 8) != 0) {
        puVar28 = (undefined *)((uint)puVar28 & 0xfffffff7);
        FUN_0040a2a0();
      }
      uStack_38 = 0xc;
      if (((uint)puVar28 & 4) != 0) {
        puVar28 = (undefined *)((uint)puVar28 & 0xfffffffb);
        FUN_0040a2a0();
      }
      uStack_38 = 0xb;
      if (((uint)puVar28 & 2) != 0) {
        puVar28 = (undefined *)((uint)puVar28 & 0xfffffffd);
        FUN_0040a2a0();
      }
      uStack_38 = 0xffffffff;
      if (((uint)puVar28 & 1) != 0) {
        FUN_0040a2a0();
      }
      if (bVar20) {
        iVar4 = param_1[0x3d4];
        param_1[0x3d4] = iVar4 + 1;
        if (iVar4 + 1 < 3) {
          uVar5 = FUN_0040a500(param_1 + 0x122,auStack_8d0);
          uStack_38 = 0xf;
          EncodeChecksumState(uVar5);
          uStack_38 = 0xffffffff;
          FUN_0040a2a0();
        }
        else {
          FUN_00406500(0);
        }
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar18)(&DAT_005a9068);
    if (cVar2 == '\0') {
      iVar4 = *(int *)(&DAT_006a7720 + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar13 = PeekPacketChecksumState();
      cVar2 = iVar4 <= iVar13;
      (*pcVar18)(&DAT_005a9068);
      if (cVar2 != '\0') goto LAB_004a5f78;
      cVar2 = FUN_0040b300(param_1 + 0x45e,*(undefined4 *)(&DAT_006a7724 + g_clientContext));
      if ((cVar2 != '\0') || (cVar2 = FUN_0040b330(param_1 + 0x45e,0xfffffc18), cVar2 != '\0'))
      goto LAB_004a5f78;
    }
    else {
LAB_004a5f78:
      *(undefined1 *)(param_1 + 5) = 1;
      cVar2 = FUN_004065a0();
      if ((cVar2 != '\0') && (cVar2 = FUN_0043a530(), cVar2 == '\0')) {
        iVar4 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
        if ((iVar4 == 5) || (uVar5 = 2, iVar4 == 6)) {
          uVar5 = 0x19;
        }
        QueueOutgoingPacketField(uVar5);
      }
    }
    cVar2 = FUN_00406710();
    if (cVar2 != '\0') {
      FUN_0040b180(piVar29,auStack_274,8);
      uStack_48 = 0x10;
      FUN_0040b180(puVar28,auStack_6bc,8);
      uStack_48._0_1_ = 0x11;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar13 = PeekPacketChecksumState();
      (*pcVar18)(&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar16 = PeekPacketChecksumState();
      (*pcVar18)(&DAT_005a9068);
      iVar4 = g_clientContext;
      piVar29 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar2 = FUN_004065a0();
      if ((cVar2 == '\0') && ((&DAT_006a7758)[iVar4] != '\0')) {
        if (((&DAT_006a7736)[iVar4] == '\x01') &&
           ((uVar14 = iVar13 - *(int *)(&DAT_006a7714 + iVar4) >> 0x1f,
            200 < (int)((iVar13 - *(int *)(&DAT_006a7714 + iVar4) ^ uVar14) - uVar14) ||
            (uVar14 = iVar16 - *(int *)(&DAT_006a7710 + iVar4) >> 0x1f,
            300 < (int)((iVar16 - *(int *)(&DAT_006a7710 + iVar4) ^ uVar14) - uVar14))))) {
          (&DAT_006a7736)[iVar4] = 0;
        }
        iVar8 = 400;
        if (399 < iVar16) {
          iVar8 = iVar16;
        }
        iVar9 = *(int *)(&DAT_006a7720 + iVar4) + -400;
        if ((iVar8 <= iVar9) && (iVar9 = iVar16, iVar16 < 400)) {
          iVar9 = 400;
        }
        iVar16 = -0x14;
        if (-0x15 < iVar13) {
          iVar16 = iVar13;
        }
        iVar8 = *(int *)(&DAT_006a7724 + iVar4) + -0x104;
        if ((iVar16 <= *(int *)(&DAT_006a7724 + iVar4) + -0x104) && (iVar8 = -0x14, -0x15 < iVar13))
        {
          iVar8 = iVar13;
        }
        iVar13 = *piVar29 - iVar9;
        *(int *)(&DAT_006a771c + iVar4) = iVar8;
        if (((*(int *)(&DAT_006a770c + iVar4) - iVar8) * (*(int *)(&DAT_006a770c + iVar4) - iVar8) +
             iVar13 * iVar13 < 40000) &&
           (((&DAT_006a7734)[iVar4] == '\x01' || ((&DAT_006a7f6c)[iVar4] == '\0')))) {
          *(int *)(&DAT_006a7710 + iVar4) = iVar9;
          *piVar29 = iVar9;
          *(int *)(&DAT_006a7714 + iVar4) = iVar8;
          *(int *)(&DAT_006a770c + iVar4) = iVar8;
        }
        if ((((&DAT_006a7734)[iVar4] == '\0') && ((&DAT_006a7f6c)[iVar4] == '\x01')) &&
           ((&DAT_006a7736)[iVar4] == '\0')) {
          iVar13 = *(int *)(&DAT_006a7730 + iVar4);
          iVar16 = iVar13;
          if (iVar9 <= iVar13) {
            iVar16 = iVar9;
          }
          iVar15 = *(int *)(&DAT_006a772c + iVar4);
          if ((iVar15 <= iVar16) && (iVar15 = iVar13, iVar9 <= iVar13)) {
            iVar15 = iVar9;
          }
          *(int *)(&DAT_006a7718 + iVar4) = iVar15;
        }
        if ((&DAT_006a7734)[iVar4] == '\x01') {
          *(int *)(&DAT_006a7718 + iVar4) = iVar9;
          *(int *)(&DAT_006a771c + iVar4) = iVar8;
        }
      }
      uStack_48 = CONCAT31(uStack_48._1_3_,0x10);
      if (iStack_6a8 != 0) {
        FUN_0040a240();
        FUN_0040b540(&stack0xfffff2c8);
      }
      uStack_48 = 0xffffffff;
      if (iStack_260 != 0) {
        FUN_0040a240();
        FUN_0040b540(&stack0xfffff2c8);
      }
    }
    goto LAB_004a61e0;
  }
  FUN_004262d0(param_1[2],param_1 + 0x45e);
  cVar2 = FUN_004065a0();
  if (cVar2 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    puVar28 = &DAT_005a9068;
    (*pcVar18)(&DAT_005a9068);
    if ((-1 < iVar4) && (iVar4 < *(int *)(&DAT_006a7720 + g_clientContext))) {
      pcVar7 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar4);
      iVar4 = 0;
      if (0 < *(int *)(&DAT_006a7724 + g_clientContext)) {
        do {
          if (*pcVar7 != '\0') goto LAB_004a4fba;
          pcVar7 = pcVar7 + *(int *)(&DAT_006a7720 + g_clientContext);
          iVar4 = iVar4 + 1;
        } while (iVar4 < *(int *)(&DAT_006a7724 + g_clientContext));
      }
    }
    iVar4 = 10000;
LAB_004a4fba:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    (*pcVar18)(&DAT_005a9068);
    FUN_00436070(&DAT_006a7f70 + g_clientContext,puVar26,uVar6);
    puVar31 = (undefined *)0x1;
    if (0 < param_1[0xfe5]) {
      puVar31 = (undefined *)param_1[0xfe5];
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puVar26 = (undefined4 *)PeekPacketChecksumState();
    (*pcVar18)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar18)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar18)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar18)(&DAT_005a9068);
    FUN_0043af40(puVar33,puVar25,0,puVar32,iVar4 / (int)puVar26,puVar28,(char)param_1[0xf]);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar18)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar18)(&DAT_005a9068);
    uVar23 = 0;
    uVar22 = 2;
    uVar21 = 0xff;
    uVar6 = 0;
    FUN_004065a0(0,iVar4,0xff,2,0);
    FUN_00431d90((char)param_1[0xf],7,0,uVar6,iVar4,uVar21,uVar22,uVar23);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  cVar24 = '\0';
  (*pcVar18)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  cVar2 = '\0';
  (*pcVar18)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar18)(&DAT_005a9068);
  if (cVar3 == '\0') {
    puVar26 = operator_new(0x3fbc);
    uStack_3c = 4;
    if (puVar26 == (undefined4 *)0x0) {
      puVar26 = (undefined4 *)0x0;
    }
    else {
      FUN_00454dc0(puVar26,0x186a9);
      *puVar26 = &PTR_FUN_0055658c;
      puVar26[0xfe7] = 0xffffffff;
    }
    uStack_3c = 0xffffffff;
    iVar13 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar14 = *(uint *)(iVar13 + 4);
    while (uVar14 < 0x186ab) {
      if (uVar14 == 0x186aa) {
        piVar29 = *(int **)(iVar13 + 0x10);
        bVar20 = true;
        if (piVar29[2] == 0) goto LAB_004a523b;
        break;
      }
      iVar13 = *(int *)(iVar13 + 0x1c);
      uVar14 = *(uint *)(iVar13 + 4);
    }
  }
  goto LAB_004a558f;
  while( true ) {
    piVar29 = (int *)piVar29[4];
    bVar20 = piVar29[2] == 0;
    if (!bVar20) break;
LAB_004a523b:
    if (bVar20) {
      iVar13 = piVar29[0xf];
      iVar16 = piVar29[0xe];
      iVar8 = FUN_004f1f10();
      iVar9 = FUN_0053753c();
      iVar16 = iVar16 - iVar9;
      iVar9 = FUN_0053753c();
      (**(code **)(*piVar29 + 4))(&DAT_00553b90);
      piVar29[0x11] = iVar8;
      cVar3 = FUN_004065a0();
      if (cVar3 == '\0') {
        uStack_8d8 = 0;
        uStack_ae4 = 0;
        EncodeOutgoingPacketField(0);
        uStack_3c = 7;
        uStack_afc = 0;
        uStack_d08 = 0;
        EncodeOutgoingPacketField(0);
        uStack_3c._0_1_ = 8;
        FUN_004262d0(iVar4 + 0x10,&stack0xfffff2e4);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        (*pcVar18)(&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        puVar26 = (undefined4 *)PeekPacketChecksumState();
        (*pcVar18)(&DAT_005a9068);
        iVar4 = param_1[0xfe5];
        uVar10 = 0;
        uVar23 = 0xff;
        uVar22 = 100;
        uVar21 = 0;
        FUN_004065a0(uVar6,0,100,0xff,iVar4,0);
        FUN_00432320((char)param_1[0xf],1,1,uVar6,uVar21,uVar22,uVar23,iVar4,uVar10);
        uStack_3c = CONCAT31(uStack_3c._1_3_,7);
        FUN_0040a2a0();
LAB_004a54f8:
        uStack_3c = 0xffffffff;
        FUN_0040a2a0();
        puVar27 = puVar26;
      }
      else {
        cVar3 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext,&stack0xfffff2e0,&stack0xfffff2dc,2,1,1);
        puVar27 = puVar26;
        if (cVar3 != '\0') {
          uStack_afc = 0;
          uStack_d08 = 0;
          EncodeOutgoingPacketField(0);
          uStack_3c = 5;
          uStack_8d8 = 0;
          uStack_ae4 = 0;
          EncodeOutgoingPacketField(0);
          uStack_3c._0_1_ = 6;
          QueueOutgoingPacketField(puVar31);
          QueueOutgoingPacketField(uVar5);
          FUN_004262d0(iVar4 + 0x10,auStack_af8);
          iVar4 = param_1[0xfe5];
          uVar10 = 0;
          uVar23 = 0xff;
          uVar22 = 100;
          uVar21 = 0;
          FUN_0040a4d0(auStack_af8);
          uVar6 = FUN_0040a4d0(&stack0xfffff2e4);
          FUN_004065a0(uVar6,uVar21,uVar22,uVar23,iVar4,uVar10);
          FUN_00432320((char)param_1[0xf],1,1,uVar6,uVar21,uVar22,uVar23,iVar4,uVar10);
          uStack_3c = CONCAT31(uStack_3c._1_3_,5);
          FUN_0040a2a0();
          goto LAB_004a54f8;
        }
      }
      puVar27[0xfea] = iVar16;
      puVar27[0xfeb] = iVar13 - iVar9;
      puVar27[0xfec] = puVar31;
      puVar27[0xfed] = uVar5;
      puVar27[0xfee] = iVar8;
      puVar26 = puVar27;
      uVar5 = FUN_004ac4d0();
      puVar27[0xfe9] = uVar5;
      iVar4 = FUN_004ac400();
      puVar27[0xfe8] = iVar4 * param_1[0xfe5];
      cVar3 = FUN_004065a0();
      if (cVar3 == '\0') {
        RegisterActiveObject();
      }
      else {
        (**(code **)*puVar27)(1);
      }
      break;
    }
  }
LAB_004a558f:
  *(undefined1 *)(param_1 + 5) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar21 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar22 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar23 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar10 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar11 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar12 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004e4970(uVar12,uVar11,uVar10,uVar23,uVar22,uVar21,uVar6,uVar5);
  FUN_004e4d00(&DAT_006a7708 + g_clientContext);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00450eb0(uVar6,uVar5,param_1,1,0,0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00436ac0(uVar6,uVar5);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004372f0(param_1[2],uVar6,uVar5,param_1[0xe25],param_1 + 0xe26);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar21 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00437150(uVar21,uVar6,0x3c,uVar5);
  iVar4 = g_clientContext;
  cVar3 = FUN_004065a0();
  if (cVar3 != '\x01') {
    iVar13 = *(int *)(&DAT_006a7750 + iVar4);
    if (iVar13 < 0xb) {
      iVar13 = 10;
    }
    *(int *)(&DAT_006a7750 + iVar4) = iVar13;
    iVar13 = *(int *)(&DAT_006a7754 + iVar4);
    if (iVar13 < 0xb) {
      iVar13 = 10;
    }
    *(int *)(&DAT_006a7754 + iVar4) = iVar13;
  }
  cVar3 = FUN_004065a0();
  if (cVar3 == '\0') {
    FUN_004ee9b0(0);
  }
  cVar3 = FUN_004065a0();
  pcVar18 = (code *)LeaveCriticalSection;
  if ((cVar3 != '\0') &&
     (cVar3 = FUN_0043a530(), pcVar18 = (code *)LeaveCriticalSection, cVar3 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    pcVar18 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    QueueOutgoingPacketField(uVar5);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  PeekPacketChecksumState();
  (*pcVar18)(&DAT_005a9068);
  cVar3 = FUN_00406610(puVar26);
  if (cVar3 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar5);
    (*pcVar18)(&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar18)(&DAT_005a9068);
  if (cVar24 == '\0') {
LAB_004a5a0d:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    cVar3 = 0 < iVar4;
    (*pcVar18)(&DAT_005a9068);
    if (cVar3 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState();
      cVar3 = iVar4 < 0;
      (*pcVar18)(&DAT_005a9068);
      if (cVar3 != '\0') goto LAB_004a5a59;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    cVar3 = 0 < iVar4;
    (*pcVar18)(&DAT_005a9068);
    if (cVar3 == '\0') goto LAB_004a5a0d;
LAB_004a5a59:
    cVar3 = FUN_004065a0();
    if (cVar3 == '\0') {
      FUN_00406500(1);
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  PeekPacketChecksumState();
  (*pcVar18)(&DAT_005a9068);
  if ((cVar2 == '\0') || (cVar2 = FUN_0040b490(param_1 + 0xed2,param_1 + 0xf5b), cVar2 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    iVar13 = PeekPacketChecksumState();
    cVar2 = iVar13 < iVar4;
    (*pcVar18)(&DAT_005a9068);
    if ((cVar2 == '\0') ||
       ((cVar2 = FUN_0040b410(param_1 + 0xed2,param_1 + 0xf5b), cVar2 == '\0' ||
        (param_1[0xed1] < 6)))) goto LAB_004a61e0;
  }
  iVar4 = g_clientContext;
  pbVar19 = (byte *)(g_clientContext + 0x62143);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar13 = _rand();
  *pbVar19 = (byte)iVar13;
  iVar13 = _rand();
  bVar1 = *pbVar19;
  *(byte *)(iVar4 + 0x62144) = (byte)iVar13;
  bVar17 = '\x01' << (bVar1 & 7);
  bVar1 = *pbVar19;
  bVar17 = ~bVar17 & (byte)iVar13 | bVar17;
  *(byte *)(iVar4 + 0x62144) = bVar17;
  *(byte *)(iVar4 + 0x62145) = bVar17 + bVar1 + -0x34;
  (*pcVar18)(&DAT_005a9068);
LAB_004a61e0:
  *unaff_FS_OFFSET = uStack_50;
  return;
}

