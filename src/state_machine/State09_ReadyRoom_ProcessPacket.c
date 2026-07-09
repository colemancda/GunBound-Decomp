/* State09_ReadyRoom_ProcessPacket - 0x004d38c0 in the original binary.
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
State09_ReadyRoom_ProcessPacket(void *this,int payloadLen,ushort opcode,byte *payload)

{
  uint uVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  short sVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  uint uVar8;
  void *_Memory;
  int *piVar9;
  char cVar10;
  undefined4 uVar11;
  char *pcVar12;
  tm *_Tm;
  char *pcVar13;
  char *pcVar14;
  int iVar15;
  byte bVar16;
  int iVar17;
  uint uVar18;
  int extraout_EDX;
  int iVar19;
  int iVar20;
  byte *pbVar21;
  undefined4 *puVar22;
  undefined *puVar23;
  int *piVar24;
  byte *pbVar25;
  int iVar26;
  char *pcStack_994;
  int *piStack_990;
  int iStack_98c;
  void *apvStack_988 [2];
  char cStack_980;
  undefined4 uStack_97f;
  char acStack_900 [128];
  char acStack_880 [128];
  char acStack_800 [2048];
  
  iVar19 = DAT_007934e8;
  iVar17 = g_clientContext;
  apvStack_988[0] = this;
  if (opcode < 0x3232) {
    if (opcode == 0x3231) {
      if (*(short *)payload == 0) {
        Replay_AppendEvent(0x8102);
        (&g_replayEventBuffer)[g_replayEventCursor] =
             (*(char *)((int)this + 8) != '\0') * '\x02' + '\x01';
        g_replayEventCursor = g_replayEventCursor + 1;
        Replay_FlushEvent();
        FUN_004da460(this,1,1);
        *(bool *)(*(int *)((int)this + 0x788) + 0x1e) = *(char *)((int)this + 8) == '\0';
        return;
      }
    }
    else {
      if (opcode < 0x3106) {
        if (opcode == 0x3105) {
          if (DAT_00e9c104 != 0) {
            FUN_0040ccf0();
          }
          DAT_00e9c104 = 0;
          FUN_004f3060(&DAT_00e9c0fc);
          SendMessageA(*(HWND *)(DAT_007934e4 + 4),0xc5,0x3c,0);
          *(undefined1 *)((int)this + 0x62c) = 0;
          FUN_004da460(this,1,0);
          if (*(short *)payload != 0) {
            return;
          }
          Replay_AppendEvent(0x8000);
          (&g_replayEventBuffer)[g_replayEventCursor] = *(undefined1 *)((int)this + 9);
          g_replayEventCursor = g_replayEventCursor + 1;
          uVar11 = FUN_0040a4d0((int)this + 0xc);
          *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
          puVar23 = &DAT_00e9aad0 + g_replayEventCursor;
          g_replayEventCursor = g_replayEventCursor + 4;
          *puVar23 = *(undefined1 *)((int)this + 0x230);
          iVar17 = g_replayEventCursor;
          puVar22 = (undefined4 *)(&DAT_00e9aacd + g_replayEventCursor);
          g_replayEventCursor = g_replayEventCursor + 1;
          *puVar22 = *(undefined4 *)((int)this + 0x25d);
          *(undefined4 *)(&DAT_00e9aad1 + iVar17) = *(undefined4 *)((int)this + 0x261);
          g_replayEventCursor = g_replayEventCursor + 8;
          pcVar13 = (char *)((int)this + 0x62d);
          pcVar12 = pcVar13;
          do {
            cVar10 = *pcVar12;
            pcVar12 = pcVar12 + 1;
          } while (cVar10 != '\0');
          Replay_AppendString(pcVar13);
          Replay_FlushEvent();
          FUN_004da460(this,1,1);
          iVar17 = g_clientContext - (int)pcVar13;
          pcVar12 = pcVar13;
          do {
            cVar10 = *pcVar12;
            pcVar12[iVar17 + 0x44e64] = cVar10;
            pcVar12 = pcVar12 + 1;
          } while (cVar10 != '\0');
          Replay_AppendEvent(0x8003);
          pcVar12 = pcVar13;
          do {
            cVar10 = *pcVar12;
            pcVar12 = pcVar12 + 1;
          } while (cVar10 != '\0');
          Replay_AppendString(pcVar13);
          Replay_FlushEvent();
          return;
        }
        if (opcode != 0x2001) {
          if (opcode == 0x3010) {
            FUN_004db720();
            FUN_004dc200(*payload);
            FUN_004dc5c0();
            return;
          }
          if (opcode != 0x3020) {
            return;
          }
          FUN_004db720();
          return;
        }
        if (*(short *)payload != 0) {
          return;
        }
        if (DAT_00793522 != '\0') {
          (**(code **)(*(int *)g_gameStateVTableArray[0xb] + 0x20))();
        }
        _DAT_007934d8 = 1;
        *(undefined1 *)(*(int *)((int)this + 0x788) + 0x1e) = 1;
        g_pendingGameState = 3;
        g_stateChangeRequested = 0;
        DAT_0056d108 = 0;
        if (DAT_007934f4 == 0) {
          FUN_00404410(&DAT_00e53e88);
          return;
        }
        FUN_00405ba0();
        return;
      }
      if (opcode == 0x3151) {
        if (*(short *)payload != 0) {
          return;
        }
        Replay_AppendEvent(0x8200);
        (&g_replayEventBuffer)[g_replayEventCursor] = payload[2];
LAB_004d3bd3:
        g_replayEventCursor = g_replayEventCursor + 1;
        Replay_FlushEvent();
        uVar11 = 1;
        goto LAB_004d3bec;
      }
      if (opcode == 0x3201) {
        if (*(short *)payload == 0) {
          Replay_AppendEvent(0x8100);
          (&g_replayEventBuffer)[g_replayEventCursor] = *(undefined1 *)((int)this + 0x259);
          puVar23 = &DAT_00e9aacd + g_replayEventCursor;
          g_replayEventCursor = g_replayEventCursor + 1;
          *puVar23 = *(undefined1 *)((int)this + 0x25a);
          goto LAB_004d3bd3;
        }
      }
      else {
        if (opcode != 0x3211) {
          return;
        }
        if (*(short *)payload == 0) {
          Replay_AppendEvent(0x8101);
          (&g_replayEventBuffer)[g_replayEventCursor] = *(undefined1 *)((int)this + 0x25b);
          goto LAB_004d3bd3;
        }
      }
    }
  }
  else {
    if (0x3432 < opcode) {
      if (opcode == 0x3fff) {
        FUN_004da460(this,0,0);
        if (payloadLen != 0) {
          FUN_00412820(payload,0);
        }
        iVar17 = DAT_007934e8;
        *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
        *(undefined2 *)(iVar17 + 0x4d4) = 0x2000;
        *(undefined2 *)(iVar17 + 0x4d6) = 0xffff;
        *(int *)(iVar17 + 0x44d0) = *(int *)(iVar17 + 0x44d0) + 2;
        FUN_004d2680();
      }
      else if ((opcode == 0x4410) && (g_pendingGameState != 3)) {
        *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3232;
        *(undefined4 *)(iVar19 + 0x44d0) = 6;
        FUN_004d2680();
        return;
      }
      return;
    }
    if (opcode == 0x3432) {
      *(undefined1 *)(*(int *)((int)this + 0x788) + 0x1e) = 1;
      if (*(FILE **)(&g_replayFileHandle + iVar17) != (FILE *)0x0) {
        _fclose(*(FILE **)(&g_replayFileHandle + iVar17));
      }
      FID_conflict___time32((__time32_t *)&piStack_990);
      _Tm = _localtime((time_t *)&piStack_990);
      _strftime(acStack_880,0x80,s__Y_m_d__H_M_005570bc,_Tm);
      cStack_980 = '\0';
      puVar22 = &uStack_97f;
      for (iVar17 = 0x1f; iVar17 != 0; iVar17 = iVar17 + -1) {
        *puVar22 = 0;
        puVar22 = puVar22 + 1;
      }
      *(undefined2 *)puVar22 = 0;
      *(undefined1 *)((int)puVar22 + 2) = 0;
      uVar18 = 0;
      pcVar12 = (char *)(g_clientContext + 0x44e64);
      pcVar13 = pcVar12;
      do {
        cVar10 = *pcVar13;
        pcVar13 = pcVar13 + 1;
      } while (cVar10 != '\0');
      iStack_98c = (int)pcVar13 - (g_clientContext + 0x44e65);
      if (iStack_98c != 0) {
        pcVar13 = &cStack_980;
        do {
          cVar10 = pcVar12[uVar18];
          if (cVar10 < 0x80) {
            if ((((((cVar10 != '\\') && (cVar10 != '/')) && (cVar10 != ':')) &&
                 ((cVar10 != '*' && (cVar10 != '?')))) &&
                ((cVar10 != '\"' && ((cVar10 != '<' && (cVar10 != '>')))))) && (cVar10 != '|'))
            goto LAB_004d3fb0;
          }
          else {
            *pcVar13 = cVar10;
            cVar10 = *(char *)(g_clientContext + 0x44e65 + uVar18);
            pcVar13 = pcVar13 + 1;
            uVar18 = uVar18 + 1;
LAB_004d3fb0:
            *pcVar13 = cVar10;
            pcVar13 = pcVar13 + 1;
          }
          uVar18 = uVar18 + 1;
          pcVar14 = pcVar12;
          do {
            cVar10 = *pcVar14;
            pcVar14 = pcVar14 + 1;
          } while (cVar10 != '\0');
        } while (uVar18 < (uint)((int)pcVar14 - (g_clientContext + 0x44e65)));
      }
      _sprintf(acStack_800,s__s_s____s_sv_005570ac,&DAT_005b1ed0,acStack_880,&cStack_980);
      iVar17 = g_clientContext;
      *(undefined4 *)(&g_replayFileHandle + g_clientContext) = 0;
      bVar2 = *payload;
      *(byte *)(iVar17 + 0x475c4) = bVar2;
      DAT_00793515 = 0;
      *(byte *)(iVar17 + 0x475c4) = bVar2 % 0xb;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar11 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar11);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      cVar10 = FUN_00419d30();
      if (cVar10 == '\0') {
        ShowErrorDialog(1);
      }
      uVar4 = *(undefined2 *)(payload + 1);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(uVar4);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar17 = g_clientContext;
      *(undefined4 *)(g_clientContext + 0x5010d) = 0;
      pbVar21 = payload + 3;
      *(undefined4 *)(iVar17 + 0x50111) = 0;
      iVar17 = 0;
      do {
        iVar19 = 8;
        do {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(0);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar20 = g_clientContext;
          iVar17 = iVar17 + 0x224;
          iVar19 = iVar19 + -1;
        } while (iVar19 != 0);
      } while (iVar17 < 0x8900);
      *(undefined1 *)(g_clientContext + 0x5010c) = *(undefined1 *)(g_clientContext + 0x45122);
      *(undefined4 *)(iVar20 + 0x58b40) = 0xffffffff;
      *(undefined4 *)(iVar20 + 0x58b44) = 0xffffffff;
      *(undefined4 *)(iVar20 + 0x58b48) = 0xffffffff;
      *(undefined4 *)(iVar20 + 0x58b4c) = 0xffffffff;
      *(undefined4 *)(iVar20 + 0x58b50) = 0xffffffff;
      *(undefined4 *)(iVar20 + 0x58b54) = 0xffffffff;
      *(undefined4 *)(iVar20 + 0x58b58) = 0xffffffff;
      *(undefined4 *)(iVar20 + 0x58b5c) = 0xffffffff;
      piStack_990 = (int *)0x0;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar17 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (0 < iVar17) {
        do {
          iVar17 = g_clientContext;
          uVar18 = (uint)*pbVar21;
          iStack_98c = uVar18 * 0xd;
          puVar22 = (undefined4 *)(iStack_98c + 0x50196 + g_clientContext);
          *puVar22 = *(undefined4 *)(pbVar21 + 1);
          puVar22[1] = *(undefined4 *)(pbVar21 + 5);
          puVar22[2] = *(undefined4 *)(pbVar21 + 9);
          *(undefined1 *)(iStack_98c + 0x501a2 + iVar17) = 0;
          *(byte *)(uVar18 + 0x50126 + iVar17) = pbVar21[0xd];
          bVar2 = pbVar21[0xe];
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(bVar2);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          bVar2 = pbVar21[0xf];
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(bVar2);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar17 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar17 < 0x11) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar17 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (0xc < iVar17) {
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar17 = PeekPacketChecksumState();
              iVar17 = iVar17 + 2;
              goto LAB_004d42c9;
            }
          }
          else {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar17 = PeekPacketChecksumState();
            iVar17 = iVar17 + -4;
LAB_004d42c9:
            EncodeOutgoingPacketField(iVar17);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar17 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar17 < 0x11) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar17 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (0xc < iVar17) {
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar17 = PeekPacketChecksumState();
              iVar17 = iVar17 + 2;
              goto LAB_004d438d;
            }
          }
          else {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar17 = PeekPacketChecksumState();
            iVar17 = iVar17 + -4;
LAB_004d438d:
            EncodeOutgoingPacketField(iVar17);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          iVar17 = g_clientContext;
          *(undefined2 *)(g_clientContext + 0x49a2c + uVar18 * 2) = *(undefined2 *)(pbVar21 + 0x10);
          *(undefined2 *)(iVar17 + 0x49a3c + uVar18 * 2) = *(undefined2 *)(pbVar21 + 0x12);
          *(uint *)(iVar17 + 0x58b40 + uVar18 * 4) = (uint)*(ushort *)(pbVar21 + 0x14);
          *(undefined1 *)(uVar18 + 0x5010d + iVar17) = 1;
          *(undefined2 *)(iVar17 + 0x50116 + uVar18 * 2) =
               *(undefined2 *)(iVar17 + 0x4591c + uVar18 * 2);
          pcVar13 = (char *)(uVar18 * 9 + 0x457a9 + iVar17);
          pbVar21 = pbVar21 + 0x16;
          do {
            cVar10 = *pcVar13;
            pcVar13[0xa985] = cVar10;
            pcVar13 = pcVar13 + 1;
          } while (cVar10 != '\0');
          uVar4 = *(undefined2 *)(iVar17 + 0x4599c + uVar18 * 4);
          *(undefined2 *)(iVar17 + 0x50176 + uVar18 * 2) =
               *(undefined2 *)(iVar17 + 0x4597c + uVar18 * 4);
          uVar11 = *(undefined4 *)(iVar17 + 0x458bc + uVar18 * 8);
          *(undefined2 *)(iVar17 + 0x50186 + uVar18 * 2) = uVar4;
          puVar22 = (undefined4 *)(iVar17 + 0x501fe + uVar18 * 8);
          *puVar22 = uVar11;
          puVar22[1] = *(undefined4 *)(iVar17 + 0x458c0 + uVar18 * 8);
          FUN_00424ac0(iVar17,puVar22,uVar18 * 0x1120 + 0x50240 + iVar17,1);
          iVar17 = (uVar18 - 0x7482) * 0xb - g_clientContext;
          pcVar13 = (char *)(iStack_98c + 0x50196 + g_clientContext);
          do {
            cVar10 = *pcVar13;
            pcVar13[(int)(&DAT_00e55d58 + iVar17)] = cVar10;
            pcVar13 = pcVar13 + 1;
          } while (cVar10 != '\0');
          piVar24 = (int *)((int)piStack_990 + 1);
          piStack_990 = piVar24;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar17 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        } while ((int)piVar24 < iVar17);
      }
      iVar17 = g_clientContext;
      sVar5 = *(short *)pbVar21;
      *(short *)(&DAT_006aa660 + g_clientContext) = sVar5;
      if (sVar5 != -1) {
        *(undefined4 *)(&DAT_006aa674 + iVar17) = 0;
        FUN_00426210();
        uVar3 = (&DAT_006aa674)[extraout_EDX];
        *(undefined1 *)(extraout_EDX + 0x457a0) = *(undefined1 *)(extraout_EDX + 0x45578);
        *(undefined1 *)(extraout_EDX + 0x45578) = uVar3;
        iVar17 = extraout_EDX;
      }
      FUN_0041fd50(iVar17,*(undefined4 *)(pbVar21 + 2));
      DAT_005b3480 = *(undefined4 *)(pbVar21 + 2);
      pbVar21 = pbVar21 + 6;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(0);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar17 = g_clientContext;
      pbVar25 = &DAT_006a7f90 + g_clientContext;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar19 = _rand();
      *pbVar25 = (byte)iVar19;
      iVar19 = _rand();
      bVar2 = *pbVar25;
      (&DAT_006a7f91)[iVar17] = (byte)iVar19;
      bVar16 = bVar2 & 7;
      bVar16 = ~('\x01' << bVar16) & (byte)iVar19 | '\0' << bVar16;
      (&DAT_006a7f91)[iVar17] = bVar16;
      (&DAT_006a7f92)[iVar17] = bVar16 + bVar2 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar17 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar17 == 3) {
        iVar17 = 0;
        do {
          uVar4 = *(undefined2 *)pbVar21;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          bVar2 = pbVar21[2];
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(bVar2);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar17 = iVar17 + 0x224;
          pbVar21 = pbVar21 + 3;
        } while (iVar17 < 0xcd8);
      }
      _DAT_00e560a0 = 0;
      _DAT_00e560a4 = 0;
      _DAT_00e560a8 = 0;
      _DAT_00e55e18 = 0;
      _DAT_00e55e1c = 0xff;
      _DAT_00e560ac = 0;
      /* DAT_00e9be94[7]/comparisons against DAT_00e9be94 itself: same
       * "value at DAT_00e9be94 + 0x1c" idiom used everywhere else this
       * global appears (`*(int *)(DAT_00e9be94 + 0x1c)`), just written
       * via array-index syntax at this call site - DAT_00e9be94 is a
       * uint32_t (a raw address value, not an array), so it can't be
       * subscripted directly under strict C; cast to a pointer at each
       * use here instead of changing the global's declared type, which
       * would break its ~15 other byte-offset call sites elsewhere. */
      puVar22 = *(undefined4 **)(DAT_00e9be94 + 0x1c);
      if (puVar22 != (undefined4 *)DAT_00e9be94) {
        do {
          puVar6 = (undefined4 *)puVar22[4];
          while (puVar6 != puVar22) {
            puVar7 = (undefined4 *)*puVar6;
            puVar6 = (undefined4 *)puVar6[4];
            (*(code *)*puVar7)(1);
          }
          puVar22[3] = puVar22;
          puVar22[4] = puVar22;
          puVar22 = (undefined4 *)puVar22[7];
        } while (puVar22 != (undefined4 *)DAT_00e9be94);
      }
      _DAT_00e9be98 = 0;
      _DAT_00e9be9c = 0;
      DAT_00793522 = 1;
      puVar22 = DAT_00e53c44;
      do {
        if (puVar22 == (undefined4 *)0x0) goto LAB_004d46f3;
        iVar17 = puVar22[2];
        puVar22 = (undefined4 *)*puVar22;
      } while ((*(int *)(iVar17 + 0x20) != 0) || (*(int *)(iVar17 + 0x24) != 40000));
      *(undefined1 *)(iVar17 + 0x1d) = 1;
