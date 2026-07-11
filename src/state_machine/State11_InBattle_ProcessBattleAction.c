/* State11_InBattle_ProcessBattleAction - 0x004b5460 in the original binary.
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


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Low-level battle action dispatcher, distinct from the CGameState::ProcessPacket
   UI-opcode protocol. Consumes a raw packet buffer (packetBuf, packetLen):
     +0x02 (ushort): action type (0x40xx/0x84xx/0x85xx/0xc4xx/0xc801 families)
     +0x05 (byte):   source player slot, validated 0-7 (8-player cap)
     +0x21:          payload start
   Action 0x8500 matches a replay-log event code -- this function is likely fed
   both live network packets and recorded replay events through the same path.
   Confirmed: action 0x4002 = chat message with spatial proximity filtering
   (distance check against ~150 units before delivering to each of the 8 slots).
   See ARCHITECTURE.md for the full opcode table. */

void __thiscall State11_InBattle_ProcessBattleAction(int *param_1,int param_2,int param_3)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xffffd806;
  undefined stack0xffffd807;
  ushort uVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  int *piVar7;
  undefined *puVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  ushort *puVar12;
  ushort *puVar13;
  byte *pbVar14;
  undefined4 *puVar15;
  byte bVar16;
  byte *pbVar17;
  undefined4 *puVar18;
  undefined4 *unaff_FS_OFFSET;
  undefined *puVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  undefined4 uVar22;
  undefined *local_27f0;
  int *local_27ec;
  byte local_27e5;
  int local_27e4;
  int *local_27e0;
  int local_27dc;
  byte local_27d8 [256];
  char local_26d8 [128];
  byte local_2658;
  byte local_2657 [2];
  byte abStack_2655 [1021];
  undefined1 local_2258 [548];
  undefined1 local_2034 [548];
  undefined1 local_1e10 [548];
  undefined1 local_1bec [548];
  undefined1 local_19c8 [548];
  undefined1 local_17a4 [548];
  undefined1 local_1580 [548];
  undefined1 local_135c [548];
  undefined1 local_1138 [548];
  undefined1 local_f14 [548];
  undefined1 local_cf0 [548];
  undefined1 local_acc [548];
  undefined1 local_8a8 [548];
  undefined1 local_684 [548];
  undefined1 local_460 [548];
  undefined1 local_23c [540];
  undefined4 uStack_20;
  undefined4 uStack_1c;
  int *piStack_18;
  undefined4 local_14;
  undefined1 *puStack_10;
  int local_c;
  
  local_c = 0xffffffff;
  puStack_10 = &LAB_00540a36;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  iVar4 = g_clientContext;
  uStack_1c = 0x4b5486;
  bVar16 = *(byte *)(param_2 + 5);
  uVar1 = *(ushort *)(param_2 + 2);
  puVar12 = (ushort *)(param_2 + 0x21);
  uVar11 = param_3 - 0x21;
  local_27e4 = CONCAT31(SUBFIELD(local_27e4,1,undefined3),bVar16);
  if (7 < bVar16) goto switchD_004b64f9_caseD_c302;
  local_27ec = param_1;
  piStack_18 = param_1;
  if (uVar1 < 0x8501) {
    if (uVar1 == 0x8500) {
      iVar4 = GetPlayerRecordBySlot(g_clientContext);
      if ((iVar4 != 0) && (cVar2 = PeekPacketChecksumBool(), cVar2 == '\0')) {
        uVar21 = QueueOutgoingPacketField(*(undefined2 *)(param_2 + 0x22));
        EncodeChecksumState(uVar21);
        uVar21 = QueueOutgoingPacketField(*(undefined2 *)(param_2 + 0x24));
        EncodeChecksumState(uVar21);
        QueueOutgoingPacketField(*(char *)(param_2 + 0x26) == '\x01');
        *unaff_FS_OFFSET = local_14;
        return;
      }
      goto switchD_004b64f9_caseD_c302;
    }
    if (uVar1 < 0x8007) {
      if (uVar1 == 0x8006) {
        piVar7 = (int *)GetPlayerRecordBySlot(g_clientContext);
        if (piVar7 != (int *)0x0) {
          uVar21 = QueueOutgoingPacketField(*puVar12);
          EncodeChecksumState(uVar21);
          uVar21 = QueueOutgoingPacketField(*(undefined2 *)(param_2 + 0x23));
          EncodeChecksumState(uVar21);
          cVar2 = *(char *)(param_2 + 0x25);
          QueueOutgoingPacketField(*(char *)(param_2 + 0x26) == '\x01');
          SetGuardedBool(cVar2 == '\x02');
          cVar3 = PeekPacketChecksumBool();
          if (cVar3 == '\0') {
            SetGuardedBool(cVar2 == '\x01');
          }
          cVar3 = FUN_0041eaa0(g_clientContext,(short)piVar7[0x2fef]);
          if (cVar3 != '\0') {
            (**(code **)(*piVar7 + 4))(s_bifire_005569d8);
            *unaff_FS_OFFSET = piStack_18;
            return;
          }
          if (cVar2 == '\0') {
            (**(code **)(*piVar7 + 4))(s_bfire1_005569f0);
            *unaff_FS_OFFSET = piStack_18;
            return;
          }
          if (cVar2 == '\x01') {
            (**(code **)(*piVar7 + 4))(s_bfire2_005569e8);
            *unaff_FS_OFFSET = piStack_18;
            return;
          }
          if (cVar2 == '\x02') {
            (**(code **)(*piVar7 + 4))(s_bsfire_005569e0);
            *unaff_FS_OFFSET = piStack_18;
            return;
          }
        }
      }
      else if (uVar1 < 0x4005) {
        if (uVar1 == 0x4004) {
          if ((*(char *)(bVar16 + 0x5010d + g_clientContext) != '\0') &&
             (iVar4 = FUN_004259d0((uint)bVar16 * 0xd + 0x50196 + g_clientContext), iVar4 == -1)) {
            uVar9 = ((int)(param_3 - 0x22U) < 0) - 1 & param_3 - 0x22U;
            pbVar14 = (byte *)(param_2 + 0x22);
            pbVar17 = local_27d8;
            for (uVar11 = uVar9 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
              *(undefined4 *)pbVar17 = *(undefined4 *)pbVar14;
              pbVar14 = pbVar14 + 4;
              pbVar17 = pbVar17 + 4;
            }
            for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
              *pbVar17 = *pbVar14;
              pbVar14 = pbVar14 + 1;
              pbVar17 = pbVar17 + 1;
            }
            (&stack0xffffd806)[param_3] = 0;
            FUN_004382d0();
            *unaff_FS_OFFSET = local_14;
            return;
          }
        }
        else if (uVar1 < 0x4003) {
          if (uVar1 == 0x4002) {
            local_27e0 = (int *)(uint)bVar16;
            if (*(char *)((int)local_27e0 + 0x5010dU + g_clientContext) != '\0') {
              local_27f0 = (undefined *)((int)local_27e0 * 0xd);
              iVar4 = FUN_004259d0(local_27f0 + g_clientContext + 0x50196);
              if (iVar4 == -1) {
                local_2658 = 0;
                pbVar14 = local_2657;
                for (iVar4 = 0xff; iVar4 != 0; iVar4 = iVar4 + -1) {
                  pbVar14[0] = 0;
                  pbVar14[1] = 0;
                  pbVar14[2] = 0;
                  pbVar14[3] = 0;
                  pbVar14 = pbVar14 + 4;
                }
                pbVar14[0] = 0;
                pbVar14[1] = 0;
                pbVar14[2] = 0;
                puVar13 = puVar12;
                pbVar14 = &local_2658;
                for (uVar9 = uVar11 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
                  *(undefined4 *)pbVar14 = *(undefined4 *)puVar13;
                  puVar13 = puVar13 + 2;
                  pbVar14 = pbVar14 + 4;
                }
                uVar21 = 0;
                for (uVar9 = uVar11 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
                  *pbVar14 = (byte)*puVar13;
                  puVar13 = (ushort *)((int)puVar13 + 1);
                  pbVar14 = pbVar14 + 1;
                }
                FUN_004e3740(&DAT_00794e14);
                AcquireSoundChannel(uVar21);
                FUN_0041ef90(g_clientContext,0,local_27e4,puVar12,uVar11,local_27ec[3] + 300,0);
                FUN_0041b8c0(g_clientContext,0,(int)local_27e0 * 9 + 0x5012e + g_clientContext,
                             local_27f0 + g_clientContext + 0x50196,puVar12,0,1);
                uVar11 = ((int)uVar11 < 0) - 1 & uVar11;
                pbVar14 = local_27d8;
                for (uVar9 = uVar11 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
                  *(undefined4 *)pbVar14 = *(undefined4 *)puVar12;
                  puVar12 = puVar12 + 2;
                  pbVar14 = pbVar14 + 4;
                }
                for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
                  *pbVar14 = (byte)*puVar12;
                  puVar12 = (ushort *)((int)puVar12 + 1);
                  pbVar14 = pbVar14 + 1;
                }
                (&stack0xffffd807)[param_3] = 0;
                FUN_004382d0();
                iVar4 = GetPlayerRecordBySlot(g_clientContext);
                iVar10 = g_clientContext + 0x45354;
                *(undefined1 *)(iVar4 + 0x900) = 1;
                cVar2 = PacketChecksumEquals(iVar10,3);
                if (cVar2 != '\0') {
                  local_27f0 = (undefined *)0x0;
                  do {
                    iVar10 = FindSpriteFrame();
                    if (iVar10 != 0) {
                      iVar6 = PeekChecksumStateUnderLock(iVar4 + 0x90c);
                      iVar10 = PeekChecksumStateUnderLock(iVar10 + 0x25c);
                      uVar11 = iVar10 - iVar6 >> 0x1f;
                      if ((int)((iVar10 - iVar6 ^ uVar11) - uVar11) < 0x96) {
                        FUN_00415bc0(local_27d8);
                      }
                    }
                    local_27f0 = local_27f0 + 1;
                  } while ((int)local_27f0 < 8);
                  *unaff_FS_OFFSET = local_14;
                  return;
                }
              }
            }
          }
          else {
            if (uVar1 == 3) {
              iVar4 = (uint)*(byte *)puVar12 * 0xd + 0x457f1 + g_clientContext;
              iVar10 = (uint)bVar16 * 0xd + 0x457f1 + g_clientContext;
              iVar6 = iVar4;
              pcVar5 = (char *)GetLocalizedString(&g_localizedStringTable,0x260);
              _sprintf((char *)local_27d8,pcVar5,iVar10,iVar4,iVar6);
              (**(code **)(*param_1 + 0x28))(local_27d8,2,6);
              *unaff_FS_OFFSET = uStack_20;
              return;
            }
            if (((uVar1 == 0x4001) &&
                (uVar11 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c), bVar16 != uVar11)) &&
               (iVar4 = GetPlayerRecordBySlot(g_clientContext), iVar4 != 0)) {
              QueueOutgoingPacketField(*(byte *)puVar12 == 1);
              *unaff_FS_OFFSET = local_14;
              return;
            }
          }
        }
        else if ((uVar1 == 0x4003) &&
                (uVar9 = (uint)bVar16, *(char *)(uVar9 + 0x5010d + g_clientContext) != '\0')) {
          local_27f0 = (undefined *)(uVar9 * 0xd);
          local_27e0 = (int *)uVar9;
          iVar4 = FUN_004259d0(local_27f0 + g_clientContext + 0x50196);
          if ((iVar4 == -1) &&
             (*(char *)(uVar9 + 0x50126 + g_clientContext) == *(char *)(g_clientContext + 0x3b6c0))) {
            local_2658 = 0;
            pbVar14 = local_2657;
            for (iVar4 = 0xff; iVar4 != 0; iVar4 = iVar4 + -1) {
              pbVar14[0] = 0;
              pbVar14[1] = 0;
              pbVar14[2] = 0;
              pbVar14[3] = 0;
              pbVar14 = pbVar14 + 4;
            }
            pbVar14[0] = 0;
            pbVar14[1] = 0;
            pbVar14[2] = 0;
            puVar13 = puVar12;
            pbVar14 = &local_2658;
            for (uVar9 = uVar11 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
              *(undefined4 *)pbVar14 = *(undefined4 *)puVar13;
              puVar13 = puVar13 + 2;
              pbVar14 = pbVar14 + 4;
            }
            uVar21 = 0;
            for (uVar9 = uVar11 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
              *pbVar14 = (byte)*puVar13;
              puVar13 = (ushort *)((int)puVar13 + 1);
              pbVar14 = pbVar14 + 1;
            }
            FUN_004e3740(&DAT_00794e14);
            AcquireSoundChannel(uVar21);
            FUN_0041ef90(g_clientContext,7,local_27e4,puVar12,uVar11,local_27ec[3] + 300,0);
            FUN_0041b8c0(g_clientContext,7,(int)local_27e0 * 9 + 0x5012e + g_clientContext,
                         local_27f0 + g_clientContext + 0x50196,puVar12,0,1);
            uVar11 = ((int)uVar11 < 0) - 1 & uVar11;
            pbVar14 = local_27d8;
            for (uVar9 = uVar11 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
              *(undefined4 *)pbVar14 = *(undefined4 *)puVar12;
              puVar12 = puVar12 + 2;
              pbVar14 = pbVar14 + 4;
            }
            for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
              *pbVar14 = (byte)*puVar12;
              puVar12 = (ushort *)((int)puVar12 + 1);
              pbVar14 = pbVar14 + 1;
            }
            (&stack0xffffd807)[param_3] = 0;
            FUN_004382d0();
            iVar4 = GetPlayerRecordBySlot(g_clientContext);
            *(undefined1 *)(iVar4 + 0x900) = 1;
            *unaff_FS_OFFSET = local_14;
            return;
          }
        }
      }
      else if (uVar1 == 0x4005) {
        uVar11 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        if (bVar16 != uVar11) {
          iVar4 = GetPlayerRecordBySlot(g_clientContext);
          bVar16 = *(byte *)puVar12;
          iVar4 = *(int *)(iVar4 + 0x24);
          if ((((iVar4 != 5) && (iVar4 != 6)) && (iVar4 != 8)) && (iVar4 != 10)) {
            QueueOutgoingPacketField(*(char *)(param_2 + 0x22) == '\x01');
            SetGuardedBool(bVar16 == 1);
            *unaff_FS_OFFSET = local_14;
            return;
          }
        }
      }
      else if (uVar1 == 0x4006) {
        uVar11 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        if (bVar16 != uVar11) {
          GetPlayerRecordBySlot(g_clientContext);
          QueueOutgoingPacketField((int)(short)*puVar12);
          *unaff_FS_OFFSET = local_14;
          return;
        }
      }
      else if (((((uVar1 == 0x8005) &&
                 (uVar11 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c), bVar16 != uVar11)) &&
                ((iVar4 = GetPlayerRecordBySlot(g_clientContext), iVar4 != 0 &&
                 ((cVar2 = PeekPacketChecksumBool(), cVar2 != '\0' && (cVar2 = PeekPacketChecksumBool(), cVar2 != '\0'))
                 )))) && (*(int *)(iVar4 + 0x24) != 5)) && (*(int *)(iVar4 + 0x24) != 6)) {
        QueueOutgoingPacketField(*puVar12);
        QueueOutgoingPacketField(*(undefined2 *)(param_2 + 0x23));
        *unaff_FS_OFFSET = local_14;
        return;
      }
      goto switchD_004b64f9_caseD_c302;
    }
    if (0x8405 < uVar1) {
      if (uVar1 == 0x8406) {
        iVar4 = GetPlayerRecordBySlot(g_clientContext);
        if ((iVar4 != 0) && (uVar11 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c), bVar16 != uVar11)) {
          uVar21 = QueueOutgoingPacketField(*puVar12);
          EncodeChecksumState(uVar21);
          uVar21 = QueueOutgoingPacketField(*(undefined2 *)(param_2 + 0x23));
          EncodeChecksumState(uVar21);
          QueueOutgoingPacketField(*(char *)(param_2 + 0x25) == '\x01');
          *unaff_FS_OFFSET = local_14;
          return;
        }
      }
      else if (uVar1 == 0x8407) {
        bVar16 = *(byte *)puVar12;
        if (bVar16 == 1) {
          uVar21 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
          AddToPacketChecksum(uVar21);
          *unaff_FS_OFFSET = local_14;
          return;
        }
        if (bVar16 == 2) {
          uVar21 = PeekChecksumStateUnderLock(&DAT_00e9b818);
          AddToPacketChecksum(uVar21);
          *unaff_FS_OFFSET = local_14;
          return;
        }
        if (bVar16 == 3) {
          uVar21 = PeekChecksumStateUnderLock(&DAT_00796aa0);
          AddToPacketChecksum(uVar21);
          *unaff_FS_OFFSET = local_14;
          return;
        }
      }
      else if (uVar1 == 0x8408) {
        param_1[param_1[0x227] + 0x228] = (uint)*puVar12;
        param_1[param_1[0x227] + 0x2a8] = (uint)*(ushort *)(param_2 + 0x23);
        param_1[param_1[0x227] + 0x3a8] = *(int *)(param_2 + 0x25);
        param_1[param_1[0x227] + 0x328] = (uint)bVar16;
        FUN_004ccc60(param_1);
        param_1[0x227] = param_1[0x227] + 1;
        *unaff_FS_OFFSET = local_14;
        return;
      }
      goto switchD_004b64f9_caseD_c302;
    }
    if (uVar1 == 0x8405) {
      FUN_0043c440();
      local_27f0 = &DAT_006a7f70 + g_clientContext;
      FUN_0043c4a0();
      FUN_0043c4f0();
      SetGuardedBool(0);
      FUN_004207c0(g_clientContext,bVar16);
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        uVar11 = PacketChecksumGreaterThan(*(int *)(g_clientContext + 0x621e0) + 0xc080,4);
        if (((char)uVar11 == '\0') ||
           (uVar11 = *(uint *)(g_clientContext + 0x621e0), *(short *)(uVar11 + 0xbfbc) != 0)) {
          uVar11 = uVar11 & 0xffffff00;
        }
        else {
          uVar11 = CONCAT31((int3)(uVar11 >> 8),1);
        }
        CreateButtonWidget(&DAT_00e9be90,0,0x12,0x3fa,s_b_play_weapon3_00554144,0x58,0x232,0x23,0x22
                           ,uVar11,0);
        cVar2 = PacketChecksumGreaterThan(*(int *)(g_clientContext + 0x621e0) + 0xc080,4);
        if ((cVar2 == '\0') || (*(short *)(*(int *)(g_clientContext + 0x621e0) + 0xbfbc) != 0)) {
          uVar21 = 0;
        }
        else {
          uVar21 = 1;
        }
        FUN_00406300(uVar21);
      }
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        cVar2 = PeekPacketChecksumBool();
        if (cVar2 == '\x01') {
          FUN_00406300(1);
          FUN_00405fb0();
          CreateButtonWidget(&DAT_00e9be90,0,1,0x3e9,s_b_play_weapon1_00554164,6,0x232,0x23,0x22,1,0
                            );
          *unaff_FS_OFFSET = local_14;
          return;
        }
        FUN_00406300(1);
        FUN_00405fb0();
        CreateButtonWidget(&DAT_00e9be90,0,2,0x3ea,s_b_play_weapon2_00554154,0x2f,0x232,0x23,0x22,1,
                           0);
        *unaff_FS_OFFSET = local_14;
        return;
      }
      goto switchD_004b64f9_caseD_c302;
    }
    if (0x8403 < uVar1) {
      if (uVar1 == 0x8404) {
        param_1[param_1[0x26] + 0x27] = (uint)*puVar12;
        param_1[param_1[0x26] + 0xa7] = (uint)*(ushort *)(param_2 + 0x23);
        param_1[param_1[0x26] + 0x127] = (uint)*(byte *)(param_2 + 0x25);
        param_1[param_1[0x26] + 0x1a7] = (uint)*(byte *)(param_2 + 0x26);
        FUN_004ccbb0(param_1);
        param_1[0x26] = param_1[0x26] + 1;
        *unaff_FS_OFFSET = local_14;
        return;
      }
      goto switchD_004b64f9_caseD_c302;
    }
    if (uVar1 != 0x8403) {
      if (uVar1 == 0x8104) {
        CreateButtonWidget(&DAT_00e9be90,0,0x10,0x3f8,s_b_result_confirm_00554074,0x29f,0x1b9,0x67,
                           0x2d,1,0);
        *unaff_FS_OFFSET = local_14;
        return;
      }
      if (((uVar1 == 0x8402) && (uVar11 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c), bVar16 != uVar11))
         && (iVar4 = GetPlayerRecordBySlot(g_clientContext), iVar4 != 0)) {
        uVar21 = QueueOutgoingPacketField(*puVar12);
        EncodeChecksumState(uVar21);
        uVar21 = QueueOutgoingPacketField(*(undefined2 *)(param_2 + 0x23));
        EncodeChecksumState(uVar21);
        QueueOutgoingPacketField(*(char *)(param_2 + 0x25) == '\x01');
        *unaff_FS_OFFSET = local_14;
        return;
      }
      goto switchD_004b64f9_caseD_c302;
    }
    piVar7 = (int *)GetPlayerRecordBySlot(g_clientContext);
    if (piVar7 == (int *)0x0) goto switchD_004b64f9_caseD_c302;
    uVar21 = QueueOutgoingPacketField(*puVar12);
    EncodeChecksumState(uVar21);
    uVar21 = QueueOutgoingPacketField(*(undefined2 *)(param_2 + 0x23));
    EncodeChecksumState(uVar21);
    QueueOutgoingPacketField(*(char *)(param_2 + 0x25) == '\x01');
    SetGuardedBool(*(char *)(param_2 + 0x26) == '\x01');
    QueueOutgoingPacketField(*(undefined2 *)(param_2 + 0x27));
    QueueOutgoingPacketField(*(undefined2 *)(param_2 + 0x29));
    *(undefined1 *)(piVar7 + 0x1947) = *(undefined1 *)(param_2 + 0x2b);
    QueueOutgoingPacketField((int)*(short *)(param_2 + 0x2c));
    QueueOutgoingPacketField((int)*(short *)(param_2 + 0x2e));
    QueueOutgoingPacketField((int)*(short *)(param_2 + 0x30));
    QueueOutgoingPacketField((int)*(short *)(param_2 + 0x32));
    QueueOutgoingPacketField((int)*(short *)(param_2 + 0x34));
    QueueOutgoingPacketField((int)*(short *)(param_2 + 0x36));
    QueueOutgoingPacketField((int)*(short *)(param_2 + 0x38));
    QueueOutgoingPacketField((int)*(short *)(param_2 + 0x3a));
    SetGuardedBool(*(char *)(param_2 + 0x3c) == '\x01');
    FUN_0043d780(param_2 + 0x3d);
    cVar2 = FUN_0043c820();
    if (cVar2 == '\x01') {
      *(undefined4 *)((int)piVar7 + 0xbffa) = SUBFIELD(s_ifire_00553b60,0,undefined4);
      *(undefined2 *)((int)piVar7 + 0xbffe) = SUBFIELD(s_ifire_00553b60,4,undefined2);
      *unaff_FS_OFFSET = local_14;
      return;
    }
    iVar4 = *piVar7;
    pcVar5 = s_ifire_00553b60;
