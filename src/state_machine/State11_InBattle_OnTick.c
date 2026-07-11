/* State11_InBattle_OnTick - 0x004bd8b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING (jumptable): Unable to track spacebase fully for stack */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall State11_InBattle_OnTick(int *param_1)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xffffc278;
  undefined stack0xffffc27c;
  undefined stack0xffffc280;
  undefined stack0xffffc284;
  undefined stack0xfffffffc;
  undefined4 *puVar1;
  int *piVar2;
  char cVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  char *pcVar9;
  int iVar10;
  uint uVar11;
  byte bVar12;
  byte bVar13;
  int *unaff_EBX;
  int iVar14;
  int *piVar15;
  uint unaff_ESI;
  code *pcVar16;
  int *unaff_EDI;
  byte *pbVar17;
  undefined4 *unaff_FS_OFFSET;
  bool bVar18;
  undefined *puVar19;
  HCURSOR hCursor;
  undefined4 uStack_3d78;
  undefined3 uVar20;
  undefined4 uStack_3d70;
  int *local_3d68;
  int *piStack_3d64;
  int *local_3d60;
  int *piStack_3d5c;
  int *local_3d58;
  uint local_3d54;
  int local_3d50;
  uint local_3d4c;
  int *local_3d34;
  char acStack_3b4c [16];
  char acStack_3b3c [20];
  undefined1 local_3b28;
  CHAR aCStack_3aac [92];
  char acStack_3a50 [140];
  char acStack_39c4 [128];
  char acStack_3944 [128];
  char acStack_38c4 [128];
  char acStack_3844 [116];
  char acStack_37d0 [140];
  char acStack_3744 [116];
  char acStack_36d0 [140];
  char acStack_3644 [132];
  undefined1 auStack_35c0 [16];
  int iStack_35b0;
  int *local_3588;
  undefined1 auStack_338c [8];
  undefined1 auStack_3384 [4];
  uint uStack_3380;
  int *piStack_3374;
  undefined1 auStack_316c [4];
  undefined1 auStack_3168 [12];
  uint uStack_315c;
  int iStack_3158;
  undefined1 auStack_2f48 [16];
  int iStack_2f38;
  undefined1 auStack_2d24 [16];
  int iStack_2d14;
  undefined1 auStack_2b00 [16];
  int iStack_2af0;
  undefined1 auStack_28d8 [12];
  uint uStack_28cc;
  undefined1 auStack_26b8 [16];
  int iStack_26a8;
  undefined1 auStack_2494 [16];
  uint uStack_2484;
  undefined1 auStack_2270 [16];
  int iStack_2260;
  undefined1 auStack_2048 [12];
  uint uStack_203c;
  undefined1 auStack_1e2c [16];
  int iStack_1e1c;
  undefined1 auStack_1bf4 [28];
  int *piStack_1bd8;
  undefined1 auStack_19e0 [16];
  int iStack_19d0;
  undefined1 auStack_17bc [16];
  int iStack_17ac;
  undefined1 auStack_1594 [12];
  int iStack_1588;
  undefined1 auStack_1370 [12];
  int iStack_1364;
  undefined1 auStack_114c [12];
  int iStack_1140;
  undefined1 auStack_f2c [16];
  uint uStack_f1c;
  undefined1 auStack_d04 [12];
  uint uStack_cf8;
  undefined1 auStack_ae0 [12];
  uint uStack_ad4;
  undefined1 auStack_8c0 [12];
  int iStack_8b4;
  undefined1 auStack_6a4 [12];
  int iStack_698;
  undefined1 auStack_474 [12];
  int iStack_468;
  undefined1 auStack_250 [12];
  int iStack_244;
  undefined1 uStack_34;
  undefined1 uStack_30;
  undefined1 uStack_2c;
  undefined1 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  int *piStack_18;
  undefined4 uStack_14;
  undefined1 *puStack_10;
  int local_c;
  
  uStack_3d78 = (int *)&stack0xfffffffc;
  local_c = 0xffffffff;
  puStack_10 = &LAB_0054095a;
  uStack_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_14;
  iVar6 = g_clientContext;
  uStack_1c = 0x4bd8d6;
  *(int *)(&DAT_006a64b8 + g_clientContext) = *(int *)(&DAT_006a64b8 + g_clientContext) + 1;
  DAT_0056d118 = 0xffffffff;
  piVar15 = (int *)&stack0xfffffffc;
  local_3d58 = param_1;
  piStack_18 = param_1;
  if ((((char)param_1[0x474] == '\x01') && (piVar15 = (int *)&stack0xfffffffc, -1 < param_1[0x475]))
     && (iVar5 = param_1[0x475] + 1, param_1[0x475] = iVar5, piVar15 = (int *)&stack0xfffffffc,
        300 < iVar5)) {
    param_1[0x475] = -1;
    InvokeWidget();
    iVar6 = DAT_007934e8;
    *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3232;
    *(undefined4 *)(iVar6 + 0x44d0) = 6;
    SendOutgoingPacket();
    iVar6 = g_clientContext;
    piVar15 = uStack_3d78;
  }
  uStack_3d78 = piVar15;
  if (*(int *)(&DAT_006a76f8 + iVar6) != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar6 == iVar5) &&
       (local_3d54 = 0, iVar6 = g_clientContext, *(int *)(&DAT_006a76f8 + g_clientContext) != 0)) {
      do {
        if (*(uint *)(&DAT_006a76f8 + iVar6) <= local_3d54) {
LAB_004bdd21:
                    /* WARNING: Subroutine does not return */
          ThrowCxxException();
        }
        iVar5 = local_3d54 * 4;
        local_3d50 = *(int *)(*(int *)(&DAT_006a76f4 + iVar6) + iVar5);
        iVar14 = *(int *)(&DAT_006aaac4 + local_3d50 * 4 + iVar6);
        *(int *)(&DAT_006aaac4 + local_3d50 * 4 + iVar6) = iVar14 + 1;
        if ((iVar14 + 1) % 0x3c == 0) {
          local_3d4c = 0;
          bVar18 = true;
          do {
            if (!bVar18) goto LAB_004bdd1c;
            if (((((&DAT_00e55e20)[local_3d4c >> 5] & 1 << ((byte)local_3d4c & 0x1f)) != 0) &&
                ((&DAT_006a7670)[local_3d4c + local_3d50 * 8 + iVar6] == '\0')) &&
               (cVar3 = FUN_004e82c0(), iVar6 = g_clientContext, cVar3 != '\0')) {
              FUN_004e83b0();
              iVar6 = g_clientContext;
            }
            local_3d4c = local_3d4c + 1;
            bVar18 = local_3d4c < 8;
          } while ((int)local_3d4c < 8);
        }
        if (*(int *)(&DAT_006aaac4 + local_3d50 * 4 + iVar6) % 200 == 0) {
          local_3d4c = 0;
          bVar18 = true;
          do {
            uVar11 = local_3d4c;
            if (!bVar18) {
LAB_004bdd1c:
                    /* WARNING: Subroutine does not return */
              FUN_00426460();
            }
            bVar13 = (byte)local_3d4c;
            if ((((&DAT_00e55e20)[local_3d4c >> 5] & 1 << (bVar13 & 0x1f)) != 0) &&
               ((&DAT_006a7670)[local_3d4c + local_3d50 * 8 + iVar6] == '\0')) {
              Replay_AppendEvent();
              if (*(uint *)(&DAT_006a76f8 + g_clientContext) <= local_3d54) goto LAB_004bdd21;
              (&g_replayEventBuffer)[g_replayEventCursor] =
                   *(undefined1 *)(*(int *)(&DAT_006a76f4 + g_clientContext) + iVar5);
              g_replayEventCursor = g_replayEventCursor + 1;
              FUN_004e7140();
              Replay_AppendEvent();
              (&g_replayEventBuffer)[g_replayEventCursor] = bVar13;
              g_replayEventCursor = g_replayEventCursor + 1;
              Replay_FlushEvent();
              iVar14 = DAT_007934e8;
              iVar6 = g_clientContext;
              if (*(int *)(&DAT_006aaac4 + local_3d50 * 4 + g_clientContext) % 600 == 0) {
                *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
                *(undefined2 *)(iVar14 + 0x4d4) = 0x4000;
                *(byte *)(iVar14 + 0x4d6) = bVar13;
                *(int *)(iVar14 + 0x44d0) = *(int *)(iVar14 + 0x44d0) + 1;
                EncodePacketBody();
                SendOutgoingPacket();
                Replay_AppendEvent();
                (&g_replayEventBuffer)[g_replayEventCursor] = (undefined1)local_3d4c;
                g_replayEventCursor = g_replayEventCursor + 1;
                Replay_FlushEvent();
                uVar11 = local_3d4c;
                iVar6 = g_clientContext;
              }
            }
            local_3d4c = uVar11 + 1;
            bVar18 = local_3d4c < 8;
          } while ((int)local_3d4c < 8);
        }
        local_3d54 = local_3d54 + 1;
        param_1 = local_3d58;
      } while (local_3d54 < *(uint *)(&DAT_006a76f8 + iVar6));
    }
  }
  if ((0 < param_1[0x8f1]) && (iVar6 = param_1[0x8f1] + -1, param_1[0x8f1] = iVar6, iVar6 == 0)) {
    param_1[0x8f1] = -1;
    _DAT_00e9b80c = 10;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar6 == *(int *)(&DAT_006a64b0 + g_clientContext)) {
    iVar6 = *(int *)(&DAT_006a64b4 + g_clientContext);
    iVar5 = g_clientContext;
    if (iVar6 != -1) {
      if ((DAT_00793549 != '\0') &&
         ((**(code **)(**(int **)(DAT_00793554 + iVar6 * 4) + 0xc))(), iVar6 == 0)) {
        DAT_00793568 = 0;
      }
      iVar5 = g_clientContext;
      *(undefined4 *)(&DAT_006a64b4 + g_clientContext) = 0xffffffff;
    }
  }
  else {
    if (*(int *)(&DAT_006a64b4 + g_clientContext) == -1) {
      uVar7 = AcquireSoundChannel();
      *(undefined4 *)(&DAT_006a64b4 + g_clientContext) = uVar7;
      param_1 = local_3d58;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = g_clientContext;
    iVar6 = iVar6 - *(int *)(&DAT_006a64b0 + g_clientContext);
    if (iVar6 < 1) {
      iVar6 = iVar6 + -0xf;
    }
    else {
      iVar6 = iVar6 + 0xf;
    }
    *(int *)(&DAT_006a64b0 + g_clientContext) =
         *(int *)(&DAT_006a64b0 + g_clientContext) + ((int)(iVar6 + (iVar6 >> 0x1f & 0xfU)) >> 4);
  }
  if (((char)param_1[4] == '\0') && (*(char *)((int)param_1 + 0x91) == '\0')) {
    iVar6 = 0;
    local_3d4c = 0;
    bVar13 = g_cursorAnchorX < 5;
    if ((bool)bVar13) {
      local_3d4c = -*(int *)(&DAT_005f2f44 + iVar5);
    }
    if (0x31b < g_cursorAnchorX) {
      local_3d4c = *(uint *)(&DAT_005f2f44 + iVar5);
      bVar13 = bVar13 | 2;
    }
    if (g_cursorAnchorY < 5) {
      iVar6 = -*(int *)(&DAT_005f2f44 + iVar5);
      bVar13 = bVar13 | 4;
    }
    if (0x253 < g_cursorAnchorY) {
      iVar6 = *(int *)(&DAT_005f2f44 + iVar5);
      bVar13 = bVar13 | 8;
    }
    if (g_lastCursorDirection < 9) {
      switch(bVar13) {
      case 0:
        if (g_lastCursorDirection != 0) {
          ResolveObjectHandle();
          g_cursorDirection = 0;
          hCursor = g_edgeCursors[0];
LAB_004bdf96:
          SetCursor(hCursor);
          iVar5 = g_clientContext;
        }
        break;
      case 1:
        if (g_lastCursorDirection != 7) {
          ResolveObjectHandle();
          g_cursorDirection = 7;
          hCursor = g_edgeCursors[7];
          goto LAB_004bdf96;
        }
        break;
      case 2:
        if (g_lastCursorDirection != 3) {
          ResolveObjectHandle();
          g_cursorDirection = 3;
          hCursor = g_edgeCursors[3];
          goto LAB_004bdf96;
        }
        break;
      case 4:
        if (g_lastCursorDirection != 1) {
          ResolveObjectHandle();
          g_cursorDirection = 1;
          hCursor = g_edgeCursors[1];
          goto LAB_004bdf96;
        }
        break;
      case 5:
        if (g_lastCursorDirection != 8) {
          ResolveObjectHandle();
          g_cursorDirection = 8;
          hCursor = g_edgeCursors[8];
          goto LAB_004bdf96;
        }
        break;
      case 6:
        if (g_lastCursorDirection != 2) {
          ResolveObjectHandle();
          g_cursorDirection = 2;
          hCursor = g_edgeCursors[2];
          goto LAB_004bdf96;
        }
        break;
      case 8:
        if (g_lastCursorDirection != 5) {
          ResolveObjectHandle();
          g_cursorDirection = 5;
          hCursor = g_edgeCursors[5];
          goto LAB_004bdf96;
        }
        break;
      case 9:
        if (g_lastCursorDirection != 6) {
          ResolveObjectHandle();
          g_cursorDirection = 6;
          hCursor = g_edgeCursors[6];
          goto LAB_004bdf96;
        }
        break;
      case 10:
        if (g_lastCursorDirection != 4) {
          ResolveObjectHandle();
          g_cursorDirection = 4;
          hCursor = g_edgeCursors[4];
          goto LAB_004bdf96;
        }
      }
    }
    iVar6 = *(int *)(&DAT_006a771c + iVar5) + iVar6;
    iVar14 = *(int *)(&DAT_006a7718 + iVar5) + local_3d4c;
    local_3d68 = (int *)(&DAT_006a7708 + iVar5);
    cVar3 = PeekPacketChecksumBool();
    iVar5 = g_clientContext;
    param_1 = local_3d58;
    if (cVar3 == '\0') {
      iVar5 = 400;
      if (399 < iVar14) {
        iVar5 = iVar14;
      }
      iVar10 = local_3d68[6] + -400;
      if ((iVar5 <= iVar10) && (iVar10 = iVar14, iVar14 < 400)) {
        iVar10 = 400;
      }
      iVar5 = -0x14;
      if (-0x15 < iVar6) {
        iVar5 = iVar6;
      }
      iVar14 = local_3d68[7] + -0x104;
      if ((iVar5 <= iVar14) && (iVar14 = iVar6, iVar6 < -0x14)) {
        iVar14 = -0x14;
      }
      local_3d68[4] = iVar10;
      local_3d68[5] = iVar14;
      iVar5 = g_clientContext;
    }
  }
  param_1[1] = param_1[1] + 1;
  param_1[3] = param_1[3] + 1;
  if ((*(char *)((int)param_1 + 0x91) != '\0') && ((char)param_1[4] == '\0')) {
    *(int *)(&DAT_006a7718 + iVar5) =
         *(int *)(&DAT_006a7718 + iVar5) + (DAT_00e536c0 * *(int *)(&DAT_005f2f44 + iVar5)) / 10;
    iVar6 = *(int *)(&DAT_006a7718 + iVar5);
    *(int *)(&DAT_006a771c + iVar5) =
         *(int *)(&DAT_006a771c + iVar5) + (DAT_00e536c4 * *(int *)(&DAT_005f2f44 + iVar5)) / 10;
    iVar14 = 400;
    if (399 < iVar6) {
      iVar14 = iVar6;
    }
    iVar10 = *(int *)(&DAT_006a7720 + iVar5) + -400;
    if ((iVar14 <= iVar10) && (iVar10 = iVar6, iVar6 < 400)) {
      iVar10 = 400;
    }
    *(int *)(&DAT_006a7718 + iVar5) = iVar10;
    iVar6 = *(int *)(&DAT_006a771c + iVar5);
    iVar14 = -0x14;
    if (-0x15 < iVar6) {
      iVar14 = iVar6;
    }
    iVar10 = *(int *)(&DAT_006a7724 + iVar5) + -0x104;
    if ((iVar14 <= iVar10) && (iVar10 = iVar6, iVar6 < -0x14)) {
      iVar10 = -0x14;
    }
    *(int *)(&DAT_006a771c + iVar5) = iVar10;
  }
  if (*(uint *)(iVar5 + 0x59154) < (uint)param_1[3]) {
    FUN_0041ee10();
  }
  pcVar16 = (code *)EnterCriticalSection;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = g_clientContext;
  pbVar17 = &DAT_006aa628 + g_clientContext;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = _rand();
  *pbVar17 = (byte)iVar5;
  iVar5 = _rand();
  bVar13 = *pbVar17;
  (&DAT_006aa629)[iVar6] = (byte)iVar5;
  local_3d68 = (int *)(bVar13 & 7);
  bVar12 = ~('\x01' << (sbyte)local_3d68) & (byte)iVar5 | '\0' << (sbyte)local_3d68;
  (&DAT_006aa629)[iVar6] = bVar12;
  (&DAT_006aa62a)[iVar6] = bVar13 + bVar12 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004507d0();
  FUN_004f3100();
  FUN_004203b0();
  iVar5 = g_clientContext;
  FUN_004068d0();
  iVar6 = *(int *)(iVar5 + 0xf0380);
  if (iVar6 != -1) {
    *(int *)(iVar5 + 0xf0380) = iVar6 + -1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (-1 < iVar6) {
    cVar3 = PeekPacketChecksumBool();
    if ((cVar3 != '\x01') || (cVar3 = PeekPacketChecksumBool(), cVar3 != '\0')) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar6 != 0xe) goto LAB_004c0ea4;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (2 < iVar6) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar6) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      EncodeOutgoingPacketField();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = g_clientContext;
    if (iVar5 == 0) {
      iVar5 = *(int *)(&DAT_006a7720 + g_clientContext);
      (&DAT_006a7734)[g_clientContext] = 1;
      (&DAT_006a7736)[iVar6] = 0;
      (&DAT_006a7f6c)[iVar6] = 0;
      *(undefined4 *)(&DAT_006a772c + iVar6) = 400;
      *(int *)(&DAT_006a7730 + iVar6) = iVar5 + -400;
      cVar3 = FUN_004cedc0();
      if (cVar3 == '\0') {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_0043bda0();
        iVar6 = 0;
        do {
          iVar5 = GetPlayerRecordBySlot();
          if ((iVar5 != 0) && (cVar3 = PeekPacketChecksumBool(), cVar3 != '\x01')) {
            FUN_0045ea40();
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < 8);
        local_3d54 = 0;
LAB_004be470:
        iVar6 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
        uVar11 = *(uint *)(iVar6 + 4);
        while (uVar11 < 0x186a7) {
          if (uVar11 == 0x186a6) {
            iVar6 = *(int *)(iVar6 + 0x10);
            uVar11 = *(uint *)(iVar6 + 8);
            if (uVar11 <= local_3d54) goto LAB_004be4b1;
            break;
          }
          iVar6 = *(int *)(iVar6 + 0x1c);
          uVar11 = *(uint *)(iVar6 + 4);
        }
        goto LAB_004be712;
      }
    }
  }
  goto LAB_004c0ea4;
  while( true ) {
    iVar6 = *(int *)(iVar6 + 0x10);
    uVar11 = *(uint *)(iVar6 + 8);
    if (local_3d54 < uVar11) break;
LAB_004be4b1:
    if (uVar11 == local_3d54) {
      FUN_00479910();
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((iVar5 == 0) ||
         (uVar11 = DAT_005b3480 * 0xda003 + 0x5703b11,
         DAT_005b3480 = DAT_005b3480 + (uVar11 * 0x61 + 0x61) % 0xf4241, (uVar11 & 1) != 0)) break;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar7 = EncodeChecksumDeltaMul(iVar6 + 0x8c8);
      local_c = 0;
      FUN_0040aea0(uVar7);
      SUBFIELD(local_c,0,undefined1) = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_c = (uint)SUBFIELD(local_c,1,undefined3) << 8;
      local_3d68 = local_3d34;
      if (local_3d34 != (int *)0x0) {
        ScrambleChecksumGuardBytes();
        TreeLowerBound();
      }
      local_c = 0xffffffff;
      local_3d68 = local_3588;
      if (local_3588 != (int *)0x0) {
        ScrambleChecksumGuardBytes();
        TreeLowerBound();
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_3d68 = (int *)PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar6 < (int)local_3d68) {
        DAT_005b3480 = DAT_005b3480 +
                       ((DAT_005b3480 * 0xda003 + 0x5703b11) * 0x61 + 0x61U) % 0xf4241;
      }
      else {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_3d68 = (int *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar6 < (int)local_3d68) {
          FUN_00415c60();
        }
        else {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar5 <= iVar6) break;
          FUN_00415c60();
        }
      }
      GetLocalizedString();
      FUN_004382d0();
      break;
    }
  }
