/* State11_InBattle_HandleFireInput - 0x0045f910 in the original binary.
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


/* WARNING: Removing unreachable block (ram,0x00460023) */
/* WARNING: Type propagation algorithm not settling */
/* Local input-side handler that decides the outcome of a fire attempt and
   sends the corresponding action code (0x8403 Fire / 0xc400 no-op / 0xc409
   confirm) to State11_InBattle_ProcessBattleAction's opcode family. Confirmed
   fields: this+0x243 and this+0x2cc are the first two payload fields sent
   (order matches ProcessBattleAction's Fire payload) -- almost certainly
   angle and power. No floating-point instructions and no gravity/velocity
   integration found in this function despite a full read-through: it selects
   between pre-existing outcome codes rather than computing a trajectory. Also
   logs the same event to the replay buffer. See ARCHITECTURE.md. */

void __fastcall State11_InBattle_HandleFireInput(int *param_1)

{
  undefined2 *puVar1;
  undefined1 *puVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  char cVar9;
  undefined1 uVar10;
  undefined2 uVar11;
  short sVar12;
  short sVar13;
  undefined2 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  int iVar18;
  int *piVar19;
  int *piVar20;
  int iVar21;
  int iVar22;
  char *pcVar23;
  DWORD DVar24;
  int iVar25;
  byte bVar26;
  undefined1 local_b40 [548];
  CHAR CStack_91c;
  char acStack_91b [127];
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 auStack_230 [548];
  undefined4 local_4;

  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup (local_c/puStack_8/
   * unaff_FS_OFFSET, FS-register manipulation) stripped: the handler
   * body (LAB_0053d745) was never included in this function's own
   * decompilation, so there's no exact recovery behavior to preserve.
   * Same rationale as entry/InitGame.c's fix - see src/README.md. */
  bVar4 = false;
  bVar7 = false;
  bVar6 = false;
  bVar5 = false;
  cVar9 = PeekPacketChecksumBool();
  if (((cVar9 != '\0') || (cVar9 = PeekPacketChecksumBool(), cVar9 == '\0')) || (DAT_007933b8 == '\0'))
  goto LAB_004619ff;
  bVar8 = false;
  if (DAT_00e52838 == -1000) {
    if (DAT_007934c4 == '\0') {
      cVar9 = PeekPacketChecksumBool();
      if (cVar9 == '\0') goto LAB_0045fdd7;
      cVar9 = PacketChecksumNotEquals(param_1 + 0x715,0);
      if (cVar9 == '\0') {
        cVar9 = PeekPacketChecksumBool();
        if ((((cVar9 == '\x01') && (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01')) &&
            ((cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01' &&
             ((cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01' && (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01'))
             )))) && (((&DAT_006a6481)[g_clientContext] == '\0' && (param_1[9] != 0xd)))) {
          cVar9 = FUN_0040b490(param_1 + 0x12db,param_1 + 0x203d);
          if ((cVar9 == '\0') || (cVar9 = FUN_0040b2d0(param_1 + 0x214f,0), cVar9 == '\0')) {
LAB_0045fb8c:
            bVar3 = false;
          }
          else {
            uVar17 = FUN_0040a6e0(param_1 + 0x2cc,local_b40,0x1e);
            local_4 = 0;
            uVar15 = FUN_0040a8c0(param_1 + 0x355,local_89c,2);
            local_4 = 1;
            uVar15 = FUN_0040aca0(param_1 + 0x243,local_454,uVar15);
            local_4 = 2;
            uVar16 = FUN_0040a6e0(param_1 + 0x2cc,local_678,0x1e);
            local_4 = 3;
            bVar4 = true;
            bVar7 = true;
            bVar6 = true;
            bVar5 = true;
            FUN_0040a4d0(uVar17);
            FUN_0040a4d0(uVar15);
            iVar18 = FUN_004e4340();
            iVar25 = FUN_0040a4d0(uVar16);
            if ((iVar18 <= iVar25) || (cVar9 = FUN_0040b2d0(param_1 + 0x243,0), cVar9 == '\0'))
            goto LAB_0045fb8c;
            bVar3 = true;
          }
          local_4 = 2;
          if (bVar6) {
            FUN_0040a2a0();
          }
          local_4 = 1;
          if (bVar7) {
            FUN_0040a2a0();
          }
          local_4 = 0;
          if (bVar4) {
            FUN_0040a2a0();
          }
          local_4 = 0xffffffff;
          if (bVar5) {
            FUN_0040a2a0();
          }
          if (bVar3) {
            if ((param_1[9] != 1) && (param_1[9] != 3)) {
              uVar17 = FUN_0040a8c0(param_1 + 0x19d1,local_b40,3);
              local_4 = 4;
              cVar9 = FUN_0040b490(param_1 + 0x1a5a,uVar17);
              local_4 = 0xffffffff;
              FUN_0040a2a0();
              if (cVar9 == '\0') {
                (**(code **)(*param_1 + 4))(&DAT_00553f90);
              }
              else {
                (**(code **)(*param_1 + 4))(s_wmove_00555ca0);
              }
            }
            FUN_0040b060();
            uVar17 = FUN_0040a7d0(param_1 + 0x12db,local_b40,2);
            local_4 = 5;
            iVar18 = FUN_0040a4d0(uVar17);
            AddToPacketChecksum(0x96 - iVar18);
            local_4 = 0xffffffff;
            FUN_0040a2a0();
            uVar17 = FUN_0040a4d0(&DAT_00796aa0);
            uVar17 = FUN_0040a8c0(param_1 + 0x21d8,local_b40,uVar17);
            local_4 = 6;
            FUN_0040aff0(uVar17);
            local_4 = 0xffffffff;
            FUN_0040a2a0();
            uVar17 = FUN_0040a4d0(&DAT_00796aa0);
            FUN_0040ab60(uVar17);
            param_1[0x2b84] = param_1[0x2b84] + 1;
            param_1[0x2c2c] = 3;
            bVar8 = true;
            *(byte *)(param_1 + 0x2c2b) = *(byte *)(param_1 + 2) & 7;
          }
          else {
            if (param_1[9] != 4) {
              if (param_1[0x2c29] != -1) {
                FUN_004eeae0();
                param_1[0x2c29] = -1;
              }
              (**(code **)(*param_1 + 4))(s_unmove_00555c98);
            }
            QueueOutgoingPacketField(0);
          }
        }
      }
      else {
        QueueOutgoingPacketField(0);
        QueueOutgoingPacketField(0);
        Replay_AppendEvent(0x4001);
        (&g_replayEventBuffer)[g_replayEventCursor] = 0;
        g_replayEventCursor = g_replayEventCursor + 1;
        Replay_FlushEvent();
      }
      if (((&DAT_006a64a4)[g_clientContext] == '\0') &&
         (cVar9 = PeekPacketChecksumBool(), iVar18 = g_clientContext, cVar9 != '\0')) {
        (&DAT_006a64a4)[g_clientContext] = 1;
        *(undefined4 *)(&DAT_006a64a8 + iVar18) = 1;
        *(undefined4 *)(&DAT_006a64ac + iVar18) = 0;
      }
      goto LAB_0045fdd7;
    }
  }
  else {
LAB_0045fdd7:
    bVar7 = false;
    bVar6 = false;
    bVar5 = false;
    if (((DAT_00e52838 == 1000) && (DAT_007934c4 == '\0')) &&
       (cVar9 = PeekPacketChecksumBool(), cVar9 != '\0')) {
      cVar9 = PacketChecksumNotEquals(param_1 + 0x715,1);
      if (cVar9 == '\0') {
        cVar9 = PeekPacketChecksumBool();
        if (((((cVar9 == '\x01') && (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01')) &&
             ((cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01' &&
              ((cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01' && (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01')
               ))))) && ((&DAT_006a6481)[g_clientContext] == '\0')) && (param_1[9] != 0xd)) {
          cVar9 = FUN_0040b490(param_1 + 0x12db,param_1 + 0x203d);
          if ((cVar9 == '\0') || (cVar9 = FUN_0040b2d0(param_1 + 0x214f,0), cVar9 == '\0')) {
LAB_0046000e:
            bVar4 = false;
          }
          else {
            uVar17 = FUN_0040a6e0(param_1 + 0x2cc,local_678,0x1e);
            local_4 = 7;
            uVar15 = FUN_0040a8c0(param_1 + 0x355,local_454,2);
            local_4 = 8;
            uVar15 = FUN_0040aba0(param_1 + 0x243,local_89c,uVar15);
            local_4 = 9;
            uVar16 = FUN_0040a6e0(param_1 + 0x2cc,local_b40,0x1e);
            local_4 = 10;
            bVar7 = true;
            bVar6 = true;
            bVar5 = true;
            FUN_0040a4d0(uVar17);
            FUN_0040a4d0(uVar15);
            iVar18 = FUN_004e4340();
            iVar25 = FUN_0040a4d0(uVar16);
            if ((iVar18 <= iVar25) ||
               (cVar9 = FUN_0040b330(param_1 + 0x243,*(int *)(&DAT_006a7720 + g_clientContext) + -2),
               cVar9 == '\0')) goto LAB_0046000e;
            bVar4 = true;
          }
          local_4 = 8;
          if (bVar5) {
            FUN_0040a2a0();
          }
          local_4 = 7;
          if (bVar6) {
            FUN_0040a2a0();
          }
          local_4 = 0xffffffff;
          if (bVar7) {
            FUN_0040a2a0();
          }
          if (bVar4) {
            if ((param_1[9] != 1) && (param_1[9] != 3)) {
              uVar17 = FUN_0040a8c0(param_1 + 0x19d1,local_b40,3);
              local_4 = 0xb;
              cVar9 = FUN_0040b490(param_1 + 0x1a5a,uVar17);
              local_4 = 0xffffffff;
              FUN_0040a2a0();
              if (cVar9 == '\0') {
                (**(code **)(*param_1 + 4))(&DAT_00553f90);
              }
              else {
                (**(code **)(*param_1 + 4))(s_wmove_00555ca0);
              }
            }
            FUN_0040b060();
            uVar17 = FUN_0040a7d0(param_1 + 0x12db,local_b40,2);
            local_4 = 0xc;
            iVar18 = FUN_0040a4d0(uVar17);
            AddToPacketChecksum(0x96 - iVar18);
            local_4 = 0xffffffff;
            FUN_0040a2a0();
            uVar17 = FUN_0040a4d0(&DAT_00796aa0);
            uVar17 = FUN_0040a8c0(param_1 + 0x21d8,local_b40,uVar17);
            local_4 = 0xd;
            FUN_0040afb0(uVar17);
            local_4 = 0xffffffff;
            FUN_0040a2a0();
            uVar17 = FUN_0040a4d0(&DAT_00796aa0);
            FUN_0040ab60(uVar17);
            param_1[0x2b84] = param_1[0x2b84] + 1;
            param_1[0x2c2c] = 3;
            bVar8 = true;
            *(byte *)(param_1 + 0x2c2b) = *(byte *)(param_1 + 2) & 7;
          }
          else {
            if (param_1[9] != 4) {
              if (param_1[0x2c29] != -1) {
                FUN_004eeae0();
                param_1[0x2c29] = -1;
              }
              (**(code **)(*param_1 + 4))(s_unmove_00555c98);
            }
            QueueOutgoingPacketField(0);
          }
        }
      }
      else {
        QueueOutgoingPacketField(1);
        QueueOutgoingPacketField(0);
        Replay_AppendEvent(0x4001);
        (&g_replayEventBuffer)[g_replayEventCursor] = 1;
        g_replayEventCursor = g_replayEventCursor + 1;
        Replay_FlushEvent();
      }
      if (((&DAT_006a64a4)[g_clientContext] == '\0') &&
         (cVar9 = PeekPacketChecksumBool(), iVar18 = g_clientContext, cVar9 != '\0')) {
        (&DAT_006a64a4)[g_clientContext] = 1;
        *(undefined4 *)(&DAT_006a64a8 + iVar18) = 1;
        *(undefined4 *)(&DAT_006a64ac + iVar18) = 0;
      }
    }
  }
  iVar18 = param_1[9];
  if ((iVar18 != 0xd) &&
     (((((iVar18 == 1 || (iVar18 == 3)) || (iVar18 == 4)) || ((iVar18 == 0 || (iVar18 == 2)))) &&
      (bVar8)))) {
    uVar17 = (**(int (**)())(*param_1 + 0x14))();
    uVar17 = FUN_0040a6e0(param_1 + 0x2cc,local_b40,uVar17);
    local_4 = 0xe;
    iVar18 = FUN_0040a4d0(&DAT_00794bf0);
    cVar9 = FUN_0040b330(uVar17,-iVar18);
    local_4 = 0xffffffff;
    FUN_0040a2a0();
    if (cVar9 != '\0') {
      (**(code **)(*param_1 + 4))(&DAT_00553bcc);
      *(undefined1 *)(param_1 + 0x240) = 1;
      QueueOutgoingPacketField(0);
      cVar9 = PeekPacketChecksumBool();
      if ((cVar9 == '\x01') && (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01')) {
        Replay_AppendEvent(0x8402);
        uVar11 = FUN_0040a4d0(param_1 + 0x243);
        *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
        g_replayEventCursor = g_replayEventCursor + 2;
        uVar11 = FUN_0040a4d0(param_1 + 0x2cc);
        *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
        g_replayEventCursor = g_replayEventCursor + 2;
        uVar10 = PacketChecksumEquals(param_1 + 0x715,1);
        (&g_replayEventBuffer)[g_replayEventCursor] = uVar10;
        g_replayEventCursor = g_replayEventCursor + 1;
        Replay_FlushEvent();
      }
    }
  }
  if ((DAT_00e52838 == 0) && (DAT_007934c4 == '\0')) {
    iVar18 = param_1[9];
    if ((iVar18 == 1) || ((iVar18 == 3 || (iVar18 == 4)))) {
      uVar17 = FUN_0040a8c0(param_1 + 0x19d1,local_b40,3);
      local_4 = 0xf;
      cVar9 = FUN_0040b490(param_1 + 0x1a5a,uVar17);
      local_4 = 0xffffffff;
      FUN_0040a2a0();
      if (cVar9 == '\0') {
        (**(code **)(*param_1 + 4))(s_normal_00552230);
      }
      else {
        (**(code **)(*param_1 + 4))(s_wnormal_00553618);
      }
    }
    QueueOutgoingPacketField(0);
    if (((&DAT_006a64a4)[g_clientContext] == '\x01') &&
       (cVar9 = PeekPacketChecksumBool(), iVar18 = g_clientContext, cVar9 != '\0')) {
      (&DAT_006a64a4)[g_clientContext] = 0;
      *(undefined4 *)(&DAT_006a64a8 + iVar18) = 0xffffffff;
      *(undefined4 *)(&DAT_006a64ac + iVar18) = 1;
    }
  }
  bVar5 = false;
  cVar9 = PeekPacketChecksumBool();
  if ((((cVar9 == '\x01') && (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01')) &&
      (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01')) && ((&DAT_006a6481)[g_clientContext] == '\0')) {
    if (DAT_00e5283c == -1000) {
      if (DAT_007934c4 != '\0') goto LAB_00460553;
      cVar9 = FUN_0040b2d0(param_1 + 0x939,0x5a);
      if (cVar9 == '\0') {
        FUN_0040b030();
      }
      else {
        FUN_0040b060();
      }
      bVar5 = true;
    }
    if ((DAT_00e5283c == 1000) && (DAT_007934c4 == '\0')) {
      cVar9 = FUN_0040b2d0(param_1 + 0x939,0x5a);
      if (cVar9 == '\0') {
        FUN_0040b060();
      }
      else {
        FUN_0040b030();
      }
      bVar5 = true;
    }
  }
LAB_00460553:
  cVar9 = PeekPacketChecksumBool();
  if (cVar9 == '\x01') {
    piVar19 = param_1 + 0xf1c;
  }
  else {
    cVar9 = PeekPacketChecksumBool();
    piVar19 = param_1 + 0xbe6;
    if (cVar9 != '\x01') {
      piVar19 = param_1 + 0x8b0;
    }
  }
  uVar17 = FUN_0040a4d0(piVar19);
  piVar19 = param_1 + 0x1252;
  cVar9 = FUN_0040b2d0(piVar19,uVar17);
  if (cVar9 != '\0') {
    QueueOutgoingPacketField(uVar17);
  }
  cVar9 = PeekPacketChecksumBool();
  if (cVar9 == '\x01') {
    piVar20 = param_1 + 0xfa5;
  }
  else {
    cVar9 = PeekPacketChecksumBool();
    piVar20 = param_1 + 0xc6f;
    if (cVar9 != '\x01') {
      piVar20 = param_1 + 0x939;
    }
  }
  uVar17 = FUN_0040a4d0(piVar20);
  cVar9 = FUN_0040b330(piVar19,uVar17);
  if (cVar9 != '\0') {
    QueueOutgoingPacketField(uVar17);
  }
  if (bVar5) {
    Replay_AppendEvent(0x4006);
    uVar11 = FUN_0040a4d0(piVar19);
    *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
    g_replayEventCursor = g_replayEventCursor + 2;
    Replay_FlushEvent();
  }
  piVar19 = param_1 + 0x1d90;
  uVar17 = FUN_0040a7d0(piVar19,local_b40,10);
  local_4 = 0x10;
  cVar9 = FUN_0040b450(param_1 + 0x1e19,uVar17);
  if ((((cVar9 == '\0') || (cVar9 = PacketChecksumNotEquals(param_1 + 0x1e19,0), cVar9 == '\0')) ||
      ((cVar9 = PeekPacketChecksumBool(), cVar9 != '\x01' ||
       (((cVar9 = PeekPacketChecksumBool(), cVar9 != '\x01' || (cVar9 = PeekPacketChecksumBool(), cVar9 != '\x01')) ||
        ((&DAT_006a6481)[g_clientContext] != '\0')))))) ||
     (cVar9 = FUN_0040b2d0(param_1 + 0x22f1,0), cVar9 == '\0')) {
LAB_004606d5:
    bVar5 = false;
  }
  else {
    cVar9 = PeekPacketChecksumBool();
    bVar5 = true;
    if (cVar9 != '\x01') goto LAB_004606d5;
  }
  local_4 = 0xffffffff;
  FUN_0040a2a0();
  if (bVar5) {
    uVar17 = FUN_0040a7d0(piVar19,local_89c,10);
    local_4 = 0x11;
    EncodeChecksumState(uVar17);
    local_4 = 0xffffffff;
    FUN_0040a2a0();
    FUN_0043c860(&DAT_006a7f70 + g_clientContext,param_1);
    cVar9 = PeekPacketChecksumBool();
    if (cVar9 == '\x01') {
      uVar17 = 0xc409;
    }
    else {
      cVar9 = FUN_0041eaa0(g_clientContext,(short)param_1[0x2fef]);
      if (cVar9 == '\0') {
        uVar17 = 0xc400;
      }
      else {
        uVar17 = 0x8403;
      }
    }
    Replay_AppendEvent(uVar17);
    uVar11 = FUN_0040a4d0(param_1 + 0x243);
    *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
    g_replayEventCursor = g_replayEventCursor + 2;
    uVar11 = FUN_0040a4d0(param_1 + 0x2cc);
    *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
    g_replayEventCursor = g_replayEventCursor + 2;
    piVar20 = param_1 + 0x715;
    uVar10 = PacketChecksumEquals(piVar20,1);
    (&g_replayEventBuffer)[g_replayEventCursor] = uVar10;
    g_replayEventCursor = g_replayEventCursor + 1;
    uVar10 = PeekPacketChecksumBool();
    (&g_replayEventBuffer)[g_replayEventCursor] = uVar10;
    g_replayEventCursor = g_replayEventCursor + 1;
    uVar11 = FUN_0040a4d0(param_1 + 0x1364);
    *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
    g_replayEventCursor = g_replayEventCursor + 2;
    sVar12 = FUN_0040a4d0(&DAT_00e9ba40);
    sVar13 = FUN_0040a4d0(piVar19);
    *(short *)(&g_replayEventBuffer + g_replayEventCursor) = sVar12 * sVar13;
    g_replayEventCursor = g_replayEventCursor + 2;
    cVar9 = FUN_0045ec30();
    (&g_replayEventBuffer)[g_replayEventCursor] = cVar9 != '\0';
    g_replayEventCursor = g_replayEventCursor + 1;
    cVar9 = PacketChecksumEquals(piVar20,0);
    if (cVar9 == '\0') {
      FUN_0040a4d0(param_1 + 0x273c);
      FUN_0040a4d0(param_1 + 0x1476);
    }
    else {
      FUN_0040a4d0(param_1 + 0x1476);
      FUN_0040a4d0(param_1 + 0x273c);
    }
    FUN_0040a4d0(param_1 + 0x27c5);
    uVar11 = FUN_0053753c();
    FUN_0040a4d0(param_1 + 0x27c5);
    uVar14 = FUN_0053753c();
    *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
    puVar1 = (undefined2 *)(&DAT_00e9aace + g_replayEventCursor);
    g_replayEventCursor = g_replayEventCursor + 2;
    *puVar1 = uVar14;
    g_replayEventCursor = g_replayEventCursor + 2;
    cVar9 = PacketChecksumEquals(piVar20,0);
    if (cVar9 == '\0') {
      FUN_0040a4d0(param_1 + 0x284e);
      FUN_0040a4d0(param_1 + 0x1476);
    }
    else {
      FUN_0040a4d0(param_1 + 0x284e);
      FUN_0040a4d0(param_1 + 0x1476);
    }
    FUN_0040a4d0(param_1 + 0x28d7);
    uVar11 = FUN_0053753c();
    FUN_0040a4d0(param_1 + 0x28d7);
    uVar14 = FUN_0053753c();
    *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
    puVar1 = (undefined2 *)(&DAT_00e9aace + g_replayEventCursor);
    g_replayEventCursor = g_replayEventCursor + 2;
    *puVar1 = uVar14;
    g_replayEventCursor = g_replayEventCursor + 2;
    cVar9 = PacketChecksumEquals(piVar20,0);
    if (cVar9 == '\0') {
      FUN_0040a4d0(param_1 + 0x2a72);
      FUN_0040a4d0(param_1 + 0x1476);
    }
    else {
      FUN_0040a4d0(param_1 + 0x1476);
      FUN_0040a4d0(param_1 + 0x2a72);
    }
    FUN_0040a4d0(param_1 + 0x2afb);
    uVar11 = FUN_0053753c();
    FUN_0040a4d0(param_1 + 0x2afb);
    uVar14 = FUN_0053753c();
    *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
    puVar1 = (undefined2 *)(&DAT_00e9aace + g_replayEventCursor);
    g_replayEventCursor = g_replayEventCursor + 2;
    *puVar1 = uVar14;
    g_replayEventCursor = g_replayEventCursor + 2;
    uVar11 = FUN_0040a4d0(g_clientContext + 0x5af88);
    iVar18 = g_clientContext;
    *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
    g_replayEventCursor = g_replayEventCursor + 2;
    uVar11 = FUN_0040a4d0(iVar18 + 0x5b1ac);
    *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
    puVar2 = &DAT_00e9aace + g_replayEventCursor;
    g_replayEventCursor = g_replayEventCursor + 2;
    *puVar2 = 0;
    g_replayEventCursor = g_replayEventCursor + 1;
    FUN_0043d6d0();
    Replay_FlushEvent();
    FUN_00406500(0);
    FUN_00406500(0);
    iVar18 = g_clientContext;
    *(undefined1 *)(param_1 + 0x2ffa) = 0;
    if ((&DAT_005f2f40)[iVar18] == '\x02') {
      FUN_00461c60(s_normal_00552230);
      FUN_0040a4d0(param_1 + 0x1e19);
      ClampCursorToRect();
    }
    *(undefined1 *)(DAT_007934e4 + 8) = 1;
  }
  if ((-1 < (char)(&DAT_00e52868)[DAT_00e52e68]) ||
     (cVar9 = PacketChecksumNotEquals(g_clientContext + 0x593b4,0xffffffff), cVar9 != '\0')) {
    piVar19 = param_1 + 0x1e19;
    cVar9 = PacketChecksumNotEquals(piVar19,0);
    if ((((cVar9 != '\0') &&
         ((cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01' && (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01'))))
        && (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01')) &&
       (((((&DAT_006a6481)[g_clientContext] == '\0' && ((&DAT_005f2f40)[g_clientContext] != '\x02')) &&
         (cVar9 = FUN_0040b2d0(param_1 + 0x22f1,0), cVar9 != '\0')) &&
        (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01')))) {
      cVar9 = PacketChecksumEquals(g_clientContext + 0x59190,0xffffffff);
      if (cVar9 == '\0') {
        cVar9 = PacketChecksumEquals(g_clientContext + 0x593b4,0xffffffff);
        if (cVar9 == '\0') {
          DVar24 = FUN_0040a4d0(g_clientContext + 0x593b4);
        }
        else {
          DVar24 = timeGetTime();
        }
        iVar18 = FUN_0040a4d0(g_clientContext + 0x59190);
        iVar18 = DVar24 - iVar18;
        if (iVar18 < 0) {
          iVar18 = 1;
        }
        if ((&DAT_005f2f40)[g_clientContext] == '\x01') {
          iVar25 = FUN_0040a4d0(&DAT_00e9ba40);
          iVar21 = FUN_0040a4d0(param_1 + 0x1d90);
          iVar22 = FUN_0040a4d0(&DAT_00e9ba40);
          QueueOutgoingPacketField((uint)(iVar25 * iVar21 * iVar18) / 3000 + iVar22);
        }
        uVar17 = FUN_0040a4d0(&DAT_00e9ba40);
        uVar17 = FUN_0040a7d0(param_1 + 0x1d90,local_b40,uVar17);
        local_4 = 0x12;
        cVar9 = FUN_0040b410(piVar19,uVar17);
        local_4 = 0xffffffff;
        FUN_0040a2a0();
        if (cVar9 != '\0') {
          uVar17 = FUN_0040a4d0(&DAT_00e9ba40);
          uVar17 = FUN_0040a7d0(param_1 + 0x1d90,local_89c,uVar17);
          local_4 = 0x13;
          EncodeChecksumState(uVar17);
          local_4 = 0xffffffff;
          FUN_0040a2a0();
        }
        FUN_0043c860(&DAT_006a7f70 + g_clientContext,param_1);
        cVar9 = PeekPacketChecksumBool();
        if (cVar9 == '\x01') {
          uVar17 = 0xc409;
        }
        else {
          cVar9 = FUN_0041eaa0(g_clientContext,(short)param_1[0x2fef]);
          if (cVar9 == '\0') {
            uVar17 = 0xc400;
          }
          else {
            uVar17 = 0x8403;
          }
        }
        Replay_AppendEvent(uVar17);
        uVar11 = FUN_0040a4d0(param_1 + 0x243);
        *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
        g_replayEventCursor = g_replayEventCursor + 2;
        uVar11 = FUN_0040a4d0(param_1 + 0x2cc);
        *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
        g_replayEventCursor = g_replayEventCursor + 2;
        piVar20 = param_1 + 0x715;
        uVar10 = PacketChecksumEquals(piVar20,1);
        (&g_replayEventBuffer)[g_replayEventCursor] = uVar10;
        g_replayEventCursor = g_replayEventCursor + 1;
        uVar10 = PeekPacketChecksumBool();
        (&g_replayEventBuffer)[g_replayEventCursor] = uVar10;
        g_replayEventCursor = g_replayEventCursor + 1;
        uVar11 = FUN_0040a4d0(param_1 + 0x1364);
        *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
        g_replayEventCursor = g_replayEventCursor + 2;
        uVar11 = FUN_0040a4d0(piVar19);
        *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
        g_replayEventCursor = g_replayEventCursor + 2;
        cVar9 = FUN_0045ec30();
        (&g_replayEventBuffer)[g_replayEventCursor] = cVar9 != '\0';
        g_replayEventCursor = g_replayEventCursor + 1;
        cVar9 = PacketChecksumEquals(piVar20,0);
        if (cVar9 == '\0') {
          FUN_0040a4d0(param_1 + 0x273c);
          FUN_0040a4d0(param_1 + 0x1476);
        }
        else {
          FUN_0040a4d0(param_1 + 0x1476);
          FUN_0040a4d0(param_1 + 0x273c);
        }
        FUN_0040a4d0(param_1 + 0x27c5);
        FUN_004ead90();
        uVar11 = FUN_0053753c();
        FUN_0040a4d0(param_1 + 0x27c5);
        FUN_004ead70();
        uVar14 = FUN_0053753c();
        *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
        puVar1 = (undefined2 *)(&DAT_00e9aace + g_replayEventCursor);
        g_replayEventCursor = g_replayEventCursor + 2;
        *puVar1 = uVar14;
        g_replayEventCursor = g_replayEventCursor + 2;
        cVar9 = PacketChecksumEquals(piVar20,0);
        if (cVar9 == '\0') {
          FUN_0040a4d0(param_1 + 0x284e);
          FUN_0040a4d0(param_1 + 0x1476);
        }
        else {
          FUN_0040a4d0(param_1 + 0x284e);
          FUN_0040a4d0(param_1 + 0x1476);
        }
        FUN_0040a4d0(param_1 + 0x28d7);
        FUN_004ead90();
        uVar11 = FUN_0053753c();
        FUN_0040a4d0(param_1 + 0x28d7);
        FUN_004ead70();
        uVar14 = FUN_0053753c();
        *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
        puVar1 = (undefined2 *)(&DAT_00e9aace + g_replayEventCursor);
        g_replayEventCursor = g_replayEventCursor + 2;
        *puVar1 = uVar14;
        g_replayEventCursor = g_replayEventCursor + 2;
        cVar9 = PacketChecksumEquals(piVar20,0);
        if (cVar9 == '\0') {
          FUN_0040a4d0(param_1 + 0x2a72);
          FUN_0040a4d0(param_1 + 0x1476);
        }
        else {
          FUN_0040a4d0(param_1 + 0x1476);
          FUN_0040a4d0(param_1 + 0x2a72);
        }
        FUN_0040a4d0(param_1 + 0x2afb);
        FUN_004ead90();
        uVar11 = FUN_0053753c();
        FUN_0040a4d0(param_1 + 0x2afb);
        FUN_004ead70();
        uVar14 = FUN_0053753c();
        iVar18 = g_clientContext;
        *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
        puVar1 = (undefined2 *)(&DAT_00e9aace + g_replayEventCursor);
        g_replayEventCursor = g_replayEventCursor + 2;
        *puVar1 = uVar14;
        g_replayEventCursor = g_replayEventCursor + 2;
        uVar11 = FUN_0040a4d0(iVar18 + 0x5af88);
        iVar18 = g_clientContext;
        *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
        g_replayEventCursor = g_replayEventCursor + 2;
        uVar11 = FUN_0040a4d0(iVar18 + 0x5b1ac);
        *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
        puVar2 = &DAT_00e9aace + g_replayEventCursor;
        g_replayEventCursor = g_replayEventCursor + 2;
        *puVar2 = 0;
        g_replayEventCursor = g_replayEventCursor + 1;
        FUN_0043d6d0();
        Replay_FlushEvent();
        FUN_00406500(0);
        FUN_00406500(0);
        *(undefined1 *)(param_1 + 0x2ffa) = 0;
        QueueOutgoingPacketField(0xffffffff);
        QueueOutgoingPacketField(0xffffffff);
        *(undefined1 *)(DAT_007934e4 + 8) = 1;
      }
      else {
        QueueOutgoingPacketField(0xffffffff);
      }
    }
  }
  bVar5 = true;
  if ((*(char *)(DAT_007934e4 + 8) == '\0') ||
     (iVar18 = GetWindowTextA(*(HWND *)(DAT_007934e4 + 4),&CStack_91c,0x80), iVar18 == 0)) {
    CStack_91c = '\0';
  }
  pcVar23 = &CStack_91c;
  do {
    cVar9 = *pcVar23;
    pcVar23 = pcVar23 + 1;
  } while (cVar9 != '\0');
  iVar18 = 0;
  if (0 < (int)pcVar23 - (int)acStack_91b) {
    do {
      if ((&CStack_91c)[iVar18] != ' ') {
        if (DAT_005b3438 != 2) {
          bVar5 = false;
          goto LAB_004613ad;
        }
        if (((&CStack_91c)[iVar18] != -0x7f) || (acStack_91b[iVar18] != '@')) {
          bVar5 = false;
          goto LAB_004613b2;
        }
        iVar18 = iVar18 + 1;
      }
      iVar18 = iVar18 + 1;
    } while (iVar18 < (int)pcVar23 - (int)acStack_91b);
  }
  SetWindowTextA(*(HWND *)(DAT_007934e4 + 4),&DAT_00551cb1);
LAB_004613ad:
  if (DAT_005b3438 == 2) {
LAB_004613b2:
    if (DAT_007934c4 != '\0') {
      (&DAT_00e52868)[DAT_00e52e68] = 0;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(0xffffffff);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(0xffffffff);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(0);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
  }
  cVar9 = PeekPacketChecksumBool();
  if ((((((cVar9 == '\x01') && (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01')) &&
        (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01')) &&
       (((cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01' && (param_1[9] != 0xd)) &&
        (((&DAT_005f2f40)[g_clientContext] != '\x02' &&
         ((*(int *)(&DAT_005f3768 + g_clientContext) != 1 &&
          (*(int *)(&DAT_005f3768 + g_clientContext) != 2)))))))) &&
      ((bVar5 && (DAT_007934c4 == '\0')))) &&
     (((char)(&DAT_00e52868)[DAT_00e52e68] < '\0' ||
      ((cVar9 = PacketChecksumNotEquals(g_clientContext + 0x59190,0xffffffff), cVar9 != '\0' &&
       (DAT_007934c4 == '\0')))))) {
    QueueOutgoingPacketField(0xffffffff);
    cVar9 = PacketChecksumEquals(param_1 + 0x1e19,0);
    if (cVar9 == '\0') {
      if ((&DAT_005f2f40)[g_clientContext] == '\0') {
        uVar17 = FUN_0040a8c0(param_1 + 0x1d90,auStack_230,6);
        local_4 = 0x15;
        FUN_0040afb0(uVar17);
        local_4 = 0xffffffff;
        FUN_0040a2a0();
      }
      else {
        iVar18 = FUN_0040a4d0(g_clientContext + 0x59190);
        DVar24 = timeGetTime();
        iVar25 = FUN_0040a4d0(param_1 + 0x1d90);
        if ((int)((DVar24 - iVar18) * iVar25 * 10) / 3000 < 1) {
          iVar18 = 1;
        }
        else {
          iVar18 = FUN_0040a4d0(g_clientContext + 0x59190);
          DVar24 = timeGetTime();
          iVar25 = FUN_0040a4d0(param_1 + 0x1d90);
          iVar18 = (int)((DVar24 - iVar18) * iVar25 * 10) / 3000;
        }
        QueueOutgoingPacketField(iVar18);
      }
    }
    else {
      DVar24 = timeGetTime();
      cVar9 = PacketChecksumEquals(g_clientContext + 0x59190,0xffffffff);
      if (cVar9 != '\0') {
        QueueOutgoingPacketField(DVar24 + 0x32);
      }
      iVar18 = FUN_0040a4d0(g_clientContext + 0x59190);
      if ((&DAT_005f2f40)[g_clientContext] == '\x01') {
        iVar18 = (int)(DVar24 - iVar18) / 5;
        if (iVar18 < 1) {
          iVar18 = 1;
        }
        QueueOutgoingPacketField(iVar18);
      }
      else {
        uVar17 = FUN_0040a8c0(param_1 + 0x1d90,local_b40,6);
        local_4 = 0x14;
        EncodeChecksumState(uVar17);
        local_4 = 0xffffffff;
        FUN_0040a2a0();
      }
      FUN_00406300(0);
      iVar18 = DAT_007934e4;
      *(undefined1 *)(DAT_007934e4 + 8) = 0;
      SetWindowTextA(*(HWND *)(iVar18 + 4),&DAT_00551cb1);
      Replay_AppendEvent(0x8006);
      uVar11 = FUN_0040a4d0(param_1 + 0x243);
      *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
      g_replayEventCursor = g_replayEventCursor + 2;
      uVar11 = FUN_0040a4d0(param_1 + 0x2cc);
      *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
      g_replayEventCursor = g_replayEventCursor + 2;
      cVar9 = PeekPacketChecksumBool();
      if (cVar9 == '\0') {
        cVar9 = PeekPacketChecksumBool();
        uVar10 = cVar9 != '\0';
      }
      else {
        uVar10 = 2;
      }
      (&g_replayEventBuffer)[g_replayEventCursor] = uVar10;
      g_replayEventCursor = g_replayEventCursor + 1;
      uVar10 = PacketChecksumEquals(param_1 + 0x715,1);
      (&g_replayEventBuffer)[g_replayEventCursor] = uVar10;
      g_replayEventCursor = g_replayEventCursor + 1;
      Replay_FlushEvent();
    }
  }
  if ((((param_1[9] == 1) || (param_1[9] == 3)) && (cVar9 = PeekPacketChecksumBool(), cVar9 != '\0')) &&
     (0x14 < param_1[0x2b84])) {
    Replay_AppendEvent(0x8005);
    uVar11 = FUN_0040a4d0(param_1 + 0x243);
    *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
    g_replayEventCursor = g_replayEventCursor + 2;
    uVar11 = FUN_0040a4d0(param_1 + 0x2cc);
    *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar11;
    g_replayEventCursor = g_replayEventCursor + 2;
    Replay_FlushEvent();
    param_1[0x2b84] = 0;
  }
  iVar18 = *(int *)(&DAT_006a7724 + g_clientContext);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar25 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (((iVar18 <= iVar25) && (param_1[0x2b8b] != 0xff)) && ((char)param_1[0x2b85] == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar18 = _rand();
    *(char *)((int)param_1 + 0xbff7) = (char)iVar18;
    iVar18 = _rand();
    *(byte *)(param_1 + 0x2ffe) = (byte)iVar18;
    bVar26 = '\x01' << (*(byte *)((int)param_1 + 0xbff7) & 7);
    bVar26 = ~bVar26 & (byte)iVar18 | bVar26;
    *(byte *)(param_1 + 0x2ffe) = bVar26;
    *(byte *)((int)param_1 + 0xbff9) = *(byte *)((int)param_1 + 0xbff7) + bVar26 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    cVar9 = PeekPacketChecksumBool();
    cVar9 = FUN_00406610('\x01' - (cVar9 != '\0'));
    if ((cVar9 != '\0') && (cVar9 = PeekPacketChecksumBool(), cVar9 == '\0')) {
      FUN_00464060();
    }
    uVar17 = FUN_00406860();
    cVar9 = FUN_00406610(uVar17);
    if ((cVar9 != '\0') && (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01')) {
      FUN_00406500(0);
      FUN_00406500(0);
      FUN_00406500(1);
      Replay_AppendEvent(0xc301);
      (&g_replayEventBuffer)[g_replayEventCursor] = 1;
      puVar1 = (undefined2 *)(&DAT_00e9aacd + g_replayEventCursor);
      g_replayEventCursor = g_replayEventCursor + 1;
      *puVar1 = 0xffff;
      g_replayEventCursor = g_replayEventCursor + 2;
      FUN_0041f200(0);
      Replay_FlushEvent();
    }
    *(undefined1 *)(param_1 + 0x2b85) = 1;
  }
LAB_004619ff:
  return;
}

