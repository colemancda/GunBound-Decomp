/* State11_InBattle_ProcessPacket - 0x004b4100 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall
State11_InBattle_ProcessPacket(void *this,int payloadLen,ushort opcode,byte *payload)

{
  bool bVar1;
  char cVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  char *pcVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 uVar9;
  uint *puVar10;
  undefined *puVar11;
  byte bVar12;
  byte bVar13;
  uint uVar14;
  byte *pbVar15;
  int *piVar16;
  uint uVar17;
  int iVar18;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar19;
  undefined4 uVar20;
  byte local_9b5;
  uint local_9b4;
  int local_9b0;
  int *local_9ac;
  int local_9a8;
  int local_9a4 [2];
  char local_99c [128];
  char local_91c [128];
  undefined1 local_89c [20];
  int *local_888;
  undefined1 local_67c;
  int *local_664;
  undefined1 local_458;
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  uint local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053e03c;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  iVar6 = DAT_007934e8;
  local_9ac = this;
  if (opcode < 0x4000) {
    if (opcode == 0x3fff) {
      *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
      *(undefined2 *)(iVar6 + 0x4d4) = 0x2000;
      *(undefined2 *)(iVar6 + 0x4d6) = 0xffff;
      *(int *)(iVar6 + 0x44d0) = *(int *)(iVar6 + 0x44d0) + 2;
      SendOutgoingPacket();
      *(undefined4 *)(g_clientContext + 0x44e60) = 0xffffffff;
    }
    else if (opcode < 0x3234) {
      if (opcode == 0x3233) {
        if (*(short *)payload == 0) {
          g_pendingGameState = 9;
          g_stateChangeRequested = 0;
          DAT_0056d108 = 0;
          _DAT_007934d8 = 1;
          Replay_AppendEvent(0x8103);
          Replay_FlushEvent();
          iVar6 = g_clientContext;
          if (*(int *)(&DAT_006a64b4 + g_clientContext) != -1) {
            FUN_004eeae0();
            iVar6 = g_clientContext;
            *(undefined4 *)(&DAT_006a64b4 + g_clientContext) = 0xffffffff;
          }
          if (*(FILE **)(&g_replayFileHandle + iVar6) != (FILE *)0x0) {
            local_9b5 = 2;
            _fwrite(&local_9b5,1,1,*(FILE **)(&g_replayFileHandle + iVar6));
            _fclose(*(FILE **)(&g_replayFileHandle + g_clientContext));
            *(undefined4 *)(&g_replayFileHandle + g_clientContext) = 0;
          }
        }
        else {
          *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
          *(undefined2 *)(iVar6 + 0x4d4) = 0x2000;
          *(undefined2 *)(iVar6 + 0x4d6) = 0xffff;
          *(int *)(iVar6 + 0x44d0) = *(int *)(iVar6 + 0x44d0) + 2;
          SendOutgoingPacket();
          *(undefined4 *)(g_clientContext + 0x44e60) = 0xffffffff;
        }
      }
      else if (opcode == 0x2001) {
        if (*(short *)payload == 0) {
          g_pendingGameState = 3;
          g_stateChangeRequested = 0;
          DAT_0056d108 = 0;
          _DAT_007934d8 = 1;
          if (DAT_007934f4 == 0) {
            FUN_00404410(&DAT_00e53e88);
          }
          else {
            FUN_00405ba0();
          }
        }
      }
      else if (opcode == 0x3020) {
        iVar6 = (uint)*payload * 0xd + 0x457f1 + g_clientContext;
        pcVar5 = (char *)GetLocalizedString(&g_localizedStringTable,0x25f);
        _sprintf(local_91c,pcVar5,iVar6);
        (**(code **)(*(int *)this + 0x28))(local_91c,2,6);
        cVar2 = PeekPacketChecksumBool();
        if (cVar2 == '\x01') {
          QueueOutgoingPacketField(0xffffffff);
          FUN_004cf050(this);
          SetGuardedBool(0);
          SetGuardedBool(1);
        }
        else {
          local_9b5 = *payload;
          uVar17 = (uint)local_9b5;
          local_9b4 = uVar17;
          local_9a8 = GetPlayerRecordBySlot(g_clientContext);
          cVar2 = FUN_0040b390(g_clientContext + 0x3b6c4,g_clientContext + 0x3b49c);
          if (((cVar2 != '\0') && (uVar17 == *(uint *)((int)this + 0x10a0))) && (payload[2] != 0)) {
            Replay_AppendEvent(0x307);
            (&g_replayEventBuffer)[g_replayEventCursor] = 0xff;
            g_replayEventCursor = g_replayEventCursor + 1;
            Replay_FlushEvent();
            FUN_004cb280(this);
          }
          cVar2 = PacketChecksumEquals(g_clientContext + 0x45354,1);
          if ((cVar2 != '\0') ||
             (cVar2 = PacketChecksumEquals(g_clientContext + 0x45354,3), cVar2 != '\0')) {
            iVar6 = 0;
            if (0 < *(int *)((int)this + 0x89c)) {
              puVar10 = (uint *)((int)this + 0xca0);
LAB_004b42d0:
              if (*puVar10 != uVar17) goto code_r0x004b42d4;
              if (iVar6 < *(int *)((int)this + 0x89c) + -1) {
                puVar7 = (undefined4 *)((int)this + iVar6 * 4 + 0x8a0);
                do {
                  *puVar7 = puVar7[1];
                  puVar7[0x80] = puVar7[0x81];
                  puVar7[0x100] = puVar7[0x101];
                  iVar6 = iVar6 + 1;
                  puVar7 = puVar7 + 1;
                } while (iVar6 < *(int *)((int)this + 0x89c) + -1);
              }
              *(int *)((int)this + 0x89c) = *(int *)((int)this + 0x89c) + -1;
            }
          }
LAB_004b4324:
          local_9b0 = uVar17 * 0x224;
          iVar6 = PeekChecksumStateUnderLock(local_9b0 + 0xebef4 + g_clientContext);
          if (iVar6 == -1) {
            cVar2 = PacketChecksumEquals(g_clientContext + 0x45354,1);
            if ((cVar2 != '\0') && (*(char *)((int)this + 0x11d0) == '\0')) {
              iVar6 = PeekChecksumStateUnderLock(g_clientContext + 0x473a0);
              iVar8 = PeekChecksumStateUnderLock(&DAT_00796aa0);
              SubFromPacketChecksum((iVar6 / 2) * iVar8);
              uVar14 = 0;
              iVar8 = 0;
              iVar18 = 0;
              iVar6 = g_clientContext;
              do {
                if (((*(char *)(iVar6 + 0x5010d + uVar14) != '\0') &&
                    (*(char *)(iVar6 + 0x50126 + uVar14) == *(char *)(local_9b4 + 0x50126 + iVar6)))
                   && (uVar14 != local_9b4)) {
                  uVar9 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                  AddToPacketChecksum(uVar9);
                  uVar9 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                  iVar6 = iVar8 + 0x50196 + g_clientContext;
                  pcVar5 = (char *)GetLocalizedString(&g_localizedStringTable,0x281);
                  _sprintf(local_99c,pcVar5,iVar6,uVar9);
                  (**(code **)(*(int *)this + 0x28))(local_99c,4,3);
                  iVar6 = g_clientContext;
                }
                iVar18 = iVar18 + 0x224;
                uVar14 = uVar14 + 1;
                iVar8 = iVar8 + 0xd;
                uVar17 = local_9b4;
              } while (iVar18 < 0x1120);
            }
          }
          else {
            FUN_004cf050(this);
            iVar6 = PeekChecksumStateUnderLock(g_clientContext + 0x473a0);
            iVar8 = PeekChecksumStateUnderLock(&DAT_00796aa0);
            SubFromPacketChecksum((iVar6 / 2 + -1) * iVar8);
            if (*(char *)((int)this + 0x11d0) == '\0') {
              uVar14 = 0;
              iVar8 = 0;
              iVar18 = 0;
              iVar6 = g_clientContext;
              do {
                if (((*(char *)(iVar6 + 0x5010d + uVar14) != '\0') &&
                    (*(char *)(iVar6 + 0x50126 + uVar14) == *(char *)(local_9b4 + 0x50126 + iVar6)))
                   && (uVar14 != local_9b4)) {
                  uVar9 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                  AddToPacketChecksum(uVar9);
                  uVar9 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                  iVar6 = iVar8 + 0x50196 + g_clientContext;
                  pcVar5 = (char *)GetLocalizedString(&g_localizedStringTable,0x281);
                  _sprintf(local_91c,pcVar5,iVar6,uVar9);
                  (**(code **)(*(int *)this + 0x28))(local_91c,4,3);
                  iVar6 = g_clientContext;
                }
                iVar18 = iVar18 + 0x224;
                uVar14 = uVar14 + 1;
                iVar8 = iVar8 + 0xd;
                uVar17 = local_9b4;
              } while (iVar18 < 0x1120);
            }
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(0xffffffff);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if ((uVar17 == *(uint *)((int)this + 0x10a0)) ||
             (uVar14 = FUN_004d0dd0(), uVar17 == uVar14)) {
            cVar2 = FUN_0040b390(g_clientContext + 0x3b6c4,g_clientContext + 0x3b49c);
            if (cVar2 != '\0') {
              Replay_AppendEvent(0x8500);
              iVar6 = local_9a8;
              (&g_replayEventBuffer)[g_replayEventCursor] = local_9b5;
              g_replayEventCursor = g_replayEventCursor + 1;
              uVar4 = PeekChecksumStateUnderLock(local_9a8 + 0x90c);
              *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar4;
              g_replayEventCursor = g_replayEventCursor + 2;
              uVar4 = PeekChecksumStateUnderLock(iVar6 + 0xb30);
              *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar4;
              g_replayEventCursor = g_replayEventCursor + 2;
              uVar3 = PacketChecksumEquals(iVar6 + 0x1c54,1);
              (&g_replayEventBuffer)[g_replayEventCursor] = uVar3;
              g_replayEventCursor = g_replayEventCursor + 1;
              Replay_FlushEvent();
            }
            iVar6 = g_clientContext;
            pbVar15 = &DAT_006a9b72 + g_clientContext;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar8 = _rand();
            *pbVar15 = (byte)iVar8;
            iVar8 = _rand();
            bVar13 = *pbVar15;
            (&DAT_006a9b73)[iVar6] = (byte)iVar8;
            bVar12 = bVar13 & 7;
            bVar12 = ~('\x01' << bVar12) & (byte)iVar8 | '\0' << bVar12;
            (&DAT_006a9b73)[iVar6] = bVar12;
            (&DAT_006a9b74)[iVar6] = bVar13 + bVar12 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = g_clientContext;
            pbVar15 = &DAT_006a9b6f + g_clientContext;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar8 = _rand();
            *pbVar15 = (byte)iVar8;
            iVar8 = _rand();
            bVar13 = *pbVar15;
            (&DAT_006a9b70)[iVar6] = (byte)iVar8;
            bVar12 = '\x01' << (bVar13 & 7);
            bVar12 = ~bVar12 & (byte)iVar8 | bVar12;
            (&DAT_006a9b70)[iVar6] = bVar12;
            (&DAT_006a9b71)[iVar6] = bVar13 + bVar12 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          cVar2 = PeekPacketChecksumBool();
          if ((((cVar2 == '\x01') &&
               (cVar2 = FUN_0040b390(g_clientContext + 0x3b49c,g_clientContext + 0x3b6c4), cVar2 != '\0'))
              && (cVar2 = PeekPacketChecksumBool(), cVar2 == '\0')) &&
             ((g_currentGameState != 0xb || (cVar2 = PeekPacketChecksumBool(), cVar2 != '\x01')))) {
            FUN_00413bf0();
          }
        }
      }
    }
    else if (opcode == 0x3400) {
      cVar2 = FUN_0040b390(g_clientContext + 0x3b49c,g_clientContext + 0x3b6c4);
      if ((cVar2 != '\0') && (*(char *)((int)this + 0x11d0) != '\0')) {
        FUN_00413bf0();
      }
      if (1 < payloadLen) {
        FUN_00425a30(g_clientContext);
      }
      local_9b0 = 0;
      do {
        iVar6 = local_9b0;
        cVar2 = PeekPacketChecksumBool();
        if (cVar2 == '\x01') {
          cVar2 = FUN_0040b390(g_clientContext + 0x3b6c4,g_clientContext + 0x3b49c);
          if (cVar2 == '\0') {
            Replay_AppendEvent(0xc302);
            iVar8 = g_clientContext;
            (&g_replayEventBuffer)[g_replayEventCursor] = (char)iVar6;
            g_replayEventCursor = g_replayEventCursor + 1;
            uVar9 = PeekChecksumStateUnderLock(iVar8 + 0xeba98);
            *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar9;
            g_replayEventCursor = g_replayEventCursor + 4;
            if (iVar6 == 0xe) {
              uVar9 = FUN_0045d360(0);
              *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar9;
              g_replayEventCursor = g_replayEventCursor + 4;
            }
            uVar9 = PeekChecksumStateUnderLock(g_clientContext + 0x3b6c4);
            iVar8 = g_clientContext;
            *(undefined4 *)(&DAT_006a7704 + g_clientContext) = uVar9;
            uVar9 = PeekChecksumStateUnderLock(iVar8 + 0x3b6c4);
            FUN_004e7140(uVar9);
          }
          else {
            iVar8 = iVar6 * 8 + g_clientContext;
            *(undefined4 *)(&DAT_006a7670 + iVar8) = 0;
            *(undefined4 *)((int)(&DAT_006a7670 + iVar8) + 4) = 0;
            FUN_004d2130(iVar6);
            FUN_004261d0();
            local_9a8 = 0xc302;
            FUN_004e8a70();
            iVar6 = local_9b0;
            if (local_9b4 != DAT_00e9af14) {
              FUN_004e87b0(&DAT_00e9af10,&local_9ac,local_9b4);
              iVar6 = local_9b0;
            }
          }
        }
        local_9b0 = iVar6 + 1;
      } while (local_9b0 < 0x10);
    }
    goto LAB_004b541a;
  }
  if (opcode == 0x4102) {
    local_9b5 = *payload;
    piVar16 = *(int **)(payload + 1);
    uVar17 = (uint)local_9b5;
    local_9ac = piVar16;
    iVar6 = GetPlayerRecordBySlot(g_clientContext);
    if (iVar6 != 0) {
      uVar14 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
      iVar8 = g_clientContext;
      if ((uVar17 == uVar14) &&
         (cVar2 = PeekPacketChecksumBool(), iVar18 = DAT_007934e8, iVar8 = g_clientContext, cVar2 != '\0')) {
        *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
        *(undefined2 *)(iVar18 + 0x4d4) = 0x2000;
        *(undefined2 *)(iVar18 + 0x4d6) = 0xffff;
        *(int *)(iVar18 + 0x44d0) = *(int *)(iVar18 + 0x44d0) + 2;
        SendOutgoingPacket();
        FUN_00422f10(*(undefined4 *)(g_clientContext + 0x44e60));
        iVar8 = g_clientContext;
        *(undefined4 *)(g_clientContext + 0x44e60) = 0xffffffff;
        piVar16 = local_9ac;
      }
      if (((uint)piVar16 & 0xf000) == 0xf000) {
        cVar2 = FUN_0040b390(iVar8 + 0x3b6c4,iVar8 + 0x3b49c);
        if (cVar2 != '\0') {
          Replay_AppendEvent(0x8500);
          (&g_replayEventBuffer)[g_replayEventCursor] = local_9b5;
          g_replayEventCursor = g_replayEventCursor + 1;
          uVar4 = PeekChecksumStateUnderLock(iVar6 + 0x90c);
          *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar4;
          g_replayEventCursor = g_replayEventCursor + 2;
          uVar4 = PeekChecksumStateUnderLock(iVar6 + 0xb30);
          *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar4;
          g_replayEventCursor = g_replayEventCursor + 2;
          uVar3 = PacketChecksumEquals(iVar6 + 0x1c54,1);
          (&g_replayEventBuffer)[g_replayEventCursor] = uVar3;
          g_replayEventCursor = g_replayEventCursor + 1;
          Replay_FlushEvent();
        }
        cVar2 = PacketChecksumEquals(g_clientContext + 0x45354,1);
        if ((cVar2 != '\0') && (cVar2 = PeekPacketChecksumBool(), cVar2 == '\0')) {
          if (0 < *(int *)((int)this + 0x10b0)) {
            iVar6 = *(int *)((int)this + 0x10b0);
            bVar1 = false;
            do {
              if (local_9b5 == *(byte *)((int)this + 0x10a8)) {
                bVar1 = true;
              }
              iVar6 = iVar6 + -1;
            } while (iVar6 != 0);
            if (bVar1) goto LAB_004b541a;
          }
          cVar2 = *(char *)(uVar17 + 0x50126 + g_clientContext);
          if (cVar2 == '\0') {
            iVar6 = *(int *)this;
            uVar20 = 8;
            uVar19 = 3;
            uVar9 = GetLocalizedString(&g_localizedStringTable,0x25c);
            (**(code **)(iVar6 + 0x28))(uVar9,uVar19,uVar20);
            FUN_0040b060();
            cVar2 = PacketChecksumLessThan(&DAT_0067e3d0 + g_clientContext,0);
          }
          else {
            if (cVar2 != '\x01') goto LAB_004b541a;
            iVar6 = *(int *)this;
            uVar20 = 8;
            uVar19 = 3;
            uVar9 = GetLocalizedString(&g_localizedStringTable,0x25d);
            (**(code **)(iVar6 + 0x28))(uVar9,uVar19,uVar20);
            FUN_0040b060();
            cVar2 = PacketChecksumLessThan(&DAT_0067e5f4 + g_clientContext,0);
          }
          if (cVar2 != '\0') {
            QueueOutgoingPacketField(0);
          }
        }
      }
    }
    goto LAB_004b541a;
  }
  if (opcode != 0x4410) {
    if (opcode == 0x4413) {
      RemoveWidget();
      RemoveWidget();
      RemoveWidget();
      RemoveWidget();
      RemoveWidget();
      RemoveWidget();
      RemoveWidget();
      RemoveWidget();
      *(undefined1 *)((int)this + 0x11d0) = 1;
      *(undefined4 *)((int)this + 0x11d4) = 0;
      CreateButtonWidget(&DAT_00e9be90,0,0x10,0x3f8,s_b_result_confirm_00554074,0x29f,0x1b9,0x67,
                         0x2d,1,0);
      iVar6 = g_clientContext;
      pbVar15 = (byte *)(g_clientContext + 0x62152);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = _rand();
      *pbVar15 = (byte)iVar8;
      iVar8 = _rand();
      bVar13 = *pbVar15;
      *(byte *)(iVar6 + 0x62153) = (byte)iVar8;
      bVar12 = '\x01' << (bVar13 & 7);
      bVar12 = ~bVar12 & (byte)iVar8 | bVar12;
      *(byte *)(iVar6 + 0x62153) = bVar12;
      *(byte *)(iVar6 + 0x62154) = bVar13 + bVar12 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    goto LAB_004b541a;
  }
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 != '\0') goto LAB_004b541a;
  SetGuardedBool(1);
  local_67c = 0;
  local_888 = (int *)0x0;
  EncodeOutgoingPacketField(0);
  local_4 = 0;
  local_458 = 0;
  local_664 = (int *)0x0;
  EncodeOutgoingPacketField(0);
  local_4 = 1;
  EncodeChecksumStateXored();
  EncodeChecksumStateXored();
  cVar2 = PacketChecksumEquals(g_clientContext + 0x45354,3);
  if (cVar2 == '\0') {
LAB_004b4d38:
    uVar9 = PeekChecksumStateUnderLock(g_clientContext + 0x473a0);
    switch(uVar9) {
    case 1:
    case 2:
      EncodeChecksumStateXored();
      break;
    case 3:
    case 4:
      EncodeChecksumStateXored();
      break;
    case 5:
    case 6:
      EncodeChecksumStateXored();
      break;
    case 7:
    case 8:
      EncodeChecksumStateXored();
      break;
    default:
      EncodeChecksumStateXored();
    }
    EncodeChecksumStateXored();
  }
  else {
    if (*(char *)(g_clientContext + 0x62155) == '\0') {
      uVar9 = PeekChecksumStateUnderLock(&DAT_00796aa0);
      puVar11 = &DAT_0067e3d0 + g_clientContext;
    }
    else {
      uVar9 = PeekChecksumStateUnderLock(&DAT_00796aa0);
      puVar11 = &DAT_0067e5f4 + g_clientContext;
    }
    cVar2 = PacketChecksumGreaterEqual(puVar11,uVar9);
    if (cVar2 != '\0') goto LAB_004b4d38;
  }
  local_9b4 = 0;
  do {
    iVar6 = GetPlayerRecordBySlot(g_clientContext);
    if (iVar6 != 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = _rand();
      *(char *)(iVar6 + 0x8ba8) = (char)iVar8;
      iVar8 = _rand();
      local_9b5 = *(byte *)(iVar6 + 0x8ba8);
      *(byte *)(iVar6 + 0x8ba9) = (byte)iVar8;
      bVar13 = ~('\x01' << (local_9b5 & 7)) & (byte)iVar8 | '\0' << (local_9b5 & 7);
      *(byte *)(iVar6 + 0x8ba9) = bVar13;
      *(byte *)(iVar6 + 0x8baa) = local_9b5 + bVar13 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = _rand();
      *(char *)(iVar6 + 0x8bb1) = (char)iVar8;
      iVar8 = _rand();
      local_9b5 = *(byte *)(iVar6 + 0x8bb1);
      *(byte *)(iVar6 + 0x8bb2) = (byte)iVar8;
      bVar13 = ~('\x01' << (local_9b5 & 7)) & (byte)iVar8 | '\0' << (local_9b5 & 7);
      *(byte *)(iVar6 + 0x8bb2) = bVar13;
      *(byte *)(iVar6 + 0x8bb3) = local_9b5 + bVar13 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    local_9b4 = local_9b4 + 1;
  } while ((int)local_9b4 < 8);
  local_9b4 = 0;
  local_9b0 = 0;
  iVar6 = g_clientContext;
  do {
    if (((*(char *)(iVar6 + 0x5010d + local_9b4) != '\0') &&
        (*(char *)(iVar6 + 0x50126 + local_9b4) == *(char *)(iVar6 + 0x62155))) &&
       (iVar8 = GetPlayerRecordBySlot(iVar6), iVar6 = g_clientContext, iVar8 != 0)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar9 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_9a8 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_9a4[0] = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_004368f0(local_9a4[0],local_9a8,uVar9);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_9a4[0] = local_9b0 + 0x5113c + g_clientContext;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_9a4[0] = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar9 = EncodeChecksumDeltaMul(local_89c,local_230,local_9a4[0] + iVar6);
      local_4 = 2;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_9a4[0] = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeChecksumDeltaDiv(uVar9,local_454,local_9a4[0]);
      local_4 = 3;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar9 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = iVar8 + 0xae15;
      pcVar5 = (char *)GetLocalizedString(&g_localizedStringTable,0x25e);
      _sprintf(local_99c,pcVar5,iVar8,uVar9);
      local_4 = 2;
      ScrubChecksumGuard();
      local_4 = 1;
      ScrubChecksumGuard();
      (**(code **)(*local_9ac + 0x28))(local_99c,4,3);
      iVar6 = g_clientContext;
    }
    piVar16 = local_664;
    local_9b0 = local_9b0 + 0x1120;
    local_9b4 = local_9b4 + 1;
  } while (local_9b0 < 0x8900);
  local_4 = local_4 & 0xffffff00;
  if (local_664 != (int *)0x0) {
    ScrambleChecksumGuardBytes();
    local_9ac = piVar16;
    TreeLowerBound(local_9a4);
  }
  piVar16 = local_888;
  local_4 = 0xffffffff;
  if (local_888 != (int *)0x0) {
    ScrambleChecksumGuardBytes();
    local_9ac = piVar16;
    TreeLowerBound(local_9a4);
  }
LAB_004b541a:
  *unaff_FS_OFFSET = local_c;
  return;
code_r0x004b42d4:
  iVar6 = iVar6 + 1;
  puVar10 = puVar10 + 1;
  if (*(int *)((int)this + 0x89c) <= iVar6) goto LAB_004b4324;
  goto LAB_004b42d0;
}

