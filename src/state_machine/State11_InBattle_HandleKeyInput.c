/* State11_InBattle_HandleKeyInput - 0x004b82b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall State11_InBattle_HandleKeyInput(int param_1,int param_2,int param_3,uint param_4)

{
  undefined2 *puVar1;
  int iVar2;
  char cVar3;
  undefined1 uVar4;
  short sVar5;
  undefined2 uVar6;
  int iVar7;
  uint uVar8;
  DWORD DVar9;
  undefined4 uVar10;
  char acStack_80 [128];
  
  iVar7 = g_clientContext;
  if (param_2 != 0) {
    if (param_2 == 0x32) {
      switch(param_3) {
      case 0x1d:
        if (((&DAT_006a6499)[g_clientContext] != '\0') && ((&DAT_006a6499)[g_clientContext] != '\0')) {
          (&DAT_006a6499)[g_clientContext] = 0;
          (&DAT_006a6498)[iVar7] = 0;
          *(undefined4 *)(&DAT_006a64a0 + iVar7) = 3;
          *(undefined4 *)(&DAT_006a649c + iVar7) = 0xffffffff;
        }
        if ((&DAT_006a6481)[iVar7] == '\0') {
          if ((&DAT_006a648d)[iVar7] != '\x01') {
            *(undefined4 *)(&DAT_006a6494 + iVar7) = 0;
            (&DAT_006a648d)[iVar7] = 1;
            *(undefined4 *)(&DAT_006a6490 + iVar7) = 1;
            return;
          }
          return;
        }
        return;
      default:
        return;
      case 0x39:
        cVar3 = PacketChecksumEquals(g_clientContext + 0x59190,0xffffffff);
        if ((((cVar3 != '\0') && ((&DAT_006a6481)[g_clientContext] == '\0')) && (DAT_007934c4 == '\0'))
           && (DAT_007933b8 == '\x01')) {
          QueueOutgoingPacketField(param_4 + 0x32);
        }
        if ((&DAT_005f2f40)[g_clientContext] != '\x02') {
          return;
        }
        cVar3 = PeekPacketChecksumBool();
        if (cVar3 == '\0') {
          return;
        }
        if (*(char *)(param_1 + 0x11c5) == '\0') {
          cVar3 = PeekPacketChecksumBool();
          if (cVar3 != '\x01') {
            return;
          }
          if ((&DAT_006a6481)[g_clientContext] == '\0') {
            *(undefined1 *)(param_1 + 0x11c5) = 1;
            return;
          }
          return;
        }
        return;
      case 0x3b:
      case 0x3c:
      case 0x3d:
      case 0x3e:
      case 0x3f:
      case 0x40:
        goto switchD_004b83e0_caseD_3b;
      case 0x41:
        cVar3 = PacketChecksumNotEquals(g_clientContext + 0x45354,2);
        if (cVar3 != '\0') {
          return;
        }
        cVar3 = PeekPacketChecksumBool();
        if (cVar3 != '\0') {
          cVar3 = PeekPacketChecksumBool();
          if (cVar3 != '\0') {
            cVar3 = PeekPacketChecksumBool();
            if (cVar3 != '\0') {
              QueueBroadcastEvent(0x8405);
              BroadcastQueuedEvent();
            }
            InvokeWidget(0);
            return;
          }
          return;
        }
        return;
      }
    }
    if (param_2 != 0x33) {
      return;
    }
    if (param_3 == 0x1d) {
      if ((&DAT_006a648d)[g_clientContext] == '\0') {
        return;
      }
      if ((&DAT_006a648d)[g_clientContext] != '\0') {
        (&DAT_006a648d)[g_clientContext] = 0;
        (&DAT_006a648c)[iVar7] = 0;
        *(undefined4 *)(&DAT_006a6494 + iVar7) = 1;
        *(undefined4 *)(&DAT_006a6490 + iVar7) = 0xffffffff;
        return;
      }
      return;
    }
    if (param_3 == 0x39) {
      cVar3 = PacketChecksumEquals(g_clientContext + 0x593b4,0xffffffff);
      if (cVar3 == '\0') {
        return;
      }
      if ((&DAT_006a6481)[g_clientContext] == '\0') {
        if (DAT_007933b8 == '\x01') {
          QueueOutgoingPacketField(param_4);
          return;
        }
        return;
      }
      return;
    }
    if (param_3 != 0x42) {
      return;
    }
    cVar3 = FUN_00406400();
    if (cVar3 == '\x01') {
      FUN_004f2da0(0,0,3);
      return;
    }
    return;
  }
  if (1000000 < param_4) {
    return;
  }
  if (param_4 == 1000000) {
    if (g_stateChangeInProgress != 0x2e) {
      return;
    }
    uVar10 = DecodeGuardedBool();
    cVar3 = CheckGuardedBoolAnd(uVar10);
    iVar7 = DAT_007934e8;
    if (cVar3 == '\0') {
      *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
      *(undefined2 *)(iVar7 + 0x4d4) = 0x2000;
      *(undefined2 *)(iVar7 + 0x4d6) = 0xffff;
      *(int *)(iVar7 + 0x44d0) = *(int *)(iVar7 + 0x44d0) + 2;
      SendOutgoingPacket(iVar7);
      FUN_00422f10(*(undefined4 *)(g_clientContext + 0x44e60));
      *(undefined4 *)(g_clientContext + 0x44e60) = 0xffffffff;
      return;
    }
    SetGuardedBool(1);
    QueueBroadcastEvent(0x8402);
    uVar6 = PeekChecksumStateUnderLock(*(int *)(g_clientContext + 0x621e0) + 0x90c);
    *(undefined2 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar6;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
    uVar6 = PeekChecksumStateUnderLock(*(int *)(g_clientContext + 0x621e0) + 0xb30);
    *(undefined2 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar6;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
    uVar4 = PacketChecksumEquals(*(int *)(g_clientContext + 0x621e0) + 0x1c54,1);
    (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = uVar4;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    BroadcastQueuedEvent();
    iVar2 = DAT_007934e8;
    *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
    *(undefined2 *)(iVar2 + 0x4d4) = 0x4100;
    *(undefined4 *)(iVar2 + 0x4d6) = 0xf001;
    iVar7 = *(int *)(iVar2 + 0x44d0);
    *(int *)(iVar2 + 0x44d0) = iVar7 + 4;
    *(undefined1 *)(iVar7 + 0x4d4 + iVar2) = 0;
    *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 1;
    SendOutgoingPacket(iVar2);
    uVar10 = DecodeGuardedBool();
    cVar3 = CheckGuardedBoolAnd(uVar10);
    if (cVar3 == '\0') {
      return;
    }
    SetGuardedBool(0);
    SetGuardedBool(0);
    QueueBroadcastEvent(0xc301);
    (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 1;
    puVar1 = (undefined2 *)(&DAT_00e9aacd + g_dwBroadcastEventCursor);
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *puVar1 = 60000;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
    FUN_0041f200(0);
    goto LAB_004b8aeb;
  }
  switch(param_4) {
  case 0:
    if (*(char *)(param_1 + 0x11ac) == '\0') {
      *(undefined1 *)(param_1 + 0x11ac) = 1;
      CreateButtonWidget(&DAT_00e9be90,0,0xc,0x3f4,s_b_option_cancel_005569b0,0xf8,0x35,0x16,0x14,1,
                         0);
      if ((*(int *)(param_1 + 4) < 0xe11) && (uVar8 = PeekPacketChecksumBool(), (char)uVar8 != '\0')) {
        uVar8 = uVar8 & 0xffffff00;
      }
      else {
        uVar8 = 1;
      }
      CreateButtonWidget(&DAT_00e9be90,0,0xd,0x3f5,s_b_option_exitgame_0055699c,0x1b,0x198,0x4a,0x1a
                         ,uVar8,0);
      CreateButtonWidget(&DAT_00e9be90,0,0xe,0x3f6,s_b_option_confirm_00556988,0xbb,0x198,0x4a,0x1a,
                         1,0);
      iVar7 = g_clientContext;
      *(undefined *)(param_1 + 0x11ad) = (&DAT_005f2f40)[g_clientContext];
      *(undefined4 *)(param_1 + 0x11b0) = *(undefined4 *)(&DAT_005f2f44 + iVar7);
      *(undefined *)(param_1 + 0x11b4) = (&DAT_005f2f48)[iVar7];
      *(undefined4 *)(param_1 + 0x11b8) = *(undefined4 *)(&DAT_005f2f4c + iVar7);
      *(undefined4 *)(param_1 + 0x11bc) = *(undefined4 *)(&DAT_005f2f50 + iVar7);
      *(undefined *)(param_1 + 0x11c0) = (&DAT_005f2f54)[iVar7];
      *(undefined *)(param_1 + 0x11c1) = (&DAT_005f2f55)[iVar7];
      FUN_004eeb10();
      FUN_004eeb30();
      return;
    }
    *(undefined1 *)(param_1 + 0x11ac) = 0;
    RemoveWidget();
    RemoveWidget();
    RemoveWidget();
    iVar7 = g_clientContext;
    (&DAT_005f2f40)[g_clientContext] = *(undefined1 *)(param_1 + 0x11ad);
    *(undefined4 *)(&DAT_005f2f44 + iVar7) = *(undefined4 *)(param_1 + 0x11b0);
    (&DAT_005f2f48)[iVar7] = *(undefined1 *)(param_1 + 0x11b4);
    *(undefined4 *)(&DAT_005f2f4c + iVar7) = *(undefined4 *)(param_1 + 0x11b8);
    *(undefined4 *)(&DAT_005f2f50 + iVar7) = *(undefined4 *)(param_1 + 0x11bc);
    (&DAT_005f2f54)[iVar7] = *(undefined1 *)(param_1 + 0x11c0);
    (&DAT_005f2f55)[iVar7] = *(undefined1 *)(param_1 + 0x11c1);
    if (*(int *)(param_1 + 0x11b8) == 0) {
      if ((DAT_0079354a != '\0') && (DAT_0079354a = '\0', DAT_00793549 != '\0')) {
        (**(code **)(*(int *)*DAT_00793554 + 0xc))();
        DAT_00793568 = 0;
      }
    }
    else {
      if (DAT_0079354a == '\0') {
        DAT_0079354a = DAT_00793549 != '\0';
        _sprintf(acStack_80,s_stage_d_mp3_005569c0,(uint)*(byte *)(iVar7 + 0x475c4));
        cVar3 = PlayMusicTrack(1,(byte *)acStack_80);
        if (cVar3 == '\0') {
          iVar7 = _rand();
          _sprintf(acStack_80,s_stage_d_mp3_005569c0,iVar7 % 6 + 1);
          PlayMusicTrack(1,(byte *)acStack_80);
        }
      }
      FUN_004eeb10();
    }
    FUN_004eeb70();
    if (*(int *)(param_1 + 0x11bc) != 0) {
      FUN_004eeb30();
      return;
    }
    break;
  case 1:
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 == '\0') {
      return;
    }
    *(undefined4 *)(g_clientContext + 0xebef0) = 0xfffffffd;
    SetGuardedBool(0);
    SetGuardedBool(0);
    RemoveWidget();
    CreateButtonWidget(&DAT_00e9be90,0,2,0x3ea,s_b_play_weapon2_00554154,0x2f,0x232,0x23,0x22,1,0);
    cVar3 = PacketChecksumGreaterThan(*(int *)(g_clientContext + 0x621e0) + 0xc080,4);
    if ((cVar3 == '\0') || (*(short *)(*(int *)(g_clientContext + 0x621e0) + 0xbfbc) != 0)) {
      uVar10 = 0;
    }
    else {
      uVar10 = 1;
    }
    CreateButtonWidget(&DAT_00e9be90,0,0x12,0x3fa,s_b_play_weapon3_00554144,0x58,0x232,0x23,0x22,
                       uVar10,0);
    uVar8 = PacketChecksumGreaterThan(*(int *)(g_clientContext + 0x621e0) + 0xc080,4);
    if (((char)uVar8 == '\0') ||
       (uVar8 = *(uint *)(g_clientContext + 0x621e0), *(short *)(uVar8 + 0xbfbc) != 0)) {
      uVar8 = uVar8 & 0xffffff00;
    }
    else {
      uVar8 = CONCAT31((int3)(uVar8 >> 8),1);
    }
    InvokeWidget(uVar8);
    QueueBroadcastEvent(0x4005);
    iVar7 = g_clientContext;
    (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 0;
    iVar7 = *(int *)(iVar7 + 0x621e0);
    goto LAB_004b8ad4;
  case 2:
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 == '\0') {
      return;
    }
    *(undefined4 *)(g_clientContext + 0xebef0) = 0xffffffe8;
    SetGuardedBool(1);
    SetGuardedBool(0);
    RemoveWidget();
    CreateButtonWidget(&DAT_00e9be90,0,1,0x3e9,s_b_play_weapon1_00554164,6,0x232,0x23,0x22,1,0);
    cVar3 = PacketChecksumGreaterThan(*(int *)(g_clientContext + 0x621e0) + 0xc080,4);
    if ((cVar3 == '\0') || (*(short *)(*(int *)(g_clientContext + 0x621e0) + 0xbfbc) != 0)) {
      uVar10 = 0;
    }
    else {
      uVar10 = 1;
    }
    CreateButtonWidget(&DAT_00e9be90,0,0x12,0x3fa,s_b_play_weapon3_00554144,0x58,0x232,0x23,0x22,
                       uVar10,0);
    cVar3 = PacketChecksumGreaterThan(*(int *)(g_clientContext + 0x621e0) + 0xc080,4);
    if ((cVar3 == '\0') || (*(short *)(*(int *)(g_clientContext + 0x621e0) + 0xbfbc) != 0)) {
      uVar10 = 0;
    }
    else {
      uVar10 = 1;
    }
    InvokeWidget(uVar10);
    QueueBroadcastEvent(0x4005);
    iVar7 = g_clientContext;
    (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 1;
    iVar7 = *(int *)(iVar7 + 0x621e0);
LAB_004b8ad4:
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    uVar4 = PacketChecksumEquals(iVar7 + 0x1c54,1);
LAB_004b8ad9:
    (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = uVar4;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
LAB_004b8aeb:
    BroadcastQueuedEvent();
    return;
  case 3:
    if ((((*(int *)(&DAT_005f3768 + g_clientContext) != 1) &&
         (*(int *)(&DAT_005f3768 + g_clientContext) != 2)) && (cVar3 = PeekPacketChecksumBool(), cVar3 != '\0'))
       && ((cVar3 = PeekPacketChecksumBool(), cVar3 != '\0' && (cVar3 = PeekPacketChecksumBool(), cVar3 != '\0')))) {
      InvokeWidget(0);
      SetGuardedBool(0);
      QueueBroadcastEvent(0x8402);
      uVar6 = PeekChecksumStateUnderLock(*(int *)(g_clientContext + 0x621e0) + 0x90c);
      *(undefined2 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar6;
      g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
      uVar6 = PeekChecksumStateUnderLock(*(int *)(g_clientContext + 0x621e0) + 0xb30);
      iVar7 = g_clientContext;
      *(undefined2 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar6;
      g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
      uVar4 = PacketChecksumEquals(*(int *)(iVar7 + 0x621e0) + 0x1c54,1);
      (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = uVar4;
      g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
      BroadcastQueuedEvent();
      cVar3 = DecodeGuardedBool();
      if (cVar3 != '\0') {
        SetGuardedBool(0);
        SetGuardedBool(0);
        SetGuardedBool(1);
        QueueBroadcastEvent(0xc301);
        (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 1;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
        uVar6 = FUN_0045d360(1);
        *(undefined2 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar6;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        FUN_0041f200(0);
        BroadcastQueuedEvent();
        DVar9 = GetTickCount();
        QueueOutgoingPacketField(DVar9);
        return;
      }
    }
    break;
  case 4:
    RemoveWidget();
    CreateButtonWidget(&DAT_00e9be90,0,5,0x3ed,s_b_play_team_00554114,0xa8,0x219,0x1d,0x10,1,0);
    *(undefined1 *)(g_clientContext + 0xebee5) = 1;
    return;
  case 5:
    RemoveWidget();
    CreateButtonWidget(&DAT_00e9be90,0,4,0x3ec,s_b_play_all_0055412c,0xa8,0x219,0x1d,0x10,1,0);
    *(undefined1 *)(g_clientContext + 0xebee5) = 0;
    return;
  case 8:
    RemoveWidget();
    RemoveWidget();
    FUN_004e1f70();
    *(undefined4 *)(&DAT_006a73c8 + g_clientContext) = 1;
    return;
  case 9:
    RemoveWidget();
    RemoveWidget();
    cVar3 = PacketChecksumEquals(&DAT_006a64c4 + g_clientContext,6);
    if ((cVar3 == '\0') &&
       (cVar3 = PacketChecksumEquals(&DAT_006a64c4 + g_clientContext,7), iVar7 = g_clientContext,
       cVar3 == '\0')) {
      *(undefined1 *)(param_1 + 0x92) = 1;
      (&DAT_006a7758)[iVar7] = 0;
      *(undefined4 *)(&DAT_006a73c8 + iVar7) = 3;
      if (*(char *)(param_1 + 0x11d0) != '\0') {
        return;
      }
      CreateButtonWidget(&DAT_00e9be90,0,10,0x3f2,s_b_slot_cancel_005540d0,0x1e2,0x201,0x34,0xe,1,0)
      ;
      return;
    }
    *(undefined4 *)(&DAT_006a73c8 + g_clientContext) = 1;
    FUN_004e1f70();
    QueueBroadcastEvent(0x8404);
    sVar5 = PeekChecksumStateUnderLock(g_clientContext + 0xeba98);
    iVar7 = g_clientContext;
    *(short *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = sVar5 + 4;
    puVar1 = (undefined2 *)(&DAT_00e9aace + g_dwBroadcastEventCursor);
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
    *puVar1 = 0xffec;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
    uVar4 = PeekChecksumStateUnderLock(&DAT_006a64c4 + iVar7);
    (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = uVar4;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    uVar4 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
    goto LAB_004b8ad9;
  case 10:
    RemoveWidget();
    *(undefined1 *)(param_1 + 0x92) = 0;
    FUN_004e1f70();
    iVar7 = g_clientContext;
    (&DAT_006a7758)[g_clientContext] = 1;
    *(undefined4 *)(&DAT_006a73c8 + iVar7) = 1;
    return;
  case 0xc:
    *(undefined1 *)(param_1 + 0x11ac) = 0;
    RemoveWidget();
    RemoveWidget();
    RemoveWidget();
    iVar7 = g_clientContext;
    (&DAT_005f2f40)[g_clientContext] = *(undefined1 *)(param_1 + 0x11ad);
    *(undefined4 *)(&DAT_005f2f44 + iVar7) = *(undefined4 *)(param_1 + 0x11b0);
    (&DAT_005f2f48)[iVar7] = *(undefined1 *)(param_1 + 0x11b4);
    *(undefined4 *)(&DAT_005f2f4c + iVar7) = *(undefined4 *)(param_1 + 0x11b8);
    *(undefined4 *)(&DAT_005f2f50 + iVar7) = *(undefined4 *)(param_1 + 0x11bc);
    (&DAT_005f2f54)[iVar7] = *(undefined1 *)(param_1 + 0x11c0);
    (&DAT_005f2f55)[iVar7] = *(undefined1 *)(param_1 + 0x11c1);
    if (*(int *)(param_1 + 0x11b8) == 0) {
      if ((DAT_0079354a != '\0') && (DAT_0079354a = '\0', DAT_00793549 != '\0')) {
        (**(code **)(*(int *)*DAT_00793554 + 0xc))();
        DAT_00793568 = 0;
      }
    }
    else {
      if (DAT_0079354a == '\0') {
        DAT_0079354a = DAT_00793549 != '\0';
        _sprintf(acStack_80,s_stage_d_mp3_005569c0,(uint)*(byte *)(iVar7 + 0x475c4));
        cVar3 = PlayMusicTrack(1,(byte *)acStack_80);
        if (cVar3 == '\0') {
          iVar7 = _rand();
          _sprintf(acStack_80,s_stage_d_mp3_005569c0,iVar7 % 6 + 1);
          PlayMusicTrack(1,(byte *)acStack_80);
        }
      }
      FUN_004eeb10();
    }
    FUN_004eeb70();
    if (*(int *)(param_1 + 0x11bc) != 0) {
      FUN_004eeb30();
      return;
    }
    break;
  case 0xd:
    uVar10 = DecodeGuardedBool();
    cVar3 = CheckGuardedBoolAnd(uVar10);
    if ((cVar3 == '\0') &&
       (cVar3 = PacketChecksumEquals(g_clientContext + 0x45354,1), iVar7 = DAT_007934e8, cVar3 == '\0')
       ) {
      *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
      *(undefined2 *)(iVar7 + 0x4d4) = 0x2000;
      *(undefined2 *)(iVar7 + 0x4d6) = 0xffff;
      *(int *)(iVar7 + 0x44d0) = *(int *)(iVar7 + 0x44d0) + 2;
      SendOutgoingPacket(iVar7);
      FUN_00422f10(*(undefined4 *)(g_clientContext + 0x44e60));
      *(undefined4 *)(g_clientContext + 0x44e60) = 0xffffffff;
      return;
    }
    ShowErrorDialog(0);
    return;
  case 0xe:
    *(undefined1 *)(param_1 + 0x11ac) = 0;
    RemoveWidget();
    RemoveWidget();
    RemoveWidget();
    return;
  case 0x10:
    InvokeWidget(0);
    iVar7 = DAT_007934e8;
    *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3232;
    *(undefined4 *)(iVar7 + 0x44d0) = 6;
    SendOutgoingPacket(iVar7);
    return;
  case 0x11:
    cVar3 = PacketChecksumNotEquals(g_clientContext + 0x45354,2);
    if (((cVar3 == '\0') && (cVar3 = PeekPacketChecksumBool(), cVar3 != '\0')) &&
       (cVar3 = PeekPacketChecksumBool(), cVar3 != '\0')) {
      cVar3 = PeekPacketChecksumBool();
      if (cVar3 != '\0') {
        QueueBroadcastEvent(0x8405);
        BroadcastQueuedEvent();
      }
      InvokeWidget(0);
      return;
    }
    break;
  case 0x12:
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 != '\0') {
      SetGuardedBool(1);
      RemoveWidget();
      CreateButtonWidget(&DAT_00e9be90,0,1,0x3e9,s_b_play_weapon1_00554164,6,0x232,0x23,0x22,1,0);
      CreateButtonWidget(&DAT_00e9be90,0,2,0x3ea,s_b_play_weapon2_00554154,0x2f,0x232,0x23,0x22,1,0)
      ;
      return;
    }
  }
  return;
switchD_004b83e0_caseD_3b:
  cVar3 = PeekPacketChecksumBool();
  cVar3 = CheckGuardedBoolAnd('\x01' - (cVar3 != '\0'));
  if (cVar3 == '\0') {
    return;
  }
  cVar3 = PeekPacketChecksumBool();
  if (cVar3 != '\x01') {
    return;
  }
  if (*(char *)(param_1 + 0x10bc) != '\x01') {
    return;
  }
  cVar3 = PacketChecksumNotEquals(g_clientContext + 0xebcbc,6);
  if (cVar3 != '\0') {
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 != '\0') {
      uVar10 = FUN_00420600(g_clientContext);
      FUN_004cbda0(param_1,uVar10);
      return;
    }
    iVar7 = FUN_00420600(g_clientContext);
    if (*(int *)(g_clientContext + 0xf0374) == iVar7) {
      *(undefined4 *)(g_clientContext + 0xf0374) = 0xffffffff;
      return;
    }
    *(int *)(g_clientContext + 0xf0374) = iVar7;
    return;
  }
  return;
}

