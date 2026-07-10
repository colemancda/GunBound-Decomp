/* FUN_0049c120 - 0x0049c120 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall FUN_0049c120(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  char cVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 extraout_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined *puVar11;
  undefined4 uStack_24d8;
  int iStack_24d4;
  undefined1 *puStack_24d0;
  undefined *puStack_24cc;
  uint uStack_24c8;
  uint uStack_24c4;
  undefined4 uStack_24c0;
  undefined4 uStack_24bc;
  undefined4 uStack_24b8;
  undefined4 uStack_24b4;
  uint uStack_24b0;
  int iStack_24ac;
  int iStack_24a8;
  undefined4 uStack_24a4;
  int iStack_24a0;
  undefined1 *puStack_249c;
  undefined *puStack_2498;
  undefined4 uStack_2484;
  undefined4 uStack_2480;
  undefined1 auStack_224c [496];
  undefined1 auStack_205c [548];
  undefined1 auStack_1e38 [548];
  undefined1 auStack_1c14 [496];
  undefined1 auStack_1a24 [600];
  undefined1 auStack_17cc [600];
  undefined1 auStack_1574 [548];
  undefined1 auStack_1350 [548];
  undefined1 auStack_112c [548];
  undefined1 auStack_f08 [548];
  undefined1 auStack_ce4 [548];
  undefined1 auStack_ac0 [496];
  undefined1 auStack_8d0 [600];
  undefined1 auStack_678 [548];
  undefined1 auStack_454 [548];
  undefined1 auStack_230 [452];
  undefined4 uStack_6c;
  uint uStack_38;
  code *pcStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053ef1b;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  pcStack_10 = (code *)FUN_0049c13f; /* cast: __fastcall vs code()'s default cc */
  puStack_2498 = (undefined *)0x49c14c;
  uVar4 = FUN_0045f840();
  switch(param_2) {
  case 1:
    if (*(int *)(param_1 + 0xb0a4) == -1) {
      puStack_2498 = (undefined *)0x1;
      puStack_249c = (undefined1 *)0x49c180;
      uVar4 = FUN_004ee9b0();
      *(undefined4 *)(param_1 + 0xb0a4) = uVar4;
    }
    break;
  default:
    iVar2 = *(int *)(param_1 + 0xb0a4);
    if (DAT_00793549 != '\0') {
      if (iVar2 != -1) {
        puStack_2498 = (undefined *)0x49cbdb;
        (**(code **)(**(int **)(DAT_00793554 + iVar2 * 4) + 0xc))();
      }
      if (iVar2 == 0) {
        DAT_00793568 = 0;
      }
    }
    *(undefined4 *)(param_1 + 0xb0a4) = 0xffffffff;
    break;
  case 4:
    if (*(int *)(param_1 + 0xb0a4) == -1) {
      puStack_2498 = (undefined *)0x1;
      puStack_249c = (undefined1 *)0x49c1a8;
      uVar4 = FUN_004ee9b0();
      *(undefined4 *)(param_1 + 0xb0a4) = uVar4;
    }
    break;
  case 5:
    if (param_3 != 0xb) break;
    puStack_2498 = (undefined *)0xffffffff;
    puStack_249c = (undefined1 *)0x49c1d5;
    QueueOutgoingPacketField();
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puStack_2498 = &DAT_00796aa0;
    }
    else {
      puStack_2498 = &DAT_00794e48;
    }
    puStack_249c = (undefined1 *)0x49c1ef;
    uVar7 = FUN_0040a4d0();
    puStack_2498 = (undefined *)0x49c1fe;
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 == '\x01') {
LAB_0049c219:
      uStack_2484 = 0;
    }
    else {
      puStack_2498 = (undefined *)0x49c20d;
      cVar3 = PeekPacketChecksumBool();
      uStack_2484 = 8;
      if (cVar3 == '\x01') goto LAB_0049c219;
    }
    iVar2 = param_1 + 0x5620;
    puStack_249c = auStack_112c;
    iVar1 = param_1 + 0xb30;
    uStack_24a4 = 0x49c23c;
    iStack_24a0 = iVar1;
    puStack_2498 = (undefined *)iVar2;
    uVar8 = FUN_0040aca0();
    puStack_2498 = (undefined *)(param_1 + 0x53fc);
    puStack_249c = auStack_ce4;
    iStack_24a0 = param_1 + 0x90c;
    uStack_4 = 0;
    uStack_24a4 = 0x49c266;
    uVar9 = FUN_0040aba0();
    puStack_2498 = (undefined *)0x3;
    uStack_4 = CONCAT31(SUBFIELD(uStack_4,1,undefined3),1);
    iStack_24a0 = 0x49c284;
    puStack_249c = (undefined1 *)uVar7;
    iStack_24a0 = PeekPacketChecksumBool();
    iStack_24a8 = 0x49c291;
    uStack_24a4 = uVar4;
    PeekPacketChecksumBool();
    iStack_24a8 = param_1 + 0x7864;
    iStack_24ac = 0x49c29d;
    iStack_24a8 = FUN_0040a4d0();
    iStack_24ac = param_1 + 0x4d90;
    uStack_24b0 = 0x49c2aa;
    iStack_24ac = FUN_0040a4d0();
    uStack_24b4 = 0x49c2b5;
    uStack_24b0 = uVar8;
    uStack_24b0 = FUN_0040a4d0();
    uStack_24b8 = 0x49c2c0;
    uStack_24b4 = uVar9;
    uStack_24b4 = FUN_0040a4d0();
    uStack_24b8 = CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                           *(int *)(param_1 + 0xae2c) != 0);
    uStack_24c8 = (uint)*(byte *)(param_1 + 8);
    uStack_24bc = 0;
    uStack_24c0 = 6;
    uStack_24c4 = uStack_2484;
    puStack_24cc = (undefined *)0x49c2e1;
    FUN_0042bbb0();
    uStack_38 = uStack_38 & 0xffffff00;
    puStack_24cc = (undefined *)0x49c2f5;
    FUN_0040a2a0();
    uStack_38 = 0xffffffff;
    puStack_24cc = (undefined *)0x49c30c;
    FUN_0040a2a0();
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puStack_24cc = &DAT_00796aa0;
    }
    else {
      puStack_24cc = &DAT_00794e48;
    }
    puStack_24d0 = (undefined1 *)0x49c326;
    uStack_24b8 = FUN_0040a4d0();
    puStack_24cc = (undefined *)0x49c335;
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 == '\x01') {
LAB_0049c350:
      uStack_24b4 = 2;
    }
    else {
      puStack_24cc = (undefined *)0x49c344;
      cVar3 = PeekPacketChecksumBool();
      uStack_24b4 = 10;
      if (cVar3 == '\x01') goto LAB_0049c350;
    }
    puStack_24d0 = auStack_8d0;
    uStack_24d8 = 0x49c367;
    iStack_24d4 = iVar1;
    puStack_24cc = (undefined *)iVar2;
    iStack_24ac = FUN_0040aca0();
    puStack_24cc = (undefined *)(param_1 + 0x53fc);
    puStack_24d0 = auStack_1e38;
    iStack_24d4 = param_1 + 0x90c;
    uStack_38 = 2;
    uStack_24d8 = 0x49c391;
    uStack_24b0 = FUN_0040aba0();
    puStack_24cc = (undefined *)0x3;
    puStack_24d0 = (undefined1 *)uStack_24b8;
    uStack_38 = CONCAT31(SUBFIELD(uStack_38,1,undefined3),3);
    iStack_24d4 = 0x49c3af;
    iStack_24d4 = PeekPacketChecksumBool();
    uStack_24d8 = uVar4;
    uVar7 = FUN_0040a4d0(param_1 + 0x7864);
    uVar8 = FUN_0040a4d0(param_1 + 0x4d90);
    uVar9 = FUN_0040a4d0(iStack_24ac);
    uVar10 = FUN_0040a4d0(uStack_24b0);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),uStack_24b4,6,0,
                 CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                          *(int *)(param_1 + 0xae2c) != 0),uVar10,uVar9,uVar8,uVar7);
    uStack_6c = CONCAT31(SUBFIELD(uStack_6c,1,undefined3),2);
    FUN_0040a2a0();
    uStack_6c = 0xffffffff;
    FUN_0040a2a0();
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar7 = FUN_0040a4d0(puVar11);
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 == '\x01') {
LAB_0049c470:
      uVar8 = 3;
    }
    else {
      cVar3 = PeekPacketChecksumBool();
      uVar8 = 0xb;
      if (cVar3 == '\x01') goto LAB_0049c470;
    }
    uVar9 = FUN_0040aca0(iVar1,&uStack_24d8,iVar2);
    uStack_6c = 4;
    uVar10 = FUN_0040aba0(param_1 + 0x90c,auStack_1a24,param_1 + 0x53fc);
    uStack_6c = CONCAT31(SUBFIELD(uStack_6c,1,undefined3),5);
    uVar7 = PeekPacketChecksumBool(uVar7,3);
    uVar5 = FUN_0040a4d0(param_1 + 0x7864);
    uVar6 = FUN_0040a4d0(param_1 + 0x4d90);
    uVar9 = FUN_0040a4d0(uVar9);
    uVar10 = FUN_0040a4d0(uVar10);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),uVar8,6,0,*(int *)(param_1 + 0xae2c) != 0,uVar10,uVar9
                 ,uVar6,uVar5,uVar4,uVar7);
    uStack_4 = CONCAT31(SUBFIELD(uStack_4,1,undefined3),4);
    puStack_2498 = (undefined *)0x49c526;
    FUN_0040a2a0();
    uStack_4 = 0xffffffff;
    puStack_2498 = (undefined *)0x49c53a;
    FUN_0040a2a0();
    puStack_2498 = (undefined *)0x49c549;
    cVar3 = PeekPacketChecksumBool();
    goto joined_r0x0049c851;
  case 6:
    if (param_3 != 0xb) break;
    puStack_2498 = (undefined *)0xffffffff;
    puStack_249c = (undefined1 *)0x49c57b;
    QueueOutgoingPacketField();
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puStack_2498 = &DAT_00796aa0;
    }
    else {
      puStack_2498 = &DAT_00794e48;
    }
    puStack_249c = (undefined1 *)0x49c595;
    uVar7 = FUN_0040a4d0();
    puStack_2498 = (undefined *)0x49c5a4;
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 == '\x01') {
LAB_0049c5bf:
      uStack_2480 = 0;
    }
    else {
      puStack_2498 = (undefined *)0x49c5b3;
      cVar3 = PeekPacketChecksumBool();
      uStack_2480 = 8;
      if (cVar3 == '\x01') goto LAB_0049c5bf;
    }
    puStack_2498 = &DAT_00794bf0;
    puStack_249c = (undefined1 *)0x49c5d7;
    puStack_2498 = (undefined *)FUN_0040a4d0();
    puStack_249c = auStack_224c;
    uStack_24a4 = 0x49c5e6;
    iStack_24a0 = param_1 + 0x7864;
    uVar8 = FUN_0040a5f0();
    puStack_249c = auStack_454;
    iStack_24a0 = param_1 + 0xb30;
    uStack_4 = 6;
    uStack_24a4 = 0x49c610;
    puStack_2498 = (undefined *)(param_1 + 0x5a68);
    uVar9 = FUN_0040aca0();
    puStack_2498 = (undefined *)(param_1 + 0x5844);
    puStack_249c = auStack_1574;
    iStack_24a0 = param_1 + 0x90c;
    SUBFIELD(uStack_4,0,undefined1) = 7;
    uStack_24a4 = 0x49c637;
    uVar10 = FUN_0040aba0();
    puStack_2498 = (undefined *)0x2;
    uStack_4 = CONCAT31(SUBFIELD(uStack_4,1,undefined3),8);
    iStack_24a0 = 0x49c655;
    puStack_249c = (undefined1 *)uVar7;
    iStack_24a0 = PeekPacketChecksumBool();
    iStack_24a8 = 0x49c662;
    uStack_24a4 = uVar4;
    PeekPacketChecksumBool();
    iStack_24ac = 0x49c66c;
    iStack_24a8 = uVar8;
    iStack_24a8 = FUN_0040a4d0();
    iStack_24ac = param_1 + 0x4d90;
    uStack_24b0 = 0x49c679;
    iStack_24ac = FUN_0040a4d0();
    uStack_24b4 = 0x49c684;
    uStack_24b0 = uVar9;
    uStack_24b0 = FUN_0040a4d0();
    uStack_24b8 = 0x49c68f;
    uStack_24b4 = uVar10;
    uStack_24b4 = FUN_0040a4d0();
    uStack_24b8 = CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                           *(int *)(param_1 + 0xae2c) != 0);
    uStack_24c8 = (uint)*(byte *)(param_1 + 8);
    uStack_24bc = 1;
    uStack_24c0 = 6;
    uStack_24c4 = uStack_2480;
    puStack_24cc = (undefined *)0x49c6b0;
    FUN_0042bbb0();
    SUBFIELD(uStack_38,0,undefined1) = 7;
    puStack_24cc = (undefined *)0x49c6c4;
    FUN_0040a2a0();
    uStack_38 = CONCAT31(SUBFIELD(uStack_38,1,undefined3),6);
    puStack_24cc = (undefined *)0x49c6d8;
    FUN_0040a2a0();
    uStack_38 = 0xffffffff;
    puStack_24cc = (undefined *)0x49c6ef;
    FUN_0040a2a0();
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puStack_24cc = &DAT_00796aa0;
    }
    else {
      puStack_24cc = &DAT_00794e48;
    }
    puStack_24d0 = (undefined1 *)0x49c709;
    uStack_24b8 = FUN_0040a4d0();
    puStack_24cc = (undefined *)0x49c718;
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 == '\x01') {
LAB_0049c733:
      uStack_24b4 = 1;
    }
    else {
      puStack_24cc = (undefined *)0x49c727;
      cVar3 = PeekPacketChecksumBool();
      uStack_24b4 = 9;
      if (cVar3 == '\x01') goto LAB_0049c733;
    }
    puStack_24cc = &DAT_00794bf0;
    puStack_24d0 = (undefined1 *)0x49c745;
    puStack_24cc = (undefined *)FUN_0040a4d0();
    puStack_24d0 = auStack_17cc;
    uStack_24d8 = 0x49c754;
    iStack_24d4 = param_1 + 0x7864;
    uVar7 = FUN_0040a6e0();
    puStack_24d0 = auStack_1c14;
    iStack_24d4 = param_1 + 0xb30;
    uStack_38 = 9;
    uStack_24d8 = 0x49c776;
    puStack_24cc = (undefined *)(param_1 + 0x5a68);
    uVar8 = FUN_0040aca0();
    puStack_24cc = (undefined *)(param_1 + 0x5844);
    puStack_24d0 = auStack_205c;
    iStack_24d4 = param_1 + 0x90c;
    SUBFIELD(uStack_38,0,undefined1) = 10;
    uStack_24d8 = 0x49c79b;
    iStack_24a8 = FUN_0040aba0();
    puStack_24cc = (undefined *)0x2;
    puStack_24d0 = (undefined1 *)uStack_24b8;
    uStack_38 = CONCAT31(SUBFIELD(uStack_38,1,undefined3),0xb);
    iStack_24d4 = 0x49c7b9;
    iStack_24d4 = PeekPacketChecksumBool();
    uStack_24d8 = uVar4;
    uVar4 = FUN_0040a4d0(uVar7);
    uVar7 = FUN_0040a4d0(param_1 + 0x4d90);
    uVar8 = FUN_0040a4d0(uVar8);
    uVar9 = FUN_0040a4d0(iStack_24a8);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),uStack_24b4,6,1,
                 CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                          *(int *)(param_1 + 0xae2c) != 0),uVar9,uVar8,uVar7,uVar4);
    SUBFIELD(uStack_4,0,undefined1) = 10;
    puStack_2498 = (undefined *)0x49c815;
    FUN_0040a2a0();
    uStack_4 = CONCAT31(SUBFIELD(uStack_4,1,undefined3),9);
    puStack_2498 = (undefined *)0x49c829;
    FUN_0040a2a0();
    uStack_4 = 0xffffffff;
    puStack_2498 = (undefined *)0x49c840;
    FUN_0040a2a0();
    puStack_2498 = (undefined *)0x49c84f;
    cVar3 = PeekPacketChecksumBool();