LAB_004be712:
  local_3d54 = local_3d54 + 1;
  if (7 < (int)local_3d54) goto code_r0x004be720;
  goto LAB_004be470;
code_r0x004be720:
  if (*(int *)(g_clientContext + 0x621e0) != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (((iVar6 < 1) && (cVar3 = PeekPacketChecksumBool(), cVar3 != '\0')) &&
       (cVar3 = PeekPacketChecksumBool(), cVar3 == '\0')) {
      iVar6 = *(int *)(g_clientContext + 0x621e0);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = _rand();
      *(byte *)(iVar6 + 0x8bc0) = (byte)iVar5;
      iVar5 = _rand();
      bVar13 = *(byte *)(iVar6 + 0x8bc0);
      *(byte *)(iVar6 + 0x8bc1) = (byte)iVar5;
      bVar12 = '\x01' << (bVar13 & 7);
      bVar12 = ~bVar12 & (byte)iVar5 | bVar12;
      *(byte *)(iVar6 + 0x8bc1) = bVar12;
      *(byte *)(iVar6 + 0x8bc2) = bVar13 + bVar12 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar14 = DAT_007934e8;
      iVar5 = g_clientContext;
      *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
      *(undefined2 *)(iVar14 + 0x4d4) = 0x4100;
      *(undefined4 *)(iVar14 + 0x4d6) = *(undefined4 *)(*(int *)(iVar5 + 0x621e0) + 0xb0b0);
      iVar6 = *(int *)(iVar14 + 0x44d0);
      *(int *)(iVar14 + 0x44d0) = iVar6 + 4;
      *(undefined1 *)(iVar6 + 0x4d4 + iVar14) = *(undefined1 *)(*(int *)(iVar5 + 0x621e0) + 0xb0ac);
      *(int *)(iVar14 + 0x44d0) = *(int *)(iVar14 + 0x44d0) + 1;
      SendOutgoingPacket();
      Replay_AppendEvent();
      iVar6 = g_clientContext;
      *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) =
           *(undefined4 *)(*(int *)(g_clientContext + 0x621e0) + 0xb0b0);
      puVar19 = &DAT_00e9aad0 + g_replayEventCursor;
      g_replayEventCursor = g_replayEventCursor + 4;
      *puVar19 = *(undefined1 *)(*(int *)(iVar6 + 0x621e0) + 0xb0ac);
      g_replayEventCursor = g_replayEventCursor + 1;
      Replay_FlushEvent();
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar6 != 3) {
    local_3d54 = 0;
    pcVar16 = (code *)EnterCriticalSection;
    do {
      local_3b28 = 0;
      local_3d34 = (int *)0x0;
      EncodeOutgoingPacketField();
      uVar11 = local_3d54;
      local_c = 2;
      local_3d4c = GetPlayerRecordBySlot();
      iVar6 = g_clientContext;
      if (*(int *)(g_clientContext + 0x5b81c + uVar11 * 4) != 0) {
        *(undefined4 *)(g_clientContext + 0x5b83c + uVar11 * 4) = 0;
      }
      (*pcVar16)();
      if ((char)((&DAT_0067e3cc)[iVar6] + (&DAT_0067e3cd)[iVar6] + -0x34) == (&DAT_0067e3ce)[iVar6])
      {
        uStack_3d70 = (int *)CONCAT13(((byte)(&DAT_0067e3cd)[iVar6] >> ((&DAT_0067e3cc)[iVar6] & 7)
                                      & 1) == 1,(undefined3)uStack_3d70);
      }
      else {
        g_valueGuardTamperFlag = 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uStack_3d70 = (int *)((uint)uStack_3d70 & 0xffffff);
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (SUBFIELD(uStack_3d70,3,undefined1) == '\0') {
        (*pcVar16)();
        PeekPacketChecksumState();
        EncodeOutgoingPacketField();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      local_3d54 = uVar11 * 0x224;
      (*pcVar16)();
      iVar6 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(iVar6 + (int)uStack_3d70);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = g_clientContext;
      piVar15 = local_3d60;
      if (0 < *(int *)(g_clientContext + 0x5b81c + uVar11 * 4)) {
        pbVar17 = &DAT_0067e3cc + g_clientContext;
        (*pcVar16)(&DAT_005a9068);
        bVar13 = *pbVar17;
        bVar12 = (&DAT_0067e3cd)[iVar6];
        bVar18 = (byte)(bVar13 + bVar12 + -0x34) != (&DAT_0067e3ce)[iVar6];
        if (bVar18) {
          g_valueGuardTamperFlag = 1;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        piVar15 = piStack_3d64;
        iVar6 = g_clientContext;
        if (bVar18 || (bVar12 >> (bVar13 & 7) & 1) != 1) {
          piStack_3d64[(int)local_3d60 + 0x435] =
               piStack_3d64[(int)local_3d60 + 0x435] +
               *(int *)(g_clientContext + 0x5b81c + (int)local_3d60 * 4);
          iVar5 = *(int *)(iVar6 + 0x5b81c + (int)local_3d60 * 4);
          if (piStack_3d64[(int)local_3d60 + 0x43d] < iVar5) {
            piStack_3d64[(int)local_3d60 + 0x43d] = iVar5;
          }
          piStack_3d64[(int)local_3d60 + 0x445] = piStack_3d64[(int)local_3d60 + 0x445] + 1;
        }
        (*pcVar16)(&DAT_005a9068);
        if ((char)((&DAT_0067e3cc)[iVar6] + (&DAT_0067e3cd)[iVar6] + -0x34) ==
            (&DAT_0067e3ce)[iVar6]) {
          unaff_ESI = CONCAT13(((byte)(&DAT_0067e3cd)[iVar6] >> ((&DAT_0067e3cc)[iVar6] & 7) & 1) ==
                               1,(int3)unaff_ESI);
        }
        else {
          g_valueGuardTamperFlag = 1;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          unaff_ESI = unaff_ESI & 0xffffff;
        }
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if ((char)(unaff_ESI >> 0x18) == '\0') {
          (*pcVar16)(&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(iVar6 + 1);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        (*pcVar16)(&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        unaff_EDI = (int *)CONCAT13(0x50 < iVar6,(int3)unaff_EDI);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (0x50 < iVar6) {
          (*pcVar16)(&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (*(int *)(g_clientContext + 0x5b81c + (int)local_3d68 * 4) < iVar6) goto LAB_004bedb3;
          (*pcVar16)(&DAT_005a9068);
          EncodeOutgoingPacketField(0x1e);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          (*pcVar16)(&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          (*pcVar16)(&DAT_005a9068);
          iVar5 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar7 = EncodeChecksumDeltaMul(&local_3d68,auStack_6a4,iVar5 + iVar6);
          uStack_2c = 3;
          (*pcVar16)(&DAT_005a9068);
          uVar8 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeChecksumDeltaDiv(uVar7,auStack_35c0,uVar8);
          uStack_30 = 4;
          (*pcVar16)(&DAT_005a9068);
          uVar7 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(uVar7);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uStack_34 = 3;
          if (iStack_35b0 != 0) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(&stack0xffffc278);
            piVar15 = unaff_EDI;
          }
          uStack_34 = 2;
          if (iStack_698 != 0) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(&stack0xffffc278);
            piVar15 = unaff_EDI;
          }
          (*pcVar16)(&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          iVar5 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(iVar5 + iVar6);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          (*pcVar16)(&DAT_005a9068);
          uVar7 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = unaff_ESI + 0xae15;
          pcVar9 = (char *)GetLocalizedString(&g_localizedStringTable,0x268);
          _sprintf(acStack_37d0,pcVar9,iVar6,uVar7);
          pcVar9 = acStack_37d0;
LAB_004beff9:
          (**(code **)(*piVar15 + 0x28))(pcVar9,4,3);
        }
        else {
LAB_004bedb3:
          (*pcVar16)(&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          unaff_EBX = (int *)CONCAT13(0x32 < iVar6,(int3)unaff_EBX);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (0x32 < iVar6) {
            (*pcVar16)(&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar6 <= *(int *)(g_clientContext + 0x5b81c + (int)piStack_3d5c * 4)) {
              (*pcVar16)(&DAT_005a9068);
              EncodeOutgoingPacketField(0xf);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              (*pcVar16)(&DAT_005a9068);
              iVar6 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uStack_3d78 = (int *)((int)piStack_3d64 * 0x1120 + 0x5113c + g_clientContext);
              (*pcVar16)(&DAT_005a9068);
              unaff_ESI = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar7 = EncodeChecksumDeltaMul(&piStack_3d5c,auStack_250,unaff_ESI + iVar6);
              uStack_20 = CONCAT31(SUBFIELD(uStack_20,1,undefined3),5);
              (*pcVar16)(&DAT_005a9068);
              unaff_EDI = (int *)PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              EncodeChecksumDeltaDiv(uVar7,auStack_2f48,unaff_EDI);
              uStack_24 = CONCAT31(SUBFIELD(uStack_24,1,undefined3),6);
              (*pcVar16)(&DAT_005a9068);
              uVar7 = PeekPacketChecksumState();
              EncodeOutgoingPacketField(uVar7);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uStack_28 = 5;
              if (iStack_2f38 != 0) {
                ScrambleChecksumGuardBytes();
                TreeLowerBound(&stack0xffffc284);
                piVar15 = unaff_EBX;
              }
              uStack_28 = 2;
              if (iStack_244 != 0) {
                ScrambleChecksumGuardBytes();
                TreeLowerBound(&stack0xffffc284);
                piVar15 = unaff_EBX;
              }
              (*pcVar16)(&DAT_005a9068);
              iVar6 = PeekPacketChecksumState();
              iVar5 = PeekPacketChecksumState();
              EncodeOutgoingPacketField(iVar5 + iVar6);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              (*pcVar16)(&DAT_005a9068);
              uVar7 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar6 = unaff_ESI + 0xae15;
              pcVar9 = (char *)GetLocalizedString(&g_localizedStringTable,0x269);
              _sprintf(acStack_3a50,pcVar9,iVar6,uVar7);
              pcVar9 = acStack_3a50;
              goto LAB_004beff9;
            }
          }
        }
        cVar3 = CheckGuardedBoolAnd(0x31 < *(int *)(g_clientContext + 0x5b81c + (int)piStack_3d5c * 4));
        if (cVar3 != '\0') {
          (*pcVar16)(&DAT_005a9068);
          EncodeOutgoingPacketField(0x14);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          (*pcVar16)(&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uStack_3d78 = (int *)((int)piStack_3d64 * 0x1120 + 0x5113c + g_clientContext);
          (*pcVar16)(&DAT_005a9068);
          unaff_ESI = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar7 = EncodeChecksumDeltaMul(&piStack_3d5c,auStack_1594,unaff_ESI + iVar6);
          uStack_20 = CONCAT31(SUBFIELD(uStack_20,1,undefined3),7);
          (*pcVar16)(&DAT_005a9068);
          unaff_EDI = (int *)PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeChecksumDeltaDiv(uVar7,auStack_2b00,unaff_EDI);
          uStack_24 = CONCAT31(SUBFIELD(uStack_24,1,undefined3),8);
          (*pcVar16)(&DAT_005a9068);
          uVar7 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(uVar7);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uStack_28 = 7;
          if (iStack_2af0 != 0) {
            iVar6 = iStack_2af0 << 4;
            iVar5 = 0x10;
            do {
              iVar14 = _rand();
              *(char *)(iVar6 + DAT_0079376c) = (char)iVar14;
              iVar6 = iVar6 + 1;
              iVar5 = iVar5 + -1;
            } while (iVar5 != 0);
            TreeLowerBound(&stack0xffffc284);
            piVar15 = unaff_EBX;
          }
          uStack_28 = 2;
          if (iStack_1588 != 0) {
            iVar6 = iStack_1588 << 4;
            iVar5 = 0x10;
            do {
              iVar14 = _rand();
              *(char *)(iVar6 + DAT_0079376c) = (char)iVar14;
              iVar6 = iVar6 + 1;
              iVar5 = iVar5 + -1;
            } while (iVar5 != 0);
            TreeLowerBound(&stack0xffffc284);
            piVar15 = unaff_EBX;
          }
          (*pcVar16)(&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          iVar5 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(iVar5 + iVar6);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          (*pcVar16)(&DAT_005a9068);
          uVar7 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = (int)uStack_3d70 + 0xae15;
          pcVar9 = (char *)GetLocalizedString(&g_localizedStringTable,0x26a);
          _sprintf(acStack_3944,pcVar9,iVar6,uVar7);
          (**(code **)(*piVar15 + 0x28))(acStack_3944,4,3);
        }
        cVar3 = DecodeGuardedBool();
        if ((cVar3 != '\0') && (cVar3 = PeekPacketChecksumBool(), cVar3 != '\0')) {
          (*pcVar16)(&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar6 <= *(int *)(g_clientContext + 0x5b81c + (int)piStack_3d5c * 4)) {
            (*pcVar16)(&DAT_005a9068);
            EncodeOutgoingPacketField(0x14);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            (*pcVar16)(&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            uStack_3d78 = (int *)((int)piStack_3d64 * 0x1120 + 0x5113c + g_clientContext);
            (*pcVar16)(&DAT_005a9068);
            unaff_ESI = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            uVar7 = EncodeChecksumDeltaMul(&piStack_3d5c,auStack_474,unaff_ESI + iVar6);
            uStack_20 = CONCAT31(SUBFIELD(uStack_20,1,undefined3),9);
            (*pcVar16)(&DAT_005a9068);
            unaff_EDI = (int *)PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeChecksumDeltaDiv(uVar7,auStack_26b8,unaff_EDI);
            uStack_24 = CONCAT31(SUBFIELD(uStack_24,1,undefined3),10);
            (*pcVar16)(&DAT_005a9068);
            uVar7 = PeekPacketChecksumState();
            EncodeOutgoingPacketField(uVar7);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            uStack_28 = 9;
            if (iStack_26a8 != 0) {
              ScrambleChecksumGuardBytes();
              TreeLowerBound(&stack0xffffc284);
              piVar15 = unaff_EBX;
            }
            uStack_28 = 2;
            if (iStack_468 != 0) {
              ScrambleChecksumGuardBytes();
              TreeLowerBound(&stack0xffffc284);
              piVar15 = unaff_EBX;
            }
            (*pcVar16)(&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            iVar5 = PeekPacketChecksumState();
            EncodeOutgoingPacketField(iVar5 + iVar6);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            (*pcVar16)(&DAT_005a9068);
            uVar7 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = (int)uStack_3d70 + 0xae15;
            pcVar9 = (char *)GetLocalizedString(&g_localizedStringTable,0x26b);
            _sprintf(acStack_3644,pcVar9,iVar6,uVar7);
            (**(code **)(*piVar15 + 0x28))(acStack_3644,4,3);
          }
        }
        cVar3 = CheckGuardedBoolAnd(0x31 < *(int *)(g_clientContext + 0x5b81c + (int)piStack_3d5c * 4));
        if (cVar3 != '\0') {
          (*pcVar16)(&DAT_005a9068);
          EncodeOutgoingPacketField(0x19);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          (*pcVar16)(&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uStack_3d78 = (int *)((int)piStack_3d64 * 0x1120 + 0x5113c + g_clientContext);
          (*pcVar16)(&DAT_005a9068);
          unaff_ESI = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar7 = EncodeChecksumDeltaMul(&piStack_3d5c,auStack_114c,unaff_ESI + iVar6);
          uStack_20 = CONCAT31(SUBFIELD(uStack_20,1,undefined3),0xb);
          (*pcVar16)(&DAT_005a9068);
          unaff_EDI = (int *)PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeChecksumDeltaDiv(uVar7,auStack_2270,unaff_EDI);
          uStack_24 = CONCAT31(SUBFIELD(uStack_24,1,undefined3),0xc);
          (*pcVar16)(&DAT_005a9068);
          uVar7 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(uVar7);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uStack_28 = 0xb;
          if (iStack_2260 != 0) {
            iVar6 = iStack_2260 << 4;
            iVar5 = 0x10;
            do {
              iVar14 = _rand();
              *(char *)(iVar6 + DAT_0079376c) = (char)iVar14;
              iVar6 = iVar6 + 1;
              iVar5 = iVar5 + -1;
            } while (iVar5 != 0);
            TreeLowerBound(&stack0xffffc284);
            piVar15 = unaff_EBX;
          }
          uStack_28 = 2;
          if (iStack_1140 != 0) {
            iVar6 = iStack_1140 << 4;
            iVar5 = 0x10;
            do {
              iVar14 = _rand();
              *(char *)(iVar6 + DAT_0079376c) = (char)iVar14;
              iVar6 = iVar6 + 1;
              iVar5 = iVar5 + -1;
            } while (iVar5 != 0);
            TreeLowerBound(&stack0xffffc284);
            piVar15 = unaff_EBX;
          }
          (*pcVar16)(&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          iVar5 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(iVar5 + iVar6);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          (*pcVar16)(&DAT_005a9068);
          uVar7 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = (int)uStack_3d70 + 0xae15;
          pcVar9 = (char *)GetLocalizedString(&g_localizedStringTable,0x26c);
          _sprintf(acStack_3844,pcVar9,iVar6,uVar7);
          (**(code **)(*piVar15 + 0x28))(acStack_3844,4,3);
        }
      }
      if (0x32 < *(int *)(g_clientContext + 0x5b83c + (int)piStack_3d5c * 4)) {
        (*pcVar16)(&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(iVar6 + -1);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        (*pcVar16)(&DAT_005a9068);
        EncodeOutgoingPacketField(0xffffffe7);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        puVar19 = &DAT_005a9068;
        (*pcVar16)(&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        unaff_ESI = (int)local_3d68 * 0x1120 + 0x5113c + g_clientContext;
        (*pcVar16)(&DAT_005a9068);
        unaff_EDI = (int *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar7 = EncodeChecksumDeltaMul(&local_3d60,auStack_8c0,(int)unaff_EDI + iVar6);
        uStack_24 = CONCAT31(SUBFIELD(uStack_24,1,undefined3),0xd);
        (*pcVar16)(&DAT_005a9068);
        uVar8 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeChecksumDeltaDiv(uVar7,auStack_1e2c,uVar8);
        uStack_28 = 0xe;
        (*pcVar16)(&DAT_005a9068);
        uVar7 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(uVar7);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uStack_2c = 0xd;
        if (iStack_1e1c != 0) {
          iVar6 = iStack_1e1c << 4;
          iVar5 = 0x10;
          do {
            iVar14 = _rand();
            *(char *)(iVar6 + DAT_0079376c) = (char)iVar14;
            iVar6 = iVar6 + 1;
            iVar5 = iVar5 + -1;
          } while (iVar5 != 0);
          TreeLowerBound(&stack0xffffc280);
          piVar15 = uStack_3d78;
        }
        uStack_2c = 2;
        if (iStack_8b4 != 0) {
          iVar6 = iStack_8b4 << 4;
          iVar5 = 0x10;
          do {
            iVar14 = _rand();
            *(char *)(iVar6 + DAT_0079376c) = (char)iVar14;
            iVar6 = iVar6 + 1;
            iVar5 = iVar5 + -1;
          } while (iVar5 != 0);
          TreeLowerBound(&stack0xffffc280);
          piVar15 = uStack_3d78;
        }
        (*pcVar16)(&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        iVar5 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(iVar5 + iVar6);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        (*pcVar16)(&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        (*pcVar16)(&DAT_005a9068);
        uVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_004368f0(uVar7,puVar19,0xffffffff);
        (*pcVar16)(&DAT_005a9068);
        uVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = (int)unaff_EBX + 0xae15;
        pcVar9 = (char *)GetLocalizedString(&g_localizedStringTable,0x26d);
        _sprintf(acStack_36d0,pcVar9,iVar6,uVar7);
        (**(code **)(*piVar15 + 0x28))(acStack_36d0,3,2);
      }
      iVar6 = *(int *)(g_clientContext + 0x5b81c + (int)piStack_3d5c * 4);
      if (iVar6 < 500) {
        if (0xf9 < iVar6) {
          (*pcVar16)(&DAT_005a9068);
          EncodeOutgoingPacketField(0x14);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          (*pcVar16)(&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uStack_3d70 = (int *)((int)piStack_3d64 * 0x1120 + 0x5113c + g_clientContext);
          (*pcVar16)(&DAT_005a9068);
          unaff_EBX = (int *)PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar7 = EncodeChecksumDeltaMul(&piStack_3d5c,auStack_28d8,(int)unaff_EBX + iVar6);
          uStack_20 = CONCAT31(SUBFIELD(uStack_20,1,undefined3),0x11);
          (*pcVar16)(&DAT_005a9068);
          uStack_3d78 = (int *)PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeChecksumDeltaDiv(uVar7,auStack_2d24,uStack_3d78);
          uStack_24 = CONCAT31(SUBFIELD(uStack_24,1,undefined3),0x12);
          (*pcVar16)(&DAT_005a9068);
          uVar7 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(uVar7);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uStack_28 = 0x11;
          if (iStack_2d14 != 0) {
            iVar6 = iStack_2d14 << 4;
            iVar5 = 0x10;
            do {
              iVar14 = _rand();
              *(char *)(iVar6 + DAT_0079376c) = (char)iVar14;
              iVar6 = iVar6 + 1;
              iVar5 = iVar5 + -1;
            } while (iVar5 != 0);
            TreeLowerBound(&stack0xffffc27c);
            piVar15 = unaff_EBX;
          }
          unaff_ESI = uStack_28cc;
          uStack_28 = 2;
          if (uStack_28cc != 0) {
            iVar6 = uStack_28cc << 4;
            iVar5 = 0x10;
            do {
              iVar14 = _rand();
              *(char *)(iVar6 + DAT_0079376c) = (char)iVar14;
              iVar6 = iVar6 + 1;
              iVar5 = iVar5 + -1;
            } while (iVar5 != 0);
            TreeLowerBound(&stack0xffffc27c);
            piVar15 = unaff_EBX;
          }
          (*pcVar16)(&DAT_005a9068);
          unaff_EDI = (int *)PeekPacketChecksumState();
          iVar6 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(iVar6 + (int)unaff_EDI);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          (*pcVar16)(&DAT_005a9068);
          uVar7 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = (int)uStack_3d70 + 0xae15;
          pcVar9 = (char *)GetLocalizedString(&g_localizedStringTable,0x26f);
          _sprintf(acStack_39c4,pcVar9,iVar6,uVar7);
          pcVar9 = acStack_39c4;
          goto LAB_004c008f;
        }
        if (0x95 < iVar6) {
          (*pcVar16)(&DAT_005a9068);
          EncodeOutgoingPacketField(10);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          (*pcVar16)(&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uStack_3d70 = (int *)((int)piStack_3d64 * 0x1120 + 0x5113c + g_clientContext);
          (*pcVar16)(&DAT_005a9068);
          unaff_EBX = (int *)PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar7 = EncodeChecksumDeltaMul(&piStack_3d5c,auStack_2048,(int)unaff_EBX + iVar6);
          uStack_20 = CONCAT31(SUBFIELD(uStack_20,1,undefined3),0x13);
          (*pcVar16)(&DAT_005a9068);
          uStack_3d78 = (int *)PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeChecksumDeltaDiv(uVar7,auStack_2494,uStack_3d78);
          uStack_24 = CONCAT31(SUBFIELD(uStack_24,1,undefined3),0x14);
          (*pcVar16)(&DAT_005a9068);
          uVar7 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(uVar7);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar11 = uStack_2484;
          uStack_28 = 0x13;
          if (uStack_2484 != 0) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(&stack0xffffc27c);
            piVar15 = unaff_EBX;
            unaff_ESI = uVar11;
          }
          uVar11 = uStack_203c;
          uStack_28 = 2;
          if (uStack_203c != 0) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(&stack0xffffc27c);
            piVar15 = unaff_EBX;
            unaff_ESI = uVar11;
          }
          (*pcVar16)(&DAT_005a9068);
          unaff_EDI = (int *)PeekPacketChecksumState();
          iVar6 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(iVar6 + (int)unaff_EDI);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          (*pcVar16)(&DAT_005a9068);
          uVar7 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = (int)uStack_3d70 + 0xae15;
          pcVar9 = (char *)GetLocalizedString(&g_localizedStringTable,0x270);
          _sprintf(acStack_38c4,pcVar9,iVar6,uVar7);
          pcVar9 = acStack_38c4;
          goto LAB_004c008f;
        }
      }
      else {
        (*pcVar16)(&DAT_005a9068);
        EncodeOutgoingPacketField(0x32);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        (*pcVar16)(&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uStack_3d70 = (int *)((int)piStack_3d64 * 0x1120 + 0x5113c + g_clientContext);
        (*pcVar16)(&DAT_005a9068);
        unaff_EBX = (int *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar7 = EncodeChecksumDeltaMul(&piStack_3d5c,auStack_d04,(int)unaff_EBX + iVar6);
        uStack_20 = CONCAT31(SUBFIELD(uStack_20,1,undefined3),0xf);
        (*pcVar16)(&DAT_005a9068);
        uStack_3d78 = (int *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeChecksumDeltaDiv(uVar7,auStack_19e0,uStack_3d78);
        uStack_24 = CONCAT31(SUBFIELD(uStack_24,1,undefined3),0x10);
        (*pcVar16)(&DAT_005a9068);
        uVar7 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(uVar7);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uStack_28 = 0xf;
        if (iStack_19d0 != 0) {
          iVar6 = iStack_19d0 << 4;
          iVar5 = 0x10;
          do {
            iVar14 = _rand();
            *(char *)(iVar6 + DAT_0079376c) = (char)iVar14;
            iVar6 = iVar6 + 1;
            iVar5 = iVar5 + -1;
          } while (iVar5 != 0);
          TreeLowerBound(&stack0xffffc27c);
          piVar15 = unaff_EBX;
        }
        unaff_ESI = uStack_cf8;
        uStack_28 = 2;
        if (uStack_cf8 != 0) {
          iVar6 = uStack_cf8 << 4;
          iVar5 = 0x10;
          do {
            iVar14 = _rand();
            *(char *)(iVar6 + DAT_0079376c) = (char)iVar14;
            iVar6 = iVar6 + 1;
            iVar5 = iVar5 + -1;
          } while (iVar5 != 0);
          TreeLowerBound(&stack0xffffc27c);
          piVar15 = unaff_EBX;
        }
        (*pcVar16)(&DAT_005a9068);
        unaff_EDI = (int *)PeekPacketChecksumState();
        iVar6 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(iVar6 + (int)unaff_EDI);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        (*pcVar16)(&DAT_005a9068);
        uVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = (int)uStack_3d70 + 0xae15;
        pcVar9 = (char *)GetLocalizedString(&g_localizedStringTable,0x26e);
        _sprintf(acStack_3744,pcVar9,iVar6,uVar7);
        pcVar9 = acStack_3744;
LAB_004c008f:
        (**(code **)(*piVar15 + 0x28))(pcVar9,4,3);
      }
      EncodeChecksumDeltaMul((int)local_3d58 + g_clientContext + 0x5ff00,auStack_1bf4,1000);
      uStack_14 = CONCAT31(SUBFIELD(uStack_14,1,undefined3),0x15);
      local_3d68 = (int *)((int)local_3d58 + g_clientContext + 0x5ede0);
      (*pcVar16)(&DAT_005a9068);
      local_3d60 = (int *)PeekPacketChecksumState();
      iVar6 = PeekPacketChecksumState();
      bVar18 = iVar6 < (int)local_3d60;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      piVar2 = piStack_1bd8;
      local_c = CONCAT31(SUBFIELD(local_c,1,undefined3),2);
      if (piStack_1bd8 != (int *)0x0) {
        iVar6 = (int)piStack_1bd8 << 4;
        local_3d68 = (int *)0x10;
        do {
          iVar5 = _rand();
          *(char *)(iVar6 + DAT_0079376c) = (char)iVar5;
          iVar6 = iVar6 + 1;
          local_3d68 = (int *)((int)local_3d68 + -1);
        } while (local_3d68 != (int *)0x0);
        local_3d60 = piVar2;
        TreeLowerBound();
        piVar15 = local_3d58;
      }
      if (bVar18) {
        (*pcVar16)();
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar6 == 1) {
          puVar19 = &DAT_005a9068;
          (*pcVar16)();
          iVar6 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(iVar6 + 1);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          (*pcVar16)(&DAT_005a9068);
          EncodeOutgoingPacketField(100);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          (*pcVar16)(&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uStack_3d70 = (int *)((int)piStack_3d64 * 0x1120 + 0x5113c + g_clientContext);
          (*pcVar16)(&DAT_005a9068);
          unaff_EBX = (int *)PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar7 = EncodeChecksumDeltaMul(&piStack_3d5c,auStack_338c,(int)unaff_EBX + iVar6);
          uStack_20 = CONCAT31(SUBFIELD(uStack_20,1,undefined3),0x16);
          (*pcVar16)(&DAT_005a9068);
          uStack_3d78 = (int *)PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeChecksumDeltaDiv(uVar7,auStack_316c,uStack_3d78);
          uStack_24 = CONCAT31(SUBFIELD(uStack_24,1,undefined3),0x17);
          (*pcVar16)(&DAT_005a9068);
          uVar7 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(uVar7);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar11 = uStack_315c;
          uStack_28 = 0x16;
          if (uStack_315c != 0) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(&stack0xffffc27c);
            piVar15 = unaff_EBX;
            unaff_ESI = uVar11;
          }
          uVar11 = uStack_3380;
          uStack_28 = 2;
          if (uStack_3380 != 0) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(&stack0xffffc27c);
            piVar15 = unaff_EBX;
            unaff_ESI = uVar11;
          }
          (*pcVar16)(&DAT_005a9068);
          unaff_EDI = (int *)PeekPacketChecksumState();
          iVar6 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(iVar6 + (int)unaff_EDI);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          (*pcVar16)(&DAT_005a9068);
          PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          (*pcVar16)(&DAT_005a9068);
          uVar7 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_004368f0(uVar7,puVar19,1);
          (*pcVar16)(&DAT_005a9068);
          uVar7 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar8 = 0x271;
LAB_004c08c8:
          iVar6 = (int)uStack_3d70 + 0xae15;
          pcVar9 = (char *)GetLocalizedString(&g_localizedStringTable,uVar8);
          _sprintf(acStack_3b4c,pcVar9,iVar6,uVar7);
          (**(code **)(*piVar15 + 0x28))(acStack_3b4c,4,3);
        }
        else {
          if (iVar6 == 2) {
            puVar19 = &DAT_005a9068;
            (*pcVar16)();
            iVar6 = PeekPacketChecksumState();
            EncodeOutgoingPacketField(iVar6 + 2);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            (*pcVar16)(&DAT_005a9068);
            EncodeOutgoingPacketField(100);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            (*pcVar16)(&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            uStack_3d70 = (int *)((int)piStack_3d64 * 0x1120 + 0x5113c + g_clientContext);
            (*pcVar16)(&DAT_005a9068);
            unaff_EBX = (int *)PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            uVar7 = EncodeChecksumDeltaMul(&piStack_3d5c,auStack_ae0,(int)unaff_EBX + iVar6);
            uStack_20 = CONCAT31(SUBFIELD(uStack_20,1,undefined3),0x18);
            (*pcVar16)(&DAT_005a9068);
            uStack_3d78 = (int *)PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeChecksumDeltaDiv(uVar7,auStack_f2c,uStack_3d78);
            uStack_24 = CONCAT31(SUBFIELD(uStack_24,1,undefined3),0x19);
            (*pcVar16)(&DAT_005a9068);
            uVar7 = PeekPacketChecksumState();
            EncodeOutgoingPacketField(uVar7);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            uVar11 = uStack_f1c;
            uStack_28 = 0x18;
            if (uStack_f1c != 0) {
              ScrambleChecksumGuardBytes();
              TreeLowerBound(&stack0xffffc27c);
              piVar15 = unaff_EBX;
              unaff_ESI = uVar11;
            }
            uVar11 = uStack_ad4;
            uStack_28 = 2;
            if (uStack_ad4 != 0) {
              ScrambleChecksumGuardBytes();
              TreeLowerBound(&stack0xffffc27c);
              piVar15 = unaff_EBX;
              unaff_ESI = uVar11;
            }
            (*pcVar16)(&DAT_005a9068);
            unaff_EDI = (int *)PeekPacketChecksumState();
            iVar6 = PeekPacketChecksumState();
            EncodeOutgoingPacketField(iVar6 + (int)unaff_EDI);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            (*pcVar16)(&DAT_005a9068);
            PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            (*pcVar16)(&DAT_005a9068);
            uVar7 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            FUN_004368f0(uVar7,puVar19,2);
            (*pcVar16)(&DAT_005a9068);
            uVar7 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            uVar8 = 0x272;
            goto LAB_004c08c8;
          }
          if (iVar6 == 3) {
            (*pcVar16)();
            iVar6 = PeekPacketChecksumState();
            EncodeOutgoingPacketField(iVar6 + 4);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            (*pcVar16)(&DAT_005a9068);
            EncodeOutgoingPacketField(100);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            (*pcVar16)(&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            (*pcVar16)(&DAT_005a9068);
            iVar5 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            uVar7 = EncodeChecksumDeltaMul(&piStack_3d5c,auStack_1370,iVar5 + iVar6);
            uStack_20 = CONCAT31(SUBFIELD(uStack_20,1,undefined3),0x1a);
            (*pcVar16)(&DAT_005a9068);
            uVar8 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeChecksumDeltaDiv(uVar7,auStack_17bc,uVar8);
            uStack_24 = CONCAT31(SUBFIELD(uStack_24,1,undefined3),0x1b);
            (*pcVar16)(&DAT_005a9068);
            uVar7 = PeekPacketChecksumState();
            EncodeOutgoingPacketField(uVar7);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            uStack_28 = 0x1a;
            if (iStack_17ac != 0) {
              ScrambleChecksumGuardBytes();
              TreeLowerBound(&stack0xffffc27c);
            }
            uStack_28 = 2;
            if (iStack_1364 != 0) {
              ScrambleChecksumGuardBytes();
              TreeLowerBound(&stack0xffffc27c);
            }
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            iVar5 = PeekPacketChecksumState();
            EncodeOutgoingPacketField(iVar5 + iVar6);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            piVar15 = local_3d68;
            uVar7 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            unaff_ESI = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            FUN_004368f0(unaff_ESI,uVar7,4);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            uVar7 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = (int)piVar15 + 0xae15;
            pcVar9 = (char *)GetLocalizedString(&g_localizedStringTable,0x273);
            _sprintf(acStack_3b3c,pcVar9,iVar6,uVar7);
            (**(code **)(*unaff_EBX + 0x28))(acStack_3b3c,4,3);
            FUN_00438360();
            pcVar16 = (code *)EnterCriticalSection;
          }
        }
        (*pcVar16)();
        PeekPacketChecksumState();
        EncodeOutgoingPacketField();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      local_c = 0xffffffff;
      if (local_3d34 != (int *)0x0) {
        iVar5 = (int)local_3d34 << 4;
        iVar6 = 0x10;
        do {
          iVar14 = _rand();
          *(char *)(iVar5 + DAT_0079376c) = (char)iVar14;
          iVar5 = iVar5 + 1;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
        local_3d60 = local_3d34;
        TreeLowerBound();
      }
      local_3d54 = local_3d54 + 1;
    } while ((int)local_3d54 < 8);
  }
  Replay_AppendEvent();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = g_clientContext;
  *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
  g_replayEventCursor = g_replayEventCursor + 4;
  uVar7 = (**(code **)(**(int **)(iVar6 + 0x621e0) + 0x14))();
  *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
  g_replayEventCursor = g_replayEventCursor + 4;
  Replay_FlushEvent();
  local_3d60 = (int *)0xc303;
  FUN_004e8a70();
  if (local_3d68 != DAT_00e9af14) {
    FUN_004e87b0(&DAT_00e9af10);
  }
  if (DAT_0056dbe8 == -1) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    iVar14 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = g_clientContext;
    if (iVar5 == iVar14) {
      *(undefined4 *)(&DAT_006aaafc + g_clientContext) = 0;
      *(undefined4 *)(&DAT_006a76e0 + iVar6) = 0;
      *(undefined4 *)(&DAT_006a76e4 + iVar6) = 0;
      uVar11 = *(uint *)(&DAT_006a76f8 + iVar6);
      iVar5 = iVar6;
      if ((*(uint *)(&DAT_006a76fc + iVar6) <= uVar11) &&
         (cVar3 = AtlArray_GrowBuffer(), iVar5 = g_clientContext, cVar3 == '\0')) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException();
      }
      puVar1 = (undefined4 *)(*(int *)(&DAT_006a76f4 + iVar6) + uVar11 * 4);
      if (puVar1 != (undefined4 *)0x0) {
        *puVar1 = 0xe;
      }
      *(int *)(&DAT_006a76f8 + iVar6) = *(int *)(&DAT_006a76f8 + iVar6) + 1;
      (&DAT_006aa624)[iVar5] = 0xe;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      (&DAT_006a76e0)[iVar5 + iVar6] = 1;
      local_3d60 = (int *)0xc302;
      FUN_004e8a70();
      if (local_3d68 != DAT_00e9af14) {
        FUN_004e87b0(&DAT_00e9af10);
      }
      uVar7 = FUN_0045d360();
      *(undefined4 *)(&DAT_006aab04 + g_clientContext) = uVar7;
      FUN_00423a20();
    }
    else {
      Replay_AppendEvent();
      (&g_replayEventBuffer)[g_replayEventCursor] = 0xe;
      g_replayEventCursor = g_replayEventCursor + 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar7 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
      g_replayEventCursor = g_replayEventCursor + 4;
      uVar7 = FUN_0045d360();
      *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
      g_replayEventCursor = g_replayEventCursor + 4;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar7 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      *(undefined4 *)(&DAT_006a7704 + g_clientContext) = uVar7;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_004e7140();
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = _rand();
    piVar15 = local_3d58;
    *(char *)((int)local_3d58 + 0x2401) = (char)iVar6;
    iVar6 = _rand();
    *(byte *)((int)piVar15 + 0x2402) = (byte)iVar6;
    bVar13 = '\x01' << (*(byte *)((int)piVar15 + 0x2401) & 7);
    bVar13 = ~bVar13 & (byte)iVar6 | bVar13;
    *(byte *)((int)piVar15 + 0x2402) = bVar13;
    *(byte *)((int)piVar15 + 0x2403) = bVar13 + *(byte *)((int)piVar15 + 0x2401) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    pcVar16 = (code *)EnterCriticalSection;
  }
  else {
    FUN_0043a5f0();
    FUN_004d0e90();
    local_3d60 = (int *)0xc300;
    FUN_004e8a70();
    if (local_3d68 != DAT_00e9af14) {
      FUN_004e87b0(&DAT_00e9af10);
    }
    local_3d60 = (int *)0xc306;
    FUN_004e8a70();
    if (local_3d68 != DAT_00e9af14) {
      FUN_004e87b0(&DAT_00e9af10);
    }
    local_3d60 = (int *)0xc40b;
    FUN_004e8a70();
    if (local_3d68 != DAT_00e9af14) {
      FUN_004e87b0(&DAT_00e9af10);
    }
    local_3d60 = (int *)0x8005;
    FUN_004e86f0();
    local_3d60 = (int *)0x8006;
    FUN_004e86f0();
    local_3d60 = (int *)0xc306;
    FUN_004e86f0();
    local_3d60 = (int *)0xc400;
    FUN_004e86f0();
    local_3d60 = (int *)0xc401;
    FUN_004e86f0();
    local_3d60 = (int *)0x8403;
    FUN_004e86f0();
    local_3d60 = (int *)0x8405;
    FUN_004e86f0();
    local_3d60 = (int *)0xc409;
    FUN_004e86f0();
    DAT_0056dbe8 = -1;
    FUN_004cb280();
    pcVar16 = (code *)EnterCriticalSection;
  }
LAB_004c0ea4:
  (*pcVar16)();
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar6 < 1) {
LAB_004c0f5c:
    if (0 < piStack_3d5c[0x42d]) {
      (*pcVar16)();
      iVar6 = PeekPacketChecksumState();
      uStack_3d70 = (int *)CONCAT13(iVar6 == -1,(undefined3)uStack_3d70);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar6 == -1) {
        piVar15 = piStack_3d5c + 0x42d;
        *piVar15 = *piVar15 + -1;
        if (*piVar15 == 0) {
          piStack_3d5c[0x42d] = -1;
          FUN_004cf310();
        }
      }
    }
  }
  else if (0 < piStack_3d5c[0x42d]) {
    piStack_3d5c[0x42d] = -1;
    (*pcVar16)();
    iVar6 = _rand();
    *(char *)((int)piStack_3d5c + 0x23d1) = (char)iVar6;
    iVar6 = _rand();
    *(byte *)((int)piStack_3d5c + 0x23d2) = (byte)iVar6;
    bVar13 = '\x01' << (*(byte *)((int)piStack_3d5c + 0x23d1) & 7);
    bVar13 = ~bVar13 & (byte)iVar6 | bVar13;
    *(byte *)((int)piStack_3d5c + 0x23d2) = bVar13;
    *(byte *)((int)piStack_3d5c + 0x23d3) = bVar13 + *(char *)((int)piStack_3d5c + 0x23d1) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    goto LAB_004c0f5c;
  }
  (*pcVar16)();
  iVar6 = PeekPacketChecksumState();
  iVar5 = CONCAT13(0 < iVar6,(int3)unaff_EBX);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((0 < iVar6) && (piStack_3d5c[0x42d] == -1)) {
    (*pcVar16)(&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar6 + -1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    (*pcVar16)(&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    iVar5 = CONCAT13(iVar6 == 0,(int3)unaff_EBX);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar6 == 0) {
      (*pcVar16)(&DAT_005a9068);
      EncodeOutgoingPacketField(0xffffffff);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((char)piStack_3d5c[0x25] == '\0') {
        FUN_004ce610(piStack_3d5c);
      }
      else {
        FUN_004ce3d0(piStack_3d5c);
      }
    }
  }
  if (*(char *)((int)piStack_3d5c + 0x10bd) != '\0') {
    FUN_004cea70(piStack_3d5c);
  }
  piVar15 = piStack_3d5c;
  if (piStack_3d5c[0x42d] == -1) {
    (*pcVar16)(&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    uVar20 = (undefined3)iVar5;
    iVar5 = CONCAT13(iVar6 == -1,uVar20);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar6 == -1) && (*(char *)((int)piStack_3d5c + 0x10bd) == '\0')) {
      cVar3 = PeekPacketChecksumBool();
      if ((cVar3 != '\x01') || (cVar3 = PeekPacketChecksumBool(), cVar3 != '\0')) {
        (*pcVar16)(&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        iVar5 = CONCAT13(iVar6 == 0xf,uVar20);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar6 != 0xf) goto LAB_004c13d9;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeGuardedBool(1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      Replay_AppendEvent(0xc40a);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar7 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = g_clientContext;
      *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
      g_replayEventCursor = g_replayEventCursor + 4;
      uVar7 = (**(code **)(**(int **)(iVar6 + 0x621e0) + 0x14))();
      *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
      g_replayEventCursor = g_replayEventCursor + 4;
      Replay_FlushEvent();
      local_3d68 = (int *)0xc303;
      FUN_004e8a70();
      if (uStack_3d70 != DAT_00e9af14) {
        FUN_004e87b0(&DAT_00e9af10,&local_3d68,uStack_3d70);
      }
      cVar3 = CompareChecksumMatch(g_clientContext + 0x3b6c4,g_clientContext + 0x3b49c);
      iVar6 = g_clientContext;
      if (cVar3 == '\0') {
        Replay_AppendEvent(0xc302);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar4 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        (&g_replayEventBuffer)[g_replayEventCursor] = uVar4;
        g_replayEventCursor = g_replayEventCursor + 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
        g_replayEventCursor = g_replayEventCursor + 4;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        *(undefined4 *)(&DAT_006a7704 + g_clientContext) = uVar7;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_004e7140(uVar7);
      }
      else {
        puVar1 = (undefined4 *)(&DAT_006a76e8 + g_clientContext);
        *(undefined4 *)(&DAT_006aab00 + g_clientContext) = 0;
        *puVar1 = 0;
        *(undefined4 *)(&DAT_006a76ec + iVar6) = 0;
        FUN_004d2130(0xf);
        iVar6 = g_clientContext;
        (&DAT_006aa624)[g_clientContext] = 0xf;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar14 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        (&DAT_006a76e8)[iVar6 + iVar14] = 1;
        FUN_004e7d60(0xc302);
        FUN_00423a20();
      }
      pcVar16 = (code *)EnterCriticalSection;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeGuardedBool(1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(0xffffffff);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      piVar15 = local_3d60;
    }
  }
LAB_004c13d9:
  iVar6 = *(int *)(g_clientContext + 0xebeec);
  if (*(int *)(g_clientContext + 0xebef0) != iVar6) {
    iVar14 = *(int *)(g_clientContext + 0xebef0) - iVar6;
    if (iVar14 < 0) {
      iVar14 = iVar14 + -3;
    }
    else {
      iVar14 = iVar14 + 3;
    }
    *(int *)(g_clientContext + 0xebeec) = ((int)(iVar14 + (iVar14 >> 0x1f & 3U)) >> 2) + iVar6;
  }
  (*pcVar16)(&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  uStack_3d78 = (int *)CONCAT13(iVar6 == 3,(undefined3)uStack_3d78);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (SUBFIELD(uStack_3d78,3,undefined1) != '\0') {
    EncodeChecksumPairDiff(&DAT_0067e5f4 + g_clientContext,auStack_3384,&DAT_0067ea3c + g_clientContext);
    piStack_18 = (int *)0x1c;
    (*pcVar16)(&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_1c = 0xffffffff;
    if (piStack_3374 != (int *)0x0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&uStack_3d78);
      piVar15 = local_3d68;
    }
    iVar14 = iVar6 + -7;
    if (-1 < iVar6) {
      iVar14 = iVar6 + 7;
    }
    uStack_3d78 = (int *)(&DAT_0067ea3c + g_clientContext);
    (*pcVar16)(&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(((int)(iVar14 + (iVar14 >> 0x1f & 7U)) >> 3) + iVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumPairDiff(&DAT_0067e3d0 + g_clientContext,auStack_3168,&DAT_0067e818 + g_clientContext);
    uStack_20 = 0x1d;
    (*pcVar16)(&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_24 = 0xffffffff;
    uStack_3d78 = (int *)iStack_3158;
    if (iStack_3158 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&stack0xffffc280);
      piVar15 = piStack_3374;
    }
    (*pcVar16)(&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField((iVar5 >> 3) + iVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  iVar6 = g_clientContext;
  if ((char)piVar15[4] != '\0') {
    if (g_cursorAnchorX < 0xf5) {
      iVar5 = 0xf5;
    }
    else {
      iVar5 = g_cursorAnchorX;
      if (0x285 < g_cursorAnchorX) {
        iVar5 = 0x285;
      }
    }
    *(int *)(g_clientContext + 0xebee8) = iVar5;
  }
  if (((-99 < *(int *)(&DAT_006a73c0 + iVar6)) &&
      (iVar5 = *(int *)(&DAT_006a73c0 + iVar6) + 1, *(int *)(&DAT_006a73c0 + iVar6) = iVar5,
      iVar5 == 0xf0)) && ((char)piStack_3d64[0x474] == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar6 == 0) {
      FUN_004e1f70();
      iVar6 = g_clientContext;
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar6 < 8) {
        if ((char)piStack_3d64[0x474] == '\0') {
          CreateButtonWidget(&DAT_00e9be90,0,8,0x3f0,s_b_slot_retry_005540ec,0x1e2,0x201,0x34,0xe,1,
                             0);
          CreateButtonWidget(&DAT_00e9be90,0,9,0x3f1,s_b_slot_use_005540e0,0x1b0,0x201,0x34,0xe,1,0)
          ;
        }
        iVar6 = g_clientContext;
        *(undefined4 *)(&DAT_006a73c8 + g_clientContext) = 2;
      }
      else {
        AcquireSoundChannel(0);
        Replay_AppendEvent(0x8407);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar6 == 8) {
          (&g_replayEventBuffer)[g_replayEventCursor] = 1;
LAB_004c1730:
          g_replayEventCursor = g_replayEventCursor + 1;
        }
        else {
          if (iVar6 == 9) {
            (&g_replayEventBuffer)[g_replayEventCursor] = 2;
            goto LAB_004c1730;
          }
          if (iVar6 == 10) {
            (&g_replayEventBuffer)[g_replayEventCursor] = 3;
            goto LAB_004c1730;
          }
        }
        Replay_FlushEvent();
        iVar6 = g_clientContext;
        piStack_3d64[0x472] = 0x1e;
      }
    }
  }
  piVar15 = piStack_3d64;
  if (piStack_3d64[0x432] < 0) {
    piStack_3d64[0x431] = -1;
  }
  else {
    piStack_3d64[0x432] = piStack_3d64[0x432] + -1;
  }
  if (piStack_3d64[0x434] < 0) {
    piStack_3d64[0x433] = -1;
  }
  else {
    piStack_3d64[0x434] = piStack_3d64[0x434] + -1;
  }
  iVar5 = piStack_3d64[0x467];
  if (iVar5 != -1) {
    piStack_3d64[0x433] = iVar5;
    piStack_3d64[0x431] = iVar5;
    piStack_3d64[0x434] = 1;
    piStack_3d64[0x432] = 1;
  }
  if (((char)piStack_3d64[0x468] == '\x01') && (*(int *)(iVar6 + 0x621e0) != 0)) {
    cVar3 = CheckBothGuardedBools();
    iVar6 = g_clientContext;
    if ((cVar3 == '\0') || ((&DAT_005f2f40)[g_clientContext] != '\x02')) {
      *(undefined1 *)(piVar15 + 0x468) = 0;
      piVar15[0x469] = 0;
      piVar15[0x46a] = 0;
    }
    else {
      iVar6 = DAT_00e536c0 / 2;
      if (iVar6 == 0) {
        iVar6 = 1;
        if (0 < piVar15[0x46a] * 2) {
          iVar6 = piVar15[0x46a] * 2;
        }
        iVar5 = _rand();
        iVar6 = iVar5 % iVar6 - piVar15[0x46a];
      }
      AddToPacketChecksum(iVar6);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar6 < 1) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(1);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      iVar5 = piVar15[0x469];
      piVar15[0x469] = iVar5 + 1;
      iVar6 = g_clientContext;
      if (10 < iVar5 + 1) {
        piVar15[0x469] = 0;
        piVar15[0x46a] = piVar15[0x46a] + 2;
      }
    }
  }
  if (((*(int *)(iVar6 + 0x621e0) != 0) && ((&DAT_005f2f40)[iVar6] == '\x02')) &&
     (cVar3 = PeekPacketChecksumBool(), iVar6 = g_clientContext, cVar3 != '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = g_clientContext;
    if (((iVar5 < 0x8c) && (*(char *)((int)piVar15 + 0x11c5) == '\0')) &&
       (cVar3 = PeekPacketChecksumBool(), iVar6 = g_clientContext, cVar3 == '\x01')) {
      *(undefined1 *)((int)piVar15 + 0x11c5) = 1;
      iVar6 = g_clientContext;
    }
  }
  if (((*(char *)((int)piVar15 + 0x11c5) != '\0') && (*(int *)(iVar6 + 0x621e0) != 0)) &&
     ((cVar3 = PeekPacketChecksumBool(), iVar6 = g_clientContext, cVar3 == '\0' &&
      (cVar3 = PeekPacketChecksumBool(), iVar6 = g_clientContext, cVar3 == '\0')))) {
    *(undefined1 *)((int)piVar15 + 0x11c5) = 0;
    iVar6 = g_clientContext;
  }
  if (-1 < piVar15[0x472]) {
    if (piVar15[0x472] == 0) {
      FUN_004e1f70();
      iVar6 = g_clientContext;
      piVar15 = piStack_3d64;
    }
    piVar15[0x472] = piVar15[0x472] + -1;
  }
  iVar5 = *(int *)(&DAT_005f3768 + iVar6);
  if (iVar5 == 0) goto LAB_004c1acb;
  iVar14 = *(int *)(&DAT_005f376c + iVar6) + 1;
  *(int *)(&DAT_005f376c + iVar6) = iVar14;
  if (iVar5 == 1) {
    if (iVar14 < 0x14) goto LAB_004c1acb;
    *(undefined4 *)(&DAT_005f3768 + iVar6) = 2;
  }
  else {
    if (iVar5 == 5) {
      if (0x13 < iVar14) {
        *(undefined4 *)(&DAT_005f376c + iVar6) = 6;
        *(undefined4 *)(&DAT_005f3768 + iVar6) = 0;
      }
      goto LAB_004c1acb;
    }
    if ((iVar5 != 6) || (iVar14 < 10)) goto LAB_004c1acb;
    *(undefined4 *)(&DAT_005f3768 + iVar6) = 0;
  }
  *(undefined4 *)(&DAT_005f376c + iVar6) = 0;
LAB_004c1acb:
  if (*(char *)(DAT_007934e4 + 8) == '\0') {
    aCStack_3aac[0] = '\0';
  }
  else {
    iVar5 = GetWindowTextA(*(HWND *)(DAT_007934e4 + 4),aCStack_3aac,0x80);
    iVar6 = g_clientContext;
    if (iVar5 == 0) {
      aCStack_3aac[0] = '\0';
    }
    else if (aCStack_3aac[0] == ' ') {
      SetWindowTextA(*(HWND *)(DAT_007934e4 + 4),&DAT_00551cb1);
      iVar6 = g_clientContext;
    }
  }
  FUN_00409990(&DAT_006a647c + iVar6,1);
  FUN_004e39b0();
  *unaff_FS_OFFSET = uStack_20;
  return;
}

