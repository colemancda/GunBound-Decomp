/* WriteReplayEventRecord - 0x004104f0 in the original binary.
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


/* WARNING: Type propagation algorithm not settling */

void WriteReplayEventRecord(size_t param_1,uint param_2,byte *param_3)

{
  byte *pbVar1;
  byte bVar2;
  short sVar3;
  char cVar4;
  undefined2 uVar5;
  uint uVar6;
  char *pcVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  int iVar12;
  char *pcVar13;
  int *piVar14;
  undefined4 uVar15;
  undefined *puVar16;
  undefined4 uVar17;
  uint uVar18;
  int iVar19;
  int iVar20;
  uint uVar21;
  byte *pbVar22;
  char *pcVar23;
  undefined4 *puVar24;
  char *pcVar25;
  undefined4 *puVar26;
  undefined4 *unaff_FS_OFFSET;
  bool bVar27;
  uint local_d78;
  byte local_d71;
  undefined4 *local_d70;
  undefined4 local_d6c;
  byte local_d61;
  undefined4 *local_d60;
  undefined4 local_d5c;
  undefined4 local_d58;
  undefined4 local_d54;
  undefined4 local_d50;
  uint local_d4c;
  undefined1 local_d48;
  undefined4 local_d44;
  undefined4 local_d40;
  undefined4 local_d3c;
  uint local_d38;
  undefined1 local_d34;
  undefined1 local_d30 [2];
  undefined2 uStack_d2e;
  char acStack_b09 [2];
  undefined4 local_b07;
  char local_708 [132];
  undefined1 local_684 [548];
  undefined1 local_460 [548];
  undefined1 local_23c [540];
  undefined4 uStack_20;
  undefined4 uStack_14;
  undefined1 *puStack_10;
  uint local_c;
  
  local_c = 0xffffffff;
  puStack_10 = &LAB_0053df47;
  uStack_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_14;
  pbVar22 = param_3;
  if (*(FILE **)(&g_replayFileHandle + g_clientContext) != (FILE *)0x0) {
    local_d71 = 0;
    _fwrite(&local_d71,1,1,*(FILE **)(&g_replayFileHandle + g_clientContext));
    _fwrite(g_gameStateVTableArray[0xb] + 4,1,4,*(FILE **)(&g_replayFileHandle + g_clientContext));
    _fwrite(&param_1,1,4,*(FILE **)(&g_replayFileHandle + g_clientContext));
    _fwrite(&param_2,1,2,*(FILE **)(&g_replayFileHandle + g_clientContext));
    pbVar22 = param_3;
    _fwrite(param_3,1,param_1,*(FILE **)(&g_replayFileHandle + g_clientContext));
  }
  iVar19 = g_clientContext;
  uVar6 = param_2 & 0xffff;
  if (0x200f < uVar6) {
    if (0x4501 < uVar6) {
      if (uVar6 < 0x6003) {
        if (uVar6 != 0x6002) {
          if (uVar6 == 0x5001) {
            if (*(short *)pbVar22 == 0) {
              uVar15 = GetLocalizedString(&g_localizedStringTable,0x1004);
              FUN_00509410(&g_uiPanelManager,uVar15);
            }
          }
          else if (uVar6 == 0x5101) {
            (*(undefined4 *)local_d30) = (*(undefined4 *)local_d30) & 0xffffff00;
            puVar26 = (undefined4 *)((int)local_d30 + 1);
            for (iVar19 = 0x7f; iVar19 != 0; iVar19 = iVar19 + -1) {
              *puVar26 = 0;
              puVar26 = puVar26 + 1;
            }
            *(undefined2 *)puVar26 = 0;
            iVar19 = 0;
            iVar12 = 0;
            *(undefined1 *)((int)puVar26 + 2) = 0;
            uVar15 = 6;
            if (0 < (int)param_1) {
              do {
                bVar2 = param_3[iVar12];
                if (bVar2 != 0xd) {
                  if (bVar2 == 10) {
                    (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                              (local_d30,2,uVar15);
                    uVar15 = 0;
                    puVar26 = (undefined4 *)local_d30;
                    for (iVar19 = 0x80; iVar19 != 0; iVar19 = iVar19 + -1) {
                      *puVar26 = 0;
                      puVar26 = puVar26 + 1;
                    }
                    iVar19 = 0;
                  }
                  else {
                    local_d30[iVar19] = bVar2;
                    iVar19 = iVar19 + 1;
                  }
                }
                iVar12 = iVar12 + 1;
              } while (iVar12 < (int)param_1);
            }
            (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                      (local_d30,2,uVar15);
            pbVar22 = param_3;
          }
          goto switchD_004105f7_caseD_1022;
        }
      }
      else if (uVar6 != 0x600f) goto switchD_004105f7_caseD_1022;
      SetGuardedBool(1);
      goto switchD_004105f7_caseD_1022;
    }
    if (uVar6 == 0x4501) {
      FUN_004e7de0(&DAT_00e55ce0,*pbVar22,pbVar22 + 1);
      goto switchD_004105f7_caseD_1022;
    }
    if (uVar6 < 0x3401) {
      if (uVar6 == 0x3400) {
        QueueOutgoingPacketField(*pbVar22);
        iVar19 = PeekChecksumStateUnderLock(g_clientContext + 0x3b6c4);
        if (*(char *)(iVar19 + 0x45914 + g_clientContext) == '\x03') {
          iVar19 = PeekChecksumStateUnderLock(g_clientContext + 0x3b6c4);
          *(undefined1 *)(iVar19 + 0x45914 + g_clientContext) = 1;
        }
      }
      else if (uVar6 == 0x3010) {
        if (g_currentGameState == 9) {
          if (g_pendingGameState != 9) goto switchD_004105f7_caseD_1022;
        }
        else if ((g_currentGameState != 0xb) || (g_pendingGameState != 0xb))
        goto switchD_004105f7_caseD_1022;
        local_d70 = (undefined4 *)(uint)*pbVar22;
        *(int *)(g_clientContext + 0x4739c) = *(int *)(g_clientContext + 0x4739c) + 1;
        FUN_00415ce0(local_d70);
        iVar12 = (int)local_d70 * 0xd + iVar19;
        local_d60 = (undefined4 *)(iVar12 + 0x457f1);
        *local_d60 = *(undefined4 *)(pbVar22 + 1);
        *(undefined4 *)(iVar12 + 0x457f5) = *(undefined4 *)(pbVar22 + 5);
        *(undefined4 *)(iVar12 + 0x457f9) = *(undefined4 *)(pbVar22 + 9);
        *(undefined1 *)(iVar12 + 0x457fd) = 0;
        *(undefined4 *)(iVar19 + 0x4585c + (int)local_d70 * 4) = *(undefined4 *)(pbVar22 + 0xd);
        *(undefined2 *)(iVar19 + 0x4589c + (int)local_d70 * 2) = *(undefined2 *)(pbVar22 + 0x11);
        *(undefined4 *)(iVar19 + 0x4587c + (int)local_d70 * 4) = *(undefined4 *)(pbVar22 + 0x13);
        *(undefined2 *)(iVar19 + 0x458ac + (int)local_d70 * 2) = *(undefined2 *)(pbVar22 + 0x17);
        *(byte *)(iVar19 + 0x458fc + (int)local_d70 * 2) = pbVar22[0x19];
        *(byte *)(iVar19 + 0x458fd + (int)local_d70 * 2) = pbVar22[0x1a];
        *(byte *)((int)local_d70 + 0x4590cU + iVar19) = pbVar22[0x1b];
        *(undefined1 *)((int)local_d70 + 0x45914U + iVar19) = 1;
        puVar26 = *(undefined4 **)(pbVar22 + 0x1c);
        local_d6c = *(undefined4 *)(pbVar22 + 0x20);
        *(short *)(iVar19 + 0x458bc + (int)local_d70 * 8) = (short)puVar26;
        *(short *)(iVar19 + 0x458c0 + (int)local_d70 * 8) = (short)local_d6c;
        *(short *)(iVar19 + 0x458be + (int)local_d70 * 8) = (short)((uint)puVar26 >> 0x10);
        *(short *)(iVar19 + 0x458c2 + (int)local_d70 * 8) = (short)((uint)local_d6c >> 0x10);
        iVar12 = iVar19 + (int)local_d70 * 9;
        *(undefined4 *)(iVar12 + 0x457a9) = *(undefined4 *)(pbVar22 + 0x24);
        *(undefined4 *)(iVar12 + 0x457ad) = *(undefined4 *)(pbVar22 + 0x28);
        *(undefined1 *)(iVar12 + 0x457b1) = 0;
        if ((*(char *)(iVar12 + 0x4354f) < '\0') && (-1 < *(char *)(iVar12 + 0x4354e))) {
          *(undefined1 *)(iVar12 + 0x4354f) = 0;
        }
        *(short *)(iVar19 + 0x4591c + (int)local_d70 * 2) = *(short *)(pbVar22 + 0x2c) + 4;
        if (*(short *)(iVar19 + 0x4591c + (int)local_d70 * 2) == -1) {
          *(undefined2 *)(iVar19 + 0x4591c + (int)local_d70 * 2) = 0x17;
        }
        sVar3 = *(short *)(pbVar22 + 0x2e);
        *(short *)(iVar19 + 0x4592c + (int)local_d70 * 2) = sVar3 + 4;
        if ((short)(sVar3 + 4) == -1) {
          *(undefined2 *)(iVar19 + 0x4592c + (int)local_d70 * 2) = 0x17;
        }
        *(char *)(iVar19 + 0x45125) = *(char *)(iVar19 + 0x45125) + '\x01';
        iVar12 = (int)local_d70 * 2;
        iVar20 = (int)local_d70 * 4;
        local_d70 = puVar26;
        FUN_004e74c0(*(undefined4 *)(iVar19 + 0x4587c + iVar20),
                     *(undefined2 *)(iVar19 + 0x458ac + iVar12),local_d60);
        pbVar22 = param_3;
      }
      else if (uVar6 == 0x3020) {
        FUN_00415ce0(*pbVar22);
        bVar27 = g_currentGameState != 3;
        *(int *)(iVar19 + 0x4739c) = *(int *)(iVar19 + 0x4739c) + -1;
        if ((bVar27) || (g_pendingGameState != 3)) {
          *(char *)(iVar19 + 0x45125) = *(char *)(iVar19 + 0x45125) + -1;
          *(undefined1 *)(*pbVar22 + 0x45914 + iVar19) = 0;
          if ((g_currentGameState == 9) && (g_bBattleSessionActive == '\x01')) {
            QueueOutgoingPacketField(0xffffffff);
          }
          FUN_004e7560();
          FUN_004e77e0(&DAT_00e55ce0);
          pbVar22 = param_3;
          if ((*(int *)(&DAT_006a76f8 + g_clientContext) != 0) &&
             (local_d78 = 0, *(int *)(&DAT_006a76f8 + g_clientContext) != 0)) {
            do {
              piVar14 = (int *)FUN_00415450();
              iVar19 = *piVar14;
              cVar4 = FUN_0041c190();
              if (cVar4 != '\0') {
                iVar12 = iVar19 * 8 + g_clientContext;
                *(undefined4 *)(&DAT_006a7670 + iVar12) = 0;
                *(undefined4 *)((int)(&DAT_006a7670 + iVar12) + 4) = 0;
                QueueBroadcastEvent(0xc303);
                (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = (char)iVar19;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
                if (iVar19 == 0xe) {
                  cVar4 = PeekPacketChecksumBool();
                  if (cVar4 == '\0') {
                    SetGuardedBool(1);
                  }
                  uVar5 = FUN_0045d360(0);
                  *(undefined2 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar5;
                  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
                  FUN_0041f200(0);
                }
                BroadcastQueuedEvent();
                FUN_00415470();
                local_d78 = local_d78 - 1;
                if (*(int *)(&DAT_006a76f8 + g_clientContext) == 0) {
                  PostTurnEvent(&DAT_00e55ce0,0xc302);
                }
              }
              local_d78 = local_d78 + 1;
              pbVar22 = param_3;
            } while (local_d78 < *(uint *)(&DAT_006a76f8 + g_clientContext));
          }
        }
      }
      goto switchD_004105f7_caseD_1022;
    }
    if (uVar6 != 0x4410) goto switchD_004105f7_caseD_1022;
    cVar4 = PeekPacketChecksumBool();
    if (cVar4 == '\0') {
      SetGuardedBool(1);
      *(byte *)(g_clientContext + 0x62155) = *pbVar22;
      InitGuardSlot();
      local_c = 0;
      InitGuardSlot();
      local_c = CONCAT31(SUBFIELD(local_c,1,undefined3),1);
      EncodeChecksumStateXored();
      EncodeChecksumStateXored();
      cVar4 = PacketChecksumEquals(g_clientContext + 0x45354,3);
      if (cVar4 == '\0') {
LAB_00411727:
        uVar15 = PeekChecksumStateUnderLock(g_clientContext + 0x473a0);
        switch(uVar15) {
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
          uVar15 = PeekChecksumStateUnderLock(&DAT_00796aa0);
          puVar16 = &DAT_0067e3d0 + g_clientContext;
        }
        else {
          uVar15 = PeekChecksumStateUnderLock(&DAT_00796aa0);
          puVar16 = &DAT_0067e5f4 + g_clientContext;
        }
        cVar4 = PacketChecksumGreaterEqual(puVar16,uVar15);
        if (cVar4 != '\0') goto LAB_00411727;
      }
      local_d78 = 0;
      iVar12 = 0;
      iVar19 = g_clientContext;
      do {
        if ((*(char *)(local_d78 + 0x5010d + iVar19) != '\0') &&
           (*(char *)(local_d78 + 0x50126 + iVar19) == *(char *)(iVar19 + 0x62155))) {
          uVar15 = PeekChecksumStateUnderLock(iVar12 + 0x5113c + iVar19);
          uVar15 = EncodeChecksumDeltaAdd(&DAT_00796aa0,local_23c,uVar15);
          SUBFIELD(local_c,0,undefined1) = 2;
          uVar15 = InitGuardedChecksumSlot(acStack_b09 + 1,local_460,uVar15);
          SUBFIELD(local_c,0,undefined1) = 3;
          uVar17 = PeekChecksumStateUnderLock(&DAT_00796aa0);
          uVar15 = EncodeChecksumDeltaDiv(uVar15,local_684,uVar17);
          SUBFIELD(local_c,0,undefined1) = 4;
          EmitChecksumSum(uVar15);
          SUBFIELD(local_c,0,undefined1) = 3;
          ScrubChecksumGuard();
          SUBFIELD(local_c,0,undefined1) = 2;
          ScrubChecksumGuard();
          local_c = CONCAT31(SUBFIELD(local_c,1,undefined3),1);
          ScrubChecksumGuard();
          EmitChecksumSum(local_d30);
          iVar19 = g_clientContext;
        }
        local_d78 = local_d78 + 1;
        iVar12 = iVar12 + 0x1120;
      } while (iVar12 < 0x8900);
      local_c = local_c & 0xffffff00;
      ScrubChecksumGuard();
      local_c = 0xffffffff;
      ScrubChecksumGuard();
      cVar4 = CompareChecksumMatch(g_clientContext + 0x3b49c,g_clientContext + 0x3b6c4);
      pbVar22 = param_3;
      if ((cVar4 != '\0') &&
         ((((cVar4 = PacketChecksumEquals(g_clientContext + 0x45354,3), cVar4 != '\0' ||
            (cVar4 = PeekPacketChecksumBool(), pbVar22 = param_3, cVar4 == '\x01')) &&
           (cVar4 = PeekPacketChecksumBool(), pbVar22 = param_3, cVar4 == '\0')) &&
          ((g_currentGameState != 0xb ||
           (cVar4 = PeekPacketChecksumBool(), pbVar22 = param_3, cVar4 != '\x01')))))) {
        FUN_00413bf0();
        pbVar22 = param_3;
      }
    }
    SetGuardedBool(1);
    goto switchD_004105f7_caseD_1022;
  }
  if (uVar6 == 0x200f) {
    if (g_currentGameState == 3) {
      if (g_pendingGameState != 3) goto switchD_004105f7_caseD_1022;
    }
    else if ((g_currentGameState != 4) || (g_pendingGameState != 4))
    goto switchD_004105f7_caseD_1022;
    *(undefined1 *)(*pbVar22 + 0x41345 + g_clientContext) = 0;
    cVar4 = *(char *)(iVar19 + 0x41344) + -1;
LAB_004111c0:
    *(char *)(iVar19 + 0x41344) = cVar4;
    iVar12 = FUN_0050f000();
    pbVar22 = param_3;
    if (iVar12 != 0) {
      Widget_SetChildRange(*(undefined1 *)(iVar19 + 0x41344),7);
      pbVar22 = param_3;
    }
    goto switchD_004105f7_caseD_1022;
  }
  if (0x1060 < uVar6) {
    if (uVar6 < 0x2002) {
      if (uVar6 == 0x2001) {
        if (*(short *)pbVar22 == 0) {
          *(undefined4 *)(g_clientContext + 0x44e60) = 0xffffffff;
          FUN_0041c230();
          FUN_0041b7e0();
          FUN_004e7430();
          iVar19 = g_clientContext;
          *(uint *)(g_clientContext + 0x41340) = (uint)*(ushort *)(param_3 + 2);
          local_d71 = param_3[4];
          bVar2 = param_3[5];
          pbVar22 = param_3 + 6;
          *(byte *)(iVar19 + 0x41344) = bVar2;
          local_d78 = 0;
          if (bVar2 != 0) {
            do {
              local_d61 = *pbVar22;
              uVar6 = (uint)local_d61;
              *(undefined1 *)(uVar6 + 0x41345 + iVar19) = 1;
              local_d70 = (undefined4 *)(uVar6 * 0xd + 0x41445 + iVar19);
              *local_d70 = *(undefined4 *)(pbVar22 + 1);
              local_d70[1] = *(undefined4 *)(pbVar22 + 5);
              local_d70[2] = *(undefined4 *)(pbVar22 + 9);
              *(undefined1 *)((uVar6 + 0x5055) * 0xd + iVar19) = 0;
              local_d60 = *(undefined4 **)(pbVar22 + 0xd);
              local_d5c = *(undefined4 *)(pbVar22 + 0x11);
              *(short *)(iVar19 + 0x42948 + uVar6 * 8) = (short)local_d60;
              *(short *)(iVar19 + 0x4294c + uVar6 * 8) = (short)local_d5c;
              *(short *)(iVar19 + 0x4294a + uVar6 * 8) = (short)((uint)local_d60 >> 0x10);
              *(short *)(iVar19 + 0x4294e + uVar6 * 8) = (short)((uint)local_d5c >> 0x10);
              iVar12 = iVar19 + uVar6 * 9;
              *(undefined4 *)(iVar12 + 0x43548) = *(undefined4 *)(pbVar22 + 0x15);
              *(undefined4 *)(iVar12 + 0x4354c) = *(undefined4 *)(pbVar22 + 0x19);
              if ((*(char *)(iVar12 + 0x4354f) < '\0') && (-1 < *(char *)(iVar12 + 0x4354e))) {
                *(undefined1 *)(iVar12 + 0x4354f) = 0;
              }
              *(undefined1 *)(iVar12 + 0x43550) = 0;
              *(short *)(iVar19 + 0x43e48 + uVar6 * 2) = *(short *)(pbVar22 + 0x1d) + 4;
              if (*(short *)(iVar19 + 0x43e48 + uVar6 * 2) == -1) {
                *(undefined2 *)(iVar19 + 0x43e48 + uVar6 * 2) = 0x17;
              }
              sVar3 = *(short *)(pbVar22 + 0x1f);
              pbVar22 = pbVar22 + 0x21;
              *(short *)(iVar19 + 0x44048 + uVar6 * 2) = sVar3 + 4;
              if ((short)(sVar3 + 4) == -1) {
                *(undefined2 *)(iVar19 + 0x44048 + uVar6 * 2) = 0x17;
              }
              if (local_d61 == local_d71) {
                FUN_004e73e0(0);
                iVar19 = g_clientContext;
              }
              local_d78 = local_d78 + 1;
            } while ((int)local_d78 < (int)(uint)*(byte *)(iVar19 + 0x41344));
          }
          FUN_004e7340();
          param_1 = param_1 + (uint)*(byte *)(g_clientContext + 0x41344) * -0x21 + -6;
          (*(undefined4 *)local_d30) = (*(undefined4 *)local_d30) & 0xffffff00;
          puVar26 = (undefined4 *)((int)local_d30 + 1);
          for (iVar19 = 0x3f; iVar19 != 0; iVar19 = iVar19 + -1) {
            *puVar26 = 0;
            puVar26 = puVar26 + 1;
          }
          *(undefined2 *)puVar26 = 0;
          *(undefined1 *)((int)puVar26 + 2) = 0;
          iVar12 = 0;
          local_d78 = 0;
          iVar19 = g_clientContext;
          if (0 < (int)param_1) {
            do {
              if (pbVar22[local_d78] == 10) {
                pcVar13 = local_d30;
                do {
                  cVar4 = *pcVar13;
                  pcVar13 = pcVar13 + 1;
                } while (cVar4 != '\0');
                AppendChatLogEntry(iVar19,2,0,0,local_d30,0,0);
                iVar12 = 0;
                puVar26 = (undefined4 *)local_d30;
                for (iVar20 = 0x40; iVar19 = g_clientContext, iVar20 != 0; iVar20 = iVar20 + -1) {
                  *puVar26 = 0;
                  puVar26 = puVar26 + 1;
                }
              }
              else {
                local_d30[iVar12] = pbVar22[local_d78];
                iVar12 = iVar12 + 1;
              }
              local_d78 = local_d78 + 1;
            } while ((int)local_d78 < (int)param_1);
          }
          pcVar13 = local_d30;
          do {
            cVar4 = *pcVar13;
            pcVar13 = pcVar13 + 1;
          } while (cVar4 != '\0');
          AppendChatLogEntry(iVar19,2,0,0,local_d30,0,0);
          pbVar22 = param_3;
        }
      }
      else if (uVar6 == 0x1079) {
        if (*(short *)pbVar22 == 0) {
          ShowErrorDialog(0);
        }
      }
      else if (uVar6 == 0x1ff8) {
        ShowErrorDialog(1);
      }
      goto switchD_004105f7_caseD_1022;
    }
    if (uVar6 != 0x200e) goto switchD_004105f7_caseD_1022;
    if (g_currentGameState == 3) {
      if (g_pendingGameState != 3) goto switchD_004105f7_caseD_1022;
    }
    else if ((g_currentGameState != 7) || (g_pendingGameState != 4))
    goto switchD_004105f7_caseD_1022;
    uVar6 = (uint)*pbVar22;
    *(undefined1 *)(uVar6 + 0x41345 + g_clientContext) = 1;
    puVar26 = (undefined4 *)(uVar6 * 0xd + 0x41445 + iVar19);
    *puVar26 = *(undefined4 *)(pbVar22 + 1);
    puVar26[1] = *(undefined4 *)(pbVar22 + 5);
    puVar26[2] = *(undefined4 *)(pbVar22 + 9);
    *(undefined1 *)((uVar6 + 0x5055) * 0xd + iVar19) = 0;
    local_d70 = *(undefined4 **)(pbVar22 + 0xd);
    local_d6c = *(undefined4 *)(pbVar22 + 0x11);
    *(short *)(iVar19 + 0x42948 + uVar6 * 8) = (short)local_d70;
    *(short *)(iVar19 + 0x4294a + uVar6 * 8) = (short)((uint)local_d70 >> 0x10);
    *(short *)(iVar19 + 0x4294e + uVar6 * 8) = (short)((uint)local_d6c >> 0x10);
    *(short *)(iVar19 + 0x4294c + uVar6 * 8) = (short)local_d6c;
    iVar12 = iVar19 + uVar6 * 9;
    *(undefined4 *)(iVar12 + 0x43548) = *(undefined4 *)(pbVar22 + 0x15);
    *(undefined4 *)(iVar12 + 0x4354c) = *(undefined4 *)(pbVar22 + 0x19);
    if ((*(char *)(iVar12 + 0x4354f) < '\0') && (-1 < *(char *)(iVar12 + 0x4354e))) {
      *(undefined1 *)(iVar12 + 0x4354f) = 0;
    }
    *(undefined1 *)(iVar12 + 0x43550) = 0;
    *(short *)(iVar19 + 0x43e48 + uVar6 * 2) = *(short *)(pbVar22 + 0x1d) + 4;
    if (*(short *)(iVar19 + 0x43e48 + uVar6 * 2) == -1) {
      *(undefined2 *)(iVar19 + 0x43e48 + uVar6 * 2) = 0x17;
    }
    sVar3 = *(short *)(pbVar22 + 0x1f);
    *(short *)(iVar19 + 0x44048 + uVar6 * 2) = sVar3 + 4;
    if ((short)(sVar3 + 4) == -1) {
      *(undefined2 *)(iVar19 + 0x44048 + uVar6 * 2) = 0x17;
    }
    cVar4 = *(char *)(iVar19 + 0x41344) + '\x01';
    goto LAB_004111c0;
  }
  if (uVar6 == 0x1060) {
    QueueOutgoingPacketField(*(undefined4 *)pbVar22);
    cVar4 = PacketChecksumEquals(g_clientContext + 0x449c4,1);
    if (cVar4 != '\0') {
      ShowErrorDialog(0);
    }
    goto switchD_004105f7_caseD_1022;
  }
  switch(uVar6) {
  case 0x1021:
    local_d58 = *(undefined4 *)(pbVar22 + 2);
    local_d54 = *(undefined4 *)(pbVar22 + 6);
    local_d50 = *(undefined4 *)(pbVar22 + 10);
    local_d4c = local_d4c & 0xffffff00;
    if (*(short *)pbVar22 != 0) {
      (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x10))
                (*(undefined2 *)(DAT_007934e8 + 0x44d8),*(undefined2 *)(pbVar22 + 0xe));
      ShowErrorDialogFmt(0,&local_d58);
      FUN_00403000(&DAT_00e53e88);
      break;
    }
    local_d44 = *(undefined4 *)(pbVar22 + 0xe);
    local_d40 = *(undefined4 *)(pbVar22 + 0x12);
    local_d3c = *(undefined4 *)(pbVar22 + 0x16);
    local_d38 = *(uint *)(pbVar22 + 0x1a);
    local_d34 = 0;
    FUN_004260f0();
    iVar19 = __stricmp(&DAT_006aa408 + g_clientContext,(char *)&local_d58);
    if (iVar19 == 0) {
      uVar15 = FUN_004d34f0(&local_d44);
      FlushEncodedSocketBuffer(uVar15);
      (&DAT_006aa408)[g_clientContext] = 0;
    }
    iVar19 = __stricmp(&DAT_006aa600 + g_clientContext,(char *)&local_d58);
    pbVar22 = param_3;
    if (iVar19 == 0) {
      uVar15 = FUN_004d34f0(&local_d44);
      FlushEncodedSocketBuffer(uVar15);
      (&DAT_006aa600)[g_clientContext] = 0;
      pbVar22 = param_3;
    }
    goto LAB_00410792;
  case 0x1023:
    if (*(short *)pbVar22 == 0) {
      local_d58 = *(undefined4 *)(pbVar22 + 2);
      local_d54 = *(undefined4 *)(pbVar22 + 6);
      local_d50 = *(undefined4 *)(pbVar22 + 10);
      local_d4c = *(uint *)(pbVar22 + 0xe);
      local_d44 = *(undefined4 *)(pbVar22 + 0x12);
      local_d40 = *(undefined4 *)(pbVar22 + 0x16);
      local_d3c = *(undefined4 *)(pbVar22 + 0x1a);
      local_d48 = 0;
      local_d38 = local_d38 & 0xffffff00;
      FUN_004260f0();
      pbVar22 = param_3;
    }
LAB_00410792:
    FUN_00403000(&DAT_00e53e88);
    break;
  case 0x1030:
    puVar26 = *(undefined4 **)pbVar22;
    pbVar1 = pbVar22 + 4;
    local_d70 = puVar26;
    if ((g_currentGameState != 0xb) || (((int)puVar26 < 1 && (puVar26 != (undefined4 *)0xfffffffd)))
       ) {
      acStack_b09[1] = 0;
      puVar24 = &local_b07;
      for (iVar19 = 0xff; iVar19 != 0; iVar19 = iVar19 + -1) {
        *puVar24 = 0;
        puVar24 = puVar24 + 1;
      }
      *(undefined2 *)puVar24 = 0;
      *(undefined1 *)((int)puVar24 + 2) = 0;
      pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,6000);
      pcVar13 = pcVar7;
      do {
        cVar4 = *pcVar13;
        pcVar13 = pcVar13 + 1;
      } while (cVar4 != '\0');
      pcVar25 = acStack_b09;
      do {
        pcVar23 = pcVar25 + 1;
        pcVar25 = pcVar25 + 1;
      } while (*pcVar23 != '\0');
      pcVar23 = pcVar7;
      for (uVar6 = (uint)((int)pcVar13 - (int)pcVar7) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar25 = *(undefined4 *)pcVar23;
        pcVar23 = pcVar23 + 4;
        pcVar25 = pcVar25 + 4;
      }
      for (uVar6 = (int)pcVar13 - (int)pcVar7 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar25 = *pcVar23;
        pcVar23 = pcVar23 + 1;
        pcVar25 = pcVar25 + 1;
      }
      switch((int)puVar26) { /* Ghidra switched on the pointer value */
      case 0x0:
        pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0x1772);
        pcVar13 = pcVar7;
        do {
          cVar4 = *pcVar13;
          pcVar13 = pcVar13 + 1;
        } while (cVar4 != '\0');
        uVar6 = (int)pcVar13 - (int)pcVar7;
        pcVar13 = acStack_b09;
        do {
          pcVar25 = pcVar13 + 1;
          pcVar13 = pcVar13 + 1;
        } while (*pcVar25 != '\0');
        break;
      case 0xfffffffc:
        pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0x1776);
        pcVar13 = pcVar7;
        do {
          cVar4 = *pcVar13;
          pcVar13 = pcVar13 + 1;
        } while (cVar4 != '\0');
        uVar6 = (int)pcVar13 - (int)pcVar7;
        pcVar13 = acStack_b09;
        do {
          pcVar25 = pcVar13 + 1;
          pcVar13 = pcVar13 + 1;
        } while (*pcVar25 != '\0');
        break;
      case 0xfffffffd:
        pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0x1775);
        pcVar13 = pcVar7;
        do {
          cVar4 = *pcVar13;
          pcVar13 = pcVar13 + 1;
        } while (cVar4 != '\0');
        uVar6 = (int)pcVar13 - (int)pcVar7;
        pcVar13 = acStack_b09;
        do {
          pcVar25 = pcVar13 + 1;
          pcVar13 = pcVar13 + 1;
        } while (*pcVar25 != '\0');
        break;
      case 0xfffffffe:
        pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0x1774);
        pcVar13 = pcVar7;
        do {
          cVar4 = *pcVar13;
          pcVar13 = pcVar13 + 1;
        } while (cVar4 != '\0');
        uVar6 = (int)pcVar13 - (int)pcVar7;
        pcVar13 = acStack_b09;
        do {
          pcVar25 = pcVar13 + 1;
          pcVar13 = pcVar13 + 1;
        } while (*pcVar25 != '\0');
        break;
      case 0xffffffff:
        pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0x1773);
        pcVar13 = pcVar7;
        do {
          cVar4 = *pcVar13;
          pcVar13 = pcVar13 + 1;
        } while (cVar4 != '\0');
        uVar6 = (int)pcVar13 - (int)pcVar7;
        pcVar13 = acStack_b09;
        do {
          pcVar25 = pcVar13 + 1;
          pcVar13 = pcVar13 + 1;
        } while (*pcVar25 != '\0');
        break;
      default:
        pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0x1771);
        pcVar13 = pcVar7;
        do {
          cVar4 = *pcVar13;
          pcVar13 = pcVar13 + 1;
        } while (cVar4 != '\0');
        uVar6 = (int)pcVar13 - (int)pcVar7;
        pcVar13 = acStack_b09;
        do {
          pcVar25 = pcVar13 + 1;
          pcVar13 = pcVar13 + 1;
        } while (*pcVar25 != '\0');
      }
      for (uVar18 = uVar6 >> 2; uVar18 != 0; uVar18 = uVar18 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar13 = pcVar13 + 4;
      }
      bVar2 = *pbVar1;
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar13 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar13 = pcVar13 + 1;
      }
      if (bVar2 != 0x20) {
        pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0x1777);
        pcVar13 = pcVar7;
        do {
          cVar4 = *pcVar13;
          pcVar13 = pcVar13 + 1;
        } while (cVar4 != '\0');
        pcVar25 = acStack_b09;
        do {
          pcVar23 = pcVar25 + 1;
          pcVar25 = pcVar25 + 1;
        } while (*pcVar23 != '\0');
        pcVar23 = pcVar7;
        for (uVar6 = (uint)((int)pcVar13 - (int)pcVar7) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined4 *)pcVar25 = *(undefined4 *)pcVar23;
          pcVar23 = pcVar23 + 4;
          pcVar25 = pcVar25 + 4;
        }
        bVar2 = *pbVar1;
        for (uVar6 = (int)pcVar13 - (int)pcVar7 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *pcVar25 = *pcVar23;
          pcVar23 = pcVar23 + 1;
          pcVar25 = pcVar25 + 1;
        }
        if ((bVar2 == 0x54) && (pbVar22[5] == 0x48)) {
          pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0x177a);
          pcVar13 = pcVar7;
          do {
            cVar4 = *pcVar13;
            pcVar13 = pcVar13 + 1;
          } while (cVar4 != '\0');
          pcVar25 = acStack_b09;
          do {
            pcVar23 = pcVar25 + 1;
            pcVar25 = pcVar25 + 1;
          } while (*pcVar23 != '\0');
          pcVar23 = pcVar7;
          for (uVar6 = (uint)((int)pcVar13 - (int)pcVar7) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
            *(undefined4 *)pcVar25 = *(undefined4 *)pcVar23;
            pcVar23 = pcVar23 + 4;
            pcVar25 = pcVar25 + 4;
          }
          for (uVar6 = (int)pcVar13 - (int)pcVar7 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
            *pcVar25 = *pcVar23;
            pcVar23 = pcVar23 + 1;
            pcVar25 = pcVar25 + 1;
          }
        }
        if (*pbVar1 == 0x46) {
          if (pbVar22[5] == 0x4d) {
            pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0x1778);
            pcVar13 = pcVar7;
            do {
              cVar4 = *pcVar13;
              pcVar13 = pcVar13 + 1;
            } while (cVar4 != '\0');
            pcVar25 = acStack_b09;
            do {
              pcVar23 = pcVar25 + 1;
              pcVar25 = pcVar25 + 1;
            } while (*pcVar23 != '\0');
            pcVar23 = pcVar7;
            for (uVar6 = (uint)((int)pcVar13 - (int)pcVar7) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
              *(undefined4 *)pcVar25 = *(undefined4 *)pcVar23;
              pcVar23 = pcVar23 + 4;
              pcVar25 = pcVar25 + 4;
            }
            for (uVar6 = (int)pcVar13 - (int)pcVar7 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
              *pcVar25 = *pcVar23;
              pcVar23 = pcVar23 + 1;
              pcVar25 = pcVar25 + 1;
            }
          }
          if ((*pbVar1 == 0x46) && (pbVar22[5] == 0x44)) {
            pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0x1779);
            pcVar13 = pcVar7;
            do {
              cVar4 = *pcVar13;
              pcVar13 = pcVar13 + 1;
            } while (cVar4 != '\0');
            pcVar25 = acStack_b09;
            do {
              pcVar23 = pcVar25 + 1;
              pcVar25 = pcVar25 + 1;
            } while (*pcVar23 != '\0');
            pcVar23 = pcVar7;
            for (uVar6 = (uint)((int)pcVar13 - (int)pcVar7) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
              *(undefined4 *)pcVar25 = *(undefined4 *)pcVar23;
              pcVar23 = pcVar23 + 4;
              pcVar25 = pcVar25 + 4;
            }
            for (uVar6 = (int)pcVar13 - (int)pcVar7 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
              *pcVar25 = *pcVar23;
              pcVar23 = pcVar23 + 1;
              pcVar25 = pcVar25 + 1;
            }
          }
        }
      }
      if (pbVar22[6] != 0) {
        pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0x177b);
        pcVar13 = pcVar7;
        do {
          cVar4 = *pcVar13;
          pcVar13 = pcVar13 + 1;
        } while (cVar4 != '\0');
        pcVar25 = acStack_b09;
        do {
          pcVar23 = pcVar25 + 1;
          pcVar25 = pcVar25 + 1;
        } while (*pcVar23 != '\0');
        pcVar23 = pcVar7;
        for (uVar6 = (uint)((int)pcVar13 - (int)pcVar7) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined4 *)pcVar25 = *(undefined4 *)pcVar23;
          pcVar23 = pcVar23 + 4;
          pcVar25 = pcVar25 + 4;
        }
        (*(undefined4 *)local_d30) = *(uint *)(pbVar22 + 6);
        for (uVar6 = (int)pcVar13 - (int)pcVar7 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *pcVar25 = *pcVar23;
          pcVar23 = pcVar23 + 1;
          pcVar25 = pcVar25 + 1;
        }
        puVar26 = (undefined4 *)((int)local_d30 + 1);
        for (iVar19 = 0x3f; iVar19 != 0; iVar19 = iVar19 + -1) {
          *puVar26 = 0;
          puVar26 = puVar26 + 1;
        }
        *(undefined2 *)puVar26 = 0;
        *(undefined1 *)((int)puVar26 + 2) = 0;
        lVar8 = _atol(local_d30);
        uStack_d2e = (ushort)((*(undefined4 *)local_d30) >> 0x10) & 0xff00;
        *(undefined2 *)local_d30 = *(undefined2 *)(pbVar22 + 10);
        lVar9 = _atol(local_d30);
        *(undefined2 *)local_d30 = *(undefined2 *)(pbVar22 + 0xc);
        lVar10 = _atol(local_d30);
        *(undefined2 *)local_d30 = *(undefined2 *)(pbVar22 + 0xe);
        local_d60 = (undefined4 *)_atol(local_d30);
        (*(undefined4 *)local_d30) = CONCAT22(uStack_d2e,*(undefined2 *)(pbVar22 + 0x10));
        lVar11 = _atol(local_d30);
        puVar26 = local_d60;
        pcVar13 = (char *)GetLocalizedString(&g_localizedStringTable,0x177c);
        _sprintf(local_d30,pcVar13,lVar8,lVar9,lVar10,puVar26,lVar11);
        pcVar13 = local_d30;
        do {
          cVar4 = *pcVar13;
          pcVar13 = pcVar13 + 1;
        } while (cVar4 != '\0');
        uVar6 = (int)pcVar13 - (int)local_d30;
        pcVar13 = acStack_b09;
        do {
          pcVar7 = pcVar13 + 1;
          pcVar13 = pcVar13 + 1;
        } while (*pcVar7 != '\0');
        pcVar7 = local_d30;
        for (uVar18 = uVar6 >> 2; uVar18 != 0; uVar18 = uVar18 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *pcVar13 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          pcVar13 = pcVar13 + 1;
        }
      }
      uVar6 = *(uint *)(pbVar22 + 0x12);
      if (uVar6 != 0) {
        pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0x177e);
        pcVar13 = pcVar7;
        do {
          cVar4 = *pcVar13;
          pcVar13 = pcVar13 + 1;
        } while (cVar4 != '\0');
        pcVar25 = acStack_b09;
        do {
          pcVar23 = pcVar25 + 1;
          pcVar25 = pcVar25 + 1;
        } while (*pcVar23 != '\0');
        pcVar23 = pcVar7;
        for (uVar18 = (uint)((int)pcVar13 - (int)pcVar7) >> 2; uVar18 != 0; uVar18 = uVar18 - 1) {
          *(undefined4 *)pcVar25 = *(undefined4 *)pcVar23;
          pcVar23 = pcVar23 + 4;
          pcVar25 = pcVar25 + 4;
        }
        for (uVar18 = (int)pcVar13 - (int)pcVar7 & 3; uVar18 != 0; uVar18 = uVar18 - 1) {
          *pcVar25 = *pcVar23;
          pcVar23 = pcVar23 + 1;
          pcVar25 = pcVar25 + 1;
        }
        uVar18 = uVar6 / 0xe10;
        uVar21 = uVar6 % 0x3c;
        uVar15 = (undefined4)(((ulonglong)uVar6 % 0xe10) / 0x3c);
        pcVar13 = (char *)GetLocalizedString(&g_localizedStringTable,0x177f);
        _sprintf(local_708,pcVar13,uVar18,uVar15,uVar21);
        pcVar13 = local_708;
        do {
          cVar4 = *pcVar13;
          pcVar13 = pcVar13 + 1;
        } while (cVar4 != '\0');
        uVar6 = (int)pcVar13 - (int)local_708;
        pcVar13 = acStack_b09;
        do {
          pcVar7 = pcVar13 + 1;
          pcVar13 = pcVar13 + 1;
        } while (*pcVar7 != '\0');
        pcVar7 = local_708;
        for (uVar18 = uVar6 >> 2; uVar18 != 0; uVar18 = uVar18 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *pcVar13 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          pcVar13 = pcVar13 + 1;
        }
      }
      if (((int)local_d70 < 1) && (local_d70 != (undefined4 *)0xfffffffd)) {
        uVar15 = 1;
      }
      else {
        uVar15 = 0;
      }
      ShowMessageDialog(acStack_b09 + 1,uVar15);
      pbVar22 = param_3;
    }
    break;
  case 0x1032:
    QueueOutgoingPacketField(*(undefined4 *)pbVar22);
    break;
  case 0x1040:
    iVar19 = *(int *)pbVar22;
    if (iVar19 == 0) {
      SetGuardedBool(0);
      QueueOutgoingPacketField(0);
    }
    else {
      SetGuardedBool(1);
      QueueOutgoingPacketField(iVar19 * 0x14);
    }
  }
switchD_004105f7_caseD_1022:
  (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 4))(param_1,param_2,pbVar22);
  *unaff_FS_OFFSET = uStack_20;
  return;
}