joined_r0x0049c851:
    if (cVar3 == '\0') {
      puStack_2498 = (undefined *)0x0;
      puStack_249c = (undefined1 *)0x49c860;
      FUN_004ee9b0();
    }
    puStack_2498 = (undefined *)0x49c86e;
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 == '\0') {
      puStack_2498 = (undefined *)0x49c881;
      cVar3 = PeekPacketChecksumBool();
      if (cVar3 == '\0') {
LAB_0049c9ad:
        puStack_2498 = (undefined *)0x49c9b2;
        cVar3 = FUN_0043a530();
        if (cVar3 == '\0') {
          puStack_2498 = &DAT_007949c8;
          puStack_249c = (undefined1 *)0x49c9c0;
          puStack_2498 = (undefined *)FUN_0040a4d0();
          puStack_249c = (undefined1 *)0x49c9d0;
          QueueOutgoingPacketField();
        }
        puStack_2498 = (undefined *)0x1;
        puStack_249c = (undefined1 *)0x49c9e1;
        FUN_00406500();
      }
    }
    break;
  case 8:
    if (param_3 != 0xb) break;
    puStack_2498 = (undefined *)0xffffffff;
    puStack_249c = (undefined1 *)0x49c8ad;
    QueueOutgoingPacketField();
    puStack_2498 = (undefined *)0x49c8b8;
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 == '\x01') {
LAB_0049c8d2:
      uVar4 = 0;
    }
    else {
      puStack_2498 = (undefined *)0x49c8c7;
      cVar3 = PeekPacketChecksumBool();
      if (cVar3 == '\x01') goto LAB_0049c8d2;
      uVar4 = 8;
    }
    puStack_2498 = (undefined *)(param_1 + 0x5620);
    puStack_249c = auStack_f08;
    iStack_24a0 = param_1 + 0xb30;
    uStack_24a4 = 0x49c8ef;
    uVar7 = FUN_0040aca0();
    puStack_2498 = (undefined *)(param_1 + 0x53fc);
    puStack_249c = auStack_1350;
    iStack_24a0 = param_1 + 0x90c;
    uStack_4 = 0xc;
    uStack_24a4 = 0x49c917;
    uVar8 = FUN_0040aba0();
    SUBFIELD(uStack_4,0,undefined1) = 0xd;
    puStack_2498 = (undefined *)(uint)*(ushort *)(param_1 + 0xbfbc);
    puStack_249c = (undefined1 *)(param_1 + 0x7864);
    iStack_24a0 = 0x49c937;
    puStack_249c = (undefined1 *)FUN_0040a4d0();
    iStack_24a0 = param_1 + 0x4d90;
    uStack_24a4 = 0x49c944;
    iStack_24a0 = FUN_0040a4d0();
    iStack_24a8 = 0x49c94b;
    uStack_24a4 = uVar7;
    uStack_24a4 = FUN_0040a4d0();
    iStack_24ac = 0x49c952;
    iStack_24a8 = uVar8;
    iStack_24a8 = FUN_0040a4d0();
    uStack_24b0 = (uint)*(byte *)(param_1 + 8);
    uStack_24b4 = 0x49c95f;
    iStack_24ac = uVar4;
    FUN_004317b0();
    uStack_4 = CONCAT31(SUBFIELD(uStack_4,1,undefined3),0xc);
    puStack_2498 = (undefined *)0x49c973;
    FUN_0040a2a0();
    uStack_4 = 0xffffffff;
    puStack_2498 = (undefined *)0x49c98a;
    FUN_0040a2a0();
    puStack_2498 = (undefined *)0x49c999;
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 == '\0') {
      puStack_2498 = (undefined *)0x0;
      puStack_249c = (undefined1 *)0x49c9aa;
      FUN_004ee9b0();
    }
    goto LAB_0049c9ad;
  case 10:
    if (param_3 == 0xb) {
      puStack_2498 = (undefined *)0xffffffff;
      puStack_249c = (undefined1 *)0x49ca05;
      QueueOutgoingPacketField();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_2498 = &DAT_00796aa0;
      }
      else {
        puStack_2498 = &DAT_00794e48;
      }
      puStack_249c = (undefined1 *)0x49ca1f;
      uVar7 = FUN_0040a4d0();
      puStack_2498 = &DAT_00794bf0;
      puStack_249c = (undefined1 *)0x49ca2d;
      puStack_2498 = (undefined *)FUN_0040a4d0();
      puStack_249c = auStack_230;
      iStack_24a0 = param_1 + 0x7864;
      uStack_24a4 = 0x49ca42;
      uVar8 = FUN_0040a5f0();
      puStack_2498 = (undefined *)(param_1 + 0x5a68);
      puStack_249c = auStack_678;
      iStack_24a0 = param_1 + 0xb30;
      uStack_4 = 0xe;
      uStack_24a4 = 0x49ca6a;
      uVar9 = FUN_0040aca0();
      puStack_2498 = (undefined *)(param_1 + 0x5844);
      puStack_249c = auStack_ac0;
      iStack_24a0 = param_1 + 0x90c;
      SUBFIELD(uStack_4,0,undefined1) = 0xf;
      uStack_24a4 = 0x49ca8f;
      uVar10 = FUN_0040aba0();
      puStack_2498 = (undefined *)0x1;
      SUBFIELD(uStack_4,0,undefined1) = 0x10;
      iStack_24a0 = 0x49caad;
      puStack_249c = (undefined1 *)uVar7;
      iStack_24a0 = PeekPacketChecksumBool();
      iStack_24a8 = 0x49caba;
      uStack_24a4 = uVar4;
      PeekPacketChecksumBool();
      iStack_24ac = 0x49cac0;
      iStack_24a8 = uVar8;
      iStack_24a8 = FUN_0040a4d0();
      iStack_24ac = param_1 + 0x4d90;
      uStack_24b0 = 0x49cacd;
      iStack_24ac = FUN_0040a4d0();
      uStack_24b4 = 0x49cad4;
      uStack_24b0 = uVar9;
      uStack_24b0 = FUN_0040a4d0();
      uStack_24b8 = 0x49cadf;
      uStack_24b4 = uVar10;
      uStack_24b4 = FUN_0040a4d0();
      uStack_24b8 = CONCAT31((int3)((uint)extraout_ECX >> 8),*(int *)(param_1 + 0xae2c) != 0);
      uStack_24c4 = (uint)*(byte *)(param_1 + 8);
      uStack_24bc = 6;
      uStack_24c0 = 0;
      uStack_24c8 = 0x49cafb;
      FUN_0042de70();
      SUBFIELD(uStack_4,0,undefined1) = 0xf;
      puStack_2498 = (undefined *)0x49cb0f;
      FUN_0040a2a0();
      uStack_4 = CONCAT31(SUBFIELD(uStack_4,1,undefined3),0xe);
      puStack_2498 = (undefined *)0x49cb23;
      FUN_0040a2a0();
      uStack_4 = 0xffffffff;
      puStack_2498 = (undefined *)0x49cb3a;
      FUN_0040a2a0();
      puStack_2498 = (undefined *)0x49cb49;
      cVar3 = PeekPacketChecksumBool();
      if (cVar3 == '\0') {
        puStack_2498 = (undefined *)0x0;
        puStack_249c = (undefined1 *)0x49cb5a;
        FUN_004ee9b0();
      }
      puStack_2498 = (undefined *)0x49cb62;
      cVar3 = FUN_0043a530();
      if (cVar3 == '\0') {
        puStack_2498 = &DAT_007949c8;
        puStack_249c = (undefined1 *)0x49cb70;
        puStack_2498 = (undefined *)FUN_0040a4d0();
        puStack_249c = (undefined1 *)0x49cb80;
        QueueOutgoingPacketField();
        iVar2 = g_clientContext;
        *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
        *(undefined4 *)(&DAT_005f376c + iVar2) = 0;
        puStack_2498 = (undefined *)0x1;
        puStack_249c = (undefined1 *)0x49cba5;
        FUN_00406500();
      }
      else {
        puStack_2498 = (undefined *)0x1;
        puStack_249c = (undefined1 *)0x49cbb8;
        FUN_00406500();
      }
    }
  }
  *unaff_FS_OFFSET = uStack_c;
  return;
}