LAB_004b5f6b:
    (**(code **)(iVar4 + 4))(pcVar5);
LAB_004b5f6e:
    piVar7 = local_27ec;
    iVar4 = local_27ec[0x428];
    iVar6 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
    iVar10 = g_clientContext;
    if (iVar4 == iVar6) {
LAB_004b7c01:
      *(undefined4 *)(*(int *)(g_clientContext + 0x621e0) + 0xb0b0) = 3;
      *unaff_FS_OFFSET = local_14;
      return;
    }
    if (*(char *)(iVar4 + 0x4590c + g_clientContext) != *(char *)(g_clientContext + 0x3b6c0)) {
      *(undefined4 *)(*(int *)(g_clientContext + 0x621e0) + 0xb0b0) = 1;
    }
    iVar4 = piVar7[0x428];
  }
  else {
    if (uVar1 < 0xc401) {
      if (uVar1 != 0xc400) {
        switch(uVar1) {
        case 0xc300:
          SetGuardedBool(0);
          param_1[0x8f3] = -1;
          if ((char)param_1[0x474] == '\0') {
            FUN_004d0a10(param_1,param_2 + 0x22);
          }
          PostTurnEvent(&DAT_00e55ce0,0xc300);
          PostTurnEvent(&DAT_00e55ce0,0xc306);
          PostTurnEvent(&DAT_00e55ce0,0xc40b);
          *unaff_FS_OFFSET = local_14;
          return;
        case 0xc301:
          param_1[0x429] = (uint)*(ushort *)(param_2 + 0x22);
          piVar7 = (int *)GetPlayerRecordBySlot(iVar4);
          if (piVar7 != (int *)0x0) {
            if ((piVar7[9] != 0xe) && (cVar2 = PeekPacketChecksumBool(), cVar2 == '\x01')) {
              uVar21 = EncodeChecksumPairSum(piVar7 + 0x19d1,local_2258,piVar7 + 0x1b6c);
              local_c = 2;
              uVar21 = EncodeChecksumDeltaDiv(uVar21,local_8a8,3);
              SUBFIELD(local_c,0,undefined1) = 3;
              local_27e5 = CompareChecksumPair(piVar7 + 0x1a5a,uVar21);
              local_c = CONCAT31(SUBFIELD(local_c,1,undefined3),2);
              ScrubChecksumGuard();
              local_c = 0xffffffff;
              ScrubChecksumGuard();
              if (local_27e5 == 0) {
                (**(code **)(*piVar7 + 4))(s_normal_00552230);
              }
              else {
                (**(code **)(*piVar7 + 4))(s_wnormal_00553618);
              }
            }
            if (piVar7[0x2c29] != -1) {
              FUN_004eeae0();
              piVar7[0x2c29] = -1;
            }
            SetGuardedBool(0);
            SetGuardedBool(0);
          }
          iVar4 = PeekChecksumStateUnderLock((uint)bVar16 * 0x224 + 0xebef4 + g_clientContext);
          if (((iVar4 != -1) && (iVar4 = local_27ec[0x429], iVar4 != 60000)) && (iVar4 != 0xffff)) {
            AddToPacketChecksum(iVar4);
          }
          puVar15 = (undefined4 *)(param_2 + 0x24);
          puVar18 = (undefined4 *)((int)local_27ec + 0x2302);
          for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar18 = *puVar15;
            puVar15 = puVar15 + 1;
            puVar18 = puVar18 + 1;
          }
          SetGuardedBool(1);
          *(undefined1 *)(*(int *)(g_clientContext + 0x621e0) + 0xae68) = 1;
          *unaff_FS_OFFSET = local_14;
          return;
        case 0xc303:
          *(undefined4 *)(&DAT_006a7704 + g_clientContext) = 0xffffffff;
          SetGuardedBool(0);
          iVar4 = g_clientContext;
          switch(*(byte *)puVar12) {
          case 0:
            param_1[0x42e] = 3;
            FUN_004cf310();
            *unaff_FS_OFFSET = local_14;
            return;
          case 1:
            param_1[0x42e] = 4;
            FUN_004cf310();
            *unaff_FS_OFFSET = local_14;
            return;
          case 2:
            param_1[0x42e] = 0;
            FUN_004cf310();
            *unaff_FS_OFFSET = local_14;
            return;
          case 0xe:
            local_27ec[0x429] = (uint)*(ushort *)(param_2 + 0x22);
            piVar7 = (int *)GetPlayerRecordBySlot(iVar4);
            if (piVar7 != (int *)0x0) {
              if ((piVar7[9] != 0xe) && (cVar2 = PeekPacketChecksumBool(), cVar2 == '\x01')) {
                uVar21 = EncodeChecksumPairSum(piVar7 + 0x19d1,local_1e10,piVar7 + 0x1b6c);
                local_c = 0;
                uVar21 = EncodeChecksumDeltaDiv(uVar21,local_19c8,3);
                SUBFIELD(local_c,0,undefined1) = 1;
                local_27e5 = CompareChecksumPair(piVar7 + 0x1a5a,uVar21);
                local_c = (uint)SUBFIELD(local_c,1,undefined3) << 8;
                ScrubChecksumGuard();
                local_c = 0xffffffff;
                ScrubChecksumGuard();
                if (local_27e5 == 0) {
                  (**(code **)(*piVar7 + 4))(s_normal_00552230);
                }
                else {
                  (**(code **)(*piVar7 + 4))(s_wnormal_00553618);
                }
              }
              if (piVar7[0x2c29] != -1) {
                FUN_004eeae0();
                piVar7[0x2c29] = -1;
              }
            }
            piVar7 = local_27ec;
            AddToPacketChecksum(local_27ec[0x429]);
            iVar10 = g_clientContext + 0x621e8;
            puVar15 = (undefined4 *)(param_2 + 0x24);
            puVar18 = (undefined4 *)((int)piVar7 + 0x2302);
            for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
              *puVar18 = *puVar15;
              puVar15 = puVar15 + 1;
              puVar18 = puVar18 + 1;
            }
            cVar2 = PacketChecksumEquals(iVar10,0xffffffff);
            if (cVar2 != '\0') {
              FUN_0043a5f0();
              FUN_004d0e90(piVar7);
              local_27f0 = (undefined *)0xc300;
              FUN_004e8a70();
              if (local_27e4 != DAT_00e9af14) {
                FUN_004e87b0(&DAT_00e9af10,&local_27f0,local_27e4);
              }
              local_27f0 = (undefined *)0xc306;
              FUN_004e8a70();
              if (local_27e4 != DAT_00e9af14) {
                FUN_004e87b0(&DAT_00e9af10,&local_27f0,local_27e4);
              }
              local_27f0 = (undefined *)0xc40b;
              FUN_004e8a70();
              if (local_27e4 != DAT_00e9af14) {
                FUN_004e87b0(&DAT_00e9af10,&local_27f0,local_27e4);
              }
              PostTurnEvent(&DAT_00e55ce0,0x8005);
              PostTurnEvent(&DAT_00e55ce0,0x8006);
              PostTurnEvent(&DAT_00e55ce0,0xc306);
              PostTurnEvent(&DAT_00e55ce0,0xc400);
              PostTurnEvent(&DAT_00e55ce0,0xc401);
              PostTurnEvent(&DAT_00e55ce0,0x8403);
              PostTurnEvent(&DAT_00e55ce0,0x8405);
              PostTurnEvent(&DAT_00e55ce0,0xc409);
              FUN_004cb280(piVar7);
              *unaff_FS_OFFSET = local_14;
              return;
            }
            DAT_0056dbe8 = 0xe;
            *unaff_FS_OFFSET = local_14;
            return;
          case 0xf:
            cVar2 = PacketChecksumEquals(g_clientContext + 0x621e8,0xffffffff);
            if (cVar2 != '\0') {
              FUN_0043a5f0();
              FUN_004d0e90(param_1);
              local_27f0 = (undefined *)0xc300;
              FUN_004e8a70();
              if (local_27e4 != DAT_00e9af14) {
                FUN_004e87b0(&DAT_00e9af10,&local_27f0,local_27e4);
              }
              local_27f0 = (undefined *)0xc306;
              FUN_004e8a70();
              if (local_27e4 != DAT_00e9af14) {
                FUN_004e87b0(&DAT_00e9af10,&local_27f0,local_27e4);
              }
              local_27f0 = (undefined *)0xc40b;
              FUN_004e8a70();
              if (local_27e4 != DAT_00e9af14) {
                FUN_004e87b0(&DAT_00e9af10,&local_27f0,local_27e4);
              }
              PostTurnEvent(&DAT_00e55ce0,0x8005);
              PostTurnEvent(&DAT_00e55ce0,0x8006);
              PostTurnEvent(&DAT_00e55ce0,0xc306);
              PostTurnEvent(&DAT_00e55ce0,0xc400);
              PostTurnEvent(&DAT_00e55ce0,0xc401);
              PostTurnEvent(&DAT_00e55ce0,0x8403);
              PostTurnEvent(&DAT_00e55ce0,0x8405);
              PostTurnEvent(&DAT_00e55ce0,0xc409);
              FUN_004cb280(param_1);
              *unaff_FS_OFFSET = local_14;
              return;
            }
            DAT_0056dbe8 = 0xf;
            *unaff_FS_OFFSET = local_14;
            return;
          }
          break;
        case 0xc304:
          local_27e5 = *(byte *)puVar12;
          local_27e0 = (int *)(uint)bVar16;
          local_27f0 = (undefined *)GetPlayerRecordBySlot(g_clientContext);
          if (local_27f0 == (undefined *)0x0) break;
          uVar11 = (uint)*(byte *)(param_2 + 0x25);
          iVar4 = GetPlayerRecordBySlot(g_clientContext);
          piVar7 = local_27ec;
          if ((((iVar4 != 0) && (*(char *)(g_clientContext + 0x45120) != '\0')) &&
              ((char)local_27ec[0x474] == '\0')) &&
             (cVar2 = PacketChecksumNotEquals(g_clientContext + 0x45354,3), bVar16 = local_27e5,
             cVar2 != '\0')) {
            FUN_0040a280();
            piVar7 = local_27e0;
            bVar16 = bVar16 & 0xf;
            local_c = 4;
            if ((local_27e5 & 0x10) == 0) {
              if (bVar16 == 1) {
                local_27dc = uVar11 * 0x224;
                AddToPacketChecksum(1);
                EncodeChecksumStateXored();
                iVar10 = PeekChecksumStateUnderLock(uVar11 * 0x1120 + 0x5113c + g_clientContext);
                iVar6 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                uVar21 = EncodeChecksumDeltaMul(&local_2658,local_acc,iVar10 + iVar6);
                SUBFIELD(local_c,0,undefined1) = 0xb;
                uVar20 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                uVar21 = EncodeChecksumDeltaDiv(uVar21,local_f14,uVar20);
                SUBFIELD(local_c,0,undefined1) = 0xc;
                EncodeChecksumState(uVar21);
                SUBFIELD(local_c,0,undefined1) = 0xb;
                ScrubChecksumGuard();
                local_c = CONCAT31(SUBFIELD(local_c,1,undefined3),4);
                ScrubChecksumGuard();
                EmitChecksumSum(&local_2658);
                uVar22 = 1;
                uVar21 = PeekChecksumStateUnderLock(iVar4 + 0xb30);
                uVar20 = PeekChecksumStateUnderLock(iVar4 + 0x90c);
                FUN_004368f0(uVar20,uVar21,uVar22);
                uVar21 = PeekChecksumStateUnderLock(&local_2658);
                iVar4 = iVar4 + 0xae15;
                pcVar5 = (char *)GetLocalizedString(&g_localizedStringTable,0x265);
                _sprintf((char *)local_27d8,pcVar5,iVar4,uVar21);
                (**(code **)(*local_27ec + 0x28))(local_27d8,4,3);
                FUN_0040b030();
              }
              else if (bVar16 == 2) {
                local_27dc = uVar11 * 0x224;
                SubFromPacketChecksum(2);
                EncodeChecksumStateXored();
                iVar10 = PeekChecksumStateUnderLock(uVar11 * 0x1120 + 0x5113c + g_clientContext);
                iVar6 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                uVar21 = EncodeChecksumDeltaMul(&local_2658,local_135c,iVar10 + iVar6);
                SUBFIELD(local_c,0,undefined1) = 0xd;
                uVar20 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                uVar21 = EncodeChecksumDeltaDiv(uVar21,local_17a4,uVar20);
                SUBFIELD(local_c,0,undefined1) = 0xe;
                EncodeChecksumState(uVar21);
                SUBFIELD(local_c,0,undefined1) = 0xd;
                ScrubChecksumGuard();
                local_c = CONCAT31(SUBFIELD(local_c,1,undefined3),4);
                ScrubChecksumGuard();
                EmitChecksumSum(&local_2658);
                uVar22 = 0xfffffffc;
                uVar21 = PeekChecksumStateUnderLock(iVar4 + 0xb30);
                uVar20 = PeekChecksumStateUnderLock(iVar4 + 0x90c);
                FUN_004368f0(uVar20,uVar21,uVar22);
                uVar21 = PeekChecksumStateUnderLock(&local_2658);
                iVar4 = iVar4 + 0xae15;
                pcVar5 = (char *)GetLocalizedString(&g_localizedStringTable,0x266);
                _sprintf((char *)local_27d8,pcVar5,iVar4,uVar21);
                (**(code **)(*local_27ec + 0x28))(local_27d8,3,2);
              }
            }
            else {
              if (bVar16 == 1) {
                local_27dc = uVar11 * 0x224;
                AddToPacketChecksum(1);
                EncodeChecksumStateXored();
                iVar10 = PeekChecksumStateUnderLock(uVar11 * 0x1120 + 0x5113c + g_clientContext);
                iVar6 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                uVar21 = EncodeChecksumDeltaMul(&local_2658,local_1bec,iVar10 + iVar6);
                SUBFIELD(local_c,0,undefined1) = 5;
                uVar20 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                uVar21 = EncodeChecksumDeltaDiv(uVar21,local_2034,uVar20);
                SUBFIELD(local_c,0,undefined1) = 6;
                EncodeChecksumState(uVar21);
                SUBFIELD(local_c,0,undefined1) = 5;
                ScrubChecksumGuard();
                local_c = CONCAT31(SUBFIELD(local_c,1,undefined3),4);
                ScrubChecksumGuard();
                EmitChecksumSum(&local_2658);
                uVar22 = 1;
                uVar21 = PeekChecksumStateUnderLock(iVar4 + 0xb30);
                uVar20 = PeekChecksumStateUnderLock(iVar4 + 0x90c);
                FUN_004368f0(uVar20,uVar21,uVar22);
                uVar21 = PeekChecksumStateUnderLock(&local_2658);
                iVar4 = iVar4 + 0xae15;
                pcVar5 = (char *)GetLocalizedString(&g_localizedStringTable,0x262);
                _sprintf((char *)local_27d8,pcVar5,iVar4,uVar21);
                (**(code **)(*local_27ec + 0x28))(local_27d8,4,3);
                FUN_0040b030();
                puVar8 = local_27f0;
              }
              else if (bVar16 == 2) {
                local_27dc = uVar11 * 0x224;
                SubFromPacketChecksum(2);
                EncodeChecksumStateXored();
                iVar10 = PeekChecksumStateUnderLock(uVar11 * 0x1120 + 0x5113c + g_clientContext);
                iVar6 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                uVar21 = EncodeChecksumDeltaMul(&local_2658,local_1138,iVar10 + iVar6);
                SUBFIELD(local_c,0,undefined1) = 7;
                uVar20 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                uVar21 = EncodeChecksumDeltaDiv(uVar21,local_460,uVar20);
                SUBFIELD(local_c,0,undefined1) = 8;
                EncodeChecksumState(uVar21);
                SUBFIELD(local_c,0,undefined1) = 7;
                ScrubChecksumGuard();
                local_c = CONCAT31(SUBFIELD(local_c,1,undefined3),4);
                ScrubChecksumGuard();
                EmitChecksumSum(&local_2658);
                uVar22 = 0xfffffffc;
                uVar21 = PeekChecksumStateUnderLock(iVar4 + 0xb30);
                uVar20 = PeekChecksumStateUnderLock(iVar4 + 0x90c);
                FUN_004368f0(uVar20,uVar21,uVar22);
                uVar21 = PeekChecksumStateUnderLock(&local_2658);
                iVar4 = iVar4 + 0xae15;
                pcVar5 = (char *)GetLocalizedString(&g_localizedStringTable,0x263);
                _sprintf((char *)local_27d8,pcVar5,iVar4,uVar21);
                (**(code **)(*local_27ec + 0x28))(local_27d8,3,2);
                puVar8 = local_27f0;
              }
              else {
                puVar8 = local_27f0;
                if (bVar16 == 3) {
                  SubFromPacketChecksum(1);
                  EncodeChecksumStateXored();
                  iVar4 = PeekChecksumStateUnderLock((int)piVar7 * 0x1120 + 0x5113c + g_clientContext);
                  iVar10 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                  uVar21 = EncodeChecksumDeltaMul(&local_2658,local_1580,iVar4 + iVar10);
                  SUBFIELD(local_c,0,undefined1) = 9;
                  uVar20 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                  uVar21 = EncodeChecksumDeltaDiv(uVar21,local_cf0,uVar20);
                  SUBFIELD(local_c,0,undefined1) = 10;
                  EncodeChecksumState(uVar21);
                  SUBFIELD(local_c,0,undefined1) = 9;
                  ScrubChecksumGuard();
                  local_c = CONCAT31(SUBFIELD(local_c,1,undefined3),4);
                  ScrubChecksumGuard();
                  EmitChecksumSum(&local_2658);
                  puVar8 = local_27f0;
                  uVar22 = 0xffffffff;
                  uVar21 = PeekChecksumStateUnderLock(local_27f0 + 0xb30);
                  uVar20 = PeekChecksumStateUnderLock(puVar8 + 0x90c);
                  FUN_004368f0(uVar20,uVar21,uVar22);
                  uVar21 = PeekChecksumStateUnderLock(&local_2658);
                  puVar19 = puVar8 + 0xae15;
                  pcVar5 = (char *)GetLocalizedString(&g_localizedStringTable,0x264);
                  _sprintf((char *)local_27d8,pcVar5,puVar19,uVar21);
                  (**(code **)(*local_27ec + 0x28))(local_27d8,3,2);
                }
              }
              QueueOutgoingPacketField(10000);
              puVar8[0xae14] = 1;
            }
            local_c = 0xffffffff;
            ScrubChecksumGuard();
            piVar7 = local_27ec;
          }
          FUN_004cf050(piVar7);
          cVar2 = PacketChecksumEquals(g_clientContext + 0x45354,1);
          if (cVar2 != '\0') {
            cVar2 = *(char *)((int)local_27e0 + g_clientContext + 0x50126);
            if (cVar2 == '\0') {
              iVar4 = *piVar7;
              uVar22 = 8;
              uVar20 = 3;
              uVar21 = GetLocalizedString(&g_localizedStringTable,0x25c);
              (**(code **)(iVar4 + 0x28))(uVar21,uVar20,uVar22);
              FUN_0040b060();
              cVar2 = PacketChecksumLessThan(&DAT_0067e3d0 + g_clientContext,0);
            }
            else {
              if (cVar2 != '\x01') goto LAB_004b7674;
              iVar4 = *piVar7;
              uVar22 = 8;
              uVar20 = 3;
              uVar21 = GetLocalizedString(&g_localizedStringTable,0x25d);
              (**(code **)(iVar4 + 0x28))(uVar21,uVar20,uVar22);
              FUN_0040b060();
              cVar2 = PacketChecksumLessThan(&DAT_0067e5f4 + g_clientContext,0);
            }
            if (cVar2 != '\0') {
              QueueOutgoingPacketField(0);
            }
          }
LAB_004b7674:
          cVar2 = PeekPacketChecksumBool();
          if (cVar2 != '\x01') break;
LAB_004b7fb2:
          cVar2 = FUN_0040b390(g_clientContext + 0x3b49c,g_clientContext + 0x3b6c4);
          if (((cVar2 != '\0') && (cVar2 = PeekPacketChecksumBool(), cVar2 == '\0')) &&
             ((g_currentGameState != 0xb || (cVar2 = PeekPacketChecksumBool(), cVar2 != '\x01')))) {
            FUN_00413bf0();
            *unaff_FS_OFFSET = local_14;
            return;
          }
          break;
        case 0xc305:
          *(undefined1 *)(param_1 + 0x42f) = 0;
          SetGuardedBool(1);
          cVar2 = *(char *)(g_clientContext + 0x45127);
          if (cVar2 == '\x01') {
            *(undefined4 *)(&DAT_006a647c + g_clientContext) = 0x11;
          }
          else if (cVar2 == '\x02') {
            *(undefined4 *)(&DAT_006a647c + g_clientContext) = 0x10;
          }
          else if (cVar2 == '\x03') {
            *(undefined4 *)(&DAT_006a647c + g_clientContext) = 0xb5;
          }
          PlayMusicTrack(1);
          FUN_00438360();
          iVar4 = *local_27ec;
          uVar22 = 6;
          uVar20 = 2;
          uVar21 = GetLocalizedString(&g_localizedStringTable,0x267);
          (**(code **)(iVar4 + 0x28))(uVar21,uVar20,uVar22);
          *unaff_FS_OFFSET = uStack_20;
          return;
        case 0xc306:
          SetGuardedBool(0);
          iVar4 = g_clientContext;
          local_27ec[0x8f3] = -1;
          iVar4 = GetPlayerRecordBySlot(iVar4);
          uVar11 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
          if (bVar16 == uVar11) {
            puVar12 = (ushort *)(param_2 + 0x26);
          }
          else if (iVar4 != 0) {
            uVar21 = QueueOutgoingPacketField(*puVar12);
            EncodeChecksumState(uVar21);
            uVar21 = QueueOutgoingPacketField(*(undefined2 *)(param_2 + 0x23));
            EncodeChecksumState(uVar21);
            puVar12 = (ushort *)(param_2 + 0x26);
            QueueOutgoingPacketField(*(char *)(param_2 + 0x25) == '\x01');
          }
          local_27ec[0x429] = (uint)*(ushort *)((int)puVar12 + 1);
          if ((iVar4 != 0) && (*(int *)(iVar4 + 0xb0a4) != -1)) {
            FUN_004eeae0();
            *(undefined4 *)(iVar4 + 0xb0a4) = 0xffffffff;
          }
          if (local_27ec[0x429] == 0xffff) {
            QueueOutgoingPacketField(0xffffffff);
          }
          iVar4 = PeekChecksumStateUnderLock((uint)bVar16 * 0x224 + 0xebef4 + g_clientContext);
          if ((iVar4 != -1) && (local_27ec[0x429] != 60000)) {
            AddToPacketChecksum(local_27ec[0x429]);
          }
          pbVar14 = (byte *)((int)puVar12 + 3);
          puVar15 = (undefined4 *)((int)local_27ec + 0x2302);
          for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar15 = *(undefined4 *)pbVar14;
            pbVar14 = pbVar14 + 4;
            puVar15 = puVar15 + 1;
          }
          SetGuardedBool(1);
          SetGuardedBool(1);
          SetGuardedBool(0);
          *unaff_FS_OFFSET = local_14;
          return;
        case 0xc308:
          AddToPacketChecksum(3);
          puVar15 = (undefined4 *)((int)local_27ec + 0x2302);
          for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar15 = *(undefined4 *)puVar12;
            puVar12 = puVar12 + 2;
            puVar15 = puVar15 + 1;
          }
          *unaff_FS_OFFSET = local_14;
          return;
        }
        goto switchD_004b64f9_caseD_c302;
      }
      piVar7 = (int *)GetPlayerRecordBySlot(g_clientContext);
      QueueOutgoingPacketField(bVar16);
      if (piVar7 == (int *)0x0) goto switchD_004b64f9_caseD_c302;
      uVar21 = QueueOutgoingPacketField(*puVar12);
      EncodeChecksumState(uVar21);
      uVar21 = QueueOutgoingPacketField(*(undefined2 *)(param_2 + 0x23));
      EncodeChecksumState(uVar21);
      QueueOutgoingPacketField(*(char *)(param_2 + 0x25) == '\x01');
      SetGuardedBool(*(char *)(param_2 + 0x26) == '\x01');
      SetGuardedBool(0);
      QueueOutgoingPacketField((int)*(short *)(param_2 + 0x27));
      QueueOutgoingPacketField(*(undefined2 *)(param_2 + 0x29));
      *(undefined1 *)(piVar7 + 0x1947) = *(undefined1 *)(param_2 + 0x2b);
      QueueOutgoingPacketField((int)*(short *)(param_2 + 0x2c));
      QueueOutgoingPacketField((int)*(short *)(param_2 + 0x2e));
      QueueOutgoingPacketField((int)*(short *)(param_2 + 0x30));
      QueueOutgoingPacketField((int)*(short *)(param_2 + 0x32));
      QueueOutgoingPacketField((int)*(short *)(param_2 + 0x34));
      QueueOutgoingPacketField((int)*(short *)(param_2 + 0x36));
      QueueOutgoingPacketField((int)*(short *)(param_2 + 0x38));
      QueueOutgoingPacketField((int)*(short *)(param_2 + 0x3a));
      SetGuardedBool(*(char *)(param_2 + 0x3c) == '\x01');
      FUN_0043d780(param_2 + 0x3d);
      *(undefined1 *)(piVar7 + 0x2ffa) = 0;
      SetGuardedBool(0);
      cVar2 = FUN_0043c820();
      if (cVar2 == '\x01') {
        cVar2 = PeekPacketChecksumBool();
        if (cVar2 != '\0') {
          *(undefined4 *)((int)piVar7 + 0xbffa) = DAT_00553b70;
          *(undefined2 *)((int)piVar7 + 0xbffe) = DAT_00553b74;
          *unaff_FS_OFFSET = local_14;
          return;
        }
        *(undefined4 *)((int)piVar7 + 0xbffa) = DAT_00553b68;
        *(undefined2 *)((int)piVar7 + 0xbffe) = DAT_00553b6c;
        *unaff_FS_OFFSET = local_14;
        return;
      }
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        iVar4 = *piVar7;
        pcVar5 = (char *)&DAT_00553b68;
        goto LAB_004b5f6b;
      }
      (**(code **)(*piVar7 + 4))(&DAT_00553b70);
      goto LAB_004b5f6e;
    }
    if (0xc801 < uVar1) {
      switch(uVar1) {
      case 0xf008:
        g_pendingGameState = 0xf;
        g_stateChangeRequested = 0;
        DAT_0056d108 = 0;
        _DAT_007934d8 = 1;
        break;
      case 0xf009:
        FUN_004d0fd0(local_27e4,*(byte *)puVar12);
        *unaff_FS_OFFSET = local_14;
        return;
      case 0xf00a:
        iVar4 = GetPlayerRecordBySlot(g_clientContext);
        if (iVar4 != 0) {
          EncodeChecksumState(iVar4 + 0x6744);
          *unaff_FS_OFFSET = local_14;
          return;
        }
        break;
      case 0xf00b:
        ComposeAvatarSprites
                  (bVar16,*puVar12,*(undefined2 *)(param_2 + 0x23),*(undefined2 *)(param_2 + 0x25),
                   *(undefined2 *)(param_2 + 0x27));
        *unaff_FS_OFFSET = local_14;
        return;
      }
      goto switchD_004b64f9_caseD_c302;
    }
    if (uVar1 == 0xc801) {
      bVar16 = *(byte *)puVar12;
      uVar11 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
      if (((uVar11 == bVar16) && (*(int *)(g_clientContext + 0x621e0) != 0)) &&
         (cVar2 = PeekPacketChecksumBool(), cVar2 == '\0')) {
        SetGuardedBool(1);
        iVar6 = DAT_007934e8;
        iVar10 = g_clientContext;
        *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
        *(undefined2 *)(iVar6 + 0x4d4) = 0x4100;
        *(undefined4 *)(iVar6 + 0x4d6) = *(undefined4 *)(*(int *)(iVar10 + 0x621e0) + 0xb0b0);
        iVar4 = *(int *)(iVar6 + 0x44d0);
        *(int *)(iVar6 + 0x44d0) = iVar4 + 4;
        *(undefined1 *)(iVar4 + 0x4d4 + iVar6) =
             *(undefined1 *)(*(int *)(iVar10 + 0x621e0) + 0xb0ac);
        *(int *)(iVar6 + 0x44d0) = *(int *)(iVar6 + 0x44d0) + 1;
        SendOutgoingPacket();
        Replay_AppendEvent(0xc304);
        iVar4 = g_clientContext;
        *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) =
             *(undefined4 *)(*(int *)(g_clientContext + 0x621e0) + 0xb0b0);
        puVar8 = &DAT_00e9aad0 + g_replayEventCursor;
        g_replayEventCursor = g_replayEventCursor + 4;
        *puVar8 = *(undefined1 *)(*(int *)(iVar4 + 0x621e0) + 0xb0ac);
        g_replayEventCursor = g_replayEventCursor + 1;
        Replay_FlushEvent();
        *unaff_FS_OFFSET = local_14;
        return;
      }
      goto switchD_004b64f9_caseD_c302;
    }
    switch(uVar1) {
    case 0xc401:
      HandleTurnTimeoutSlot(param_1,local_27e4);
      *unaff_FS_OFFSET = local_14;
      return;
    default:
      goto switchD_004b64f9_caseD_c302;
    case 0xc409:
      piVar7 = (int *)GetPlayerRecordBySlot(g_clientContext);
      QueueOutgoingPacketField(bVar16);
      if (piVar7 == (int *)0x0) goto switchD_004b64f9_caseD_c302;
      uVar21 = QueueOutgoingPacketField(*puVar12);
      EncodeChecksumState(uVar21);
      uVar21 = QueueOutgoingPacketField(*(undefined2 *)(param_2 + 0x23));
      EncodeChecksumState(uVar21);
      QueueOutgoingPacketField(*(char *)(param_2 + 0x25) == '\x01');
      SetGuardedBool(1);
      QueueOutgoingPacketField(0);
      QueueOutgoingPacketField((int)*(short *)(param_2 + 0x27));
      QueueOutgoingPacketField(*(undefined2 *)(param_2 + 0x29));
      *(undefined1 *)(piVar7 + 0x1947) = *(undefined1 *)(param_2 + 0x2b);
      QueueOutgoingPacketField((int)*(short *)(param_2 + 0x2c));
      QueueOutgoingPacketField((int)*(short *)(param_2 + 0x2e));
      QueueOutgoingPacketField((int)*(short *)(param_2 + 0x30));
      QueueOutgoingPacketField((int)*(short *)(param_2 + 0x32));
      QueueOutgoingPacketField((int)*(short *)(param_2 + 0x34));
      QueueOutgoingPacketField((int)*(short *)(param_2 + 0x36));
      iVar4 = g_clientContext;
      *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 1;
      *(undefined4 *)(&DAT_005f376c + iVar4) = 0;
      QueueOutgoingPacketField((int)*(short *)(param_2 + 0x38));
      QueueOutgoingPacketField((int)*(short *)(param_2 + 0x3a));
      SetGuardedBool(*(char *)(param_2 + 0x3c) == '\x01');
      FUN_0043d780(param_2 + 0x3d);
      *(undefined1 *)(piVar7 + 0x2ffa) = 0;
      SetGuardedBool(0);
      cVar2 = FUN_0043c820();
      if (cVar2 == '\x01') {
        *(undefined4 *)((int)piVar7 + 0xbffa) = SUBFIELD(s_sfire_00553b78,0,undefined4);
        *(undefined2 *)((int)piVar7 + 0xbffe) = SUBFIELD(s_sfire_00553b78,4,undefined2);
        *unaff_FS_OFFSET = local_14;
        return;
      }
      (**(code **)(*piVar7 + 4))(s_sfire_00553b78);
      piVar7 = local_27ec;
      iVar4 = local_27ec[0x428];
      iVar6 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
      iVar10 = g_clientContext;
      if (iVar4 == iVar6) goto LAB_004b7c01;
      if (*(char *)(iVar4 + 0x4590c + g_clientContext) != *(char *)(g_clientContext + 0x3b6c0)) {
        *(undefined4 *)(*(int *)(g_clientContext + 0x621e0) + 0xb0b0) = 1;
      }
      iVar4 = piVar7[0x428];
      break;
    case 0xc40a:
      param_1[(uint)bVar16 * 2 + 0x8e1] = *(int *)puVar12;
      param_1[(uint)bVar16 * 2 + 0x8e2] = *(int *)(param_2 + 0x25);
      *unaff_FS_OFFSET = local_14;
      return;
    case 0xc40b:
      cVar2 = PacketChecksumNotEquals(g_clientContext + 0x45354,3);
      if (cVar2 != '\0') {
        param_1 = param_1 + 0x477;
        local_27f0 = (undefined *)0x0;
        local_27dc = 0;
        local_27e4 = 0;
        do {
          iVar4 = local_27dc;
          local_27e0 = param_1;
          cVar2 = PacketChecksumGreaterEqual(param_1,2);
          if (cVar2 != '\0') {
            QueueOutgoingPacketField(0);
            iVar4 = GetPlayerRecordBySlot(g_clientContext);
            AddToPacketChecksum(4);
            FUN_0040a280();
            local_c = 0xf;
            EncodeChecksumStateXored();
            iVar10 = PeekChecksumStateUnderLock(local_27e4 + 0x5113c + g_clientContext);
            iVar6 = PeekChecksumStateUnderLock(&DAT_00796aa0);
            uVar21 = EncodeChecksumDeltaMul(&local_2658,local_23c,iVar10 + iVar6);
            SUBFIELD(local_c,0,undefined1) = 0x10;
            uVar20 = PeekChecksumStateUnderLock(&DAT_00796aa0);
            uVar21 = EncodeChecksumDeltaDiv(uVar21,local_684,uVar20);
            SUBFIELD(local_c,0,undefined1) = 0x11;
            EncodeChecksumState(uVar21);
            SUBFIELD(local_c,0,undefined1) = 0x10;
            ScrubChecksumGuard();
            local_c = CONCAT31(SUBFIELD(local_c,1,undefined3),0xf);
            ScrubChecksumGuard();
            EmitChecksumSum(&local_2658);
            uVar22 = 4;
            uVar21 = PeekChecksumStateUnderLock(iVar4 + 0xb30);
            uVar20 = PeekChecksumStateUnderLock(iVar4 + 0x90c);
            FUN_004368f0(uVar20,uVar21,uVar22);
            iVar4 = iVar4 + 0xae15;
            uVar21 = PeekChecksumStateUnderLock(&local_2658);
            iVar10 = iVar4;
            pcVar5 = (char *)GetLocalizedString(&g_localizedStringTable,0x274);
            _sprintf(local_26d8,pcVar5,iVar10,uVar21);
            (**(code **)(*local_27ec + 0x28))(local_26d8,4,3);
            FUN_00438360();
            puVar8 = (undefined *)PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
            if (local_27f0 == puVar8) {
              iVar10 = *(int *)(g_clientContext + 0x44e60) + 1;
              pcVar5 = (char *)GetLocalizedString(&g_localizedStringTable,5000);
              _sprintf(local_26d8,pcVar5,iVar4,iVar10);
              iVar4 = DAT_007934e8;
              *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
              *(undefined2 *)(iVar4 + 0x4d4) = 0x5010;
              *(undefined1 *)(iVar4 + 0x4d6) = 0xff;
              iVar10 = *(int *)(iVar4 + 0x44d0) + 1;
              *(int *)(iVar4 + 0x44d0) = iVar10;
              pcVar5 = local_26d8;
              do {
                cVar2 = *pcVar5;
                pcVar5 = pcVar5 + 1;
              } while (cVar2 != '\0');
              *(char *)(iVar4 + 0x4d0 + iVar10) = (char)pcVar5 - ((char)local_26d8 + '\x01');
              *(int *)(iVar4 + 0x44d0) = *(int *)(iVar4 + 0x44d0) + 1;
              pcVar5 = local_26d8;
              do {
                cVar2 = *pcVar5;
                pcVar5 = pcVar5 + 1;
              } while (cVar2 != '\0');
              AppendPacketBytes(local_26d8);
              EncodePacketBody();
              SendOutgoingPacket();
            }
            local_c = 0xffffffff;
            ScrubChecksumGuard();
            param_1 = local_27e0;
            iVar4 = local_27dc;
          }
          local_27f0 = local_27f0 + 1;
          local_27e4 = local_27e4 + 0x1120;
          local_27dc = iVar4 + 0x224;
          param_1 = param_1 + 0x89;
          local_27e0 = param_1;
        } while (local_27e4 < 0x8900);
      }
      FUN_004d09c0();
      goto LAB_004b7fb2;
    }
  }
  if (*(char *)(iVar10 + 0x4590c + iVar4) == *(char *)(iVar10 + 0x3b6c0)) {
    *(undefined4 *)(*(int *)(iVar10 + 0x621e0) + 0xb0b0) = 2;
    *unaff_FS_OFFSET = local_14;
    return;
  }
switchD_004b64f9_caseD_c302:
  *unaff_FS_OFFSET = local_14;
  return;
}

