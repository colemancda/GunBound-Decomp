/* State09_ReadyRoom_ProcessBattleAction - 0x004d4ea0 in the original binary.
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


void __thiscall State09_ReadyRoom_ProcessBattleAction(void *this,int packetBuf,int packetLen)

{
  byte bVar1;
  ushort uVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  char *pcVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  byte *pbVar10;
  byte *pbVar11;
  int iVar12;
  int iVar13;
  char local_488 [128];
  byte local_408;
  byte local_407 [2];
  byte abStack_405 [1025];
  
  iVar4 = g_clientContext;
  bVar1 = *(byte *)(packetBuf + 5);
  uVar2 = *(ushort *)(packetBuf + 2);
  uVar9 = packetLen - 0x21;
  pbVar10 = (byte *)(packetBuf + 0x21);
  if (bVar1 < 8) {
    if (uVar2 < 0x8101) {
      if (uVar2 == 0x8100) {
        uVar7 = (uint)bVar1;
        uVar9 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        if (uVar7 == uVar9) {
          RefreshReadyRoomControls(this,1,0);
          RefreshTeamSlotHighlights();
        }
        cVar3 = *(char *)(g_clientContext + 0x458fc + uVar7 * 2);
        if ((cVar3 == -1) || ('\x10' < cVar3)) {
          uVar5 = FindPreloadedTextureByName(s_rider_00553f98);
          pcVar6 = &DAT_00553f90;
        }
        else {
          _sprintf(local_488,s_tank_d_00553fa0,cVar3 + 1);
          uVar5 = FindPreloadedTextureByName(local_488);
          pcVar6 = s_normal_00552230;
        }
        *(undefined4 *)(*(int *)((int)this + uVar7 * 8 + 0x6fc) + 0x1c) = uVar5;
        (**(code **)(**(int **)((int)this + uVar7 * 8 + 0x6fc) + 4))(pcVar6);
        (**(code **)(**(int **)((int)this + uVar7 * 8 + 0x700) + 4))(s_normal_00552230);
        return;
      }
      if (uVar2 < 0x8003) {
        if (0x8000 < uVar2) {
          uVar9 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
          if (bVar1 == uVar9) {
            RefreshReadyRoomControls(this,1,0);
          }
          uVar9 = (uint)*(byte *)(g_clientContext + 0x45124);
          PeekChecksumStateUnderLock(g_clientContext + 0x44efc);
          ApplyRoomSettings(this,uVar9);
          return;
        }
        if (uVar2 == 1) {
          iVar4 = FUN_004259d0((uint)bVar1 * 0xd + 0x457f1 + g_clientContext);
          if (iVar4 == -1) {
            local_408 = 0;
            pbVar11 = local_407;
            for (iVar4 = 0xff; iVar4 != 0; iVar4 = iVar4 + -1) {
              pbVar11[0] = 0;
              pbVar11[1] = 0;
              pbVar11[2] = 0;
              pbVar11[3] = 0;
              pbVar11 = pbVar11 + 4;
            }
            pbVar11[0] = 0;
            pbVar11[1] = 0;
            pbVar11[2] = 0;
            pbVar11 = &local_408;
            for (uVar7 = uVar9 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
              *(undefined4 *)pbVar11 = *(undefined4 *)pbVar10;
              pbVar10 = pbVar10 + 4;
              pbVar11 = pbVar11 + 4;
            }
            for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
              *pbVar11 = *pbVar10;
              pbVar10 = pbVar10 + 1;
              pbVar11 = pbVar11 + 1;
            }
            FUN_004382d0();
            *(undefined1 *)(*(int *)((int)this + (uint)bVar1 * 8 + 0x700) + 0x8c8) = 1;
            return;
          }
        }
        else {
          if (uVar2 == 3) {
            iVar4 = (uint)*pbVar10 * 0xd + 0x457f1 + g_clientContext;
            iVar12 = (uint)bVar1 * 0xd + 0x457f1 + g_clientContext;
            iVar13 = iVar4;
            pcVar6 = (char *)GetLocalizedString(&g_localizedStringTable,0x260);
            _sprintf(local_488,pcVar6,iVar12,iVar4,iVar13);
            (**(code **)(*(int *)this + 0x28))(local_488,2,6);
            return;
          }
          if (uVar2 == 0x8000) {
            uVar9 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
            if (bVar1 == uVar9) {
              RefreshReadyRoomControls(this,1,0);
            }
            uVar9 = (uint)*(byte *)(g_clientContext + 0x45124);
            PeekChecksumStateUnderLock(g_clientContext + 0x44efc);
            ApplyRoomSettings(this,uVar9);
            iVar4 = g_clientContext + 0x44efc;
            *(undefined1 *)((int)this + 9) = *(undefined1 *)(g_clientContext + 0x44ef8);
            uVar5 = PeekChecksumStateUnderLock(iVar4);
            QueueOutgoingPacketField(uVar5);
            iVar4 = g_clientContext;
            *(undefined4 *)((int)this + 0x25d) = *(undefined4 *)(g_clientContext + 0x457a1);
            *(undefined4 *)((int)this + 0x261) = *(undefined4 *)(iVar4 + 0x457a5);
            *(undefined1 *)((int)this + 0x230) = *(undefined1 *)(iVar4 + 0x45124);
            pcVar6 = (char *)(iVar4 + 0x44e64);
            iVar4 = 0x62d - (int)pcVar6;
            do {
              cVar3 = *pcVar6;
              pcVar6[(int)this + iVar4] = cVar3;
              pcVar6 = pcVar6 + 1;
            } while (cVar3 != '\0');
            RefreshTeamSlotHighlights();
            BuildItemLoadout(this,1);
            return;
          }
        }
      }
      else {
        if (uVar2 == 0x8003) {
          uVar8 = ((int)uVar9 < 0) - 1 & uVar9;
          pbVar11 = (byte *)(g_clientContext + 0x44e64);
          for (uVar7 = uVar8 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined4 *)pbVar11 = *(undefined4 *)pbVar10;
            pbVar10 = pbVar10 + 4;
            pbVar11 = pbVar11 + 4;
          }
          for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
            *pbVar11 = *pbVar10;
            pbVar10 = pbVar10 + 1;
            pbVar11 = pbVar11 + 1;
          }
          *(undefined1 *)(iVar4 + 0x44e64 + uVar9) = 0;
          return;
        }
        if (uVar2 == 0x8004) {
          BuildItemLoadout(this,1);
          return;
        }
      }
    }
    else if (uVar2 < 0x8201) {
      if (uVar2 == 0x8200) {
        bVar1 = *pbVar10;
        uVar9 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        if (bVar1 == uVar9) {
          FUN_00422f10(*(undefined4 *)(g_clientContext + 0x44e60));
          iVar4 = DAT_007934e8;
          *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
          *(undefined2 *)(iVar4 + 0x4d4) = 0x2000;
          *(undefined2 *)(iVar4 + 0x4d6) = 0xffff;
          *(int *)(iVar4 + 0x44d0) = *(int *)(iVar4 + 0x44d0) + 2;
          SendOutgoingPacket(iVar4);
          return;
        }
        iVar4 = (uint)bVar1 * 0xd + 0x457f1 + g_clientContext;
        pcVar6 = (char *)GetLocalizedString(&g_localizedStringTable,0x275);
        _sprintf(local_488,pcVar6,iVar4);
        (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))(local_488,2,6);
        return;
      }
      if (uVar2 == 0x8101) {
        uVar9 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        if (bVar1 == uVar9) {
          *(undefined1 *)(g_clientContext + 0x3b6c0) = *(undefined1 *)((int)this + 0x25b);
          RefreshReadyRoomControls(this,1,0);
          if (*(char *)(g_clientContext + 0x3b6c0) == -1) {
            *(undefined1 *)(g_clientContext + 0x3b6c0) = 0;
          }
        }
        FUN_00415ce0((uint)bVar1);
        TallyRoomTeamStats();
        ComputeTurnOrder();
        return;
      }
      if (uVar2 == 0x8102) {
        uVar9 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        if (bVar1 == uVar9) {
          *(bool *)((int)this + 0x4cc) = *pbVar10 == 3;
          RefreshReadyRoomControls(this,1,0);
          return;
        }
      }
    }
    else if (uVar2 == 0x8400) {
      uVar9 = (uint)bVar1;
      LoadRoomSlotAvatar();
      cVar3 = *(char *)(g_clientContext + 0x458fc + uVar9 * 2);
      if ((cVar3 != -1) && (cVar3 < '\x11')) {
        _sprintf(local_488,s_tank_d_00553fa0,cVar3 + 1);
        uVar5 = FindPreloadedTextureByName(local_488);
        *(undefined4 *)(*(int *)((int)this + uVar9 * 8 + 0x6fc) + 0x1c) = uVar5;
        (**(code **)(**(int **)((int)this + uVar9 * 8 + 0x6fc) + 4))(s_normal_00552230);
        (**(code **)(**(int **)((int)this + uVar9 * 8 + 0x700) + 4))(s_normal_00552230);
        return;
      }
      uVar5 = FindPreloadedTextureByName(s_rider_00553f98);
      *(undefined4 *)(*(int *)((int)this + uVar9 * 8 + 0x6fc) + 0x1c) = uVar5;
      (**(code **)(**(int **)((int)this + uVar9 * 8 + 0x6fc) + 4))(&DAT_00553f90);
      (**(code **)(**(int **)((int)this + uVar9 * 8 + 0x700) + 4))(s_normal_00552230);
    }
    else if (((uVar2 == 0x9002) && (*(char *)((int)this + 0x4cc) == '\0')) &&
            (*(int *)((int)this + 0x4d4) == -1)) {
      cVar3 = ChecksumPairDiffers(g_clientContext + 0x3b49c,g_clientContext + 0x3b6c4);
      if (cVar3 != '\0') {
        *(undefined4 *)((int)this + 0x4d4) = 0x31;
        return;
      }
    }
  }
  return;
}

