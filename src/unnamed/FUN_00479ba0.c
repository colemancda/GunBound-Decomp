/* FUN_00479ba0 - 0x00479ba0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_00479ba0(int *param_1)

{
  int *piVar1;
  bool bVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  undefined4 *puVar13;
  char *pcVar14;
  int *unaff_FS_OFFSET;
  undefined4 uVar15;
  int local_924 [2];
  char acStack_91c [128];
  undefined1 local_89c [20];
  int local_888;
  undefined1 uStack_67c;
  undefined1 auStack_678 [20];
  undefined4 uStack_664;
  undefined1 uStack_458;
  undefined1 auStack_454 [548];
  undefined1 auStack_230 [548];
  int local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053c294;
  iVar5 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (int)&local_c;
  local_c = iVar5;
  if ((char)param_1[5] == '\x01') goto LAB_0047a932;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaSub(param_1 + 0x120,local_89c,uVar4);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = FindGroundHeightAtColumn();
  local_4 = 0xffffffff;
  if (local_888 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_924);
  }
  EncodeChecksumPairSum(param_1 + 0x120,local_89c,param_1 + 0x67d);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar6 < iVar5) {
LAB_00479d44:
    bVar2 = false;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar6 < 0) goto LAB_00479d44;
    cVar3 = PacketChecksumLessThan(param_1 + 0x97,*(undefined4 *)(&DAT_006a7720 + g_clientContext));
    bVar2 = true;
    if (cVar3 == '\0') goto LAB_00479d44;
  }
  local_4 = 0xffffffff;
  if (local_888 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_924);
  }
  if (bVar2) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar6 < 5) {
      QueueOutgoingPacketField(iVar5);
      if (param_1[9] == 1) {
        (**(code **)(*param_1 + 4))(s_normal_00552230);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(0);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(0);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      cVar3 = PeekPacketChecksumBool();
      if (cVar3 == '\x01') {
        uVar7 = FUN_00415c60();
        if ((uVar7 & 1) != 0) {
          uVar7 = FUN_00415c60();
          GetLocalizedString(&g_localizedStringTable,uVar7 % 10 + 0x80d);
          FUN_004382d0();
        }
LAB_00479e75:
        uVar4 = PeekChecksumStateUnderLock(&DAT_00e55ab8);
        QueueOutgoingPacketField(uVar4);
        FUN_0040b030();
        SetGuardedBool(0);
      }
    }
    else {
      iVar6 = PeekChecksumStateUnderLock(param_1 + 0x67d);
      QueueOutgoingPacketField(iVar5 - iVar6);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(0);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      cVar3 = PeekPacketChecksumBool();
      if ((cVar3 == '\x01') && (iVar5 < *(int *)(&DAT_006a7724 + g_clientContext))) goto LAB_00479e75;
    }
  }
  else {
    if (param_1[9] == 0) {
      (**(code **)(*param_1 + 4))(&DAT_00553bcc);
      EncodeChecksumState(g_clientContext + 0x62630);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar5 + 1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EmitChecksumSum(param_1 + 0x67d);
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 != '\0') {
      PeekChecksumStateUnderLock(g_clientContext + 0x5b1ac);
      PeekChecksumStateUnderLock(g_clientContext + 0x5af88);
      iVar5 = FloatToInt64();
      AddToPacketChecksum(iVar5 * 3);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar4 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar4 = EncodeChecksumDeltaDiv(param_1 + 0x5f4,local_89c,uVar4);
      local_4 = 2;
      EmitChecksumSum(uVar4);
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar4 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EmitChecksumMod(uVar4);
    }
  }
  iVar5 = PeekPacketChecksumBool();
  if ((char)iVar5 != '\0') goto LAB_0047a932;
  cVar3 = PeekPacketChecksumBool();
  if (cVar3 == '\x01') {
    iVar6 = PeekChecksumStateUnderLock(param_1 + 0x120);
    iVar8 = PeekChecksumStateUnderLock(param_1 + 0x97);
    iVar5 = g_clientContext;
    piVar1 = (int *)(&DAT_006a7708 + g_clientContext);
    cVar3 = PeekPacketChecksumBool();
    if ((cVar3 == '\0') && ((&DAT_006a7758)[iVar5] != '\0')) {
      if (((&DAT_006a7736)[iVar5] == '\x01') &&
         ((uVar7 = iVar6 - *(int *)(&DAT_006a7714 + iVar5) >> 0x1f,
          200 < (int)((iVar6 - *(int *)(&DAT_006a7714 + iVar5) ^ uVar7) - uVar7) ||
          (uVar7 = iVar8 - *(int *)(&DAT_006a7710 + iVar5) >> 0x1f,
          300 < (int)((iVar8 - *(int *)(&DAT_006a7710 + iVar5) ^ uVar7) - uVar7))))) {
        (&DAT_006a7736)[iVar5] = 0;
      }
      iVar10 = 400;
      if (399 < iVar8) {
        iVar10 = iVar8;
      }
      iVar9 = *(int *)(&DAT_006a7720 + iVar5) + -400;
      if ((iVar10 <= iVar9) && (iVar9 = 400, 399 < iVar8)) {
        iVar9 = iVar8;
      }
      iVar8 = iVar6;
      if (iVar6 < -0x14) {
        iVar8 = -0x14;
      }
      iVar10 = *(int *)(&DAT_006a7724 + iVar5) + -0x104;
      if ((iVar8 <= *(int *)(&DAT_006a7724 + iVar5) + -0x104) && (iVar10 = iVar6, iVar6 < -0x14)) {
        iVar10 = -0x14;
      }
      local_924[0] = *piVar1;
      *(int *)(&DAT_006a771c + iVar5) = iVar10;
      local_924[0] = local_924[0] - iVar9;
      if (((*(int *)(&DAT_006a770c + iVar5) - iVar10) * (*(int *)(&DAT_006a770c + iVar5) - iVar10) +
           local_924[0] * local_924[0] < 40000) &&
         (((&DAT_006a7734)[iVar5] == '\x01' || ((&DAT_006a7f6c)[iVar5] == '\0')))) {
        *(int *)(&DAT_006a7710 + iVar5) = iVar9;
        *piVar1 = iVar9;
        *(int *)(&DAT_006a7714 + iVar5) = iVar10;
        *(int *)(&DAT_006a770c + iVar5) = iVar10;
      }
      if ((((&DAT_006a7734)[iVar5] == '\0') && ((&DAT_006a7f6c)[iVar5] == '\x01')) &&
         ((&DAT_006a7736)[iVar5] == '\0')) {
        iVar6 = *(int *)(&DAT_006a7730 + iVar5);
        iVar8 = iVar9;
        if (iVar6 < iVar9) {
          iVar8 = iVar6;
        }
        iVar11 = *(int *)(&DAT_006a772c + iVar5);
        if ((iVar11 <= iVar8) && (iVar11 = iVar6, iVar9 <= iVar6)) {
          iVar11 = iVar9;
        }
        *(int *)(&DAT_006a7718 + iVar5) = iVar11;
      }
      if ((&DAT_006a7734)[iVar5] == '\x01') {
        *(int *)(&DAT_006a7718 + iVar5) = iVar9;
        *(int *)(&DAT_006a771c + iVar5) = iVar10;
      }
    }
  }
  FUN_004785f0(param_1);
  AdvanceSpriteAnimation();
  if ((char)param_1[0xd] != '\0') {
    (**(code **)(*param_1 + 4))(s_normal_00552230);
  }
  iVar5 = *(int *)(&DAT_006a7724 + g_clientContext);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar5 < iVar6) || (cVar3 = FUN_0040b450(param_1 + 0x232,param_1 + 0x1a9), cVar3 != '\0')) {
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 == '\x01') {
      uVar4 = PeekChecksumStateUnderLock(&DAT_00e55ab8);
      QueueOutgoingPacketField(uVar4);
    }
    else if (g_gameStateVTableArray[0xb][0x2382] == '\0') {
      uStack_67c = 0;
      local_888 = 0;
      EncodeOutgoingPacketField(0);
      local_4 = 3;
      uStack_458 = 0;
      uStack_664 = 0;
      EncodeOutgoingPacketField(0);
      piVar1 = param_1 + 0xe;
      local_4 = 4;
      uVar4 = PeekChecksumStateUnderLock(piVar1);
      switch(uVar4) {
      case 0:
        EncodeChecksumStateXored();
        break;
      case 1:
        EncodeChecksumStateXored();
        break;
      case 2:
        EncodeChecksumStateXored();
        break;
      case 3:
        EncodeChecksumStateXored();
        break;
      default:
        EncodeChecksumStateXored();
      }
      EncodeChecksumStateXored();
      iVar5 = PeekChecksumStateUnderLock(param_1 + 0x345);
      iVar6 = GetPlayerRecordBySlot(g_clientContext);
      if (iVar6 != 0) {
        iVar8 = PeekChecksumStateUnderLock(iVar5 * 0x1120 + 0x5113c + g_clientContext);
        iVar10 = PeekChecksumStateUnderLock(&DAT_00796aa0);
        uVar4 = EncodeChecksumDeltaMul(local_89c,auStack_230,iVar8 + iVar10);
        local_4 = 5;
        uVar12 = PeekChecksumStateUnderLock(&DAT_00796aa0);
        uVar4 = EncodeChecksumDeltaDiv(uVar4,auStack_454,uVar12);
        local_4 = 6;
        uVar4 = PeekChecksumStateUnderLock(uVar4);
        local_4 = 5;
        ScrubChecksumGuard();
        local_4 = 4;
        ScrubChecksumGuard();
        AddToPacketChecksum(uVar4);
        uVar12 = PeekChecksumStateUnderLock(auStack_678);
        iVar8 = iVar6 + 0xae15;
        iVar10 = PeekChecksumStateUnderLock(piVar1);
        pcVar14 = (char *)GetLocalizedString(&g_localizedStringTable,iVar10 + 600);
        _sprintf(acStack_91c,pcVar14,iVar8,uVar12,uVar4);
        cVar3 = PacketChecksumEquals(piVar1,3);
        if (cVar3 == '\0') {
          uVar12 = 3;
          uVar4 = 4;
        }
        else {
          uVar12 = 2;
          uVar4 = 3;
        }
        (**(code **)(*(int *)g_gameStateVTableArray[0xb] + 0x28))(acStack_91c,uVar4,uVar12);
        iVar8 = PeekChecksumStateUnderLock(piVar1);
        if (iVar8 == 0) {
          uVar15 = 2;
          uVar4 = PeekChecksumStateUnderLock(iVar6 + 0xb30);
          uVar12 = PeekChecksumStateUnderLock(iVar6 + 0x90c);
          FUN_004368f0(uVar12,uVar4,uVar15);
          uVar4 = 2;
        }
        else {
          if (iVar8 != 1) goto LAB_0047a564;
          uVar15 = 1;
          uVar4 = PeekChecksumStateUnderLock(iVar6 + 0xb30);
          uVar12 = PeekChecksumStateUnderLock(iVar6 + 0x90c);
          FUN_004368f0(uVar12,uVar4,uVar15);
          uVar4 = 1;
        }
        AddToPacketChecksum(uVar4);
      }
LAB_0047a564:
      cVar3 = *(char *)(g_clientContext + 0x50126 + iVar5);
      if (cVar3 == '\0') {
        EmitChecksumSum(auStack_678);
        cVar3 = PacketChecksumLessThan(&DAT_0067e3d0 + g_clientContext,0);
joined_r0x0047a5db:
        if (cVar3 != '\0') {
          QueueOutgoingPacketField(0);
        }
      }
      else if (cVar3 == '\x01') {
        EmitChecksumSum(auStack_678);
        cVar3 = PacketChecksumLessThan(&DAT_0067e5f4 + g_clientContext,0);
        goto joined_r0x0047a5db;
      }
      uVar4 = PeekChecksumStateUnderLock(&DAT_00796aa0);
      cVar3 = PacketChecksumGreaterEqual(&DAT_0067e5f4 + g_clientContext,uVar4);
      if (cVar3 == '\0') {
        uVar4 = PeekChecksumStateUnderLock(&DAT_00796aa0);
        cVar3 = PacketChecksumGreaterEqual(&DAT_0067e3d0 + g_clientContext,uVar4);
        if (cVar3 != '\0') goto LAB_0047a634;
      }
      else {
LAB_0047a634:
        cVar3 = FUN_0040b390(g_clientContext + 0x3b6c4,g_clientContext + 0x3b49c);
        iVar5 = DAT_007934e8;
        if ((cVar3 != '\0') && (g_gameStateVTableArray[0xb][0x2382] == '\0')) {
          *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x4200;
          *(undefined4 *)(iVar5 + 0x44d0) = 6;
          cVar3 = FUN_0040b410(&DAT_0067e5f4 + g_clientContext,&DAT_0067e3d0 + g_clientContext);
          iVar5 = DAT_007934e8;
          if (cVar3 == '\0') {
            *(undefined1 *)(DAT_007934e8 + 0x4d0 + *(int *)(DAT_007934e8 + 0x44d0)) = 0;
          }
          else {
            *(undefined1 *)(DAT_007934e8 + 0x4d0 + *(int *)(DAT_007934e8 + 0x44d0)) = 1;
          }
          *(int *)(iVar5 + 0x44d0) = *(int *)(iVar5 + 0x44d0) + 1;
          EncodePacketBody();
          SendOutgoingPacket();
          g_gameStateVTableArray[0xb][0x2382] = 1;
          local_4 = 3;
          ScrubChecksumGuard();
          local_4 = 0xffffffff;
          iVar5 = ScrubChecksumGuard();
          goto LAB_0047a932;
        }
      }
      AcquireSoundChannel(0);
      FUN_0040b060();
      local_4 = 3;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
    }
    cVar3 = FUN_0040b450(param_1 + 0x232,param_1 + 0x1a9);
    if (cVar3 != '\0') {
      iVar5 = PeekChecksumStateUnderLock(param_1 + 0xe);
      _sprintf(acStack_91c,s_jflame_d_00555ff0,iVar5 + 1);
      uVar7 = param_1[2];
      if ((uVar7 & 3) < 3) {
        iVar5 = 7;
      }
      else {
        iVar5 = PeekChecksumStateUnderLock(&DAT_00794bf0);
      }
      pcVar14 = acStack_91c;
      iVar6 = PeekChecksumStateUnderLock(param_1 + 0xe);
      iVar6 = iVar6 + 0xc80;
      uVar4 = PeekChecksumStateUnderLock(param_1 + 0x120);
      uVar12 = PeekChecksumStateUnderLock(param_1 + 0x97);
      FUN_004372f0(iVar5 - (uVar7 & 3),uVar12,uVar4,iVar6,pcVar14);
      uVar7 = FUN_00415c60();
      GetLocalizedString(&g_localizedStringTable,uVar7 % 10 + 0x7f9);
      FUN_004382d0();
    }
    *(undefined1 *)(param_1 + 5) = 1;
  }
  iVar6 = _rand();
  iVar5 = iVar6 / 1000;
  if (((iVar6 % 1000 == 0) && (iVar5 = PacketChecksumEquals(param_1 + 0x67d,0), (char)iVar5 != '\0')
      ) && (iVar5 = FUN_0040b390(g_clientContext + 0x3b6c4,g_clientContext + 0x3b49c), (char)iVar5 != '\0'
           )) {
    Replay_AppendEvent(0x4004);
    (&g_replayEventBuffer)[g_replayEventCursor] = (char)param_1[2];
    g_replayEventCursor = g_replayEventCursor + 1;
    iVar5 = param_1[0x791];
    iVar6 = _rand();
    if (iVar5 == 0) {
      iVar5 = iVar6 % 10 + 0x7d1;
      pcVar14 = (char *)GetLocalizedString(&g_localizedStringTable,iVar5);
      do {
        cVar3 = *pcVar14;
        pcVar14 = pcVar14 + 1;
      } while (cVar3 != '\0');
      uVar4 = GetLocalizedString(&g_localizedStringTable,iVar5);
    }
    else {
      puVar13 = (undefined4 *)FUN_00415450();
      pcVar14 = (char *)*puVar13;
      do {
        cVar3 = *pcVar14;
        pcVar14 = pcVar14 + 1;
      } while (cVar3 != '\0');
      puVar13 = (undefined4 *)FUN_00415450();
      uVar4 = *puVar13;
    }
    Replay_AppendString(uVar4);
    iVar5 = Replay_FlushEvent();
  }
LAB_0047a932:
  *unaff_FS_OFFSET = local_c;
  return iVar5;
}

