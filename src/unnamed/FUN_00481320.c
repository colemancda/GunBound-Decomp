/* FUN_00481320 - 0x00481320 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x004813c3) */

void __fastcall FUN_00481320(int *param_1)

{
  int *piVar1;
  byte bVar2;
  bool bVar3;
  bool bVar4;
  char cVar5;
  byte bVar6;
  char cVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  char extraout_var;
  uint uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  code *pcVar17;
  undefined4 unaff_EBP;
  uint unaff_ESI;
  code *pcVar18;
  byte *pbVar19;
  undefined4 *unaff_FS_OFFSET;
  char cVar20;
  int *local_ad0;
  undefined1 auStack_acc [4];
  int local_ac8;
  undefined1 auStack_ac4 [4];
  undefined1 local_ac0 [8];
  int iStack_ab8;
  int iStack_ab4;
  int local_aac;
  undefined1 auStack_8a8 [12];
  undefined1 local_89c [20];
  int local_888;
  undefined1 auStack_684 [548];
  undefined1 auStack_460 [548];
  undefined1 auStack_23c [532];
  undefined4 uStack_28;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00539bef;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  pcVar18 = (code *)EnterCriticalSection;
  local_ad0 = (int *)0x0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = PeekPacketChecksumState();
  iVar9 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar9 + iVar8);
  pcVar17 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_ac8 = PeekPacketChecksumState();
  iVar8 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar8 + local_ac8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = *(int *)(*(int *)(&DAT_006a7f8c + DAT_005b3484) + 0x1c);
  uVar12 = *(uint *)(iVar8 + 4);
  while (uVar12 < 0x186a6) {
    if (uVar12 == 0x186a5) {
      iVar8 = *(int *)(iVar8 + 0x10);
      uVar12 = *(uint *)(iVar8 + 8);
      goto joined_r0x00481401;
    }
    iVar8 = *(int *)(iVar8 + 0x1c);
    uVar12 = *(uint *)(iVar8 + 4);
  }
  iVar8 = 0;
