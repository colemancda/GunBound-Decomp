/* FUN_0044d9b0 - 0x0044d9b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0044d9b0(int *param_1)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffff518;
  undefined stack0xfffff51c;
  int *piVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  char cVar5;
  undefined3 extraout_EAX;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 uVar9;
  char extraout_var;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  char *pcVar15;
  code *pcVar16;
  undefined4 unaff_EBP;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  int iStack_ae0;
  undefined4 uStack_adc;
  int local_ad8;
  undefined1 auStack_ad4 [4];
  undefined4 uStack_ad0;
  undefined1 auStack_acc [4];
  undefined1 auStack_ac8 [4];
  undefined1 auStack_ac4 [4];
  int iStack_ac0;
  int iStack_abc;
  int iStack_ab8;
  int iStack_ab4;
  int iStack_ab0;
  int iStack_aac;
  undefined1 auStack_8b0 [4];
  undefined1 auStack_8ac [4];
  undefined1 auStack_8a8 [4];
  undefined1 auStack_8a4 [4];
  undefined1 auStack_8a0 [4];
  int iStack_89c;
  int iStack_898;
  int iStack_894;
  int iStack_890;
  int iStack_88c;
  int iStack_888;
  undefined1 auStack_68c [548];
  undefined1 auStack_468 [548];
  undefined1 auStack_244 [556];
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0054061d;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_ad8 = 0;
  if ((param_1[0xfe7] != -1) && (iVar6 = param_1[0xfe7] + 1, param_1[0xfe7] = iVar6, iVar6 == 0x24))
  {
    param_1[0xfe7] = -1;
    (**(code **)(*param_1 + 4))(s_change_00555af0);
  }
  pcVar16 = (code *)LeaveCriticalSection;
  if ((char)param_1[0xd] == '\x01') {
    if (param_1[9] == 1) {
      (**(code **)(*param_1 + 4))(s_cnormal_00555ae8);
      uVar7 = FUN_0040ada0(param_1 + 0x795,auStack_ac4,param_1 + 0xcf2);
      puStack_8 = (undefined1 *)0x0;
      FUN_0040a8c0(uVar7,auStack_8a0,100);
      puStack_8 = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar7 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar7);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      puStack_8 = (undefined1 *)0;
      if (iStack_88c != 0) {
        FUN_0040a240();
        FUN_0040b540(&local_ad8);
        pcVar16 = (code *)LeaveCriticalSection;
      }
      puStack_8 = (undefined1 *)0xffffffff;
      if (iStack_ab0 != 0) {
        FUN_0040a240();
        FUN_0040b540(&local_ad8);
        pcVar16 = (code *)LeaveCriticalSection;
      }
      uVar7 = FUN_0040ada0(param_1 + 0x81e,auStack_8a0,param_1 + 0xcf2);
      puStack_8 = (undefined1 *)0x2;
      FUN_0040a8c0(uVar7,auStack_ac4,100);
      puStack_8 = (undefined1 *)3;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar7 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar7);
      (*pcVar16)(&DAT_005a9068);
      uStack_c = 2;
      if (iStack_ab4 != 0) {
        FUN_0040a240();
        FUN_0040b540(&uStack_adc);
        pcVar16 = (code *)LeaveCriticalSection;
      }
      uStack_c = 0xffffffff;
      if (iStack_890 != 0) {
        FUN_0040a240();
        FUN_0040b540(&uStack_adc);
        pcVar16 = (code *)LeaveCriticalSection;
      }
      uVar7 = FUN_0040ada0(param_1 + 0x8a7,auStack_8a4,param_1 + 0xcf2);
      uStack_c = 4;
      unaff_EBP = FUN_0040a8c0(uVar7,auStack_ac8,100);
      uStack_c = 5;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar7 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar7);
      (*pcVar16)(&DAT_005a9068);
      uStack_10 = 4;
      if (iStack_ab8 != 0) {
        FUN_0040a240();
        FUN_0040b540(&iStack_ae0);
        pcVar16 = (code *)LeaveCriticalSection;
      }
      uStack_10 = 0xffffffff;
      if (iStack_894 != 0) {
        FUN_0040a240();
        FUN_0040b540(&iStack_ae0);
        pcVar16 = (code *)LeaveCriticalSection;
      }
      uVar7 = FUN_0040ada0(param_1 + 0x930,auStack_8a8,param_1 + 0xd7b);
      uStack_10 = 6;
      FUN_0040a8c0(uVar7,auStack_acc,100);
      uStack_10 = 7;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar7 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar7);
      (*pcVar16)(&DAT_005a9068);
      uStack_14 = 6;
      if (iStack_abc != 0) {
        FUN_0040a240();
        FUN_0040b540(&stack0xfffff51c);
        pcVar16 = (code *)LeaveCriticalSection;
      }
      uStack_14 = 0xffffffff;
      if (iStack_898 != 0) {
        FUN_0040a240();
        FUN_0040b540(&stack0xfffff51c);
        pcVar16 = (code *)LeaveCriticalSection;
      }
      uVar7 = FUN_0040ada0(param_1 + 0x9b9,auStack_8ac,param_1 + 0xd7b);
      uStack_14 = 8;
      FUN_0040a8c0(uVar7,&uStack_ad0,100);
      uStack_14 = 9;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar7 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar7);
      (*pcVar16)(&DAT_005a9068);
      uStack_18 = 8;
      if (iStack_ac0 != 0) {
        FUN_0040a240();
        FUN_0040b540(&stack0xfffff518);
        pcVar16 = (code *)LeaveCriticalSection;
      }
      uStack_18 = 0xffffffff;
      if (iStack_89c != 0) {
        FUN_0040a240();
        FUN_0040b540(&stack0xfffff518);
        pcVar16 = (code *)LeaveCriticalSection;
      }
      uVar7 = FUN_0040ada0(param_1 + 0xa42,auStack_8b0,param_1 + 0xd7b);
      uStack_18 = 10;
      FUN_0040a8c0(uVar7,auStack_ad4,100);
      uStack_18 = 0xb;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar7 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar7);
      (*pcVar16)(&DAT_005a9068);
      uStack_4 = 10;
      if (iStack_aac != 0) {
        FUN_0040a240();
        iStack_ae0 = iStack_aac;
        FUN_0040b540(auStack_ad4);
        pcVar16 = (code *)LeaveCriticalSection;
      }
      uStack_4 = 0xffffffff;
      if (iStack_888 != 0) {
        FUN_0040a240();
        iStack_ae0 = iStack_888;
        FUN_0040b540(auStack_ad4);
        pcVar16 = (code *)LeaveCriticalSection;
      }
      goto LAB_0044df28;
    }
  }
  else {
LAB_0044df28:
    if (param_1[9] == 1) goto LAB_0044e8d1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iStack_ae0 = PeekPacketChecksumState();
  iVar6 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar6 + iStack_ae0);
  (*pcVar16)(&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  iVar8 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar8 + iVar6);
  (*pcVar16)(&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(8);
  cVar5 = FUN_004065a0();
  if (cVar5 == '\0') {
    FUN_0040b180(param_1 + 0x10,auStack_acc,8);
    uStack_10 = 0xc;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar7);
    (*pcVar16)(&DAT_005a9068);
    uStack_14 = 0xffffffff;
    if (iStack_abc != 0) {
      FUN_0040a240();
      FUN_0040b540(&uStack_adc);
      pcVar16 = (code *)LeaveCriticalSection;
    }
    FUN_0040b180(param_1 + 0x99,&uStack_ad0,8);
    uStack_14 = 0xd;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar7);
    (*pcVar16)(&DAT_005a9068);
    uStack_18 = 0xffffffff;
    if (iStack_ac0 != 0) {
      FUN_0040a240();
      FUN_0040b540(&iStack_ae0);
      pcVar16 = (code *)LeaveCriticalSection;
    }
    cVar5 = FUN_00406610(param_1[0x3d2] != 0);
    if (cVar5 == '\0') {
      FUN_0040afb0(param_1 + 0x2bd);
      FUN_0040afb0(param_1 + 0x346);
    }
    else {
      uVar10 = FUN_0040a4d0(param_1 + 0x122);
      if ((int)((uVar10 ^ (int)uVar10 >> 0x1f) - ((int)uVar10 >> 0x1f)) < 200) {
        cVar5 = FUN_0040b330(param_1 + 0x122,0);
        if (cVar5 == '\0') {
          uVar7 = 200;
        }
        else {
          uVar7 = 0xffffff38;
        }
        QueueOutgoingPacketField(uVar7);
      }
      uVar7 = FUN_0040a8c0(param_1[0x3d2] + 0x25c,auStack_468,4);
      uStack_18 = 0xe;
      uVar7 = FUN_0040aca0(param_1[0x3d2] + 0x38,auStack_68c,uVar7);
      uStack_18 = 0xf;
      bVar3 = false;
      bVar2 = false;
      cVar5 = FUN_0040b490(param_1 + 0x3d5,uVar7);
      if (cVar5 == '\0') {
        uVar7 = FUN_0040a8c0(param_1[0x3d2] + 0x25c,auStack_8b0,4);
        uStack_18 = 0x10;
        uVar7 = FUN_0040aba0(param_1[0x3d2] + 0x38,auStack_ad4,uVar7);
        uStack_18 = 0x11;
        bVar3 = true;
        bVar2 = true;
        cVar5 = FUN_0040b490(uVar7,param_1 + 0x3d5);
        bVar4 = false;
        if (cVar5 != '\0') goto LAB_0044e580;
      }
      else {
LAB_0044e580:
        bVar4 = true;
      }
      uStack_18 = 0x10;
      if (bVar2) {
        FUN_0040a2a0();
      }
      uStack_18 = 0xf;
      if (bVar3) {
        FUN_0040a2a0();
      }
      uStack_18 = 0xe;
      FUN_0040a2a0();
      uStack_18 = 0xffffffff;
      FUN_0040a2a0();
      if (bVar4) {
        iVar6 = param_1[0x3d4];
        param_1[0x3d4] = iVar6 + 1;
        if (iVar6 + 1 < 3) {
          uVar7 = FUN_0040a500(param_1 + 0x122,auStack_244);
          uStack_18 = 0x12;
          EncodeChecksumState(uVar7);
          uStack_18 = 0xffffffff;
          FUN_0040a2a0();
        }
        else {
          FUN_00406500(0);
        }
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    if ((((SUBFIELD(uStack_adc,3,undefined1) != '\0') ||
         (cVar5 = FUN_0040b300(param_1 + 0x3d5,*(undefined4 *)(&DAT_006a7720 + g_clientContext)),
         iVar6 = iStack_ae0, cVar5 != '\0')) ||
        (cVar5 = FUN_0040b300(iStack_ae0,*(undefined4 *)(&DAT_006a7724 + g_clientContext)),
        cVar5 != '\0')) || (cVar5 = FUN_0040b330(iVar6,0xfffffc18), cVar5 != '\0')) {
      *(undefined1 *)(param_1 + 5) = 1;
      cVar5 = FUN_004065a0();
      if ((cVar5 != '\0') && (cVar5 = FUN_0043a530(), cVar5 == '\0')) {
        iVar6 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
        if ((iVar6 == 5) || (uVar7 = 2, iVar6 == 6)) {
          uVar7 = 0x19;
        }
        QueueOutgoingPacketField(uVar7);
        iVar6 = g_clientContext;
        *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
        *(undefined4 *)(&DAT_005f376c + iVar6) = 0;
      }
    }
    cVar5 = FUN_00406710();
    if (cVar5 != '\0') {
      iVar8 = FUN_0040a4d0(iStack_ae0);
      iVar11 = FUN_0040a4d0(param_1 + 0x3d5);
      iVar6 = g_clientContext;
      piVar1 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar5 = FUN_004065a0();
      if ((cVar5 == '\0') && ((&DAT_006a7758)[iVar6] != '\0')) {
        if (((&DAT_006a7736)[iVar6] == '\x01') &&
           ((uVar10 = iVar8 - *(int *)(&DAT_006a7714 + iVar6) >> 0x1f,
            200 < (int)((iVar8 - *(int *)(&DAT_006a7714 + iVar6) ^ uVar10) - uVar10) ||
            (uVar10 = iVar11 - *(int *)(&DAT_006a7710 + iVar6) >> 0x1f,
            300 < (int)((iVar11 - *(int *)(&DAT_006a7710 + iVar6) ^ uVar10) - uVar10))))) {
          (&DAT_006a7736)[iVar6] = 0;
        }
        iVar13 = 400;
        if (399 < iVar11) {
          iVar13 = iVar11;
        }
        iVar12 = *(int *)(&DAT_006a7720 + iVar6) + -400;
        if ((iVar13 <= iVar12) && (iVar12 = iVar11, iVar11 < 400)) {
          iVar12 = 400;
        }
        iVar11 = -0x14;
        if (-0x15 < iVar8) {
          iVar11 = iVar8;
        }
        iVar13 = *(int *)(&DAT_006a7724 + iVar6) + -0x104;
        if ((iVar11 <= iVar13) && (iVar13 = -0x14, -0x15 < iVar8)) {
          iVar13 = iVar8;
        }
        iVar8 = *piVar1 - iVar12;
        *(int *)(&DAT_006a771c + iVar6) = iVar13;
        if (((*(int *)(&DAT_006a770c + iVar6) - iVar13) * (*(int *)(&DAT_006a770c + iVar6) - iVar13)
             + iVar8 * iVar8 < 40000) &&
           (((&DAT_006a7734)[iVar6] == '\x01' || ((&DAT_006a7f6c)[iVar6] == '\0')))) {
          *(int *)(&DAT_006a7710 + iVar6) = iVar12;
          *piVar1 = iVar12;
          *(int *)(&DAT_006a7714 + iVar6) = iVar13;
          *(int *)(&DAT_006a770c + iVar6) = iVar13;
        }
        if ((((&DAT_006a7734)[iVar6] == '\0') && ((&DAT_006a7f6c)[iVar6] == '\x01')) &&
           ((&DAT_006a7736)[iVar6] == '\0')) {
          iVar8 = *(int *)(&DAT_006a7730 + iVar6);
          iVar11 = iVar8;
          if (iVar12 <= iVar8) {
            iVar11 = iVar12;
          }
          iVar14 = *(int *)(&DAT_006a772c + iVar6);
          if ((iVar14 <= iVar11) && (iVar14 = iVar8, iVar12 <= iVar8)) {
            iVar14 = iVar12;
          }
          *(int *)(&DAT_006a7718 + iVar6) = iVar14;
        }
        if ((&DAT_006a7734)[iVar6] == '\x01') {
          *(int *)(&DAT_006a7718 + iVar6) = iVar12;
          *(int *)(&DAT_006a771c + iVar6) = iVar13;
        }
      }
    }
    goto LAB_0044e8d1;
  }
  FUN_004262d0(param_1[2],param_1 + 0x45e);
  cVar5 = FUN_004065a0();
  if (cVar5 != '\0') {
    iVar6 = FUN_0040a4d0(param_1 + 0x3d5);
    if ((-1 < iVar6) && (iVar6 < *(int *)(&DAT_006a7720 + g_clientContext))) {
      pcVar15 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar6);
      iVar6 = 0;
      if (0 < *(int *)(&DAT_006a7724 + g_clientContext)) {
        do {
          if (*pcVar15 != '\0') goto LAB_0044e02e;
          pcVar15 = pcVar15 + *(int *)(&DAT_006a7720 + g_clientContext);
          iVar6 = iVar6 + 1;
        } while (iVar6 < *(int *)(&DAT_006a7724 + g_clientContext));
      }
    }
    iVar6 = 10000;
LAB_0044e02e:
    piVar1 = param_1 + 0x3d5;
    iVar8 = iVar6;
    uVar7 = FUN_0040a4d0(piVar1);
    FUN_00436070(&DAT_006a7f70 + g_clientContext,uVar7,iVar8);
    iVar8 = 1;
    if (0 < param_1[0xfe5]) {
      iVar8 = param_1[0xfe5];
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_ad0 = PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_adc = PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    unaff_EBP = PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    uVar10 = (uint)*(byte *)(param_1 + 0xf);
    iVar8 = local_ad8 / iVar8;
    uVar17 = 0;
    iVar11 = iStack_ae0;
    uVar7 = uStack_ad0;
    uVar9 = FUN_0040a4d0(piVar1);
    FUN_0043af40(uVar9,iVar6,uVar17,iVar11,iVar8,uVar7,uVar10);
    uVar19 = 0;
    uVar18 = 2;
    uVar17 = 0xff;
    uVar7 = FUN_0040a4d0(param_1 + 0x5f9);
    uVar9 = 0;
    FUN_0040a4d0(piVar1);
    FUN_004065a0(uVar9,uVar7,uVar17,uVar18,uVar19);
    FUN_00431d90((char)param_1[0xf],7,0,uVar9,uVar7,uVar17,uVar18,uVar19);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iStack_ae0 = PeekPacketChecksumState();
  (*pcVar16)(&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  SUBFIELD(uStack_adc,0,undefined3) = extraout_EAX;
  SUBFIELD(uStack_adc,3,undefined1) = extraout_var;
  (*pcVar16)(&DAT_005a9068);
  FUN_004398e0(&DAT_006a7f70 + g_clientContext,param_1[2],iStack_ae0,unaff_EBP,param_1,0);
  *(undefined1 *)(param_1 + 5) = 1;
  (**(code **)(*param_1 + 0x20))();
  if (1 < param_1[9]) {
    pcVar15 = s_ssflame1_00555410;
    uVar17 = 0x206c;
    uVar7 = FUN_0040a4d0(param_1 + 0x45e);
    uVar9 = FUN_0040a4d0(param_1 + 0x3d5);
    FUN_004373c0(uVar9,uVar7,uVar17,pcVar15);
  }
  cVar5 = FUN_004065a0();
  iVar6 = g_clientContext;
  if ((cVar5 != '\0') && (cVar5 = FUN_0043a530(), iVar6 = g_clientContext, cVar5 == '\0')) {
    uVar7 = FUN_0040a4d0(&DAT_007949c8);
    QueueOutgoingPacketField(uVar7);
    iVar6 = g_clientContext;
    *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
    *(undefined4 *)(&DAT_005f376c + iVar6) = 0;
  }
  uVar7 = FUN_0040b490(iVar6 + 0x5b85c,param_1 + 0xe48);
  cVar5 = FUN_00406610(uVar7);
  if (cVar5 != '\0') {
    EncodeChecksumState(param_1 + 0xe48);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar16)(&DAT_005a9068);
  if ((SUBFIELD(uStack_adc,3,undefined1) == '\0') || (cVar5 = FUN_0040b2d0(param_1 + 0x122,0), cVar5 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    SUBFIELD(uStack_adc,3,undefined1) = 0 < iVar6;
    (*pcVar16)(&DAT_005a9068);
    if ((SUBFIELD(uStack_adc,3,undefined1) != '\0') && (cVar5 = FUN_0040b330(param_1 + 0x122,0), cVar5 != '\0'))
    goto LAB_0044e2cb;
  }
  else {
LAB_0044e2cb:
    cVar5 = FUN_004065a0();
    if (cVar5 == '\0') {
      FUN_00406500(1);
    }
  }
  piVar1 = param_1 + 0xed2;
  cVar5 = FUN_0040b490(param_1 + 0x3d5,piVar1);
  if (((cVar5 != '\0') && (cVar5 = FUN_0040b490(piVar1,param_1 + 0xf5b), cVar5 != '\0')) ||
     ((cVar5 = FUN_0040b410(param_1 + 0x3d5,piVar1), cVar5 != '\0' &&
      ((cVar5 = FUN_0040b410(piVar1,param_1 + 0xf5b), cVar5 != '\0' && (5 < param_1[0xed1])))))) {
    FUN_00406500(1);
  }
LAB_0044e8d1:
  *unaff_FS_OFFSET = uStack_c;
  return;
}

