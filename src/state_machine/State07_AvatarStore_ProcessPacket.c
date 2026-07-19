/* State07_AvatarStore_ProcessPacket - 0x004440c0 in the original binary.
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
State07_AvatarStore_ProcessPacket(void *this,int payloadLen,ushort opcode,ushort *payload)

{
  ushort uVar1;
  char cVar2;
  undefined2 uVar3;
  int iVar4;
  tm *ptVar5;
  int iVar6;
  char *pcVar7;
  uint uVar8;
  undefined4 uVar9;
  char *pcVar10;
  uint uVar11;
  byte bVar12;
  ushort *puVar13;
  int *piVar14;
  byte *pbVar15;
  undefined2 *puVar16;
  undefined4 *puVar17;
  int *piVar18;
  code *pcVar19;
  int iVar20;
  undefined4 *puVar21;
  int local_520;
  uint local_514;
  undefined4 local_50c;
  int local_508 [4];
  short local_4f6;
  char local_4f4;
  undefined1 local_4f3;
  undefined4 local_4f0;
  undefined4 local_4ec [33];
  byte local_468;
  byte local_467;
  char local_466;
  int local_464;
  undefined4 local_c;
  
  local_c = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped (local_14/
   * puStack_10/uStack_18/unaff_FS_OFFSET) - handler body
   * (LAB_00540797) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. local_c
   * is a real, separate local reused elsewhere in this function,
   * kept as-is. */
  iVar4 = DAT_007934e8;
  if (opcode < 0x6010) {
    if (opcode == 0x600f) {
      *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
      *(undefined2 *)(iVar4 + 0x4d4) = 0x6000;
      *(undefined1 *)(iVar4 + 0x4d6) = 0;
      *(int *)(iVar4 + 0x44d0) = *(int *)(iVar4 + 0x44d0) + 1;
      SendOutgoingPacket(iVar4);
      return;
    }
    if (opcode < 0x6003) {
      if (opcode == 0x6002) {
        uVar1 = *payload;
        puVar13 = payload + 1;
        local_520 = 0;
        pcVar19 = (code *)EnterCriticalSection;
        if (uVar1 != 0) {
          do {
            piVar14 = local_508;
            for (iVar4 = 0x27; iVar4 != 0; iVar4 = iVar4 + -1) {
              *piVar14 = 0;
              piVar14 = piVar14 + 1;
            }
            local_508[0] = *(int *)puVar13;
            local_508[1] = *(int *)(puVar13 + 2);
            local_508[2] = *(int *)(puVar13 + 4);
            local_508[3] = *(int *)(puVar13 + 6);
            local_50c = *(undefined4 *)(puVar13 + 8);
            ptVar5 = _localtime((time_t *)&local_50c);
            local_4f3 = (undefined1)ptVar5->tm_mday;
            local_4f6 = (short)ptVar5->tm_year + 0x76c;
            local_4f0 = *(undefined4 *)(puVar13 + 10);
            bVar12 = (byte)puVar13[0xc];
            local_4f4 = (char)ptVar5->tm_mon + '\x01';
            puVar17 = (undefined4 *)((int)puVar13 + 0x19);
            puVar21 = local_4ec;
            for (uVar11 = (uint)(bVar12 >> 2); uVar11 != 0; uVar11 = uVar11 - 1) {
              *puVar21 = *puVar17;
              puVar17 = puVar17 + 1;
              puVar21 = puVar21 + 1;
            }
            puVar13 = (ushort *)((int)puVar13 + 0x19 + (uint)bVar12);
            for (uVar11 = bVar12 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
              *(undefined1 *)puVar21 = *(undefined1 *)puVar17;
              puVar17 = (undefined4 *)((int)puVar17 + 1);
              puVar21 = (undefined4 *)((int)puVar21 + 1);
            }
            FUN_00428550(&local_468);
            pcVar19 = (code *)EnterCriticalSection;
            local_c = 2;
            local_464 = -1;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar4 = _rand();
            local_468 = (byte)iVar4;
            iVar4 = _rand();
            local_467 = '\x01' << (local_468 & 7);
            local_467 = ~local_467 & (byte)iVar4 | local_467;
            local_466 = local_467 + local_468 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(local_508[0]);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(local_4f0);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (local_508[0] < *(int *)((int)this + 0x32f98)) {
              *(int *)((int)this + 0x32f98) = local_508[0];
            }
            if (*(int *)((int)this + 0x32f94) < local_508[0]) {
              *(int *)((int)this + 0x32f94) = local_508[0];
            }
            *(undefined1 *)((int)this + 0x32f91) = 1;
            local_514 = 0;
            if (*(int *)(g_clientContext + 0x44e24) != 0) {
              if (*(int *)(g_clientContext + 0x44e24) == 0) goto LAB_00444d76;
              do {
                EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                iVar4 = PeekPacketChecksumState();
                iVar20 = PeekPacketChecksumState();
                LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                if (iVar4 == iVar20) goto LAB_0044469b;
                local_514 = local_514 + 1;
              } while (local_514 < *(uint *)(g_clientContext + 0x44e24));
            }
            FUN_0042ae30(&local_468);
            iVar4 = g_clientContext;
            uVar11 = *(uint *)(g_clientContext + 0x44bec);
            piVar14 = (int *)(g_clientContext + 0x44be8);
            if ((*(uint *)(g_clientContext + 0x44bf0) <= uVar11) &&
               (cVar2 = FUN_004268b0(), cVar2 == '\0')) {
                    /* WARNING: Subroutine does not return */
              ThrowCxxException(0x8007000e);
            }
            piVar14 = (int *)(uVar11 * 0x9c + *piVar14);
            if (piVar14 != (int *)0x0) {
              piVar18 = local_508;
              for (iVar20 = 0x27; iVar20 != 0; iVar20 = iVar20 + -1) {
                *piVar14 = *piVar18;
                piVar18 = piVar18 + 1;
                piVar14 = piVar14 + 1;
              }
            }
            *(int *)(iVar4 + 0x44bec) = *(int *)(iVar4 + 0x44bec) + 1;
            FUN_0042ae30(&local_468);
            LoadAvatarSprites(0xffffffff,0xffffffff,0xffffffff,0xffffffff,(int)this + 0x31488,200000,
                         300000);
            Widget_SetChildRange(*(undefined4 *)(g_clientContext + 0x44e24),0xe);
            pcVar19 = (code *)EnterCriticalSection;
LAB_0044469b:
            local_c = 0xffffffff;
            FUN_00426810(&local_468);
            local_520 = local_520 + 1;
          } while (local_520 < (int)(uint)uVar1);
        }
        cVar2 = PeekPacketChecksumBool();
        if (cVar2 == '\0') {
          RenderInventoryItemDetail(this);
        }
        iVar4 = g_clientContext;
        *(undefined1 *)((int)this + 0x32f92) = 1;
        pbVar15 = (byte *)(iVar4 + 0x23310);
        (*pcVar19)(&DAT_005a9068);
        iVar20 = _rand();
        *pbVar15 = (byte)iVar20;
        iVar20 = _rand();
        *(byte *)(iVar4 + 0x23311) = (byte)iVar20;
        bVar12 = ~('\x01' << (*pbVar15 & 7)) & (byte)iVar20 | '\0' << (*pbVar15 & 7);
        *(byte *)(iVar4 + 0x23311) = bVar12;
        *(byte *)(iVar4 + 0x23312) = bVar12 + *pbVar15 + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_0044b0b0(this);
        return;
      }
      if (opcode != 0x2001) {
        if ((opcode == 0x6001) && (*payload == 0)) {
          QueueOutgoingPacketField(payload[1]);
          QueueOutgoingPacketField(payload[2]);
          QueueOutgoingPacketField(payload[3]);
          QueueOutgoingPacketField(payload[4]);
          QueueOutgoingPacketField(*(undefined4 *)(payload + 5));
          if (0xe < payloadLen) {
            QueueOutgoingPacketField(payload[7]);
            puVar13 = payload + 8;
            FUN_0044c5f0();
            FUN_0044c5f0();
            iVar20 = 0;
            iVar4 = PeekChecksumStateUnderLock(&DAT_005f4894 + g_clientContext);
            if (0 < iVar4) {
              do {
                FUN_00428550(&local_468);
                local_c = 4;
                local_464 = iVar20;
                SetGuardedBool(0,GB_GUARD_UNRECOVERED);
                QueueOutgoingPacketField(0x80000000);
                QueueOutgoingPacketField(*(undefined4 *)puVar13);
                FUN_0042ae30(&local_468);
                FUN_0042ae30(&local_468);
                puVar13 = puVar13 + 2;
                local_c = 0xffffffff;
                FUN_00426810(&local_468);
                iVar20 = iVar20 + 1;
                iVar4 = PeekChecksumStateUnderLock(&DAT_005f4894 + g_clientContext);
              } while (iVar20 < iVar4);
            }
            LoadAvatarSprites(0xffffffff,0xffffffff,0xffffffff,0xffffffff,(int)this + 0x31488,200000,
                         300000);
            FUN_0044b0b0(this);
            Widget_SetChildRange(*(undefined4 *)(g_clientContext + 0x44e24),0xe);
          }
          *(undefined1 *)(g_clientContext + 0x44bf8) = 1;
          return;
        }
        goto LAB_00445282;
      }
      if (*payload == 0) {
        g_pendingGameState = 3;
        g_stateChangeRequested = 1;
        ChangeGameState(3);
        if (DAT_007934f4 != 0) {
          FUN_00405ba0();
          return;
        }
        FUN_00404410(&DAT_00e53e88);
        return;
      }
    }
    else {
      if (opcode != 0x6005) goto LAB_00445282;
      iVar20 = 0;
      if (*payload == 0) {
        if (*(char *)((int)this + 0x30bb8) == '\0') {
          if (*(char *)((int)this + 0x30bb9) == '\0') {
            puVar16 = (undefined2 *)((int)this + 0x325a8);
            do {
              uVar3 = PeekChecksumStateUnderLock(iVar20 + 0x3ac08 + g_clientContext);
              *puVar16 = uVar3;
              iVar20 = iVar20 + 0x224;
              puVar16 = puVar16 + 1;
            } while (iVar20 < 0x890);
          }
          else {
            *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
            *(undefined2 *)(iVar4 + 0x4d4) = 0x2000;
            *(undefined2 *)(iVar4 + 0x4d6) = 0xffff;
            *(int *)(iVar4 + 0x44d0) = *(int *)(iVar4 + 0x44d0) + 2;
            SendOutgoingPacket(iVar4);
          }
        }
        else {
          g_pendingGameState = 0xf;
          g_stateChangeRequested = 0;
          DAT_0056d108 = 0;
          _DAT_007934d8 = 1;
        }
        *(undefined4 *)((int)this + 0x32f94) = 0x80000000;
        *(undefined4 *)((int)this + 0x32f98) = 0x7fffffff;
        *(undefined1 *)((int)this + 0x32f92) = 0;
        FUN_0044c5f0();
        FUN_0044c5f0();
        FUN_0044c630();
        return;
      }
    }
  }
  else {
    if (opcode == 0x6017) {
      if (*payload == 0) {
        EmitChecksumSum((int)this + 0x30770);
        QueueOutgoingPacketField(0);
        QueueOutgoingPacketField(0);
        cVar2 = PacketChecksumLessThan(g_clientContext + 0x396a0,0);
        if (cVar2 != '\0') {
          QueueOutgoingPacketField(0);
        }
        FUN_00428550(&local_468);
        local_c = 0;
        local_464 = FUN_0044c310();
        SetGuardedBool(0,GB_GUARD_UNRECOVERED);
        QueueOutgoingPacketField(0x80000000);
        uVar9 = PeekChecksumStateUnderLock((int)this + 0x3054c);
        QueueOutgoingPacketField(uVar9);
        FUN_0042ae30(&local_468);
        FUN_0042ae30(&local_468);
        QueueOutgoingPacketField(0xffffffff);
        LoadAvatarSprites(0xffffffff,0xffffffff,0xffffffff,0xffffffff,(int)this + 0x31488,200000,300000);
        FUN_0044b0b0(this);
        Widget_SetChildRange(*(undefined4 *)(g_clientContext + 0x44e24),0xe);
        QueueOutgoingPacketField(4);
        pcVar10 = (char *)GetLocalizedString(&g_localizedStringTable,0xea6a);
        pcVar7 = (char *)((int)this + 0x327d4);
        do {
          cVar2 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          *pcVar7 = cVar2;
          pcVar7 = pcVar7 + 1;
        } while (cVar2 != '\0');
        iVar4 = (int)this + 0x34794;
        *(undefined1 *)((int)this + 0x32854) = 0;
        pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0xea6b);
        _sprintf((char *)((int)this + 0x328d4),pcVar7,iVar4);
        pcVar10 = (char *)GetLocalizedString(&g_localizedStringTable,0xea6c);
        pcVar7 = (char *)((int)this + 0x32954);
        do {
          cVar2 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          *pcVar7 = cVar2;
          pcVar7 = pcVar7 + 1;
        } while (cVar2 != '\0');
        *(undefined1 *)((int)this + 0x329d4) = 0;
        pcVar10 = (char *)GetLocalizedString(&g_localizedStringTable,0xea6d);
        pcVar7 = (char *)((int)this + 0x32a54);
        do {
          cVar2 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          *pcVar7 = cVar2;
          pcVar7 = pcVar7 + 1;
        } while (cVar2 != '\0');
        *(undefined1 *)((int)this + 0x32ad4) = 0;
        CreateButtonWidget(&DAT_00e9be90,0,0x3b,0x516,s_b_storewindow_confirm_00555a8c,0x14d,0x154,
                           0x4a,0x1a,1,0);
        g_serverWaitTicks = 0xffffffff;
        local_c = 0xffffffff;
        FUN_00426810(&local_468);
        return;
      }
      if (*payload == 0x6003) {
        ShowErrorDialog(0);
        iVar20 = DAT_007934e8;
        iVar4 = g_clientContext;
        *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
        *(undefined2 *)(iVar20 + 0x4d4) = 0x6000;
        *(bool *)(iVar20 + 0x4d6) = *(char *)(iVar4 + 0x44bf8) == '\0';
        *(int *)(iVar20 + 0x44d0) = *(int *)(iVar20 + 0x44d0) + 1;
        SendOutgoingPacket(iVar20);
      }
    }
    else {
      if (opcode != 0x6027) {
        if (opcode == 0x6037) {
          if (*payload == 0) {
            uVar11 = PeekChecksumStateUnderLock((int)this + 0x3054c);
            if (*(uint *)(g_clientContext + 0x44e24) <= uVar11) {
                    /* WARNING: Subroutine does not return */
              ThrowCxxException(0x80070057);
            }
            FUN_0044c370();
            PeekChecksumStateUnderLock((int)this + 0x3054c);
            FUN_0044c6a0(g_clientContext + 0x44e20);
            iVar4 = 0;
            local_520 = 0;
            do {
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar20 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar6 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              if (iVar20 == iVar6) {
                switch(local_520) {
                case 0:
                  cVar2 = PeekPacketChecksumBool();
                  uVar11 = -(uint)(cVar2 != '\0') & 0x8000;
                  break;
                case 1:
                  cVar2 = PeekPacketChecksumBool();
                  uVar11 = -(uint)(cVar2 != '\0') & 0x8000;
                  break;
                case 2:
                  cVar2 = PeekPacketChecksumBool();
                  uVar11 = -(uint)(cVar2 != '\0') & 0x8000;
                  break;
                case 3:
                  uVar11 = 0x8000;
                  break;
                default:
                  goto switchD_004449fc_default;
                }
                QueueOutgoingPacketField(uVar11);
switchD_004449fc_default:
                EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                EncodeOutgoingPacketField(0xffffffff);
                LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                LoadAvatarSprites(0xffffffff,0xffffffff,0xffffffff,0xffffffff,(int)this + 0x31488,200000,
                             300000);
                break;
              }
              local_520 = local_520 + 1;
              iVar4 = iVar4 + 0x224;
            } while (iVar4 < 0x890);
            FUN_0044b0b0(this);
            FUN_00424400();
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(0xffffffff);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            *(undefined1 *)((int)this + 0x32f91) = 1;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(0xffffffff);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            ShowErrorDialog(0);
            iVar4 = g_clientContext + 0x23330;
            pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0xfa8);
            _sprintf((char *)local_508,pcVar7,iVar4);
            FUN_00402900(&DAT_00e53e88,(int)this + 0x32ce3);
            Widget_SetChildRange(*(undefined4 *)(g_clientContext + 0x44e24),0xe);
          }
          else if (*payload == 0x6002) {
            ShowErrorDialog(0);
          }
          *(undefined1 *)((int)this + 0x32f90) = 1;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar4 = _rand();
          *(char *)((int)this + 0x32ce0) = (char)iVar4;
          iVar4 = _rand();
          *(byte *)((int)this + 0x32ce1) = (byte)iVar4;
          bVar12 = *(byte *)((int)this + 0x32ce0) & 7;
          bVar12 = ~('\x01' << bVar12) & (byte)iVar4 | '\0' << bVar12;
          *(byte *)((int)this + 0x32ce1) = bVar12;
          *(byte *)((int)this + 0x32ce2) = *(byte *)((int)this + 0x32ce0) + bVar12 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar4 = _rand();
          *(char *)((int)this + 0x32c54) = (char)iVar4;
          iVar4 = _rand();
          *(byte *)((int)this + 0x32c55) = (byte)iVar4;
          bVar12 = *(byte *)((int)this + 0x32c54) & 7;
          bVar12 = ~('\x01' << bVar12) & (byte)iVar4 | '\0' << bVar12;
          *(byte *)((int)this + 0x32c55) = bVar12;
          *(byte *)((int)this + 0x32c56) = *(byte *)((int)this + 0x32c54) + bVar12 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          RemoveWidget();
          RemoveWidget();
          FUN_0040cdf0();
          FUN_0040cdf0();
          FUN_0044b720(this);
          return;
        }
        goto LAB_00445282;
      }
      if (*payload == 0) {
        EmitChecksumSum((int)this + 0x30770);
        QueueOutgoingPacketField(0);
        cVar2 = PacketChecksumLessThan(g_clientContext + 0x396a0,0);
        if (cVar2 != '\0') {
          QueueOutgoingPacketField(0);
        }
        iVar4 = (int)this + 0x3054c;
        uVar11 = PeekChecksumStateUnderLock(iVar4);
        if (*(uint *)(g_clientContext + 0x44e24) <= uVar11) {
LAB_00444d76:
                    /* WARNING: Subroutine does not return */
          ThrowCxxException(0x80070057);
        }
        FUN_0044c370();
        PeekChecksumStateUnderLock(iVar4);
        FUN_0044c6a0(g_clientContext + 0x44e20);
        uVar11 = *(uint *)(g_clientContext + 0x44e34);
        uVar8 = PeekChecksumStateUnderLock(iVar4);
        if (uVar8 < uVar11) {
          PeekChecksumStateUnderLock(iVar4);
          FUN_0044c6a0(g_clientContext + 0x44e30);
        }
        local_514 = 0;
        local_520 = 0;
        do {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar4 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar20 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar4 == iVar20) {
            switch(local_514) {
            case 0:
              cVar2 = PeekPacketChecksumBool();
              uVar11 = -(uint)(cVar2 != '\0') & 0x8000;
              break;
            case 1:
              cVar2 = PeekPacketChecksumBool();
              uVar11 = -(uint)(cVar2 != '\0') & 0x8000;
              break;
            case 2:
              cVar2 = PeekPacketChecksumBool();
              uVar11 = -(uint)(cVar2 != '\0') & 0x8000;
              break;
            case 3:
              uVar11 = 0x8000;
              break;
            default:
              goto switchD_00444e7c_default;
            }
            QueueOutgoingPacketField(uVar11);
switchD_00444e7c_default:
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(0xffffffff);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            LoadAvatarSprites(0xffffffff,0xffffffff,0xffffffff,0xffffffff,(int)this + 0x31488,200000,
                         300000);
            break;
          }
          local_520 = local_520 + 0x224;
          local_514 = local_514 + 1;
        } while (local_520 < 0x890);
        FUN_0044b0b0(this);
        FUN_00424400();
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(0xffffffff);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(0xffffffff);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        Widget_SetChildRange(*(undefined4 *)(g_clientContext + 0x44e24),0xe);
      }
      else if (*payload == 0x6002) {
        ShowErrorDialog(0);
      }
    }
    *(undefined1 *)((int)this + 0x32f90) = 1;
  }
  FUN_00449250(this,1,0);
LAB_00445282:
  return;
}