LAB_004d46f3:
      *(undefined4 *)((int)apvStack_988[0] + 0x740) = 0;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar17 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      _sprintf(acStack_900,s_load_stage_02d_img_00557098,
               (uint)*(byte *)(g_clientContext + 0x475c4) + iVar17 * 0xb);
      FUN_004f1790(&DAT_00ea0e18,0x2718);
      uVar18 = 0x3f2;
      iVar17 = 0xd;
      do {
        puVar22 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
        uVar8 = puVar22[1];
        uVar1 = uVar18 - 10;
        if (uVar8 <= uVar1) {
LAB_004d4783:
          if (uVar8 != uVar1) goto code_r0x004d4785;
          puVar6 = (undefined4 *)puVar22[4];
          while (puVar6 != puVar22) {
            puVar7 = (undefined4 *)*puVar6;
            puVar6 = (undefined4 *)puVar6[4];
            (*(code *)*puVar7)(1);
          }
          puVar22[3] = puVar22;
          puVar22[4] = puVar22;
        }
LAB_004d47ad:
        puVar22 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
        uVar1 = puVar22[1];
        if (uVar1 <= uVar18) {
LAB_004d47bd:
          if (uVar1 != uVar18) goto code_r0x004d47bf;
          puVar6 = (undefined4 *)puVar22[4];
          while (puVar6 != puVar22) {
            puVar7 = (undefined4 *)*puVar6;
            puVar6 = (undefined4 *)puVar6[4];
            (*(code *)*puVar7)(1);
          }
          puVar22[3] = puVar22;
          puVar22[4] = puVar22;
        }
LAB_004d47e7:
        puVar22 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
        uVar8 = puVar22[1];
        uVar1 = uVar18 + 10;
        if (uVar8 <= uVar1) {
LAB_004d47f9:
          if (uVar8 != uVar1) goto code_r0x004d47fb;
          puVar6 = (undefined4 *)puVar22[4];
          while (puVar6 != puVar22) {
            puVar7 = (undefined4 *)*puVar6;
            puVar6 = (undefined4 *)puVar6[4];
            (*(code *)*puVar7)(1);
          }
          puVar22[3] = puVar22;
          puVar22[4] = puVar22;
        }
LAB_004d4825:
        puVar22 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
        uVar8 = puVar22[1];
        uVar1 = uVar18 + 0x14;
        if (uVar8 <= uVar1) {
LAB_004d4837:
          if (uVar8 != uVar1) goto code_r0x004d4839;
          puVar6 = (undefined4 *)puVar22[4];
          while (puVar6 != puVar22) {
            puVar7 = (undefined4 *)*puVar6;
            puVar6 = (undefined4 *)puVar6[4];
            (*(code *)*puVar7)(1);
          }
          puVar22[3] = puVar22;
          puVar22[4] = puVar22;
        }
LAB_004d4865:
        puVar22 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
        uVar8 = puVar22[1];
        uVar1 = uVar18 + 0x1e;
        if (uVar8 <= uVar1) {
LAB_004d4877:
          if (uVar8 != uVar1) goto code_r0x004d4879;
          puVar6 = (undefined4 *)puVar22[4];
          while (puVar6 != puVar22) {
            puVar7 = (undefined4 *)*puVar6;
            puVar6 = (undefined4 *)puVar6[4];
            (*(code *)*puVar7)(1);
          }
          puVar22[3] = puVar22;
          puVar22[4] = puVar22;
        }
LAB_004d48a5:
        puVar22 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
        uVar8 = puVar22[1];
        uVar1 = uVar18 + 0x28;
        if (uVar8 <= uVar1) {
LAB_004d48b7:
          if (uVar8 != uVar1) goto code_r0x004d48b9;
          puVar6 = (undefined4 *)puVar22[4];
          while (puVar6 != puVar22) {
            puVar7 = (undefined4 *)*puVar6;
            puVar6 = (undefined4 *)puVar6[4];
            (*(code *)*puVar7)(1);
          }
          puVar22[3] = puVar22;
          puVar22[4] = puVar22;
        }
LAB_004d48e5:
        puVar22 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
        uVar8 = puVar22[1];
        uVar1 = uVar18 + 0x32;
        if (uVar8 <= uVar1) {
LAB_004d48f7:
          if (uVar8 != uVar1) goto code_r0x004d48f9;
          puVar6 = (undefined4 *)puVar22[4];
          while (puVar6 != puVar22) {
            puVar7 = (undefined4 *)*puVar6;
            puVar6 = (undefined4 *)puVar6[4];
            (*(code *)*puVar7)(1);
          }
          puVar22[3] = puVar22;
          puVar22[4] = puVar22;
        }
LAB_004d4925:
        puVar22 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
        uVar8 = puVar22[1];
        uVar1 = uVar18 + 0x5a;
        if (uVar8 <= uVar1) {
LAB_004d4937:
          if (uVar8 != uVar1) goto code_r0x004d4939;
          puVar6 = (undefined4 *)puVar22[4];
          while (puVar6 != puVar22) {
            puVar7 = (undefined4 *)*puVar6;
            puVar6 = (undefined4 *)puVar6[4];
            (*(code *)*puVar7)(1);
          }
          puVar22[3] = puVar22;
          puVar22[4] = puVar22;
        }
LAB_004d4965:
        puVar22 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
        uVar8 = puVar22[1];
        uVar1 = uVar18 + 0xbe;
        if (uVar8 <= uVar1) {
LAB_004d497a:
          if (uVar8 != uVar1) goto code_r0x004d497c;
          puVar6 = (undefined4 *)puVar22[4];
          while (puVar6 != puVar22) {
            puVar7 = (undefined4 *)*puVar6;
            puVar6 = (undefined4 *)puVar6[4];
            (*(code *)*puVar7)(1);
          }
          puVar22[3] = puVar22;
          puVar22[4] = puVar22;
        }
LAB_004d49a5:
        iVar19 = g_clientContext;
        uVar18 = uVar18 + 1;
        iVar17 = iVar17 + -1;
      } while (iVar17 != 0);
      pbVar21 = &DAT_006a9b6c + g_clientContext;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar17 = _rand();
      *pbVar21 = (byte)iVar17;
      iVar17 = _rand();
      bVar2 = *pbVar21;
      (&DAT_006a9b6d)[iVar19] = (byte)iVar17;
      bVar16 = bVar2 & 7;
      bVar16 = ~('\x01' << bVar16) & (byte)iVar17 | '\0' << bVar16;
      (&DAT_006a9b6d)[iVar19] = bVar16;
      (&DAT_006a9b6e)[iVar19] = bVar2 + bVar16 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar17 = g_clientContext;
      pbVar21 = (byte *)(g_clientContext + 0x6214f);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar19 = _rand();
      *pbVar21 = (byte)iVar19;
      iVar19 = _rand();
      bVar2 = *pbVar21;
      *(byte *)(iVar17 + 0x62150) = (byte)iVar19;
      bVar16 = bVar2 & 7;
      bVar16 = ~('\x01' << bVar16) & (byte)iVar19 | '\0' << bVar16;
      *(byte *)(iVar17 + 0x62150) = bVar16;
      *(byte *)(iVar17 + 0x62151) = bVar2 + bVar16 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar17 = g_clientContext;
      pbVar21 = (byte *)(g_clientContext + 0x62152);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar19 = _rand();
      *pbVar21 = (byte)iVar19;
      iVar19 = _rand();
      bVar2 = *pbVar21;
      *(byte *)(iVar17 + 0x62153) = (byte)iVar19;
      bVar16 = bVar2 & 7;
      bVar16 = ~('\x01' << bVar16) & (byte)iVar19 | '\0' << bVar16;
      *(byte *)(iVar17 + 0x62153) = bVar16;
      *(byte *)(iVar17 + 0x62154) = bVar2 + bVar16 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_00420280(g_clientContext);
      iVar17 = g_clientContext;
      puVar22 = (undefined4 *)(&DAT_006a7670 + g_clientContext);
      for (iVar19 = 0x20; iVar19 != 0; iVar19 = iVar19 + -1) {
        *puVar22 = 0;
        puVar22 = puVar22 + 1;
      }
      *(undefined4 *)(g_gameStateVTableArray[0xb] + 0x10b8) = 0;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar19 = _rand();
      *(byte *)(iVar17 + 0x62149) = (byte)iVar19;
      iVar19 = _rand();
      bVar2 = *(byte *)(iVar17 + 0x62149);
      *(byte *)(iVar17 + 0x6214a) = (byte)iVar19;
      bVar16 = bVar2 & 7;
      bVar16 = ~('\x01' << bVar16) & (byte)iVar19 | '\0' << bVar16;
      *(byte *)(iVar17 + 0x6214a) = bVar16;
      *(byte *)(iVar17 + 0x6214b) = bVar2 + bVar16 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar17 = g_clientContext;
      pbVar21 = (byte *)(g_clientContext + 0x6214c);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar19 = _rand();
      *pbVar21 = (byte)iVar19;
      iVar19 = _rand();
      bVar2 = *pbVar21;
      *(byte *)(iVar17 + 0x6214d) = (byte)iVar19;
      bVar16 = bVar2 & 7;
      bVar16 = ~('\x01' << bVar16) & (byte)iVar19 | '\0' << bVar16;
      *(byte *)(iVar17 + 0x6214d) = bVar16;
      *(byte *)(iVar17 + 0x6214e) = bVar2 + bVar16 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar20 = 0;
      piStack_990 = (int *)((int)apvStack_988[0] + 0x6fc);
      iVar19 = 0;
      iVar17 = g_clientContext;
      do {
        if (*(char *)(iVar17 + 0x45914 + iVar20) != '\0') {
          *(undefined1 *)(iVar17 + 0x45914 + iVar20) = 4;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar17 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          _sprintf(acStack_900,s_tank_d_00553fa0,iVar17 + 1);
          iVar17 = g_clientContext;
          piVar24 = (int *)(&DAT_0067ec70 + g_clientContext);
          iVar26 = 0;
          if (0 < *(int *)(&DAT_0067ec70 + g_clientContext)) {
            pcStack_994 = &DAT_0067ec74 + g_clientContext;
            do {
              iVar15 = __stricmp(acStack_900,pcStack_994);
              if (iVar15 == 0) {
                puVar23 = &DAT_0069ec74 + iVar26 * 0x18 + iVar17;
                goto LAB_004d4cc7;
              }
              iVar26 = iVar26 + 1;
              pcStack_994 = pcStack_994 + 0x80;
            } while (iVar26 < *piVar24);
          }
          puVar23 = (undefined *)0x0;
LAB_004d4cc7:
          piVar24 = piStack_990;
          *(undefined **)(*piStack_990 + 0x1c) = puVar23;
          (**(code **)(*(int *)*piStack_990 + 4))(s_normal_00552230);
          (**(code **)(*(int *)piVar24[1] + 4))(s_normal_00552230);
          iVar17 = g_clientContext;
        }
        iVar19 = iVar19 + 0x448;
        piStack_990 = piStack_990 + 2;
        iVar20 = iVar20 + 1;
        if (0x223f < iVar19) {
          *(undefined4 *)((int)apvStack_988[0] + 0x744) = 0xffffffff;
          _Memory = *(void **)(&DAT_006a76f4 + iVar17);
          iVar19 = iVar17;
          if (_Memory != (void *)0x0) {
            _free(_Memory);
            iVar19 = g_clientContext;
            *(undefined4 *)(&DAT_006a76f4 + iVar17) = 0;
          }
          *(undefined4 *)(&DAT_006a76f8 + iVar17) = 0;
          *(undefined4 *)(&DAT_006a76fc + iVar17) = 0;
          *(undefined4 *)(&DAT_006a7704 + iVar19) = 0xffffffff;
          cVar10 = *(char *)((int)*(int **)(DAT_00e9af14 + 4) + 0xf);
          piVar24 = *(int **)(DAT_00e9af14 + 4);
          while (cVar10 == '\0') {
            FUN_004e8ad0(piVar24[2]);
            piVar9 = (int *)*piVar24;
            _free(piVar24);
            piVar24 = piVar9;
            cVar10 = *(char *)((int)piVar9 + 0xf);
          }
          *(int *)(DAT_00e9af14 + 4) = DAT_00e9af14;
          _DAT_00e9af18 = 0;
          *(int *)DAT_00e9af14 = DAT_00e9af14;
          *(int *)(DAT_00e9af14 + 8) = DAT_00e9af14;
          iStack_98c = 0xc303;
          FUN_004e86f0(apvStack_988);
          iStack_98c = 0xc302;
          FUN_004e86f0(apvStack_988);
          return;
        }
      } while( true );
    }
    if (opcode == 0x3233) {
      if (*(short *)payload != 0) {
        *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
        *(undefined2 *)(iVar19 + 0x4d4) = 0x2000;
        *(undefined2 *)(iVar19 + 0x4d6) = 0xffff;
        *(int *)(iVar19 + 0x44d0) = *(int *)(iVar19 + 0x44d0) + 2;
        FUN_004d2680();
        *(undefined4 *)(g_clientContext + 0x44e60) = 0xffffffff;
        return;
      }
      (**(code **)(*(int *)g_gameStateVTableArray[0xb] + 0x20))();
      g_pendingGameState = 9;
      g_stateChangeRequested = 0;
      DAT_0056d108 = 0;
      _DAT_007934d8 = 1;
      *(undefined1 *)(*(int *)((int)this + 0x788) + 0x1e) = 1;
      Replay_AppendEvent(0x8103);
      Replay_FlushEvent();
      if (*(int *)(&DAT_006a64b4 + g_clientContext) == -1) {
        return;
      }
      FUN_004eeae0();
      *(undefined4 *)(&DAT_006a64b4 + g_clientContext) = 0xffffffff;
      return;
    }
    if (opcode == 0x3400) {
      if (1 < payloadLen) {
        FUN_00425a30(g_clientContext);
        uVar18 = (uint)*(byte *)(g_clientContext + 0x45124);
        FUN_0040a4d0(g_clientContext + 0x44efc);
        FUN_004daa60(this,uVar18);
      }
      cVar10 = FUN_0040b390(g_clientContext + 0x3b49c,g_clientContext + 0x3b6c4);
      if (cVar10 == '\0') {
        FUN_00405fb0();
        CreateButtonWidget(&DAT_00e9be90,0,0,1000,s_b_ready_ready_005570c8,0x28f,0x226,0x6b,0x2d,1,0
                          );
        FUN_004dbd50(this,0);
      }
      else {
        FUN_00405fb0();
        CreateButtonWidget(&DAT_00e9be90,0,1,0x3e9,s_b_ready_startgame_005570d8,0x28f,0x226,0x6b,
                           0x2d,1,0);
        *(undefined1 *)((int)this + 0x4cc) = 0;
        FUN_004dbd50(this,0);
        FUN_004db720();
        FUN_004da460(this,1,0);
      }
      iVar17 = FUN_0040a4d0(g_clientContext + 0x3b6c4);
      if (*(char *)(iVar17 + 0x45914 + g_clientContext) != '\x03') {
        return;
      }
      iVar17 = FUN_0040a4d0(g_clientContext + 0x3b6c4);
      *(undefined1 *)(iVar17 + 0x45914 + g_clientContext) = 1;
      return;
    }
    if (opcode != 0x3431) {
      return;
    }
  }
  uVar11 = 0;
