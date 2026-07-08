/* State09_ReadyRoom_HandleChatInput - 0x004d6210 in the original binary.
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


void __thiscall State09_ReadyRoom_HandleChatInput(int *param_1,int param_2,int param_3,uint param_4)

{
  byte *pbVar1;
  undefined1 uVar2;
  ushort uVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  uint uVar9;
  uint uVar10;
  char *pcVar11;
  char *pcVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  int aiStack_c0 [15];
  undefined4 uStack_84;
  char cStack_81;
  char acStack_80 [60];
  undefined1 uStack_44;
  
  if (param_2 == 0x100) {
    if ((param_3 == 0xd) && (DAT_007933b8 == '\x01')) {
      cVar4 = FUN_004065a0();
      if (cVar4 == '\0') {
        FUN_0040c880();
        if ((acStack_80[0] != '\0') &&
           (cVar4 = FUN_004218c0(g_clientContext,acStack_80), cVar4 == '\0')) {
          cVar4 = FUN_00415b00(acStack_80);
          if (cVar4 == '\x01') {
            uVar13 = 0x202;
          }
          else {
            cVar4 = FUN_00415230();
            if (cVar4 == '\0') {
              Replay_AppendEvent(1);
              pcVar8 = acStack_80;
              do {
                cVar4 = *pcVar8;
                pcVar8 = pcVar8 + 1;
              } while (cVar4 != '\0');
              Replay_AppendString(acStack_80);
              Replay_FlushEvent();
              goto LAB_004d67e1;
            }
            uVar13 = 0x205;
          }
          uVar15 = 6;
          uVar14 = 2;
          iVar5 = *param_1;
          uVar13 = FUN_0043dc70(&DAT_00796eec,uVar13);
          (**(code **)(iVar5 + 0x28))(uVar13,uVar14,uVar15);
        }
      }
      else {
        FUN_00426230();
      }
LAB_004d67e1:
      SetWindowTextA(*(HWND *)(DAT_007934e4 + 4),&DAT_00551cb1);
      return;
    }
  }
  else {
    if (param_2 == 0x201) {
      uVar10 = param_4 & 0xffff;
      param_4 = param_4 >> 0x10;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((((iVar5 == 2) && (0x17a < uVar10)) && (uVar10 < 0x1ea)) &&
         (((0x186 < param_4 && (param_4 < 0x218)) && ((char)param_1[0x133] == '\0')))) {
        FUN_004da460(param_1,0,0);
        iVar6 = DAT_007934e8;
        *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
        *(undefined2 *)(iVar6 + 0x4d4) = 0x3200;
        uVar2 = *(undefined1 *)((int)param_1 + 0x25a);
        *(undefined1 *)((int)param_1 + 0x25a) = *(undefined1 *)((int)param_1 + 0x259);
        *(undefined1 *)((int)param_1 + 0x259) = uVar2;
        *(undefined1 *)(iVar6 + 0x4d0 + *(int *)(iVar6 + 0x44d0)) = uVar2;
        iVar5 = *(int *)(iVar6 + 0x44d0);
        *(int *)(iVar6 + 0x44d0) = iVar5 + 1;
        *(undefined1 *)(iVar5 + 0x4d1 + iVar6) = *(undefined1 *)((int)param_1 + 0x25a);
        *(int *)(iVar6 + 0x44d0) = *(int *)(iVar6 + 0x44d0) + 1;
        FUN_004d2680();
      }
      if (((0x16c < param_4) && (param_4 < 0x18b)) && ((char)param_1[0x133] == '\0')) {
        iVar5 = 0x20b;
        do {
          if ((iVar5 <= (int)uVar10) && ((int)uVar10 <= iVar5 + 0x23)) {
            iVar6 = FUN_004dc0f0();
            if (iVar6 == -1) break;
            cVar4 = PacketChecksumEquals(iVar6 * 0x224 + 0x39f30 + g_clientContext,0xff);
            if (cVar4 != '\0') {
              QueueOutgoingPacketField(0);
            }
            QueueOutgoingPacketField(0);
          }
          iVar5 = iVar5 + 0x24;
        } while (iVar5 < 0x2e3);
      }
      aiStack_c0[8] = 0x26;
      aiStack_c0[9] = 0xb1;
      aiStack_c0[10] = 0x26;
      aiStack_c0[0xb] = 0xb1;
      aiStack_c0[0xc] = 0x1f0;
      aiStack_c0[0xd] = 0x27b;
      aiStack_c0[0xe] = 0x1f0;
      uStack_84 = 0x27b;
      aiStack_c0[0] = 0x3d;
      aiStack_c0[1] = 0x3d;
      aiStack_c0[2] = 0xd5;
      aiStack_c0[3] = 0xd5;
      aiStack_c0[4] = 0x3d;
      aiStack_c0[5] = 0x3d;
      aiStack_c0[6] = 0xd5;
      aiStack_c0[7] = 0xd5;
      iVar5 = 0;
      while ((((iVar6 = (int)*(char *)(iVar5 + 0x4a0 + (int)param_1),
               *(char *)(g_clientContext + 0x45914 + iVar5) == '\0' ||
               ((int)param_4 <= aiStack_c0[iVar6])) || (aiStack_c0[iVar6] + 0x81 <= (int)param_4))
             || (((int)uVar10 <= aiStack_c0[iVar6 + 8] ||
                 (aiStack_c0[iVar6 + 8] + 0x7f <= (int)uVar10))))) {
        iVar5 = iVar5 + 1;
        if (7 < iVar5) goto LAB_004d6626;
      }
      FUN_0040c880();
      pcVar8 = (char *)(iVar5 * 0xd + 0x457f1 + g_clientContext);
      pcVar7 = pcVar8;
      do {
        cVar4 = *pcVar7;
        pcVar7 = pcVar7 + 1;
      } while (cVar4 != '\0');
      pcVar12 = &cStack_81;
      do {
        pcVar11 = pcVar12 + 1;
        pcVar12 = pcVar12 + 1;
      } while (*pcVar11 != '\0');
      pcVar11 = pcVar8;
      for (uVar10 = (uint)((int)pcVar7 - (int)pcVar8) >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
        *(undefined4 *)pcVar12 = *(undefined4 *)pcVar11;
        pcVar11 = pcVar11 + 4;
        pcVar12 = pcVar12 + 4;
      }
      for (uVar10 = (int)pcVar7 - (int)pcVar8 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
        *pcVar12 = *pcVar11;
        pcVar11 = pcVar11 + 1;
        pcVar12 = pcVar12 + 1;
      }
      uStack_44 = 0;
      FUN_0040c8b0();
      pcVar8 = acStack_80;
      do {
        cVar4 = *pcVar8;
        pcVar8 = pcVar8 + 1;
      } while (cVar4 != '\0');
      FUN_0040c8d0((int)pcVar8 - (int)(acStack_80 + 1));
LAB_004d6626:
      if ((char)param_1[0x133] != '\0') {
        return;
      }
      iVar5 = FUN_004dc570();
      if (iVar5 == -1) {
        return;
      }
      iVar5 = iVar5 + param_1[0x188] * 9;
      if (param_1[0x187] <= iVar5) {
        return;
      }
      uVar3 = (&DAT_0056dc40)[param_1[iVar5 + 0x146]];
      if (*(char *)(param_1[iVar5 + 0x146] + 0x4d8 + (int)param_1) == '\0') {
        return;
      }
      iVar5 = FUN_004dc140(((uVar3 & 0xff00) != 0) + '\x01');
      if (iVar5 == -1) {
        return;
      }
      if ((uVar3 & 0xff00) != 0) {
        QueueOutgoingPacketField(0xff);
        QueueOutgoingPacketField(uVar3 & 0xff);
        return;
      }
      QueueOutgoingPacketField(uVar3 & 0xff);
      return;
    }
    if (((param_2 == 0x204) &&
        (cVar4 = FUN_0040b3d0(g_clientContext + 0x3b49c,g_clientContext + 0x3b6c4), cVar4 == '\0')) &&
       (((char)param_1[0x186] != '\0' &&
        (((cVar4 = FUN_00406400(), cVar4 != '\0' && (iVar5 = FUN_004dc570(), iVar5 != -1)) &&
         (iVar5 = iVar5 + param_1[0x188] * 9, uVar10 = param_1[iVar5 + 0x146],
         iVar5 < param_1[0x187])))))) {
      FUN_004da460(param_1,0,0);
      iVar5 = g_clientContext;
      *(undefined4 *)((int)param_1 + 0x25d) = *(undefined4 *)(g_clientContext + 0x457a1);
      *(undefined4 *)((int)param_1 + 0x261) = *(undefined4 *)(iVar5 + 0x457a5);
      iVar5 = DAT_007934e8;
      uVar9 = uVar10 & 0x80000007;
      pbVar1 = (byte *)(((int)(uVar10 + ((int)uVar10 >> 0x1f & 7U)) >> 3) + 0x25d + (int)param_1);
      if ((int)uVar9 < 0) {
        uVar9 = (uVar9 - 1 | 0xfffffff8) + 1;
      }
      *pbVar1 = *pbVar1 ^ (byte)(0x80 >> ((byte)uVar9 & 0x1f));
      *(undefined4 *)(iVar5 + 0x44d0) = 6;
      *(undefined2 *)(iVar5 + 0x4d4) = 0x3102;
      *(undefined4 *)(iVar5 + 0x4d6) = *(undefined4 *)((int)param_1 + 0x25d);
      *(undefined4 *)(iVar5 + 0x4da) = *(undefined4 *)((int)param_1 + 0x261);
      *(int *)(iVar5 + 0x44d0) = *(int *)(iVar5 + 0x44d0) + 8;
      FUN_004d2680();
      param_1[0x18a] = 100;
      return;
    }
  }
  return;
}

