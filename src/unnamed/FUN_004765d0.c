/* FUN_004765d0 - 0x004765d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004765d0(int *param_1)

{
  int *piVar1;
  int *piVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  code *pcVar17;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar18;
  char *pcVar19;
  uint uStack_ad8;
  int *apiStack_acc [2];
  undefined1 auStack_ac4 [20];
  int iStack_ab0;
  undefined1 auStack_8a0 [548];
  undefined1 auStack_67c [548];
  undefined1 auStack_458 [548];
  undefined1 auStack_234 [548];
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053c398;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  iVar8 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar8 + iVar7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  iVar8 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar8 + iVar7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(8);
  cVar6 = FUN_004065a0();
  if (cVar6 != '\0') {
    *(undefined1 *)(param_1 + 5) = 1;
    cVar6 = FUN_004065a0();
    if (cVar6 == '\0') {
      FUN_004ee9b0(0);
    }
    piVar9 = (int *)GetPlayerRecordBySlot(DAT_005b3484);
    if ((piVar9 != (int *)0x0) && ((short)param_1[0xfe7] == -0xf6)) {
      pcVar19 = s_teleport2_005543cc;
      apiStack_acc[0] = piVar9 + 0x2cc;
      uVar18 = 0x14b6;
      piVar1 = piVar9 + 0x243;
      uVar10 = FUN_0040a4d0(apiStack_acc[0]);
      uVar11 = FUN_0040a4d0(piVar1);
      FUN_004372f0(0,uVar11,uVar10,uVar18,pcVar19);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar10 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      piVar2 = param_1 + 0x45e;
      uVar10 = FUN_0040a6e0(piVar2,auStack_67c,uVar10);
      puStack_8 = (undefined1 *)0x0;
      FUN_0040a4d0(uVar10);
      FUN_0040a4d0(param_1 + 0x3d5);
      iVar7 = FUN_004e4340();
      iVar8 = FUN_0040a4d0(piVar2);
      puStack_8 = (undefined1 *)0xffffffff;
      FUN_0040a2a0();
      if (iVar7 == iVar8) {
        uVar10 = EncodeChecksumState(param_1 + 0x3d5);
        EncodeChecksumState(uVar10);
        EncodeChecksumState(piVar2);
      }
      else {
        cVar6 = FUN_0040b330(param_1 + 0x122,0);
        uStack_ad8 = 2;
        if (cVar6 == '\0') {
          uVar10 = FUN_0040a6e0(param_1 + 0x3d5,auStack_8a0,1);
        }
        else {
          uStack_ad8 = 1;
          uVar10 = FUN_0040a5f0(param_1 + 0x3d5,auStack_ac4,1);
        }
        puStack_8 = (undefined1 *)uStack_ad8;
        EncodeChecksumState(uVar10);
        puStack_8 = (undefined1 *)0x1;
        if ((uStack_ad8 & 2) != 0) {
          uStack_ad8 = uStack_ad8 & 0xfffffffd;
          FUN_0040a2a0();
        }
        puStack_8 = (undefined1 *)0xffffffff;
        if ((uStack_ad8 & 1) != 0) {
          FUN_0040a2a0();
        }
        EncodeChecksumState(piVar1);
        EncodeChecksumState(piVar2);
        (**(code **)(*piVar9 + 4))(&DAT_00553bcc);
      }
      pcVar19 = s_teleport1_005535f8;
      uVar18 = 0x14b5;
      uVar10 = FUN_0040a4d0(apiStack_acc[0]);
      uVar11 = FUN_0040a4d0(piVar1);
      FUN_004372f0(1,uVar11,uVar10,uVar18,pcVar19);
    }
    cVar6 = FUN_004065a0();
    if ((cVar6 != '\0') && (cVar6 = FUN_0043a530(), cVar6 == '\0')) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar10 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      QueueOutgoingPacketField(uVar10);
    }
    goto LAB_00476f35;
  }
  FUN_0040b180(param_1 + 0x10,auStack_ac4,8);
  puStack_8 = (undefined1 *)0x3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar10 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar10);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_8 = (undefined1 *)0xffffffff;
  if (iStack_ab0 != 0) {
    FUN_0040a240();
    FUN_0040b540(apiStack_acc);
  }
  FUN_0040b180(param_1 + 0x99,auStack_ac4,8);
  pcVar17 = (code *)EnterCriticalSection;
  puStack_8 = (undefined1 *)0x4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar10 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar10);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_8 = (undefined1 *)0xffffffff;
  if (iStack_ab0 != 0) {
    FUN_0040a240();
    FUN_0040b540(apiStack_acc);
  }
  cVar6 = FUN_00406610(param_1[0x3d2] != 0);
  if (cVar6 == '\0') {
    FUN_0040afb0(param_1 + 0x2bd);
    FUN_0040afb0(param_1 + 0x346);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar12 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((int)((uVar12 ^ (int)uVar12 >> 0x1f) - ((int)uVar12 >> 0x1f)) < 200) {
      cVar6 = FUN_0040b330(param_1 + 0x122,0);
      if (cVar6 == '\0') {
        uVar10 = 200;
      }
      else {
        uVar10 = 0xffffff38;
      }
      QueueOutgoingPacketField(uVar10);
    }
    uVar10 = FUN_0040a8c0(param_1[0x3d2] + 0x25c,auStack_458,4);
    puStack_8 = (undefined1 *)0x5;
    uVar10 = FUN_0040aca0(param_1[0x3d2] + 0x38,auStack_67c,uVar10);
    puStack_8 = (undefined1 *)0x6;
    bVar4 = false;
    bVar3 = false;
    cVar6 = FUN_0040b490(param_1 + 0x3d5,uVar10);
    if (cVar6 == '\0') {
      uVar10 = FUN_0040a8c0(param_1[0x3d2] + 0x25c,auStack_8a0,4);
      puStack_8 = (undefined1 *)0x7;
      uVar10 = FUN_0040aba0(param_1[0x3d2] + 0x38,auStack_ac4,uVar10);
      puStack_8 = (undefined1 *)0x8;
      bVar4 = true;
      bVar3 = true;
      cVar6 = FUN_0040b490(uVar10,param_1 + 0x3d5);
      bVar5 = false;
      if (cVar6 != '\0') goto LAB_00476b65;
    }
    else {
LAB_00476b65:
      bVar5 = true;
    }
    puStack_8 = (undefined1 *)0x7;
    if (bVar3) {
      FUN_0040a2a0();
    }
    puStack_8 = (undefined1 *)0x6;
    if (bVar4) {
      FUN_0040a2a0();
    }
    puStack_8 = (undefined1 *)0x5;
    FUN_0040a2a0();
    puStack_8 = (undefined1 *)0xffffffff;
    FUN_0040a2a0();
    if (bVar5) {
      iVar7 = param_1[0x3d4];
      param_1[0x3d4] = iVar7 + 1;
      if (iVar7 + 1 < 3) {
        uVar10 = FUN_0040a500(param_1 + 0x122,auStack_234);
        puStack_8 = (undefined1 *)0x9;
        EncodeChecksumState(uVar10);
        puStack_8 = (undefined1 *)0xffffffff;
        FUN_0040a2a0();
      }
      else {
        FUN_00406500(0);
      }
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar7 < 0) {
LAB_00476d03:
    *(undefined1 *)(param_1 + 5) = 1;
    cVar6 = FUN_004065a0();
    if ((cVar6 != '\0') && (cVar6 = FUN_0043a530(), cVar6 == '\0')) {
      iVar7 = *(int *)(*(int *)(DAT_005b3484 + 0x621e4) + 0x24);
      if ((iVar7 == 5) || (uVar10 = 2, iVar7 == 6)) {
        uVar10 = 0x19;
      }
      QueueOutgoingPacketField(uVar10);
    }
  }
  else {
    iVar7 = *(int *)(&DAT_006a7720 + DAT_005b3484);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (((iVar7 <= iVar8) ||
        (cVar6 = FUN_0040b300(param_1 + 0x45e,*(undefined4 *)(&DAT_006a7724 + DAT_005b3484)),
        cVar6 != '\0')) || (cVar6 = FUN_0040b330(param_1 + 0x45e,0xfffffc18), cVar6 != '\0'))
    goto LAB_00476d03;
  }
  cVar6 = FUN_00406710();
  if (cVar6 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar13 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = DAT_005b3484;
    piVar9 = (int *)(&DAT_006a7708 + DAT_005b3484);
    cVar6 = FUN_004065a0();
    if ((cVar6 == '\0') && ((&DAT_006a7758)[iVar7] != '\0')) {
      if (((&DAT_006a7736)[iVar7] == '\x01') &&
         ((uVar12 = iVar8 - *(int *)(&DAT_006a7714 + iVar7) >> 0x1f,
          200 < (int)((iVar8 - *(int *)(&DAT_006a7714 + iVar7) ^ uVar12) - uVar12) ||
          (uVar12 = iVar13 - *(int *)(&DAT_006a7710 + iVar7) >> 0x1f,
          300 < (int)((iVar13 - *(int *)(&DAT_006a7710 + iVar7) ^ uVar12) - uVar12))))) {
        (&DAT_006a7736)[iVar7] = 0;
      }
      iVar15 = 400;
      if (399 < iVar13) {
        iVar15 = iVar13;
      }
      iVar14 = *(int *)(&DAT_006a7720 + iVar7) + -400;
      if ((iVar15 <= iVar14) && (iVar14 = iVar13, iVar13 < 400)) {
        iVar14 = 400;
      }
      iVar13 = -0x14;
      if (-0x15 < iVar8) {
        iVar13 = iVar8;
      }
      iVar15 = *(int *)(&DAT_006a7724 + iVar7) + -0x104;
      if ((iVar13 <= iVar15) && (iVar15 = iVar8, iVar8 < -0x14)) {
        iVar15 = -0x14;
      }
      iVar8 = *piVar9 - iVar14;
      *(int *)(&DAT_006a771c + iVar7) = iVar15;
      if (((*(int *)(&DAT_006a770c + iVar7) - iVar15) * (*(int *)(&DAT_006a770c + iVar7) - iVar15) +
           iVar8 * iVar8 < 40000) &&
         (((&DAT_006a7734)[iVar7] == '\x01' || ((&DAT_006a7f6c)[iVar7] == '\0')))) {
        *(int *)(&DAT_006a7710 + iVar7) = iVar14;
        *piVar9 = iVar14;
        *(int *)(&DAT_006a7714 + iVar7) = iVar15;
        *(int *)(&DAT_006a770c + iVar7) = iVar15;
      }
      if ((((&DAT_006a7734)[iVar7] == '\0') && ((&DAT_006a7f6c)[iVar7] == '\x01')) &&
         ((&DAT_006a7736)[iVar7] == '\0')) {
        iVar8 = *(int *)(&DAT_006a7730 + iVar7);
        iVar13 = iVar8;
        if (iVar14 <= iVar8) {
          iVar13 = iVar14;
        }
        iVar16 = *(int *)(&DAT_006a772c + iVar7);
        if ((iVar16 <= iVar13) && (iVar16 = iVar8, iVar14 <= iVar8)) {
          iVar16 = iVar14;
        }
        *(int *)(&DAT_006a7718 + iVar7) = iVar16;
      }
      pcVar17 = (code *)EnterCriticalSection;
      if ((&DAT_006a7734)[iVar7] == '\x01') {
        *(int *)(&DAT_006a7718 + iVar7) = iVar14;
        *(int *)(&DAT_006a771c + iVar7) = iVar15;
      }
    }
  }
  (*pcVar17)(&DAT_005a9068);
  uVar10 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar17)(&DAT_005a9068);
  uVar11 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00436980(uVar11,uVar10,(short)param_1[0xfe9]);
LAB_00476f35:
  *unaff_FS_OFFSET = uStack_10;
  return;
}