LAB_004d3bec:
  FUN_004da460(this,1,uVar11);
  return;
code_r0x004d4785:
  puVar22 = (undefined4 *)puVar22[7];
  uVar8 = puVar22[1];
  if (uVar1 < uVar8) goto LAB_004d47ad;
  goto LAB_004d4783;
code_r0x004d47bf:
  puVar22 = (undefined4 *)puVar22[7];
  uVar1 = puVar22[1];
  if (uVar18 < uVar1) goto LAB_004d47e7;
  goto LAB_004d47bd;
code_r0x004d47fb:
  puVar22 = (undefined4 *)puVar22[7];
  uVar8 = puVar22[1];
  if (uVar1 < uVar8) goto LAB_004d4825;
  goto LAB_004d47f9;
code_r0x004d4839:
  puVar22 = (undefined4 *)puVar22[7];
  uVar8 = puVar22[1];
  if (uVar1 < uVar8) goto LAB_004d4865;
  goto LAB_004d4837;
code_r0x004d4879:
  puVar22 = (undefined4 *)puVar22[7];
  uVar8 = puVar22[1];
  if (uVar1 < uVar8) goto LAB_004d48a5;
  goto LAB_004d4877;
code_r0x004d48b9:
  puVar22 = (undefined4 *)puVar22[7];
  uVar8 = puVar22[1];
  if (uVar1 < uVar8) goto LAB_004d48e5;
  goto LAB_004d48b7;
code_r0x004d48f9:
  puVar22 = (undefined4 *)puVar22[7];
  uVar8 = puVar22[1];
  if (uVar1 < uVar8) goto LAB_004d4925;
  goto LAB_004d48f7;
code_r0x004d4939:
  puVar22 = (undefined4 *)puVar22[7];
  uVar8 = puVar22[1];
  if (uVar1 < uVar8) goto LAB_004d4965;
  goto LAB_004d4937;
code_r0x004d497c:
  puVar22 = (undefined4 *)puVar22[7];
  uVar8 = puVar22[1];
  if (uVar1 < uVar8) goto LAB_004d49a5;
  goto LAB_004d497a;
}

