/* FUN_004513b0 - 0x004513b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004513b0(int *param_1)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  char extraout_var;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  uint uVar15;
  code *pcVar16;
  code *pcVar17;
  int *piVar18;
  byte *pbVar19;
  undefined4 *unaff_FS_OFFSET;
  bool bVar20;
  undefined4 in_stack_fffff440;
  undefined4 in_stack_fffff450;
  undefined *puVar21;
  undefined *puVar22;
  undefined *puVar23;
  undefined *puVar24;
  undefined *puVar25;
  undefined *puVar26;
  undefined4 uVar27;
  char cVar28;
  undefined4 uVar29;
  undefined4 uStack_b6c;
  undefined4 uStack_b68;
  undefined **ppuStack_b64;
  undefined4 uStack_b60;
  undefined4 uStack_b5c;
  undefined4 uStack_b58;
  undefined4 *puStack_b54;
  undefined *puStack_b50;
  undefined *puStack_b4c;
  int *piStack_b48;
  undefined4 *puStack_b44;
  undefined *puStack_b40;
  int *piStack_b3c;
  undefined **ppuStack_b38;
  undefined *puStack_b34;
  undefined4 *puStack_b30;
  undefined4 *puStack_b2c;
  undefined *puStack_b28;
  undefined *puStack_b24;
  undefined *puStack_b20;
  undefined *puStack_b1c;
  undefined *puStack_b18;
  undefined *puStack_b14;
  undefined *puStack_b10;
  undefined *puStack_b0c;
  undefined *puStack_b08;
  undefined1 auStack_908 [20];
  undefined4 uStack_8f4;
  undefined1 uStack_6e8;
  undefined1 auStack_6e4 [548];
  undefined1 auStack_4c0 [548];
  undefined1 auStack_29c [448];
  undefined4 uStack_dc;
  undefined4 uStack_98;
  undefined4 uStack_90;
  undefined4 uStack_88;
  undefined4 uStack_70;
  undefined4 uStack_68;
  undefined4 uStack_60;
  undefined4 uStack_58;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  cVar28 = (char)((uint)in_stack_fffff440 >> 0x18);
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005404e4;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  cVar2 = FUN_004065a0();
  pcVar17 = (code *)EnterCriticalSection;
  if (cVar2 == '\0') {
    puStack_b08 = (undefined *)0x4514d5;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_b08 = (undefined *)0x4514dc;
    EncodeOutgoingPacketField();
    pcVar16 = (code *)LeaveCriticalSection;
    puStack_b08 = (undefined *)0x4514e9;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  else {
    cVar2 = FUN_004065a0();
    pcVar17 = (code *)EnterCriticalSection;
    pcVar16 = (code *)LeaveCriticalSection;
    if (cVar2 == '\0') {
      FUN_004585e0();
      puStack_b08 = (undefined *)0x451419;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = _rand();
      *(byte *)((int)param_1 + 0x3f9f) = (byte)iVar4;
      iVar4 = _rand();
      bVar1 = *(byte *)((int)param_1 + 0x3f9f);
      *(byte *)(param_1 + 0xfe8) = (byte)iVar4;
      bVar3 = '\x01' << (bVar1 & 7);
      bVar3 = ~bVar3 & (byte)iVar4 | bVar3;
      *(byte *)(param_1 + 0xfe8) = bVar3;
      *(byte *)((int)param_1 + 0x3fa1) = bVar1 + bVar3 + -0x34;
      puStack_b08 = (undefined *)0x45147b;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      puStack_b08 = (undefined *)0x451482;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState();
      puStack_b08 = (undefined *)0x45149c;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      param_1[0xfe9] = (uint)(iVar4 < 0x5a) * 2 + -1;
    }
    if (param_1[0xfe9] == 0) {
      FUN_004585e0();
    }
  }
  puStack_b08 = (undefined *)0x4514f0;
  (*pcVar17)();
  puStack_b08 = (undefined *)0x4514fb;
  PeekPacketChecksumState();
  puStack_b08 = &DAT_005a9068;
  puStack_b0c = (undefined *)0x451504;
  (*pcVar16)();
  puStack_b0c = &DAT_005a9068;
  puStack_b10 = (undefined *)0x45152a;
  (*pcVar17)();
  puStack_b10 = (undefined *)0x451537;
  PeekPacketChecksumState();
  puStack_b10 = &DAT_005a9068;
  puStack_b14 = (undefined *)0x451542;
  (*pcVar16)();
  puStack_b14 = &DAT_005a9068;
  puStack_b18 = (undefined *)0x451549;
  (*pcVar17)();
  puStack_b18 = (undefined *)0x451553;
  PeekPacketChecksumState();
  puStack_b18 = &DAT_005a9068;
  puStack_b1c = (undefined *)0x45155e;
  (*pcVar16)();
  puStack_b1c = &DAT_005a9068;
  puStack_b20 = (undefined *)0x451565;
  (*pcVar17)();
  puStack_b20 = (undefined *)0x45156f;
  PeekPacketChecksumState();
  puStack_b20 = &DAT_005a9068;
  puStack_b24 = (undefined *)0x45157a;
  (*pcVar16)();
  puStack_b24 = (undefined *)0x45158b;
  FUN_0053753c();
  puStack_b24 = &DAT_005a9068;
  puStack_b28 = (undefined *)0x45159b;
  (*pcVar17)();
  puStack_b28 = (undefined *)0x4515a6;
  puStack_b08 = (undefined *)PeekPacketChecksumState();
  puStack_b28 = &DAT_005a9068;
  puStack_b2c = (undefined4 *)0x4515b1;
  (*pcVar16)();
  iVar4 = (int)(puStack_b0c + 0x5a) % 0x168;
  if (iVar4 < 0) {
    iVar4 = iVar4 + 0x168;
  }
  puStack_b08 = *(undefined **)(&g_sineTable360 + iVar4 * 4);
  puStack_b2c = (undefined4 *)&DAT_005a9068;
  puStack_b30 = (undefined4 *)0x4515d8;
  (*pcVar17)();
  puStack_b30 = (undefined4 *)0x4515df;
  puStack_b08 = (undefined *)PeekPacketChecksumState();
  puStack_b30 = (undefined4 *)&DAT_005a9068;
  puStack_b34 = (undefined *)0x4515ea;
  (*pcVar16)();
  puStack_b34 = &DAT_005a9068;
  ppuStack_b38 = (undefined **)0x4515f1;
  (*pcVar17)();
  ppuStack_b38 = (undefined **)0x4515fb;
  puStack_b18 = (undefined *)PeekPacketChecksumState();
  ppuStack_b38 = (undefined **)&DAT_005a9068;
  piStack_b3c = (int *)0x451606;
  (*pcVar16)();
  piStack_b3c = (int *)&DAT_005a9068;
  puStack_b40 = (undefined *)0x45160d;
  (*pcVar17)();
  puStack_b40 = (undefined *)0x451617;
  iVar4 = PeekPacketChecksumState();
  puStack_b40 = &DAT_005a9068;
  puStack_b44 = (undefined4 *)0x451620;
  (*pcVar16)();
  puStack_b44 = (undefined4 *)0x451631;
  iVar5 = FUN_0053753c();
  puStack_b20 = (undefined *)-(iVar5 / iVar4);
  if (0 < (int)puStack_b20) {
    puStack_b10 = (undefined *)-(int)puStack_b10;
    puStack_b20 = (undefined *)(iVar5 / iVar4);
  }
  puStack_b44 = (undefined4 *)0x451659;
  cVar2 = FUN_00406860();
  if (cVar2 != '\0') {
    puStack_b44 = (undefined4 *)&DAT_005a9068;
    piStack_b48 = (int *)0x45166a;
    (*pcVar17)();
    piStack_b48 = (int *)0x451671;
    iVar4 = PeekPacketChecksumState();
    piStack_b48 = (int *)(puStack_b14 + iVar4);
    puStack_b4c = (undefined *)0x45167d;
    EncodeOutgoingPacketField();
    piStack_b48 = (int *)&DAT_005a9068;
    puStack_b4c = (undefined *)0x451684;
    (*pcVar16)();
    puStack_b4c = &DAT_005a9068;
    puStack_b50 = (undefined *)0x451691;
    (*pcVar17)();
    puStack_b50 = (undefined *)0x451698;
    iVar4 = PeekPacketChecksumState();
    puStack_b50 = (undefined *)(iVar4 + (int)puStack_b2c);
    puStack_b54 = (undefined4 *)0x4516a4;
    EncodeOutgoingPacketField();
    puStack_b50 = &DAT_005a9068;
    puStack_b54 = (undefined4 *)0x4516ab;
    (*pcVar16)();
  }
  puStack_b44 = (undefined4 *)&DAT_005a9068;
  piStack_b48 = (int *)0x4516b5;
  (*pcVar17)();
  piStack_b48 = (int *)0x4516bc;
  puStack_b28 = (undefined *)PeekPacketChecksumState();
  piStack_b48 = (int *)0x4516cb;
  iVar4 = PeekPacketChecksumState();
  piStack_b48 = (int *)(iVar4 + (int)puStack_b28);
  puStack_b4c = (undefined *)0x4516d7;
  EncodeOutgoingPacketField();
  piStack_b48 = (int *)&DAT_005a9068;
  puStack_b4c = (undefined *)0x4516de;
  (*pcVar16)();
  puStack_b4c = &DAT_005a9068;
  puStack_b50 = (undefined *)0x4516eb;
  (*pcVar17)();
  puStack_b50 = (undefined *)0x4516f2;
  puStack_b30 = (undefined4 *)PeekPacketChecksumState();
  puStack_b50 = (undefined *)0x451701;
  iVar4 = PeekPacketChecksumState();
  puStack_b50 = (undefined *)(iVar4 + (int)puStack_b30);
  puStack_b54 = (undefined4 *)0x45170d;
  EncodeOutgoingPacketField();
  puStack_b50 = &DAT_005a9068;
  puStack_b54 = (undefined4 *)0x451714;
  (*pcVar16)();
  puStack_b54 = (undefined4 *)0x8;
  uStack_b58 = (int *)0x45171d;
  (**(code **)(*param_1 + 0x14))();
  uStack_b58 = (int *)0x451728;
  cVar2 = FUN_004065a0();
  if (cVar2 == '\0') {
    uStack_b58 = (int *)0x8;
    uStack_b5c = &puStack_b14;
    uStack_b60 = (undefined **)(param_1 + 0x10);
    ppuStack_b64 = (undefined **)0x45256c;
    FUN_0040b180();
    uStack_b58 = (int *)&DAT_005a9068;
    uStack_58 = 8;
    uStack_b5c = (undefined **)0x452580;
    (*pcVar17)();
    uStack_b5c = (undefined **)0x452587;
    uStack_b5c = (undefined **)PeekPacketChecksumState();
    uStack_b60 = (undefined **)0x452593;
    EncodeOutgoingPacketField();
    uStack_b5c = (undefined **)&DAT_005a9068;
    uStack_b60 = (undefined **)0x45259a;
    (*pcVar16)();
    puVar26 = puStack_b08;
    uStack_60 = 0xffffffff;
    if (puStack_b08 != (undefined *)0x0) {
      uStack_b60 = (undefined **)0x4525b9;
      FUN_0040a240();
      uStack_b60 = &puStack_b34;
      piStack_b48 = (int *)puVar26;
      ppuStack_b64 = (undefined **)0x4525d0;
      FUN_0040b540();
      pcVar16 = (code *)LeaveCriticalSection;
    }
    uStack_b60 = (undefined **)0x8;
    ppuStack_b64 = &puStack_b1c;
    uStack_b68 = (int **)(param_1 + 0x99);
    uStack_b6c = (undefined *)0x4525e9;
    FUN_0040b180();
    piStack_b3c = param_1 + 0x45e;
    uStack_b60 = (undefined **)&DAT_005a9068;
    uStack_60 = 9;
    ppuStack_b64 = (undefined **)0x452607;
    (*pcVar17)();
    ppuStack_b64 = (undefined **)0x45260e;
    ppuStack_b64 = (undefined **)PeekPacketChecksumState();
    uStack_b68 = (int **)0x452618;
    EncodeOutgoingPacketField();
    ppuStack_b64 = (undefined **)&DAT_005a9068;
    uStack_b68 = (int **)0x45261f;
    (*pcVar16)();
    puVar26 = puStack_b10;
    uStack_68 = 0xffffffff;
    uVar8 = extraout_EDX;
    if (puStack_b10 != (undefined *)0x0) {
      uStack_b68 = (int **)0x45263e;
      FUN_0040a240();
      uStack_b68 = &piStack_b3c;
      puStack_b50 = puVar26;
      uStack_b6c = (undefined *)0x452655;
      FUN_0040b540();
      uVar8 = extraout_EDX_00;
      pcVar16 = (code *)LeaveCriticalSection;
    }
    uStack_b68 = (int **)CONCAT31((int3)((uint)uVar8 >> 8),param_1[0x3d2] != 0);
    uStack_b6c = (undefined *)0x452672;
    cVar2 = FUN_00406610();
    if (cVar2 == '\0') {
      uStack_b68 = (int **)(param_1 + 0x2bd);
      uStack_b6c = (undefined *)0x4528b9;
      FUN_0040afb0();
      uStack_b68 = (int **)(param_1 + 0x346);
      uStack_b6c = (undefined *)0x4528cd;
      FUN_0040afb0();
      uStack_b68 = (int **)&DAT_005a9068;
      uStack_b6c = (undefined *)0x4528d4;
      (*pcVar17)();
      uStack_b6c = (undefined *)0x4528db;
      iVar4 = PeekPacketChecksumState();
      uStack_b6c = &DAT_005a9068;
      uStack_b58 = (int *)CONCAT13(0 < iVar4,(undefined3)uStack_b58);
      (*pcVar16)();
      if (uStack_b5c._3_1_ != '\0') {
        param_1[0xfe9] = 0;
      }
    }
    else {
      uStack_b68 = (int **)&DAT_005a9068;
      uStack_b6c = (undefined *)0x452681;
      (*pcVar17)();
      uStack_b6c = (undefined *)0x45268e;
      puStack_b54 = (undefined4 *)PeekPacketChecksumState();
      uStack_b6c = &DAT_005a9068;
      (*pcVar16)();
      if ((int)(((uint)uStack_b58 ^ (int)uStack_b58 >> 0x1f) - ((int)uStack_b58 >> 0x1f)) < 200) {
        cVar2 = FUN_0040b330(param_1 + 0x122,0);
        if (cVar2 == '\0') {
          uVar8 = 200;
        }
        else {
          uVar8 = 0xffffff38;
        }
        QueueOutgoingPacketField(uVar8);
      }
      uVar8 = FUN_0040a8c0(param_1[0x3d2] + 0x25c,auStack_4c0,4);
      uStack_70 = 10;
      puStack_b54 = (undefined4 *)0x1;
      uVar8 = FUN_0040aca0(param_1[0x3d2] + 0x38,auStack_6e4,uVar8);
      uStack_70 = 0xb;
      puStack_b54 = (undefined4 *)0x3;
      cVar2 = FUN_0040b490(param_1 + 0x3d5,uVar8);
      if (cVar2 == '\0') {
        uVar8 = FUN_0040a8c0(param_1[0x3d2] + 0x25c,auStack_908,4);
        uStack_70 = 0xc;
        puStack_b54 = (undefined4 *)0x7;
        uVar8 = FUN_0040aba0(param_1[0x3d2] + 0x38,&puStack_b2c,uVar8);
        uStack_70 = 0xd;
        puStack_b54 = (undefined4 *)0xf;
        cVar2 = FUN_0040b490(uVar8,param_1 + 0x3d5);
        uStack_b5c = (undefined **)((uint)uStack_b5c & 0xffffff);
        if (cVar2 != '\0') goto LAB_0045279a;
      }
      else {
LAB_0045279a:
        uStack_b5c = (undefined **)CONCAT13(1,(undefined3)uStack_b5c);
      }
      uStack_70 = 0xc;
      if (((uint)puStack_b54 & 8) != 0) {
        puStack_b54 = (undefined4 *)((uint)puStack_b54 & 0xfffffff7);
        FUN_0040a2a0();
      }
      uStack_70 = 0xb;
      if (((uint)puStack_b54 & 4) != 0) {
        puStack_b54 = (undefined4 *)((uint)puStack_b54 & 0xfffffffb);
        FUN_0040a2a0();
      }
      uStack_70 = 10;
      if (((uint)puStack_b54 & 2) != 0) {
        puStack_b54 = (undefined4 *)((uint)puStack_b54 & 0xfffffffd);
        FUN_0040a2a0();
      }
      uStack_70 = 0xffffffff;
      if (((uint)puStack_b54 & 1) != 0) {
        FUN_0040a2a0();
      }
      if (uStack_b5c._3_1_ != '\0') {
        iVar4 = param_1[0x3d4];
        param_1[0x3d4] = iVar4 + 1;
        if (iVar4 + 1 < 3) {
          uVar8 = FUN_0040a500(param_1 + 0x122,auStack_29c);
          uStack_70 = 0xe;
          EncodeChecksumState(uVar8);
          uStack_70 = 0xffffffff;
          FUN_0040a2a0();
        }
        else {
          FUN_00406500(0);
        }
      }
    }
    cVar2 = FUN_004065a0();
    if (cVar2 != '\0') {
      uStack_b58 = (int *)param_1[0xfe9];
      (*pcVar17)(&DAT_005a9068);
      iVar4 = PeekPacketChecksumState();
      EncodeOutgoingPacketField((undefined *)((int)uStack_b5c + iVar4));
      (*pcVar16)(&DAT_005a9068);
      if (((param_1[0xfe9] == 1) && (cVar2 = FUN_0040b300(param_1 + 0x70b,0x5a), cVar2 != '\0')) ||
         ((param_1[0xfe9] == -1 && (cVar2 = FUN_0040b360(param_1 + 0x70b,0x5a), cVar2 != '\0')))) {
        param_1[0xfe9] = 0;
        QueueOutgoingPacketField(0);
      }
    }
    (*pcVar17)(&DAT_005a9068);
    piStack_b48 = param_1 + 0x3d5;
    iVar4 = PeekPacketChecksumState();
    uStack_b60 = (undefined **)CONCAT13(iVar4 < 0,(undefined3)uStack_b60);
    (*pcVar16)(&DAT_005a9068);
    if (cVar28 == '\0') {
      (*pcVar17)(&DAT_005a9068);
      PeekPacketChecksumState();
      (*pcVar16)(&DAT_005a9068);
      if (((cVar28 != '\0') ||
          (cVar2 = FUN_0040b300(in_stack_fffff450,*(undefined4 *)(&DAT_006a7724 + g_clientContext)),
          cVar2 != '\0')) || (cVar2 = FUN_0040b330(in_stack_fffff450,0xfffffc18), cVar2 != '\0'))
      goto LAB_00452a0a;
    }
    else {
LAB_00452a0a:
      *(undefined1 *)(param_1 + 5) = 1;
      cVar2 = FUN_004065a0();
      if ((cVar2 != '\0') && (cVar2 = FUN_0043a530(), cVar2 == '\0')) {
        iVar4 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
        if ((iVar4 == 5) || (uVar8 = 2, iVar4 == 6)) {
          uVar8 = 0x19;
        }
        QueueOutgoingPacketField(uVar8);
      }
    }
    cVar2 = FUN_00406710();
    if (cVar2 != '\0') {
      (*pcVar17)(&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      (*pcVar16)(&DAT_005a9068);
      (*pcVar17)(&DAT_005a9068);
      iVar11 = PeekPacketChecksumState();
      (*pcVar16)(&DAT_005a9068);
      iVar4 = g_clientContext;
      piVar18 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar2 = FUN_004065a0();
      if ((cVar2 == '\0') && ((&DAT_006a7758)[iVar4] != '\0')) {
        if (((&DAT_006a7736)[iVar4] == '\x01') &&
           ((uVar15 = iVar5 - *(int *)(&DAT_006a7714 + iVar4) >> 0x1f,
            200 < (int)((iVar5 - *(int *)(&DAT_006a7714 + iVar4) ^ uVar15) - uVar15) ||
            (uVar15 = iVar11 - *(int *)(&DAT_006a7710 + iVar4) >> 0x1f,
            300 < (int)((iVar11 - *(int *)(&DAT_006a7710 + iVar4) ^ uVar15) - uVar15))))) {
          (&DAT_006a7736)[iVar4] = 0;
        }
        iVar13 = 400;
        if (399 < iVar11) {
          iVar13 = iVar11;
        }
        iVar12 = *(int *)(&DAT_006a7720 + iVar4) + -400;
        if ((iVar13 <= iVar12) && (iVar12 = iVar11, iVar11 < 400)) {
          iVar12 = 400;
        }
        iVar11 = -0x14;
        if (-0x15 < iVar5) {
          iVar11 = iVar5;
        }
        iVar13 = *(int *)(&DAT_006a7724 + iVar4) + -0x104;
        if ((iVar11 <= iVar13) && (iVar13 = -0x14, -0x15 < iVar5)) {
          iVar13 = iVar5;
        }
        iVar5 = *piVar18 - iVar12;
        *(int *)(&DAT_006a771c + iVar4) = iVar13;
        if (((*(int *)(&DAT_006a770c + iVar4) - iVar13) * (*(int *)(&DAT_006a770c + iVar4) - iVar13)
             + iVar5 * iVar5 < 40000) &&
           (((&DAT_006a7734)[iVar4] == '\x01' || ((&DAT_006a7f6c)[iVar4] == '\0')))) {
          *(int *)(&DAT_006a7710 + iVar4) = iVar12;
          *piVar18 = iVar12;
          *(int *)(&DAT_006a7714 + iVar4) = iVar13;
          *(int *)(&DAT_006a770c + iVar4) = iVar13;
        }
        if ((((&DAT_006a7734)[iVar4] == '\0') && ((&DAT_006a7f6c)[iVar4] == '\x01')) &&
           ((&DAT_006a7736)[iVar4] == '\0')) {
          iVar5 = *(int *)(&DAT_006a7730 + iVar4);
          iVar11 = iVar5;
          if (iVar12 <= iVar5) {
            iVar11 = iVar12;
          }
          iVar14 = *(int *)(&DAT_006a772c + iVar4);
          if ((iVar14 <= iVar11) && (iVar14 = iVar5, iVar12 <= iVar5)) {
            iVar14 = iVar12;
          }
          *(int *)(&DAT_006a7718 + iVar4) = iVar14;
        }
        if ((&DAT_006a7734)[iVar4] == '\x01') {
          *(int *)(&DAT_006a7718 + iVar4) = iVar12;
          *(int *)(&DAT_006a771c + iVar4) = iVar13;
        }
      }
    }
    goto LAB_00452bc8;
  }
  uStack_b5c = (undefined **)param_1[2];
  uStack_b58 = param_1 + 0x45e;
  uStack_b60 = (undefined **)0x45174e;
  FUN_004262d0();
  uStack_b58 = (int *)0x451759;
  cVar2 = FUN_004065a0();
  if (cVar2 != '\0') {
    uStack_b58 = (int *)&DAT_005a9068;
    uStack_b5c = (undefined **)0x451768;
    (*pcVar17)();
    uStack_b5c = (undefined **)0x45176f;
    iVar4 = PeekPacketChecksumState();
    uStack_b5c = (undefined **)&DAT_005a9068;
    uStack_b60 = (undefined **)0x451778;
    (*pcVar16)();
    if ((-1 < iVar4) &&
       (puStack_b40 = *(undefined **)(&DAT_006a7720 + g_clientContext), iVar4 < (int)puStack_b40)) {
      pcVar6 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar4);
      puStack_b44 = (undefined4 *)0x0;
      if (0 < *(int *)(&DAT_006a7724 + g_clientContext)) {
        do {
          if (*pcVar6 != '\0') goto LAB_004517be;
          pcVar6 = pcVar6 + (int)puStack_b40;
          puStack_b44 = (undefined4 *)((int)puStack_b44 + 1);
        } while ((int)puStack_b44 < *(int *)(&DAT_006a7724 + g_clientContext));
      }
    }
    puStack_b44 = (undefined4 *)0x2710;
LAB_004517be:
    uStack_b60 = (undefined **)&DAT_005a9068;
    ppuStack_b64 = (undefined **)0x4517c5;
    (*pcVar17)();
    ppuStack_b64 = (undefined **)0x4517d2;
    puStack_b44 = (undefined4 *)PeekPacketChecksumState();
    ppuStack_b64 = (undefined **)&DAT_005a9068;
    uStack_b68 = (int **)0x4517dd;
    (*pcVar16)();
    uStack_b68 = (int **)puStack_b4c;
    uStack_b6c = (undefined *)piStack_b48;
    FUN_00436070(&DAT_006a7f70 + g_clientContext);
    puStack_b44 = (undefined4 *)0x1;
    if (0 < param_1[0xfe5]) {
      puStack_b44 = (undefined4 *)param_1[0xfe5];
    }
    uStack_b68 = (int **)&DAT_005a9068;
    uStack_b6c = (undefined *)0x451817;
    (*pcVar17)();
    uStack_b6c = (undefined *)0x451821;
    puStack_b4c = (undefined *)PeekPacketChecksumState();
    uStack_b6c = &DAT_005a9068;
    (*pcVar16)();
    (*pcVar17)(&DAT_005a9068);
    puStack_b4c = (undefined *)PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    (*pcVar17)(&DAT_005a9068);
    puStack_b44 = (undefined4 *)PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    (*pcVar17)(&DAT_005a9068);
    piStack_b48 = (int *)PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    FUN_0043af40(puStack_b4c,uStack_b6c,0,puStack_b50,(int)uStack_b60 / (int)ppuStack_b64,uStack_b68
                 ,(char)param_1[0xf]);
    (*pcVar17)(&DAT_005a9068);
    uStack_b6c = (undefined *)PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    (*pcVar17)(&DAT_005a9068);
    uStack_b6c = (undefined *)PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    uStack_b58 = (int *)0x0;
    uStack_b5c = (undefined **)0x2;
    uStack_b60 = (undefined **)0xff;
    ppuStack_b64 = ppuStack_b38;
    uStack_b68 = (int **)0x0;
    uStack_b6c = (undefined *)0x4518f9;
    FUN_004065a0();
    uStack_b6c = (undefined *)0x0;
    FUN_00431d90((char)param_1[0xf],7);
  }
  uStack_b58 = (int *)&DAT_005a9068;
  uStack_b5c = (undefined **)0x451917;
  (*pcVar17)();
  uStack_b5c = (undefined **)0x451922;
  ppuStack_b38 = (undefined **)PeekPacketChecksumState();
  uStack_b5c = (undefined **)&DAT_005a9068;
  uStack_b60 = (undefined **)0x45192d;
  (*pcVar16)();
  uStack_b60 = (undefined **)&DAT_005a9068;
  ppuStack_b64 = (undefined **)0x451934;
  (*pcVar17)();
  ppuStack_b64 = (undefined **)0x45193b;
  puVar7 = (undefined4 *)PeekPacketChecksumState();
  ppuStack_b64 = (undefined **)&DAT_005a9068;
  uStack_b68 = (int **)0x451948;
  puStack_b44 = puVar7;
  (*pcVar16)();
  puStack_b28 = (undefined *)param_1[2];
  puStack_b30 = puStack_b44;
  puStack_b50 = &DAT_006a7f70 + g_clientContext;
  uStack_b68 = (int **)&DAT_005a9068;
  uStack_b6c = (undefined *)0x451977;
  puStack_b2c = puVar7;
  (*pcVar17)();
  uStack_b6c = (undefined *)0x45197e;
  iVar4 = PeekPacketChecksumState();
  uStack_b6c = &DAT_005a9068;
  uStack_b58 = (int *)CONCAT13(iVar4 != 4,(undefined3)uStack_b58);
  (*pcVar16)();
  if (uStack_b5c._3_1_ == '\0') {
    puVar7 = operator_new(0x3fbc);
    uStack_70 = 0;
    puStack_b44 = puVar7;
    if (puVar7 == (undefined4 *)0x0) {
      puStack_b54 = (undefined4 *)0x0;
    }
    else {
      FUN_00454dc0(puVar7,0x186a9);
      *puVar7 = &PTR_FUN_0055658c;
      puVar7[0xfe7] = 0xffffffff;
      puStack_b54 = puVar7;
    }
    uStack_70 = 0xffffffff;
    iVar4 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar15 = *(uint *)(iVar4 + 4);
    while (uVar15 < 0x186ab) {
      if (uVar15 == 0x186aa) {
        piVar18 = *(int **)(iVar4 + 0x10);
        bVar20 = true;
        piStack_b3c = piVar18;
        if (piVar18[2] == 0) goto LAB_00451a3a;
        break;
      }
      iVar4 = *(int *)(iVar4 + 0x1c);
      uVar15 = *(uint *)(iVar4 + 4);
    }
  }
  goto LAB_00451da3;
  while( true ) {
    piVar18 = (int *)piVar18[4];
    bVar20 = piVar18[2] == 0;
    piStack_b3c = piVar18;
    if (!bVar20) break;
LAB_00451a3a:
    if (bVar20) {
      puStack_b44 = (undefined4 *)piVar18[0xf];
      piStack_b48 = (int *)piVar18[0xe];
      piStack_b3c = piVar18;
      puStack_b4c = (undefined *)FUN_004f1f10();
      iVar4 = FUN_0053753c();
      piStack_b48 = (int *)((int)piStack_b48 - iVar4);
      iVar4 = FUN_0053753c();
      puStack_b50 = (undefined *)((int)puStack_b44 - iVar4);
      (**(code **)(*piVar18 + 4))(&DAT_00553b90);
      piVar18[0x11] = (int)puStack_b4c;
      puStack_b44 = (undefined4 *)((int)uStack_b58 + 4);
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
        uStack_6e8 = 0;
        uStack_8f4 = 0;
        EncodeOutgoingPacketField(0);
        uStack_70 = 3;
        puStack_b18 = (undefined *)0x0;
        EncodeOutgoingPacketField(0);
        uStack_70 = 4;
        FUN_004262d0(puStack_b30 + 4,&puStack_b2c);
        (*pcVar17)(&DAT_005a9068);
        PeekPacketChecksumState();
        (*pcVar16)(&DAT_005a9068);
        (*pcVar17)(&DAT_005a9068);
        ppuStack_b64 = (undefined **)PeekPacketChecksumState();
        (*pcVar16)(&DAT_005a9068);
        iVar4 = param_1[0xfe5];
        uVar27 = 0;
        uVar10 = 0xff;
        uVar9 = 100;
        uVar8 = 0;
        iVar5 = (int)uStack_b58;
        FUN_004065a0(uStack_b58,0,100,0xff,iVar4,0);
        FUN_00432320((char)param_1[0xf],1,1,iVar5,uVar8,uVar9,uVar10,iVar4,uVar27);
        uStack_70 = 3;
        FUN_0040a2a0();
LAB_00451d02:
        uStack_70 = 0xffffffff;
        FUN_0040a2a0();
      }
      else {
        cVar2 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext,&puStack_b34,&ppuStack_b38,2,1,1);
        if (cVar2 != '\0') {
          puStack_b18 = (undefined *)0x0;
          EncodeOutgoingPacketField(0);
          uStack_70 = 1;
          uStack_6e8 = 0;
          uStack_8f4 = 0;
          EncodeOutgoingPacketField(0);
          uStack_70 = 2;
          QueueOutgoingPacketField(puStack_b34);
          QueueOutgoingPacketField(ppuStack_b38);
          FUN_004262d0(puStack_b30 + 4,auStack_908);
          iVar4 = param_1[0xfe5];
          uVar29 = 0;
          uVar27 = 0xff;
          uVar10 = 100;
          uVar9 = 0;
          FUN_0040a4d0(auStack_908);
          uVar8 = FUN_0040a4d0(&puStack_b2c);
          FUN_004065a0(uVar8,uVar9,uVar10,uVar27,iVar4,uVar29);
          FUN_00432320((char)param_1[0xf],1,1,uVar8,uVar9,uVar10,uVar27,iVar4,uVar29);
          uStack_70 = 1;
          FUN_0040a2a0();
          goto LAB_00451d02;
        }
      }
      puStack_b54[0xfea] = piStack_b48;
      puStack_b54[0xfeb] = puStack_b50;
      puStack_b54[0xfec] = puStack_b34;
      puStack_b54[0xfed] = ppuStack_b38;
      puStack_b54[0xfee] = puStack_b4c;
      uVar8 = FUN_004ac4d0();
      puStack_b54[0xfe9] = uVar8;
      iVar4 = FUN_004ac400();
      puStack_b54[0xfe8] = iVar4 * param_1[0xfe5];
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
        RegisterActiveObject();
      }
      else {
        (**(code **)*puStack_b54)(1);
      }
      break;
    }
  }
LAB_00451da3:
  (*pcVar17)(&DAT_005a9068);
  uStack_b5c = (undefined **)PeekPacketChecksumState();
  iVar4 = PeekPacketChecksumState();
  cVar28 = '\0';
  uStack_b5c = (undefined **)CONCAT31(uStack_b5c._1_3_,(int)uStack_b5c < iVar4);
  (*pcVar16)();
  cVar2 = FUN_00406610(uStack_b60);
  if (cVar2 != '\0') {
    uStack_b60 = (undefined **)(g_clientContext + 0x5b85c);
    (*pcVar17)(&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar8);
    (*pcVar16)(&DAT_005a9068);
  }
  (*pcVar17)(&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  uStack_b68 = (int **)CONCAT13(iVar4 < 0,(undefined3)uStack_b68);
  (*pcVar16)(&DAT_005a9068);
  if (uStack_b6c._3_1_ == '\0') {
LAB_00451e73:
    (*pcVar17)(&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    if (uStack_b6c._3_1_ != '\0') {
      (*pcVar17)(&DAT_005a9068);
      PeekPacketChecksumState();
      (*pcVar16)(&DAT_005a9068);
      if (uStack_b6c._3_1_ != '\0') goto LAB_00451ebf;
    }
  }
  else {
    (*pcVar17)(&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    if (uStack_b6c._3_1_ == '\0') goto LAB_00451e73;
LAB_00451ebf:
    cVar2 = FUN_004065a0();
    if (cVar2 == '\0') {
      FUN_00406500(1);
    }
  }
  (*pcVar17)(&DAT_005a9068);
  uStack_b6c = (undefined *)PeekPacketChecksumState();
  PeekPacketChecksumState();
  puVar26 = &DAT_005a9068;
  (*pcVar16)(&DAT_005a9068);
  if ((cVar28 == '\0') || (cVar2 = FUN_0040b490(param_1 + 0xed2,param_1 + 0xf5b), cVar2 == '\0')) {
    (*pcVar17)(&DAT_005a9068);
    PeekPacketChecksumState();
    cVar2 = extraout_var;
    PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    if ((cVar2 != '\0') &&
       ((cVar2 = FUN_0040b410(param_1 + 0xed2,param_1 + 0xf5b), cVar2 != '\0' &&
        (5 < param_1[0xed1])))) goto LAB_00451f7a;
  }
  else {
LAB_00451f7a:
    iVar4 = g_clientContext;
    pbVar19 = (byte *)(g_clientContext + 0x62143);
    (*pcVar17)(&DAT_005a9068);
    iVar5 = _rand();
    *pbVar19 = (byte)iVar5;
    iVar5 = _rand();
    bVar1 = *pbVar19;
    *(byte *)(iVar4 + 0x62144) = (byte)iVar5;
    bVar3 = '\x01' << (bVar1 & 7);
    bVar1 = *pbVar19;
    bVar3 = ~bVar3 & (byte)iVar5 | bVar3;
    *(byte *)(iVar4 + 0x62144) = bVar3;
    *(byte *)(iVar4 + 0x62145) = bVar3 + bVar1 + -0x34;
    (*pcVar16)(&DAT_005a9068);
  }
  cVar2 = FUN_004065a0();
  if ((cVar2 == '\x01') ||
     (cVar2 = FUN_004065a0(), pcVar16 = (code *)LeaveCriticalSection, cVar2 == '\x01')) {
    FUN_0040a8c0(param_1 + 0x795,&puStack_b44,10);
    uStack_88 = 5;
    (*pcVar17)(&DAT_005a9068);
    uStack_b60 = (undefined **)PeekPacketChecksumState();
    iVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField((undefined *)((int)uStack_b60 + iVar4));
    (*pcVar16)(&DAT_005a9068);
    uStack_90 = 0xffffffff;
    if (ppuStack_b38 != (undefined **)0x0) {
      FUN_0040a240();
      FUN_0040b540(&ppuStack_b64);
      pcVar16 = (code *)LeaveCriticalSection;
    }
    FUN_0040a8c0(param_1 + 0x81e,&puStack_b4c,10);
    uStack_90 = 6;
    (*pcVar17)(&DAT_005a9068);
    uStack_b68 = (int **)PeekPacketChecksumState();
    iVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar4 + (int)uStack_b68);
    (*pcVar16)(&DAT_005a9068);
    uStack_98 = 0xffffffff;
    if (puStack_b40 != (undefined *)0x0) {
      FUN_0040a240();
      FUN_0040b540(&uStack_b6c);
      pcVar16 = (code *)LeaveCriticalSection;
    }
    FUN_0040a8c0(param_1 + 0x8a7,&puStack_b54,10);
    uStack_98 = 7;
    (*pcVar17)(&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    iVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar5 + iVar4);
    (*pcVar16)(&DAT_005a9068);
    uStack_88 = 0xffffffff;
    if (puStack_b30 != (undefined4 *)0x0) {
      FUN_0040a240();
      FUN_0040b540(&uStack_b5c);
    }
  }
  puVar25 = &DAT_005a9068;
  *(undefined1 *)(param_1 + 5) = 1;
  (*pcVar17)(&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puVar24 = &DAT_005a9068;
  (*pcVar17)(&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puVar23 = &DAT_005a9068;
  (*pcVar17)(&DAT_005a9068);
  uStack_b68 = (int **)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar17)(&DAT_005a9068);
  uVar9 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puVar22 = &DAT_005a9068;
  (*pcVar17)(&DAT_005a9068);
  uVar10 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar17)(&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puVar21 = &DAT_005a9068;
  (*pcVar17)(&DAT_005a9068);
  uStack_b6c = (undefined *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar17)(&DAT_005a9068);
  uStack_b6c = (undefined *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar17)(&DAT_005a9068);
  uStack_b6c = (undefined *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar17)(&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004e4970(uVar10,uVar9,puVar24,puVar25,puVar23,puVar26,puVar22,uVar8);
  FUN_004e4d00(&DAT_006a7708 + g_clientContext);
  puVar22 = &DAT_005a9068;
  (*pcVar17)(&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar17)(&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00450eb0(uVar8,puVar21,param_1,1,0,0);
  (*pcVar17)(&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puVar26 = &DAT_005a9068;
  (*pcVar17)(&DAT_005a9068);
  uVar9 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00436ac0(uVar9,uVar8);
  (*pcVar17)(&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar17)(&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004372f0(param_1[2],uVar8,puVar22,param_1[0xe25],param_1 + 0xe26);
  (*pcVar17)(&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar17)(&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar17)(&DAT_005a9068);
  uVar9 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00437150(uVar9,uVar8,0x3c,puVar26);
  iVar4 = g_clientContext;
  cVar2 = FUN_004065a0();
  if (cVar2 != '\x01') {
    iVar5 = *(int *)(&DAT_006a7750 + iVar4);
    if (iVar5 < 0x10) {
      iVar5 = 0xf;
    }
    *(int *)(&DAT_006a7750 + iVar4) = iVar5;
    iVar5 = *(int *)(&DAT_006a7754 + iVar4);
    if (iVar5 < 0xb) {
      iVar5 = 10;
    }
    *(int *)(&DAT_006a7754 + iVar4) = iVar5;
  }
  cVar2 = FUN_004065a0();
  if (cVar2 == '\0') {
    FUN_004ee9b0(0);
  }
  cVar2 = FUN_004065a0();
  if ((cVar2 != '\0') && (cVar2 = FUN_0043a530(), cVar2 == '\0')) {
    (*pcVar17)(&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    QueueOutgoingPacketField(uVar8);
  }
LAB_00452bc8:
  *unaff_FS_OFFSET = uStack_dc;
  return;
}

