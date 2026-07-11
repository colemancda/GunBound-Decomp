/* State03_GameRoomList_ProcessPacket - 0x00426ad0 in the original binary.
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


/* WARNING: Removing unreachable block (ram,0x00426bea) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Virtual method referenced from g_gameStateObjects[3]'s vtable (slot 1).
   State 3's packet-receive handler: dispatches by opcode (ushort) on the
   payload. Confirmed opcode 0x6001 -> ChangeGameState(7); a later branch
   sums per-player equipped-item stats then resets viewport to (0,0,799,599)
   and calls ChangeGameState(9). See PROTOCOL.md for the opcode map. */

void __thiscall
State03_GameRoomList_ProcessPacket(void *this,int payloadLen,ushort opcode,ushort *payload)

{
  int *piVar1;
  undefined1 uVar2;
  byte bVar3;
  short sVar4;
  undefined4 uVar5;
  ushort uVar6;
  char cVar7;
  undefined2 uVar8;
  ushort *puVar9;
  int iVar10;
  undefined1 *puVar11;
  undefined4 *puVar12;
  undefined4 uVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  byte *pbVar18;
  byte *pbVar19;
  uint uVar20;
  uint uVar21;
  uint *puVar22;
  uint uVar23;
  int iVar24;
  char *pcVar25;
  int extraout_EDX;
  int extraout_EDX_00;
  undefined4 *puVar26;
  ushort *puVar27;
  undefined4 *puVar28;
  char *pcVar29;
  bool bVar30;
  int local_69c;
  undefined1 *local_690;
  undefined4 *local_688;
  undefined4 local_684;
  uint local_680;
  undefined1 local_67c;
  undefined4 local_678;
  undefined4 local_674;
  undefined4 local_670;
  undefined1 local_66c;
  byte local_668;
  undefined4 local_667;
  byte local_468;
  byte local_467;
  char local_466;
  int local_464;
  undefined4 local_c;
  
  local_c = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped (local_14/
   * puStack_10/unaff_FS_OFFSET) - handler body (LAB_005407bd) wasn't
   * included in this function's own decompile. Same rationale as
   * entry/InitGame.c - see src/README.md. local_c is a real, separate
   * local reused elsewhere in this function, kept as-is. */
  iVar10 = g_clientContext;
  if (0x21f1 < opcode) {
    if (opcode < 0x6002) {
      if (opcode == 0x6001) {
        if (*payload == 0) {
          uVar23 = *(uint *)(payload + 1);
          uVar21 = *(uint *)(payload + 3);
          QueueOutgoingPacketField(uVar23 & 0xffff);
          QueueOutgoingPacketField(uVar23 >> 0x10);
          QueueOutgoingPacketField(uVar21 & 0xffff);
          QueueOutgoingPacketField(uVar21 >> 0x10);
          QueueOutgoingPacketField(*(undefined4 *)(payload + 5));
          if (0xe < payloadLen) {
            QueueOutgoingPacketField(payload[7]);
            payload = payload + 8;
            local_690 = (undefined1 *)0x0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar10 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (0 < iVar10) {
              do {
                FUN_00428550(&local_468);
                local_c = 0;
                local_464 = (int)local_690;
                EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                iVar10 = _rand();
                local_468 = (byte)iVar10;
                iVar10 = _rand();
                local_467 = ~('\x01' << (local_468 & 7)) & (byte)iVar10 | '\0' << (local_468 & 7);
                local_466 = local_467 + local_468 + -0x34;
                LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                EncodeOutgoingPacketField(0x80000000);
                LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                uVar13 = *(undefined4 *)payload;
                EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                EncodeOutgoingPacketField(uVar13);
                LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                FUN_0042ae30(&local_468);
                FUN_0042ae30(&local_468);
                payload = payload + 2;
                local_c = 0xffffffff;
                FUN_00426810(&local_468);
                local_690 = (undefined1 *)((int)local_690 + 1);
                EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                iVar10 = PeekPacketChecksumState();
                LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              } while ((int)local_690 < iVar10);
            }
          }
          *(undefined1 *)(g_clientContext + 0x44bf8) = 1;
          g_pendingGameState = 7;
          g_stateChangeRequested = 1;
          ChangeGameState(7);
          bVar30 = DAT_007934f4 != 0;
          *(undefined4 *)(g_clientContext + 0x41340) = 0xfffffffe;
          if (bVar30) {
            FUN_00405ba0();
            return;
          }
          FUN_00404410(&DAT_00e53e88);
        }
      }
      else {
        switch(opcode) {
        case 0x21f2:
          iVar10 = FUN_0041c290();
          if (iVar10 != -1) {
            if (*(int *)((int)this + 4) == iVar10) {
              *(undefined4 *)((int)this + 4) = 0xffffffff;
            }
            iVar10 = iVar10 * 0x80 + g_clientContext;
            uVar21 = payloadLen - 2U & ((int)(payloadLen - 2U) < 0) - 1;
            puVar9 = payload + 1;
            puVar12 = (undefined4 *)(iVar10 + 0x4467c);
            for (uVar23 = uVar21 >> 2; uVar23 != 0; uVar23 = uVar23 - 1) {
              *puVar12 = *(undefined4 *)puVar9;
              puVar9 = puVar9 + 2;
              puVar12 = puVar12 + 1;
            }
            for (uVar21 = uVar21 & 3; uVar21 != 0; uVar21 = uVar21 - 1) {
              *(char *)puVar12 = (char)*puVar9;
              puVar9 = (ushort *)((int)puVar9 + 1);
              puVar12 = (undefined4 *)((int)puVar12 + 1);
            }
            *(undefined1 *)(iVar10 + 0x4467a + payloadLen) = 0;
            return;
          }
          break;
        case 0x21f3:
          iVar10 = FUN_0041c290();
          if (iVar10 != -1) {
            if (*(int *)((int)this + 4) == iVar10) {
              *(undefined4 *)((int)this + 4) = 0xffffffff;
            }
            *(char *)(iVar10 + 0x4497c + g_clientContext) = (char)payload[1];
            return;
          }
          break;
        case 0x21f4:
          iVar10 = FUN_0041c290();
          if (iVar10 != -1) {
            if (*(int *)((int)this + 4) == iVar10) {
              *(undefined4 *)((int)this + 4) = 0xffffffff;
            }
            *(undefined4 *)(g_clientContext + 0x44984 + iVar10 * 4) = *(undefined4 *)(payload + 1);
            return;
          }
          break;
        case 0x21f5:
          iVar10 = FUN_0041c290();
          if (iVar10 != -1) {
            if (*(int *)((int)this + 4) == iVar10) {
              *(undefined4 *)((int)this + 4) = 0xffffffff;
            }
            *(char *)(iVar10 + 0x4499c + g_clientContext) = (char)payload[1];
            return;
          }
          break;
        case 0x21f6:
          iVar10 = FUN_0041c290();
          if (iVar10 != -1) {
            if (*(int *)((int)this + 4) == iVar10) {
              *(undefined4 *)((int)this + 4) = 0xffffffff;
            }
            *(char *)(iVar10 + 0x449a2 + g_clientContext) = (char)payload[1];
            return;
          }
          break;
        case 0x21f7:
          iVar10 = FUN_0041c290();
          if (iVar10 != -1) {
            if (*(int *)((int)this + 4) == iVar10) {
              *(undefined4 *)((int)this + 4) = 0xffffffff;
            }
            *(char *)(iVar10 + 0x449a8 + g_clientContext) = (char)payload[1];
            return;
          }
        }
      }
    }
switchD_00428058_default:
    return;
  }
  if (opcode == 0x21f1) {
    iVar24 = 0;
    if (*(char *)(g_clientContext + 0x44648) != '\0') {
      puVar22 = (uint *)(g_clientContext + 0x44664);
      while (*puVar22 != (uint)*payload) {
        iVar24 = iVar24 + 1;
        puVar22 = puVar22 + 1;
        if ((int)(uint)*(byte *)(g_clientContext + 0x44648) <= iVar24) {
          return;
        }
      }
      if (iVar24 != -1) {
        if (*(int *)((int)this + 4) == iVar24) {
          *(undefined4 *)((int)this + 4) = 0xffffffff;
        }
        *(undefined4 *)(iVar10 + 0x4464c + iVar24 * 4) = 0;
        return;
      }
    }
    goto switchD_00428058_default;
  }
  if (opcode < 0x2106) {
    if (opcode == 0x2105) {
      if (*payload != 0) {
        State03_GameRoomList_CreateButtons();
        *(undefined4 *)((int)this + 0x124) = 0xffffffff;
        return;
      }
      uVar23 = (uint)(byte)payload[1];
      puVar12 = (undefined4 *)((int)payload + 3);
      puVar28 = (undefined4 *)(*(int *)((int)this + 0x124) * 0x80 + 0x4467c + g_clientContext);
      for (uVar21 = (uint)(byte)((byte)payload[1] >> 2); uVar21 != 0; uVar21 = uVar21 - 1) {
        *puVar28 = *puVar12;
        puVar12 = puVar12 + 1;
        puVar28 = puVar28 + 1;
      }
      for (uVar21 = uVar23 & 3; iVar10 = g_clientContext, uVar21 != 0; uVar21 = uVar21 - 1) {
        *(undefined1 *)puVar28 = *(undefined1 *)puVar12;
        puVar12 = (undefined4 *)((int)puVar12 + 1);
        puVar28 = (undefined4 *)((int)puVar28 + 1);
      }
      puVar11 = (undefined1 *)((int)payload + 3 + uVar23);
      *(undefined1 *)(*(int *)((int)this + 0x124) * 0x80 + uVar23 + 0x4467c + g_clientContext) = 0;
      pcVar25 = (char *)(*(int *)((int)this + 0x124) * 0x80 + 0x4467c + iVar10);
      pcVar29 = (char *)((int)this + 300);
      do {
        cVar7 = *pcVar25;
        pcVar25 = pcVar25 + 1;
        *pcVar29 = cVar7;
        pcVar29 = pcVar29 + 1;
      } while (cVar7 != '\0');
      uVar2 = *puVar11;
      *(undefined1 *)((int)this + 0x1ac) = uVar2;
      *(undefined1 *)(*(int *)((int)this + 0x124) + 0x4497c + iVar10) = uVar2;
      uVar13 = *(undefined4 *)(puVar11 + 1);
      *(undefined4 *)((int)this + 0x1b0) = uVar13;
      *(undefined4 *)(iVar10 + 0x44984 + *(int *)((int)this + 0x124) * 4) = uVar13;
      uVar2 = puVar11[5];
      *(undefined1 *)((int)this + 0x1b4) = uVar2;
      *(undefined1 *)(*(int *)((int)this + 0x124) + 0x4499c + iVar10) = uVar2;
      uVar2 = puVar11[6];
      *(undefined1 *)((int)this + 0x1b5) = uVar2;
      *(undefined1 *)(*(int *)((int)this + 0x124) + 0x449a2 + iVar10) = uVar2;
      uVar2 = puVar11[7];
      *(undefined1 *)((int)this + 0x1b6) = uVar2;
      *(undefined1 *)(*(int *)((int)this + 0x124) + 0x449a8 + iVar10) = uVar2;
      uVar2 = puVar11[8];
      *(undefined1 *)((int)this + 0x1b7) = uVar2;
      *(undefined1 *)(*(int *)((int)this + 0x124) + 0x449ae + iVar10) = uVar2;
      puVar12 = (undefined4 *)(puVar11 + 9);
      local_69c = 0;
      if (*(char *)((int)this + 0x1b4) != '\0') {
        local_688 = (undefined4 *)((int)this + 0x268);
        iVar10 = (int)this + (0x220 - (int)&local_684);
        local_66c = 0;
        local_67c = 0;
        iVar24 = (int)this + (0x1b8 - (int)&local_678);
        do {
          local_678 = *puVar12;
          local_670 = puVar12[2];
          local_684 = puVar12[5];
          local_680 = puVar12[6];
          local_674 = puVar12[1];
          if (((local_680 & 0x80000000) != 0) && ((local_680 & 0x800000) == 0)) {
            local_680 = local_680 & 0xffffff;
          }
          uVar13 = puVar12[7];
          puVar12 = puVar12 + 8;
          pcVar29 = (char *)&local_678;
          do {
            cVar7 = *pcVar29;
            pcVar29[iVar24] = cVar7;
            pcVar29 = pcVar29 + 1;
          } while (cVar7 != '\0');
          pcVar29 = (char *)&local_684;
          do {
            cVar7 = *pcVar29;
            pcVar29[iVar10] = cVar7;
            pcVar29 = pcVar29 + 1;
          } while (cVar7 != '\0');
          *local_688 = uVar13;
          local_688 = local_688 + 1;
          local_69c = local_69c + 1;
          iVar24 = iVar24 + 0xd;
          iVar10 = iVar10 + 9;
        } while (local_69c < (int)(uint)*(byte *)((int)this + 0x1b4));
        return;
      }
      goto switchD_00428058_default;
    }
    if (opcode == 0x2001) {
      if (*payload == 0) {
        if (DAT_007934f4 == 0) {
          FUN_00404410(&DAT_00e53e88);
        }
        else {
          FUN_00405ba0();
        }
      }
      FUN_00507cc0(1,*(undefined4 *)(g_clientContext + 0x41340));
      return;
    }
    if (opcode == 0x201f) {
      iVar10 = FUN_004259d0((uint)(byte)*payload * 0xd + 0x41445 + g_clientContext);
      if (iVar10 == -1) {
        FUN_0041b8c0(g_clientContext,0,(uint)(byte)*payload * 9 + 0x43548 + g_clientContext,
                     (uint)(byte)*payload * 0xd + 0x41445 + g_clientContext,payload + 7,0,0);
        return;
      }
      goto switchD_00428058_default;
    }
    if (opcode != 0x2103) goto switchD_00428058_default;
    if (*payload == 0) {
      uVar6 = payload[1];
      puVar9 = payload + 2;
      *(char *)(g_clientContext + 0x44648) = (char)uVar6;
      *(bool *)((int)this + 0x120) = (char)uVar6 == '\x06';
      if (*(char *)(iVar10 + 0x44648) != '\0') {
        *(undefined4 *)((int)this + 0x118) = *(undefined4 *)((int)this + 0x11c);
      }
      puVar12 = (undefined4 *)(iVar10 + 0x4464c);
      *puVar12 = 0;
      *(undefined4 *)(iVar10 + 0x44650) = 0;
      *(undefined4 *)(iVar10 + 0x44654) = 0;
      *(undefined4 *)(iVar10 + 0x44658) = 0;
      *(undefined4 *)(iVar10 + 0x4465c) = 0;
      *(undefined4 *)(iVar10 + 0x44660) = 0;
      local_688 = (undefined4 *)0x0;
      if (*(char *)(iVar10 + 0x44648) != '\0') {
        local_690 = (undefined1 *)(iVar10 + 0x4469a);
        do {
          puVar12[6] = (uint)*puVar9;
          uVar23 = (uint)(byte)puVar9[1];
          puVar9 = (ushort *)((int)puVar9 + 3);
          if (uVar23 != 0) {
            *puVar12 = 1;
            uVar21 = uVar23;
            if (0x1e < uVar23) {
              uVar21 = 0x1e;
            }
            puVar27 = puVar9;
            puVar28 = (undefined4 *)(local_690 + -0x1e);
            for (uVar20 = uVar21 >> 2; uVar20 != 0; uVar20 = uVar20 - 1) {
              *puVar28 = *(undefined4 *)puVar27;
              puVar27 = puVar27 + 2;
              puVar28 = puVar28 + 1;
            }
            for (uVar21 = uVar21 & 3; iVar10 = g_clientContext, uVar21 != 0; uVar21 = uVar21 - 1) {
              *(char *)puVar28 = (char)*puVar27;
              puVar27 = (ushort *)((int)puVar27 + 1);
              puVar28 = (undefined4 *)((int)puVar28 + 1);
            }
            local_690[uVar23 - 0x1e] = 0;
            *local_690 = 0;
            local_690[1] = 0;
            *(undefined1 *)(iVar10 + 0x4497c + (int)local_688) =
                 *(undefined1 *)((int)puVar9 + uVar23);
            puVar12[0xce] = *(undefined4 *)((int)puVar9 + uVar23 + 1);
            *(undefined1 *)(iVar10 + 0x4499c + (int)local_688) =
                 *(undefined1 *)((int)puVar9 + uVar23 + 5);
            *(undefined1 *)(iVar10 + 0x449a2 + (int)local_688) =
                 *(undefined1 *)((int)puVar9 + uVar23 + 6);
            *(undefined1 *)(iVar10 + 0x449a8 + (int)local_688) =
                 *(undefined1 *)((int)puVar9 + uVar23 + 7);
            *(undefined1 *)(iVar10 + 0x449ae + (int)local_688) =
                 *(undefined1 *)((int)puVar9 + uVar23 + 8);
            puVar9 = (ushort *)((int)puVar9 + uVar23 + 9);
            *(undefined1 *)(iVar10 + 0x449b4 + (int)local_688) = 0;
          }
          local_690 = local_690 + 0x80;
          local_688 = (undefined4 *)((int)local_688 + 1);
          puVar12 = puVar12 + 1;
        } while ((int)local_688 < (int)(uint)*(byte *)(iVar10 + 0x44648));
      }
      cVar7 = PeekPacketChecksumBool();
      iVar10 = g_clientContext;
      if ((cVar7 == '\x01') && (*(short *)(g_clientContext + 0x3b96f) != -1)) {
        iVar24 = (int)*(short *)(g_clientContext + 0x3b96f) % 6;
        *(int *)((int)this + 4) = iVar24;
        if ((*(int *)(iVar10 + 0x4464c + iVar24 * 4) != 0) &&
           ((*(char *)(iVar24 + 0x449a8 + iVar10) == '\0' &&
            (*(char *)(iVar24 + 0x4499c + iVar10) != *(char *)(iVar24 + 0x449a2 + iVar10))))) {
          if (*(char *)(iVar24 + 0x449ae + iVar10) != '\0') {
            SetGuardedBool(0);
          }
          SendJoinRoomChecked();
          return;
        }
        SetGuardedBool(0);
        FUN_0042a090();
        return;
      }
      goto LAB_00426d84;
    }
  }
  else {
    if (opcode != 0x2111) {
      if (opcode != 0x2121) {
        if (opcode == 0x21f0) {
          iVar24 = FUN_0041c290();
          if (iVar24 != -1) {
            uVar6 = payload[1];
            uVar23 = (uint)(byte)uVar6;
            if (uVar23 == 0) {
              *(undefined4 *)(iVar10 + 0x4464c + iVar24 * 4) = 0;
              return;
            }
            *(undefined4 *)(iVar10 + 0x4464c + iVar24 * 4) = 1;
            iVar10 = iVar10 + iVar24 * 0x80;
            puVar12 = (undefined4 *)((int)payload + 3);
            puVar28 = (undefined4 *)(iVar10 + 0x4467c);
            for (uVar21 = (uint)(byte)((byte)uVar6 >> 2); uVar21 != 0; uVar21 = uVar21 - 1) {
              *puVar28 = *puVar12;
              puVar12 = puVar12 + 1;
              puVar28 = puVar28 + 1;
            }
            for (uVar21 = uVar23 & 3; iVar14 = g_clientContext, uVar21 != 0; uVar21 = uVar21 - 1) {
              *(undefined1 *)puVar28 = *(undefined1 *)puVar12;
              puVar12 = (undefined4 *)((int)puVar12 + 1);
              puVar28 = (undefined4 *)((int)puVar28 + 1);
            }
            *(undefined1 *)(iVar10 + 0x4467c + uVar23) = 0;
            puVar11 = (undefined1 *)((int)payload + 3 + uVar23);
            *(undefined1 *)(iVar14 + 0x4497c + iVar24) = *puVar11;
            *(undefined4 *)(iVar14 + 0x44984 + iVar24 * 4) = *(undefined4 *)(puVar11 + 1);
            *(undefined1 *)(iVar14 + 0x4499c + iVar24) = puVar11[5];
            *(undefined1 *)(iVar14 + 0x449a2 + iVar24) = puVar11[6];
            *(undefined1 *)(iVar14 + 0x449a8 + iVar24) = puVar11[7];
            *(undefined1 *)(iVar14 + 0x449ae + iVar24) = puVar11[8];
            return;
          }
        }
        goto switchD_00428058_default;
      }
      if (*payload == 0) {
        FUN_00415ca0();
        FUN_004e7430();
        FUN_0041b7e0();
        *(undefined1 *)(extraout_EDX + 0x3b6c0) = 0;
        /* QueueOutgoingPacketField is void-returning (see its own
         * definition) - this call site's return-value use is a Ghidra
         * per-call-site decompilation inconsistency, same class as
         * entry/WinMain.c's FUN_004058c0 fix. uVar13 is left
         * uninitialized here as a result; EncodeChecksumState's real
         * argument at this site isn't recoverable without more
         * context. */
        QueueOutgoingPacketField((char)payload[1]);
        EncodeChecksumState(uVar13);
        PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        FUN_004e7340();
        uVar13 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        iVar10 = g_clientContext;
        *(int *)(g_clientContext + 0x4739c) = *(int *)(g_clientContext + 0x4739c) + 1;
        FUN_00415ce0(uVar13);
        *(uint *)(iVar10 + 0x44e60) = (uint)*(ushort *)((int)payload + 3);
        *(undefined1 *)((int)this + 0x115) = 2;
        *(undefined1 *)((int)this + 0x116) = 0;
        *(undefined4 *)((int)this + 0x11c) = 0;
        *(undefined4 *)(iVar10 + 0x45914) = 0;
        *(undefined4 *)(iVar10 + 0x45918) = 0;
        pcVar29 = (char *)((int)this + 0xf);
        iVar24 = iVar10 - (int)pcVar29;
        do {
          cVar7 = *pcVar29;
          pcVar29[iVar24 + 0x44e64] = cVar7;
          pcVar29 = pcVar29 + 1;
        } while (cVar7 != '\0');
        pcVar29 = (char *)((int)this + 0x8f);
        iVar24 = iVar10 - (int)pcVar29;
        do {
          cVar7 = *pcVar29;
          pcVar29[iVar24 + 0x44ee4] = cVar7;
          pcVar29 = pcVar29 + 1;
        } while (cVar7 != '\0');
        *(undefined1 *)(iVar10 + 0x44ef8) = 0;
        QueueOutgoingPacketField(*(undefined4 *)((int)this + 0x110));
        iVar10 = g_clientContext;
        *(undefined1 *)(g_clientContext + 0x45124) = *(undefined1 *)((int)this + 0x114);
        *(undefined1 *)(iVar10 + 0x45125) = 1;
        pcVar29 = (char *)(iVar10 + 0x23330);
        *(undefined4 *)(iVar10 + 0x457a1) = 0xffffffff;
        *(undefined4 *)(iVar10 + 0x457a5) = 0xffffffff;
        iVar24 = PeekChecksumStateUnderLock(iVar10 + 0x3b49c);
        iVar10 = g_clientContext;
        pcVar25 = (char *)(iVar24 * 0xd + 0x457f1 + g_clientContext);
        do {
          cVar7 = *pcVar29;
          pcVar29 = pcVar29 + 1;
          *pcVar25 = cVar7;
          pcVar25 = pcVar25 + 1;
        } while (cVar7 != '\0');
        iVar24 = PeekChecksumStateUnderLock(iVar10 + 0x3b49c);
        iVar10 = g_clientContext;
        *(undefined1 *)(g_clientContext + 0x458fc + iVar24 * 2) = 0xff;
        iVar24 = PeekChecksumStateUnderLock(iVar10 + 0x3b49c);
        iVar10 = g_clientContext;
        *(undefined1 *)(g_clientContext + 0x458fd + iVar24 * 2) = 0xff;
        iVar24 = PeekChecksumStateUnderLock(iVar10 + 0x3b49c);
        iVar10 = g_clientContext;
        *(undefined1 *)(iVar24 + 0x4590c + g_clientContext) = 0;
        iVar24 = PeekChecksumStateUnderLock(iVar10 + 0x3b49c);
        iVar10 = g_clientContext;
        *(undefined1 *)(iVar24 + 0x45914 + g_clientContext) = 1;
        pcVar29 = (char *)(iVar10 + 0x23313);
        iVar24 = PeekChecksumStateUnderLock(iVar10 + 0x3b49c);
        iVar10 = g_clientContext;
        pcVar25 = (char *)(iVar24 * 9 + 0x457a9 + g_clientContext);
        do {
          cVar7 = *pcVar29;
          pcVar29 = pcVar29 + 1;
          *pcVar25 = cVar7;
          pcVar25 = pcVar25 + 1;
        } while (cVar7 != '\0');
        uVar13 = PeekChecksumStateUnderLock(iVar10 + 0x239b4);
        iVar24 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        iVar10 = g_clientContext;
        *(undefined4 *)(g_clientContext + 0x4599c + iVar24 * 4) = uVar13;
        iVar14 = PeekChecksumStateUnderLock(iVar10 + 0x3b49c);
        iVar24 = g_clientContext;
        *(undefined2 *)(g_clientContext + 0x4591c + iVar14 * 2) = *(undefined2 *)(iVar10 + 0x23344);
        iVar14 = PeekChecksumStateUnderLock(iVar24 + 0x3b49c);
        iVar10 = g_clientContext;
        *(undefined2 *)(g_clientContext + 0x4592c + iVar14 * 2) = *(undefined2 *)(iVar24 + 0x23346);
        uVar13 = PeekChecksumStateUnderLock(iVar10 + 0x23348);
        iVar24 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        iVar10 = g_clientContext;
        *(undefined4 *)(g_clientContext + 0x4593c + iVar24 * 4) = uVar13;
        uVar13 = PeekChecksumStateUnderLock(iVar10 + 0x2356c);
        iVar24 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        iVar10 = g_clientContext;
        *(undefined4 *)(g_clientContext + 0x4595c + iVar24 * 4) = uVar13;
        uVar13 = PeekChecksumStateUnderLock(iVar10 + 0x23790);
        iVar24 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        iVar10 = g_clientContext;
        *(undefined4 *)(g_clientContext + 0x4597c + iVar24 * 4) = uVar13;
        uVar8 = PeekChecksumStateUnderLock(iVar10 + 0x3ac08);
        iVar24 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        iVar10 = g_clientContext;
        *(undefined2 *)(g_clientContext + 0x458bc + iVar24 * 8) = uVar8;
        uVar8 = PeekChecksumStateUnderLock(iVar10 + 0x3ae2c);
        iVar24 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        iVar10 = g_clientContext;
        *(undefined2 *)(g_clientContext + 0x458be + iVar24 * 8) = uVar8;
        uVar8 = PeekChecksumStateUnderLock(iVar10 + 0x3b050);
        iVar24 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        iVar10 = g_clientContext;
        *(undefined2 *)(g_clientContext + 0x458c0 + iVar24 * 8) = uVar8;
        uVar8 = PeekChecksumStateUnderLock(iVar10 + 0x3b274);
        iVar24 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        iVar10 = g_clientContext;
        *(undefined2 *)(g_clientContext + 0x458c2 + iVar24 * 8) = uVar8;
        iVar24 = PeekChecksumStateUnderLock(iVar10 + 0x3b49c);
        iVar10 = g_clientContext;
        *(undefined4 *)(g_clientContext + 0x4663c + iVar24 * 4) = 0;
        iVar24 = PeekChecksumStateUnderLock(iVar10 + 0x3b49c);
        iVar10 = g_clientContext;
        *(undefined4 *)(g_clientContext + 0x4665c + iVar24 * 4) = 0;
        iVar24 = PeekChecksumStateUnderLock(iVar10 + 0x3b49c);
        iVar10 = g_clientContext;
        *(undefined4 *)(g_clientContext + 0x4733c + iVar24 * 4) = 0;
        iVar24 = PeekChecksumStateUnderLock(iVar10 + 0x3b49c);
        iVar10 = g_clientContext;
        *(undefined4 *)(g_clientContext + 0x4735c + iVar24 * 4) = 0;
        iVar24 = PeekChecksumStateUnderLock(iVar10 + 0x3b49c);
        iVar10 = g_clientContext;
        *(undefined4 *)(g_clientContext + 0x472fc + iVar24 * 4) = 0;
        iVar24 = PeekChecksumStateUnderLock(iVar10 + 0x3b49c);
        iVar10 = g_clientContext;
        iVar14 = 0;
        *(undefined4 *)(g_clientContext + 0x4731c + iVar24 * 4) = 0;
        iVar24 = 0;
        do {
          uVar13 = PeekChecksumStateUnderLock(iVar24 + 0x23bd8 + iVar10);
          iVar15 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
          iVar10 = iVar24 + 0x266a8 + g_clientContext;
          *(undefined4 *)(g_clientContext + 0x459bc + (iVar14 + iVar15 * 0x14) * 4) = uVar13;
          uVar13 = PeekChecksumStateUnderLock(iVar10);
          iVar15 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
          iVar10 = g_clientContext;
          *(undefined4 *)(g_clientContext + 0x45c3c + (iVar14 + iVar15 * 0x14) * 4) = uVar13;
          iVar16 = PeekChecksumStateUnderLock(iVar10 + 0x3b49c);
          iVar10 = g_clientContext + 0x45c3c;
          iVar15 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
          iVar15 = *(int *)(g_clientContext + 0x459bc + (iVar14 + iVar15 * 0x14) * 4);
          iVar10 = *(int *)(iVar10 + (iVar14 + iVar16 * 0x14) * 4);
          iVar17 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
          iVar16 = g_clientContext;
          *(int *)(g_clientContext + 0x463bc + (iVar14 + iVar17 * 0x14) * 4) = iVar15 + iVar10;
          iVar10 = PeekChecksumStateUnderLock(iVar16 + 0x3b49c);
          piVar1 = (int *)(g_clientContext + 0x4663c + iVar10 * 4);
          iVar10 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
          iVar15 = g_clientContext + 0x3b49c;
          *piVar1 = *piVar1 + *(int *)(g_clientContext + 0x459bc + (iVar14 + iVar10 * 0x14) * 4);
          iVar10 = PeekChecksumStateUnderLock(iVar15);
          piVar1 = (int *)(g_clientContext + 0x4665c + iVar10 * 4);
          iVar15 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
          iVar10 = iVar24 + 0x2e718 + g_clientContext;
          *piVar1 = *piVar1 + *(int *)(g_clientContext + 0x45c3c + (iVar14 + iVar15 * 0x14) * 4);
          uVar13 = PeekChecksumStateUnderLock(iVar10);
          iVar15 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
          iVar10 = iVar24 + 0x311e8 + g_clientContext;
          *(undefined4 *)(g_clientContext + 0x4667c + (iVar14 + iVar15 * 0x14) * 4) = uVar13;
          uVar13 = PeekChecksumStateUnderLock(iVar10);
          iVar15 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
          iVar10 = g_clientContext;
          *(undefined4 *)(g_clientContext + 0x468fc + (iVar14 + iVar15 * 0x14) * 4) = uVar13;
          iVar16 = PeekChecksumStateUnderLock(iVar10 + 0x3b49c);
          iVar10 = g_clientContext + 0x468fc;
          iVar15 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
          iVar15 = *(int *)(g_clientContext + 0x4667c + (iVar14 + iVar15 * 0x14) * 4);
          iVar10 = *(int *)(iVar10 + (iVar14 + iVar16 * 0x14) * 4);
          iVar17 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
          iVar16 = g_clientContext;
          *(int *)(g_clientContext + 0x4707c + (iVar14 + iVar17 * 0x14) * 4) = iVar15 + iVar10;
          iVar10 = PeekChecksumStateUnderLock(iVar16 + 0x3b49c);
          piVar1 = (int *)(g_clientContext + 0x472fc + iVar10 * 4);
          iVar10 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
          iVar15 = g_clientContext + 0x3b49c;
          *piVar1 = *piVar1 + *(int *)(g_clientContext + 0x4667c + (iVar14 + iVar10 * 0x14) * 4);
          iVar10 = PeekChecksumStateUnderLock(iVar15);
          piVar1 = (int *)(g_clientContext + 0x4731c + iVar10 * 4);
          iVar15 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
          iVar10 = g_clientContext;
          iVar15 = iVar14 + iVar15 * 0x14;
          iVar24 = iVar24 + 0x224;
          iVar14 = iVar14 + 1;
          *piVar1 = *piVar1 + *(int *)(g_clientContext + 0x468fc + iVar15 * 4);
        } while (iVar24 < 0x2ad0);
        iVar10 = PeekChecksumStateUnderLock(iVar10 + 0x3b49c);
        piVar1 = (int *)(g_clientContext + 0x4733c + iVar10 * 4);
        iVar10 = PeekChecksumStateUnderLock(g_clientContext + 0x3947c);
        *piVar1 = *piVar1 + iVar10;
        iVar10 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        piVar1 = (int *)(g_clientContext + 0x4735c + iVar10 * 4);
        iVar24 = PeekChecksumStateUnderLock(g_clientContext + 0x39258);
        iVar10 = g_clientContext;
        *piVar1 = *piVar1 + iVar24;
        _DAT_00e53c24 = 0;
        _DAT_00e53c28 = 799;
        _DAT_00e53c2c = 0;
        _DAT_00e53c30 = 599;
        *(undefined1 *)(DAT_007934e4 + 8) = 0;
        _DAT_0056dc98 = *(undefined2 *)(iVar10 + 0x44e60);
        _DAT_0056dc90 = *(undefined2 *)(iVar10 + 0x3f804);
        DAT_0079350d = 0;
        _DAT_0056dca0 = _DAT_0056dc90;
        _DAT_0056dca8 = _DAT_0056dc98;
        *(undefined1 *)(iVar10 + 0x45578) = 0;
        g_pendingGameState = 9;
        g_stateChangeRequested = 1;
        ChangeGameState(9);
        *(undefined4 *)(g_clientContext + 0x41340) = 0xffffffff;
        if (DAT_007934f4 == 0) {
          FUN_00404410(&DAT_00e53e88);
        }
        else {
          FUN_00405ba0();
        }
        local_668 = 0;
        puVar12 = &local_667;
        for (iVar10 = 0x7f; iVar10 != 0; iVar10 = iVar10 + -1) {
          *puVar12 = 0;
          puVar12 = puVar12 + 1;
        }
        *(undefined2 *)puVar12 = 0;
        *(undefined1 *)((int)puVar12 + 2) = 0;
        iVar10 = 0;
        iVar24 = 0;
        if (0 < payloadLen + -5) {
          do {
            bVar3 = *(byte *)((int)payload + iVar24 + 5);
            if (bVar3 == 10) {
              pbVar18 = &local_668;
              do {
                bVar3 = *pbVar18;
                pbVar18 = pbVar18 + 1;
              } while (bVar3 != 0);
              FUN_0041b8c0(g_clientContext,2,0,0,&local_668,0,1);
              iVar10 = 0;
              pbVar18 = &local_668;
              for (iVar14 = 0x80; iVar14 != 0; iVar14 = iVar14 + -1) {
                pbVar18[0] = 0;
                pbVar18[1] = 0;
                pbVar18[2] = 0;
                pbVar18[3] = 0;
                pbVar18 = pbVar18 + 4;
              }
            }
            else {
              (&local_668)[iVar10] = bVar3;
              iVar10 = iVar10 + 1;
            }
            iVar24 = iVar24 + 1;
          } while (iVar24 < payloadLen + -5);
        }
        pbVar18 = &local_668;
        do {
          bVar3 = *pbVar18;
          pbVar18 = pbVar18 + 1;
        } while (bVar3 != 0);
        FUN_0041b8c0(g_clientContext,2,0,0,&local_668,0,1);
        return;
      }
      FUN_00429dc0();
      goto LAB_00426d84;
    }
    if (*(char *)((int)this + 0xd) != '\0') {
      FUN_00429fb0();
    }
    if (*(char *)((int)this + 0xe) != '\0') {
      FUN_00429f90();
    }
    if (*payload == 0) {
      FUN_004e7430();
      FUN_0041b7e0();
      FUN_00415ca0();
      *(undefined4 *)(extraout_EDX_00 + 0x45914) = 0;
      *(undefined4 *)(extraout_EDX_00 + 0x45918) = 0;
      QueueOutgoingPacketField((char)payload[1]);
      QueueOutgoingPacketField(*(undefined1 *)((int)payload + 3));
      PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
      FUN_004e7340();
      iVar10 = g_clientContext;
      *(uint *)(g_clientContext + 0x44e60) = (uint)payload[2];
      *(undefined1 *)((int)this + 0x115) = 2;
      *(undefined1 *)((int)this + 0x116) = 0;
      *(undefined4 *)((int)this + 0x11c) = 0;
      uVar23 = (uint)(byte)payload[3];
      puVar26 = (undefined4 *)((int)payload + 7);
      puVar12 = puVar26;
      puVar28 = (undefined4 *)(iVar10 + 0x44e64);
      for (uVar21 = (uint)(byte)((byte)payload[3] >> 2); uVar21 != 0; uVar21 = uVar21 - 1) {
        *puVar28 = *puVar12;
        puVar12 = puVar12 + 1;
        puVar28 = puVar28 + 1;
      }
      for (uVar21 = uVar23 & 3; uVar21 != 0; uVar21 = uVar21 - 1) {
        *(undefined1 *)puVar28 = *(undefined1 *)puVar12;
        puVar12 = (undefined4 *)((int)puVar12 + 1);
        puVar28 = (undefined4 *)((int)puVar28 + 1);
      }
      pcVar29 = (char *)((int)this + 0x8f);
      iVar24 = iVar10 - (int)pcVar29;
      do {
        cVar7 = *pcVar29;
        pcVar29[iVar24 + 0x44ee4] = cVar7;
        pcVar29 = pcVar29 + 1;
      } while (cVar7 != '\0');
      *(undefined1 *)(uVar23 + 0x44e64 + iVar10) = 0;
      *(undefined1 *)(iVar10 + 0x44ef8) = *(undefined1 *)((int)puVar26 + uVar23);
      QueueOutgoingPacketField(*(undefined4 *)((int)puVar26 + uVar23 + 1));
      iVar10 = g_clientContext;
      *(undefined4 *)(g_clientContext + 0x457a1) = *(undefined4 *)((int)puVar26 + uVar23 + 5);
      *(undefined4 *)(iVar10 + 0x457a5) = *(undefined4 *)((int)puVar26 + uVar23 + 9);
      *(undefined1 *)(iVar10 + 0x45124) = *(undefined1 *)((int)puVar26 + uVar23 + 0xd);
      cVar7 = *(char *)((int)puVar26 + uVar23 + 0xe);
      pbVar18 = (byte *)((int)puVar26 + uVar23 + 0xf);
      *(char *)(iVar10 + 0x45125) = cVar7;
      local_69c = 0;
      if (cVar7 != '\0') {
        do {
          iVar10 = g_clientContext;
          uVar20 = (uint)*pbVar18;
          *(int *)(g_clientContext + 0x4739c) = *(int *)(g_clientContext + 0x4739c) + 1;
          FUN_00415ce0(uVar20);
          iVar24 = uVar20 * 0xd;
          puVar12 = (undefined4 *)(iVar24 + 0x457f1 + iVar10);
          *puVar12 = *(undefined4 *)(pbVar18 + 1);
          puVar12[1] = *(undefined4 *)(pbVar18 + 5);
          puVar12[2] = *(undefined4 *)(pbVar18 + 9);
          iVar10 = g_clientContext;
          *(undefined1 *)(iVar24 + 0x457fd + g_clientContext) = 0;
          *(undefined4 *)(iVar10 + 0x4585c + uVar20 * 4) = *(undefined4 *)(pbVar18 + 0xd);
          *(undefined2 *)(iVar10 + 0x4589c + uVar20 * 2) = *(undefined2 *)(pbVar18 + 0x11);
          *(undefined4 *)(iVar10 + 0x4587c + uVar20 * 4) = *(undefined4 *)(pbVar18 + 0x13);
          *(undefined2 *)(iVar10 + 0x458ac + uVar20 * 2) = *(undefined2 *)(pbVar18 + 0x17);
          *(byte *)(iVar10 + 0x458fc + uVar20 * 2) = pbVar18[0x19];
          *(byte *)(iVar10 + 0x458fd + uVar20 * 2) = pbVar18[0x1a];
          *(byte *)(uVar20 + 0x4590c + iVar10) = pbVar18[0x1b];
          uVar21 = PeekChecksumStateUnderLock(iVar10 + 0x3b49c);
          iVar10 = g_clientContext;
          if (uVar20 == uVar21) {
            *(undefined1 *)(g_clientContext + 0x3b6c0) =
                 *(undefined1 *)(uVar20 + 0x4590c + g_clientContext);
          }
          *(byte *)(uVar20 + 0x45914 + iVar10) = pbVar18[0x1c];
          uVar21 = PeekChecksumStateUnderLock(iVar10 + 0x3b6c4);
          iVar10 = g_clientContext;
          if ((uVar20 == uVar21) && (*(char *)(uVar20 + 0x45914 + g_clientContext) == '\x03')) {
            *(undefined1 *)(uVar20 + 0x45914 + g_clientContext) = 1;
          }
          uVar13 = *(undefined4 *)(pbVar18 + 0x1d);
          uVar5 = *(undefined4 *)(pbVar18 + 0x21);
          *(short *)(iVar10 + 0x458bc + uVar20 * 8) = (short)uVar13;
          *(short *)(iVar10 + 0x458c0 + uVar20 * 8) = (short)uVar5;
          *(short *)(iVar10 + 0x458be + uVar20 * 8) = (short)((uint)uVar13 >> 0x10);
          *(short *)(iVar10 + 0x458c2 + uVar20 * 8) = (short)((uint)uVar5 >> 0x10);
          iVar14 = iVar10 + uVar20 * 9;
          *(undefined4 *)(iVar14 + 0x457a9) = *(undefined4 *)(pbVar18 + 0x25);
          *(undefined4 *)(iVar14 + 0x457ad) = *(undefined4 *)(pbVar18 + 0x29);
          if (((*(byte *)(iVar14 + 0x457b0) & 0x80) != 0) &&
             ((*(byte *)(iVar14 + 0x457af) & 0x80) == 0)) {
            *(undefined1 *)(iVar14 + 0x457b0) = 0;
          }
          *(undefined1 *)(iVar14 + 0x457b1) = 0;
          *(short *)(iVar10 + 0x4591c + uVar20 * 2) = *(short *)(pbVar18 + 0x2d) + 4;
          if (*(short *)(iVar10 + 0x4591c + uVar20 * 2) == -1) {
            *(undefined2 *)(iVar10 + 0x4591c + uVar20 * 2) = 0x17;
          }
          sVar4 = *(short *)(pbVar18 + 0x2f);
          pbVar18 = pbVar18 + 0x31;
          *(short *)(iVar10 + 0x4592c + uVar20 * 2) = sVar4 + 4;
          if ((short)(sVar4 + 4) == -1) {
            *(undefined2 *)(iVar10 + 0x4592c + uVar20 * 2) = 0x17;
          }
          FUN_004e74c0(*(undefined4 *)(iVar10 + 0x4587c + uVar20 * 4),
                       *(undefined2 *)(iVar10 + 0x458ac + uVar20 * 2),iVar24 + 0x457f1 + iVar10);
          local_69c = local_69c + 1;
        } while (local_69c < (int)(uint)*(byte *)(g_clientContext + 0x45125));
      }
      PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
      FUN_004e7340();
      _DAT_0056dc98 = *(undefined2 *)(g_clientContext + 0x44e60);
      _DAT_0056dc90 = *(undefined2 *)(g_clientContext + 0x3f804);
      _DAT_0056dca0 = _DAT_0056dc90;
      _DAT_0056dca8 = _DAT_0056dc98;
      *(undefined1 *)(g_clientContext + 0x45578) = 0;
      g_pendingGameState = 9;
      g_stateChangeRequested = 1;
      ChangeGameState(9);
      *(undefined4 *)(g_clientContext + 0x41340) = 0xffffffff;
      if (DAT_007934f4 == 0) {
        FUN_00404410(&DAT_00e53e88);
      }
      else {
        FUN_00405ba0();
      }
      cVar7 = PeekPacketChecksumBool();
      if (cVar7 != '\0') {
        SetGuardedBool(0);
      }
      iVar24 = payloadLen + (((uint)*(byte *)(g_clientContext + 0x45125) * -0x31 + -0x16) - uVar23);
      local_668 = 0;
      puVar12 = &local_667;
      for (iVar10 = 0x3f; iVar10 != 0; iVar10 = iVar10 + -1) {
        *puVar12 = 0;
        puVar12 = puVar12 + 1;
      }
      *(undefined2 *)puVar12 = 0;
      *(undefined1 *)((int)puVar12 + 2) = 0;
      iVar14 = 0;
      local_69c = 0;
      iVar10 = g_clientContext;
      if (0 < iVar24) {
        do {
          if (pbVar18[local_69c] == 10) {
            pbVar19 = &local_668;
            do {
              bVar3 = *pbVar19;
              pbVar19 = pbVar19 + 1;
            } while (bVar3 != 0);
            FUN_0041b8c0(iVar10,2,0,0,&local_668,0,1);
            iVar14 = 0;
            pbVar19 = &local_668;
            for (iVar15 = 0x40; iVar10 = g_clientContext, iVar15 != 0; iVar15 = iVar15 + -1) {
              pbVar19[0] = 0;
              pbVar19[1] = 0;
              pbVar19[2] = 0;
              pbVar19[3] = 0;
              pbVar19 = pbVar19 + 4;
            }
          }
          else {
            (&local_668)[iVar14] = pbVar18[local_69c];
            iVar14 = iVar14 + 1;
          }
          local_69c = local_69c + 1;
        } while (local_69c < iVar24);
      }
      pbVar18 = &local_668;
      do {
        bVar3 = *pbVar18;
        pbVar18 = pbVar18 + 1;
      } while (bVar3 != 0);
      FUN_0041b8c0(iVar10,2,0,0,&local_668,0,1);
      return;
    }
    if (*payload == 0x1d) {
      *(undefined4 *)(g_clientContext + 0x4464c + *(int *)((int)this + 4) * 4) = 0;
      *(undefined4 *)((int)this + 4) = 0xffffffff;
    }
  }
  cVar7 = PeekPacketChecksumBool();
  if (cVar7 != '\0') {
    SetGuardedBool(0);
  }
LAB_00426d84:
  FUN_0042a090();
  return;
}