LAB_00481528:
  cVar7 = '\0';
  (**(code **)(*param_1 + 0x14))();
  cVar5 = FUN_004065a0();
  if (cVar5 == '\0') {
    FUN_0040b180(param_1 + 0x10,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x2;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar10);
    (*pcVar17)(&DAT_005a9068);
    uStack_c = 0xffffffff;
    if (iStack_ab4 != 0) {
      FUN_0040a240();
      FUN_0040b540(&local_ad0);
      pcVar17 = (code *)LeaveCriticalSection;
    }
    FUN_0040b180(param_1 + 0x99,&local_ac8,8);
    local_ad0 = param_1 + 0x45e;
    uStack_c = 3;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar10);
    cVar5 = '\0';
    (*pcVar17)();
    uStack_10 = 0xffffffff;
    if (iStack_ab8 != 0) {
      FUN_0040a240();
      FUN_0040b540(&stack0xfffff524);
      pcVar17 = (code *)LeaveCriticalSection;
    }
    cVar7 = FUN_00406610(param_1[0x3d2] != 0);
    if (cVar7 == '\0') {
      FUN_0040afb0(param_1 + 0x2bd);
      FUN_0040afb0(param_1 + 0x346);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar12 = PeekPacketChecksumState();
      (*pcVar17)(&DAT_005a9068);
      if ((int)((uVar12 ^ (int)uVar12 >> 0x1f) - ((int)uVar12 >> 0x1f)) < 200) {
        cVar7 = FUN_0040b330(param_1 + 0x122,0);
        if (cVar7 == '\0') {
          uVar10 = 200;
        }
        else {
          uVar10 = 0xffffff38;
        }
        QueueOutgoingPacketField(uVar10);
      }
      uVar10 = FUN_0040a8c0(param_1[0x3d2] + 0x25c,auStack_684,4);
      uStack_10 = 4;
      uVar10 = FUN_0040aca0(param_1[0x3d2] + 0x38,auStack_460,uVar10);
      uStack_10 = 5;
      bVar4 = false;
      bVar3 = false;
      cVar7 = FUN_0040b490(param_1 + 0x3d5,uVar10);
      if (cVar7 == '\0') {
        uVar10 = FUN_0040a8c0(param_1[0x3d2] + 0x25c,auStack_8a8,4);
        uStack_10 = 6;
        uVar10 = FUN_0040aba0(param_1[0x3d2] + 0x38,auStack_acc,uVar10);
        uStack_10 = 7;
        bVar4 = true;
        bVar3 = true;
        cVar7 = FUN_0040b490(uVar10,param_1 + 0x3d5);
        unaff_ESI = unaff_ESI & 0xffffff;
        if (cVar7 != '\0') goto LAB_00481a4d;
      }
      else {
LAB_00481a4d:
        unaff_ESI = CONCAT13(1,(int3)unaff_ESI);
      }
      uStack_10 = 6;
      if (bVar3) {
        FUN_0040a2a0();
      }
      uStack_10 = 5;
      if (bVar4) {
        FUN_0040a2a0();
      }
      uStack_10 = 4;
      FUN_0040a2a0();
      uStack_10 = 0xffffffff;
      FUN_0040a2a0();
      if ((char)(unaff_ESI >> 0x18) != '\0') {
        iVar8 = param_1[0x3d4];
        param_1[0x3d4] = iVar8 + 1;
        if (iVar8 + 1 < 3) {
          uVar10 = FUN_0040a500(param_1 + 0x122,auStack_23c);
          uStack_10 = 8;
          EncodeChecksumState(uVar10);
          uStack_10 = 0xffffffff;
          FUN_0040a2a0();
        }
        else {
          FUN_00406500(0);
        }
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = PeekPacketChecksumState();
    uVar10 = CONCAT13(iVar8 < 0,(int3)unaff_ESI);
    (*pcVar17)(&DAT_005a9068);
    if (cVar5 == '\0') {
      iVar8 = *(int *)(&DAT_006a7720 + DAT_005b3484);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar9 = PeekPacketChecksumState();
      cVar5 = iVar8 <= iVar9;
      (*pcVar17)(&DAT_005a9068);
      if (((cVar5 != '\0') ||
          (cVar5 = FUN_0040b300(uVar10,*(undefined4 *)(&DAT_006a7724 + DAT_005b3484)), cVar5 != '\0'
          )) || (cVar5 = FUN_0040b330(uVar10,0xfffffc18), cVar5 != '\0')) goto LAB_00481c0c;
    }
    else {
LAB_00481c0c:
      *(undefined1 *)(param_1 + 5) = 1;
      cVar5 = FUN_004065a0();
      if ((cVar5 != '\0') && (cVar5 = FUN_0043a530(), cVar5 == '\0')) {
        iVar8 = *(int *)(*(int *)(DAT_005b3484 + 0x621e4) + 0x24);
        if ((iVar8 == 5) || (uVar10 = 2, iVar8 == 6)) {
          uVar10 = 0x19;
        }
        QueueOutgoingPacketField(uVar10);
        uVar10 = PacketChecksumEquals(DAT_005b3484 + 0x621e8,2);
        FUN_00406500(uVar10);
        iVar8 = DAT_005b3484;
        if (*(int *)(&DAT_005f3768 + DAT_005b3484) != 0) {
          *(undefined4 *)(&DAT_005f3768 + DAT_005b3484) = 5;
          *(undefined4 *)(&DAT_005f376c + iVar8) = 0;
        }
      }
    }
    cVar5 = FUN_00406710();
    if (cVar5 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar9 = PeekPacketChecksumState();
      (*pcVar17)(&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar13 = PeekPacketChecksumState();
      (*pcVar17)(&DAT_005a9068);
      iVar8 = DAT_005b3484;
      piVar1 = (int *)(&DAT_006a7708 + DAT_005b3484);
      cVar5 = FUN_004065a0();
      if ((cVar5 == '\0') && ((&DAT_006a7758)[iVar8] != '\0')) {
        if (((&DAT_006a7736)[iVar8] == '\x01') &&
           ((uVar12 = iVar9 - *(int *)(&DAT_006a7714 + iVar8) >> 0x1f,
            200 < (int)((iVar9 - *(int *)(&DAT_006a7714 + iVar8) ^ uVar12) - uVar12) ||
            (uVar12 = iVar13 - *(int *)(&DAT_006a7710 + iVar8) >> 0x1f,
            300 < (int)((iVar13 - *(int *)(&DAT_006a7710 + iVar8) ^ uVar12) - uVar12))))) {
          (&DAT_006a7736)[iVar8] = 0;
        }
        iVar15 = 400;
        if (399 < iVar13) {
          iVar15 = iVar13;
        }
        iVar14 = *(int *)(&DAT_006a7720 + iVar8) + -400;
        if ((iVar15 <= iVar14) && (iVar14 = iVar13, iVar13 < 400)) {
          iVar14 = 400;
        }
        iVar13 = -0x14;
        if (-0x15 < iVar9) {
          iVar13 = iVar9;
        }
        iVar15 = *(int *)(&DAT_006a7724 + iVar8) + -0x104;
        if ((iVar13 <= iVar15) && (iVar15 = -0x14, -0x15 < iVar9)) {
          iVar15 = iVar9;
        }
        iVar9 = *piVar1 - iVar14;
        *(int *)(&DAT_006a771c + iVar8) = iVar15;
        if (((*(int *)(&DAT_006a770c + iVar8) - iVar15) * (*(int *)(&DAT_006a770c + iVar8) - iVar15)
             + iVar9 * iVar9 < 40000) &&
           (((&DAT_006a7734)[iVar8] == '\x01' || ((&DAT_006a7f6c)[iVar8] == '\0')))) {
          *(int *)(&DAT_006a7710 + iVar8) = iVar14;
          *piVar1 = iVar14;
          *(int *)(&DAT_006a7714 + iVar8) = iVar15;
          *(int *)(&DAT_006a770c + iVar8) = iVar15;
        }
        if ((((&DAT_006a7734)[iVar8] == '\0') && ((&DAT_006a7f6c)[iVar8] == '\x01')) &&
           ((&DAT_006a7736)[iVar8] == '\0')) {
          iVar9 = *(int *)(&DAT_006a7730 + iVar8);
          iVar13 = iVar9;
          if (iVar14 <= iVar9) {
            iVar13 = iVar14;
          }
          iVar16 = *(int *)(&DAT_006a772c + iVar8);
          if ((iVar16 <= iVar13) && (iVar16 = iVar9, iVar14 <= iVar9)) {
            iVar16 = iVar14;
          }
          *(int *)(&DAT_006a7718 + iVar8) = iVar16;
        }
        if ((&DAT_006a7734)[iVar8] == '\x01') {
          *(int *)(&DAT_006a7718 + iVar8) = iVar14;
          *(int *)(&DAT_006a771c + iVar8) = iVar15;
        }
      }
    }
    goto LAB_00481e0f;
  }
  *(undefined1 *)(param_1 + 5) = 1;
  if (iVar8 != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    pcVar17 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0047fad0(uVar11,uVar10,(char)param_1[0xfe7],param_1[2]);
    pcVar18 = (code *)EnterCriticalSection;
  }
  (*pcVar18)(&DAT_005a9068);
  PeekPacketChecksumState();
  PeekPacketChecksumState();
  cVar20 = '\0';
  (*pcVar17)();
  cVar5 = FUN_00406610(unaff_EBP);
  if (cVar5 != '\0') {
    (*pcVar18)(&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar10);
    (*pcVar17)(&DAT_005a9068);
  }
  (*pcVar18)();
  PeekPacketChecksumState();
  (*pcVar17)(&DAT_005a9068);
  if (cVar7 == '\0') {
LAB_00481683:
    cVar5 = '\0';
    (*pcVar18)(&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar17)(&DAT_005a9068);
    if (cVar5 != '\0') {
      (*pcVar18)(&DAT_005a9068);
      PeekPacketChecksumState();
      (*pcVar17)(&DAT_005a9068);
      if (cVar5 != '\0') goto LAB_004816cf;
    }
  }
  else {
    (*pcVar18)(&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar17)(&DAT_005a9068);
    if (cVar7 == '\0') goto LAB_00481683;
LAB_004816cf:
    cVar5 = FUN_004065a0();
    if (cVar5 == '\0') {
      FUN_00406500(1);
    }
  }
  (*pcVar18)(&DAT_005a9068);
  PeekPacketChecksumState();
  PeekPacketChecksumState();
  (*pcVar17)(&DAT_005a9068);
  if ((cVar20 == '\0') || (cVar5 = FUN_0040b490(param_1 + 0xed2,param_1 + 0xf5b), cVar5 == '\0')) {
    (*pcVar18)(&DAT_005a9068);
    PeekPacketChecksumState();
    cVar5 = extraout_var;
    PeekPacketChecksumState();
    (*pcVar17)(&DAT_005a9068);
    if ((cVar5 == '\0') ||
       ((cVar5 = FUN_0040b410(param_1 + 0xed2,param_1 + 0xf5b), cVar5 == '\0' ||
        (param_1[0xed1] < 6)))) goto LAB_00481e0f;
  }
  iVar8 = DAT_005b3484;
  pbVar19 = (byte *)(DAT_005b3484 + 0x62143);
  (*pcVar18)(&DAT_005a9068);
  iVar9 = _rand();
  *pbVar19 = (byte)iVar9;
  iVar9 = _rand();
  bVar2 = *pbVar19;
  *(byte *)(iVar8 + 0x62144) = (byte)iVar9;
  bVar6 = '\x01' << (bVar2 & 7);
  bVar6 = ~bVar6 & (byte)iVar9 | bVar6;
  *(byte *)(iVar8 + 0x62144) = bVar6;
  *(byte *)(iVar8 + 0x62145) = bVar2 + bVar6 + -0x34;
  (*pcVar17)(&DAT_005a9068);
LAB_00481e0f:
  *unaff_FS_OFFSET = uStack_28;
  return;
joined_r0x00481401:
  if ((*(byte *)(param_1 + 0xf) & 0x80000007) < uVar12) goto LAB_0048140f;
  if (uVar12 == (*(byte *)(param_1 + 0xf) & 0x80000007)) {
    local_ac8 = iVar8;
    local_ad0 = (int *)FUN_0040b180(param_1 + 0x99,local_ac0,8);
    local_4 = 0;
    FUN_0040b180(param_1 + 0x10,local_89c,8);
    local_4._0_1_ = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_ad0 = (int *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (*(int *)(iVar8 + 0x24) == 0) {
      *(undefined4 *)(iVar8 + 0x3fa8) = uVar10;
      *(int **)(iVar8 + 0x3fac) = local_ad0;
    }
    local_4 = (uint)local_4._1_3_ << 8;
    if (local_888 != 0) {
      FUN_0040a240();
      FUN_0040b540(&local_ad0);
      pcVar17 = (code *)LeaveCriticalSection;
    }
    local_4 = 0xffffffff;
    iVar8 = local_ac8;
    if (local_aac != 0) {
      FUN_0040a240();
      FUN_0040b540(&local_ad0);
      pcVar17 = (code *)LeaveCriticalSection;
      iVar8 = local_ac8;
    }
    goto LAB_00481528;
  }
  iVar8 = *(int *)(iVar8 + 0x10);
  uVar12 = *(uint *)(iVar8 + 8);
  goto joined_r0x00481401;
LAB_0048140f:
  iVar8 = 0;
  goto LAB_00481528;
}

