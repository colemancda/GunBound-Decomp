/* SimulateMobileFrame - 0x00461ca0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall SimulateMobileFrame(int *param_1)

{
  int *piVar1;
  int *piVar2;
  bool bVar3;
  bool bVar4;
  char cVar5;
  undefined1 uVar6;
  undefined2 uVar7;
  int iVar8;
  undefined4 uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  undefined4 *puVar13;
  undefined4 *unaff_FS_OFFSET;
  char *pcVar14;
  undefined4 uVar15;
  undefined1 auStack_454 [548];
  undefined1 auStack_230 [548];
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053d571;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  (**(code **)(param_1[0xe] + 8))();
  cVar5 = PeekPacketChecksumBool();
  if (cVar5 == '\x01') goto LAB_004628db;
  cVar5 = PeekPacketChecksumBool();
  if (cVar5 == '\0') {
    AdvanceSpriteAnimation();
    *unaff_FS_OFFSET = uStack_c;
    return;
  }
  cVar5 = PeekPacketChecksumBool();
  if (cVar5 == '\0') {
    cVar5 = PacketChecksumLessThan(param_1 + 0x243,0);
    if (cVar5 != '\0') {
      QueueOutgoingPacketField(0);
    }
    cVar5 = PacketChecksumGreaterEqual(param_1 + 0x243,*(undefined4 *)(&DAT_006a7720 + g_clientContext));
    if (cVar5 != '\0') {
      QueueOutgoingPacketField(*(int *)(&DAT_006a7720 + g_clientContext) + -1);
    }
  }
  FUN_0045cb50();
  if ((*(char *)((int)param_1 + 0xbffa) != '\0') && (cVar5 = FUN_0043c820(), cVar5 == '\0')) {
    (**(code **)(*param_1 + 4))((undefined4 *)((int)param_1 + 0xbffa));
    iVar12 = *(int *)(g_gameStateVTableArray[0xb] + 0x10a0);
    iVar8 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
    iVar11 = g_clientContext;
    if (iVar12 == iVar8) {
      *(undefined4 *)(*(int *)(g_clientContext + 0x621e0) + 0xb0b0) = 3;
    }
    else {
      if (*(char *)(g_clientContext + 0x4590c + iVar12) != *(char *)(g_clientContext + 0x3b6c0)) {
        *(undefined4 *)(*(int *)(g_clientContext + 0x621e0) + 0xb0b0) = 1;
      }
      if (*(char *)(*(int *)(g_gameStateVTableArray[0xb] + 0x10a0) + 0x4590c + iVar11) ==
          *(char *)(iVar11 + 0x3b6c0)) {
        *(undefined4 *)(*(int *)(iVar11 + 0x621e0) + 0xb0b0) = 2;
      }
    }
    puVar13 = (undefined4 *)((int)param_1 + 0xbffa);
    for (iVar12 = 0x20; iVar12 != 0; iVar12 = iVar12 + -1) {
      *puVar13 = 0;
      puVar13 = puVar13 + 1;
    }
  }
  cVar5 = PeekPacketChecksumBool();
  if (cVar5 != '\0') {
    (**(code **)(*param_1 + 0x18))();
  }
  FUN_0045ba50(param_1);
  AdvanceSpriteAnimation();
  if ((char)param_1[0xd] != '\0') {
    FUN_0045ed80();
  }
  (**(code **)(*param_1 + 0x1c))(param_1[9],param_1[0xb]);
  cVar5 = PeekPacketChecksumBool();
  if (cVar5 == '\x01') goto LAB_004628db;
  cVar5 = PeekPacketChecksumBool();
  if (((cVar5 == '\0') && (param_1[9] != 0xd)) && (cVar5 = PeekPacketChecksumBool(), cVar5 != '\0')) {
    piVar1 = param_1 + 0x579;
    piVar2 = param_1 + 0x243;
    cVar5 = ChecksumPairDiffers(piVar2,piVar1);
    if (cVar5 == '\0') {
      if ((param_1[9] != 1) && (param_1[9] != 3)) goto LAB_004622cf;
      uVar9 = EncodeChecksumDeltaDiv(param_1 + 0x19d1,auStack_454,3);
      uStack_4 = 10;
      cVar5 = CompareChecksumPair(param_1 + 0x1a5a,uVar9);
      uStack_4 = 0xffffffff;
      ScrubChecksumGuard();
      if (cVar5 == '\0') {
        pcVar14 = s_normal_00552230;
        goto LAB_004622bc;
      }
      (**(code **)(*param_1 + 4))(s_wnormal_00553618);
    }
    else {
      cVar5 = CompareChecksumPair(piVar1,piVar2);
      if (cVar5 == '\0') {
        QueueOutgoingPacketField(1);
        uVar9 = EncodeChecksumPairDiff(piVar2,auStack_454,piVar1);
        uStack_4 = 5;
        uVar10 = PeekChecksumStateUnderLock(uVar9);
        if (((int)((uVar10 ^ (int)uVar10 >> 0x1f) - ((int)uVar10 >> 0x1f)) < 3) ||
           ((cVar5 = PacketChecksumGreaterEqual(piVar2,*(int *)(&DAT_006a7720 + g_clientContext) + -2), cVar5 != '\0'
            && (*(int *)(&DAT_006a7720 + g_clientContext) != 2)))) {
          bVar3 = true;
        }
        else {
          bVar3 = false;
        }
        uStack_4 = 0xffffffff;
        ScrubChecksumGuard();
        if (!bVar3) {
          if ((param_1[9] != 1) && (param_1[9] != 3)) {
            uVar9 = EncodeChecksumDeltaDiv(param_1 + 0x19d1,auStack_454,3);
            uStack_4 = 7;
            cVar5 = CompareChecksumPair(param_1 + 0x1a5a,uVar9);
            uStack_4 = 0xffffffff;
            ScrubChecksumGuard();
            if (cVar5 == '\0') {
              (**(code **)(*param_1 + 4))(&DAT_00553f90);
            }
            else {
              (**(code **)(*param_1 + 4))(s_wmove_00555ca0);
            }
          }
          uVar9 = EncodeChecksumDeltaMul(param_1 + 0x12db,auStack_454,2);
          uStack_4 = 8;
          iVar12 = PeekChecksumStateUnderLock(uVar9);
          AddToPacketChecksum(0x96 - iVar12);
          uStack_4 = 0xffffffff;
          ScrubChecksumGuard();
          uVar9 = PeekChecksumStateUnderLock(&DAT_00796aa0);
          uVar9 = EncodeChecksumDeltaDiv(param_1 + 0x21d8,auStack_454,uVar9);
          uStack_4 = 9;
          EmitChecksumSum(uVar9);
          goto LAB_0046205f;
        }
        EncodeChecksumState(piVar1);
        uVar9 = EncodeChecksumDeltaDiv(param_1 + 0x19d1,auStack_454,3);
        uStack_4 = 6;
      }
      else {
        QueueOutgoingPacketField(0);
        uVar9 = EncodeChecksumPairDiff(piVar2,auStack_454,piVar1);
        uStack_4 = 0;
        uVar10 = PeekChecksumStateUnderLock(uVar9);
        if (((int)((uVar10 ^ (int)uVar10 >> 0x1f) - ((int)uVar10 >> 0x1f)) < 3) ||
           ((cVar5 = PacketChecksumLessEqual(piVar2,1), cVar5 != '\0' &&
            (cVar5 = PacketChecksumLessEqual(piVar1,1), cVar5 != '\0')))) {
          bVar3 = true;
        }
        else {
          bVar3 = false;
        }
        uStack_4 = 0xffffffff;
        ScrubChecksumGuard();
        if (!bVar3) {
          if ((param_1[9] != 1) && (param_1[9] != 3)) {
            uVar9 = EncodeChecksumDeltaDiv(param_1 + 0x19d1,auStack_454,3);
            uStack_4 = 2;
            cVar5 = CompareChecksumPair(param_1 + 0x1a5a,uVar9);
            uStack_4 = 0xffffffff;
            ScrubChecksumGuard();
            if (cVar5 == '\0') {
              (**(code **)(*param_1 + 4))(&DAT_00553f90);
            }
            else {
              (**(code **)(*param_1 + 4))(s_wmove_00555ca0);
            }
          }
          uVar9 = EncodeChecksumDeltaMul(param_1 + 0x12db,auStack_454,2);
          uStack_4 = 3;
          iVar12 = PeekChecksumStateUnderLock(uVar9);
          AddToPacketChecksum(0x96 - iVar12);
          uStack_4 = 0xffffffff;
          ScrubChecksumGuard();
          uVar9 = PeekChecksumStateUnderLock(&DAT_00796aa0);
          uVar9 = EncodeChecksumDeltaDiv(param_1 + 0x21d8,auStack_454,uVar9);
          uStack_4 = 4;
          EmitChecksumDiff(uVar9);
LAB_0046205f:
          uStack_4 = 0xffffffff;
          ScrubChecksumGuard();
          uVar9 = PeekChecksumStateUnderLock(&DAT_00796aa0);
          EmitChecksumMod(uVar9);
          goto LAB_004622cf;
        }
        EncodeChecksumState(piVar1);
        uVar9 = EncodeChecksumDeltaDiv(param_1 + 0x19d1,auStack_454,3);
        uStack_4 = 1;
      }
      cVar5 = CompareChecksumPair(param_1 + 0x1a5a,uVar9);
      uStack_4 = 0xffffffff;
      ScrubChecksumGuard();
      if (cVar5 == '\0') {
        (**(code **)(*param_1 + 4))(s_normal_00552230);
      }
      else {
        pcVar14 = s_wnormal_00553618;
LAB_004622bc:
        (**(code **)(*param_1 + 4))(pcVar14);
      }
    }
    QueueOutgoingPacketField(0);
  }
LAB_004622cf:
  cVar5 = PeekPacketChecksumBool();
  if (cVar5 != '\0') {
    iVar11 = PeekChecksumStateUnderLock(&DAT_00e9bed8);
    iVar12 = param_1[0x2c26];
    param_1[0x2c25] = (param_1[0x2c25] + 9) % iVar11;
    param_1[0x2c26] = iVar12 + param_1[0x2c27];
    if (0xfe < iVar12 + param_1[0x2c27]) {
      param_1[0x2c26] = 0xff;
      param_1[0x2c27] = -0x10;
    }
    if (param_1[0x2c26] < 0x30) {
      param_1[0x2c26] = 0x2f;
      param_1[0x2c27] = 0x10;
    }
    iVar12 = (param_1[0x2c28] << 2) / 5;
    param_1[0x2c28] = iVar12;
    if (iVar12 < 0xc0) {
      param_1[0x2c28] = 0xc0;
    }
  }
  piVar1 = param_1 + 0x22f1;
  cVar5 = PacketChecksumGreaterThan(piVar1,0);
  if ((((cVar5 != '\0') && (cVar5 = PeekPacketChecksumBool(), cVar5 == '\x01')) &&
      (cVar5 = PeekPacketChecksumBool(), cVar5 == '\x01')) &&
     ((*(int *)(&DAT_005f3768 + g_clientContext) != 1 && (*(int *)(&DAT_005f3768 + g_clientContext) != 2))
     )) {
    FUN_0040b060();
    uVar9 = EncodeChecksumDeltaMod(piVar1,auStack_454,0x14);
    uStack_4 = 0xb;
    cVar5 = PacketChecksumEquals(uVar9,0);
    if ((((cVar5 == '\0') ||
         ((cVar5 = PeekPacketChecksumBool(), cVar5 == '\0' || (cVar5 = PeekPacketChecksumBool(), cVar5 == '\0')))) ||
        (cVar5 = PeekPacketChecksumBool(), cVar5 == '\0')) ||
       (cVar5 = PacketChecksumNotEquals(piVar1,0), cVar5 == '\0')) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    uStack_4 = 0xffffffff;
    ScrubChecksumGuard();
    if (bVar3) {
      FUN_004ee9b0(0);
    }
  }
  bVar3 = false;
  cVar5 = PacketChecksumEquals(piVar1,0);
  if ((cVar5 != '\0') && (cVar5 = PeekPacketChecksumBool(), cVar5 == '\x01')) {
    QueueOutgoingPacketField(0xffffffff);
    cVar5 = PacketChecksumNotEquals(param_1 + 0x1e19,0);
    if (cVar5 != '\0') {
      *(undefined1 *)(DAT_007934e4 + 8) = 1;
    }
    FUN_00461c60(s_normal_00552230);
    uVar9 = FUN_00406860();
    cVar5 = FUN_00406610(uVar9);
    if (((cVar5 != '\0') && (cVar5 = PeekPacketChecksumBool(), cVar5 != '\0')) &&
       (cVar5 = PeekPacketChecksumBool(), cVar5 != '\0')) {
      Replay_AppendEvent(0x8402);
      uVar7 = PeekChecksumStateUnderLock(param_1 + 0x243);
      *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
      g_replayEventCursor = g_replayEventCursor + 2;
      uVar7 = PeekChecksumStateUnderLock(param_1 + 0x2cc);
      *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
      g_replayEventCursor = g_replayEventCursor + 2;
      uVar6 = PacketChecksumEquals(param_1 + 0x715,1);
      (&g_replayEventBuffer)[g_replayEventCursor] = uVar6;
      g_replayEventCursor = g_replayEventCursor + 1;
      Replay_FlushEvent();
      SetGuardedBool(0);
      SetGuardedBool(0);
      Replay_AppendEvent(0xc301);
      (&g_replayEventBuffer)[g_replayEventCursor] = 1;
      g_replayEventCursor = g_replayEventCursor + 1;
      uVar7 = FUN_0045d360(1);
      *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
      g_replayEventCursor = g_replayEventCursor + 2;
      FUN_0041f200(0);
      Replay_FlushEvent();
    }
  }
  cVar5 = PacketChecksumGreaterEqual(param_1 + 0x2cc,*(undefined4 *)(&DAT_006a7724 + g_clientContext));
  if (((cVar5 != '\0') && (cVar5 = PeekPacketChecksumBool(), cVar5 == '\x01')) &&
     ((cVar5 = PacketChecksumEquals(g_clientContext + 0x45354,1), cVar5 != '\0' ||
      (cVar5 = PacketChecksumEquals(g_clientContext + 0x45354,3), cVar5 != '\0')))) {
    (**(code **)(*param_1 + 4))(&DAT_00555c90);
    QueueOutgoingPacketField(5);
    iVar11 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
    iVar12 = g_clientContext;
    if (param_1[2] == iVar11) {
      g_gameStateVTableArray[0xb][0x93] = 1;
      (&DAT_006a7758)[iVar12] = 0;
    }
    *(undefined1 *)(param_1 + 0x2b85) = 1;
    SetGuardedBool(0);
    SetGuardedBool(1);
  }
  cVar5 = FUN_00406610(param_1[9] != 0xe);
  if (cVar5 == '\0') {
LAB_00462742:
    bVar4 = false;
  }
  else {
    uVar9 = EncodeChecksumDeltaDiv(param_1 + 0x19d1,auStack_454,3);
    uStack_4 = 0xc;
    bVar3 = true;
    cVar5 = CompareChecksumPair(param_1 + 0x1a5a,uVar9);
    if (cVar5 == '\0') goto LAB_00462742;
    bVar4 = true;
  }
  uStack_4 = 0xffffffff;
  if (bVar3) {
    ScrubChecksumGuard();
  }
  if (bVar4) {
    uVar15 = 0x28;
    PeekChecksumStateUnderLock(param_1 + 0x2cc);
    uVar9 = PeekChecksumStateUnderLock(param_1 + 0x243);
    FUN_00436cd0(uVar9,uVar15);
  }
  uVar9 = EncodeChecksumPairDiff(param_1 + 0x1ae3,auStack_454,param_1 + 0x1a5a);
  uStack_4 = 0xd;
  iVar12 = PeekChecksumStateUnderLock(uVar9);
  uStack_4 = 0xffffffff;
  ScrubChecksumGuard();
  if (iVar12 < 0) {
    iVar12 = iVar12 + -7;
  }
  else {
    iVar12 = iVar12 + 7;
  }
  SubFromPacketChecksum((int)(iVar12 + (iVar12 >> 0x1f & 7U)) >> 3);
  uVar9 = EncodeChecksumPairDiff(param_1 + 0x1c7e,auStack_230,param_1 + 0x1bf5);
  uStack_4 = 0xe;
  iVar12 = PeekChecksumStateUnderLock(uVar9);
  uStack_4 = 0xffffffff;
  ScrubChecksumGuard();
  if (iVar12 < 0) {
    iVar12 = iVar12 + -7;
  }
  else {
    iVar12 = iVar12 + 7;
  }
  SubFromPacketChecksum((int)(iVar12 + (iVar12 >> 0x1f & 7U)) >> 3);
  iVar12 = param_1[0x2ff9] - param_1[0x2ff8];
  if (iVar12 < 0) {
    iVar12 = iVar12 + -9;
  }
  else {
    iVar12 = iVar12 + 9;
  }
  param_1[0x2ff9] = param_1[0x2ff9] - iVar12 / 10;
  cVar5 = PacketChecksumNotEquals(param_1 + 0x243,param_1[0x30a9]);
  if ((cVar5 != '\0') ||
     (cVar5 = PacketChecksumNotEquals(param_1 + 0x2cc,param_1[0x30aa]), cVar5 != '\0')) {
    SetGuardedBool(1);
  }
  iVar12 = PeekChecksumStateUnderLock(param_1 + 0x243);
  param_1[0x30a9] = iVar12;
  iVar12 = PeekChecksumStateUnderLock(param_1 + 0x2cc);
  param_1[0x30aa] = iVar12;
LAB_004628db:
  *unaff_FS_OFFSET = uStack_c;
  return;
}

