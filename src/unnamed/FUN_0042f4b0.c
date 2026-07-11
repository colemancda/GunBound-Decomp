/* FUN_0042f4b0 - 0x0042f4b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x0042f6d4) */

void FUN_0042f4b0(undefined4 param_1,undefined4 param_2,int param_3)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffff6c4;
  undefined stack0xfffff6d0;
  undefined4 *puVar1;
  char cVar2;
  int *piVar3;
  int iVar4;
  undefined *puVar5;
  char *pcVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  byte bVar9;
  code *pcVar10;
  code *pcVar11;
  char *pcVar12;
  int *unaff_FS_OFFSET;
  undefined *puVar13;
  undefined *puStack_924;
  undefined *puStack_920;
  undefined *puStack_91c;
  undefined *puStack_918;
  undefined *puStack_914;
  undefined *puStack_910;
  undefined *puStack_90c;
  undefined *puStack_908;
  undefined *puStack_904;
  undefined *puStack_900;
  undefined *puStack_8fc;
  undefined *puStack_8f8;
  undefined *puStack_8f4;
  undefined *puStack_8f0;
  undefined *puStack_8ec;
  undefined *puStack_8e8;
  undefined *puStack_8e4;
  undefined *puStack_8e0;
  undefined *puStack_8dc;
  undefined *puStack_8d8;
  undefined *puStack_8d4;
  undefined *puStack_8d0;
  undefined1 auStack_704 [12];
  undefined1 auStack_6f8 [4];
  int iStack_6f4;
  undefined1 auStack_6f0 [8];
  int iStack_6e8;
  int iStack_6dc;
  undefined1 auStack_4f4 [60];
  int iStack_4b8;
  undefined1 auStack_2c8 [52];
  int iStack_294;
  undefined1 uStack_a4;
  undefined4 uStack_9c;
  undefined4 uStack_94;
  undefined1 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  int iStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined1 uStack_74;
  undefined1 uStack_70;
  uint uStack_6c;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_4c;
  int iStack_40;
  int iStack_1c;
  int iStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ce11;
  iStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (int)&iStack_c;
  piVar3 = operator_new(0x40a8);
  if (param_3 == 0) {
    local_4 = 0;
    if (piVar3 == (int *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      InitProjectile();
      *piVar3 = (int)&PTR_FUN_00556468;
      piVar3[0xfe7] = 0;
      piVar3[0x1028] = 0;
    }
    piVar3[0x1029] = 0xf00ff00;
  }
  else {
    local_4 = 1;
    if (piVar3 == (int *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      InitProjectile();
      *piVar3 = (int)&PTR_FUN_00556468;
      piVar3[0xfe7] = 0;
      piVar3[0x1028] = 0;
    }
    piVar3[0x1029] = 0xfffff00;
  }
  local_4 = 0xffffffff;
  if (*(char *)(g_clientContext + 0x45578) == '\0') {
    piVar3[0xe25] = param_3 + 0x1f52;
    puStack_8d0 = (undefined *)0x42f6a8;
    _sprintf((char *)(piVar3 + 0xe26),s_flame10_d_00553d44);
    pcVar10 = (code *)EnterCriticalSection;
    pcVar11 = (code *)LeaveCriticalSection;
  }
  else {
    pcVar10 = (code *)EnterCriticalSection;
    pcVar11 = (code *)LeaveCriticalSection;
    if (*(char *)(g_clientContext + 0x45578) == '\x01') {
      piVar3[6] = 6000;
      piVar3[0xe] = 0x17d4;
      piVar3[0xe25] = 8000;
      iVar4 = FindPreloadedTextureByName();
      pcVar10 = (code *)EnterCriticalSection;
      piVar3[7] = iVar4;
      piVar3[0xe26] = SUBFIELD(s_flameevent1_00553e2c,0,undefined4);
      piVar3[0xe27] = SUBFIELD(s_flameevent1_00553e2c,4,undefined4);
      piVar3[0xe28] = SUBFIELD(s_flameevent1_00553e2c,8,undefined4);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = _rand();
      *(char *)(piVar3 + 0xe04) = (char)iVar4;
      iVar4 = _rand();
      *(byte *)((int)piVar3 + 0x3811) = (byte)iVar4;
      pcVar11 = (code *)LeaveCriticalSection;
      bVar9 = ~('\x01' << (*(byte *)(piVar3 + 0xe04) & 7)) & (byte)iVar4 |
              '\0' << (*(byte *)(piVar3 + 0xe04) & 7);
      *(byte *)((int)piVar3 + 0x3811) = bVar9;
      *(byte *)((int)piVar3 + 0x3812) = bVar9 + (char)piVar3[0xe04] + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      (**(code **)(*piVar3 + 4))();
    }
  }
  piVar3[0xfe4] = 6;
  *(byte *)(piVar3 + 0xf) = (byte)param_1 & 7;
  (*pcVar10)();
  EncodeOutgoingPacketField();
  (*pcVar11)();
  puStack_8d0 = (undefined *)0x42f704;
  (*pcVar10)();
  puStack_8d0 = (undefined *)0x42f70b;
  puStack_8d0 = (undefined *)PeekPacketChecksumState();
  puStack_8d4 = (undefined *)0x42f717;
  EncodeOutgoingPacketField();
  puStack_8d0 = &DAT_005a9068;
  puStack_8d4 = (undefined *)0x42f71e;
  (*pcVar11)();
  puStack_8d4 = &DAT_005a9068;
  puStack_8d8 = (undefined *)0x42f72b;
  (*pcVar10)();
  puStack_8d8 = (undefined *)param_1;
  puStack_8dc = (undefined *)0x42f738;
  EncodeOutgoingPacketField();
  puStack_8d8 = &DAT_005a9068;
  puStack_8dc = (undefined *)0x42f73f;
  (*pcVar11)();
  puStack_8dc = &DAT_005a9068;
  puStack_8e0 = (undefined *)0x42f749;
  (*pcVar10)();
  puStack_8e0 = (undefined *)((int)puStack_8 << 8);
  puStack_8e4 = (undefined *)0x42f759;
  EncodeOutgoingPacketField();
  puStack_8e0 = &DAT_005a9068;
  puStack_8e4 = (undefined *)0x42f760;
  (*pcVar11)();
  puStack_8e4 = &DAT_005a9068;
  puStack_8e8 = (undefined *)0x42f76d;
  (*pcVar10)();
  puStack_8e8 = (undefined *)(iStack_c << 8);
  puStack_8ec = (undefined *)0x42f77d;
  EncodeOutgoingPacketField();
  puStack_8e8 = &DAT_005a9068;
  puStack_8ec = (undefined *)0x42f784;
  (*pcVar11)();
  puStack_8ec = &DAT_005a9068;
  puStack_8f0 = (undefined *)0x42f7ba;
  (*pcVar10)();
  puStack_8f0 = (undefined *)0x42f7c9;
  puStack_8f0 = (undefined *)FloatToInt64();
  puStack_8f4 = (undefined *)0x42f7cf;
  EncodeOutgoingPacketField();
  puStack_8f0 = &DAT_005a9068;
  puStack_8f4 = (undefined *)0x42f7d6;
  (*pcVar11)();
  puVar5 = puStack_8d0;
  if ((int)puStack_8d0 < 0) {
    puVar5 = puStack_8d0 + 0x168;
  }
  puStack_8d4 = *(undefined **)(&g_sineTable360 + (int)puVar5 * 4);
  puStack_8f4 = &DAT_005a9068;
  puStack_8f8 = (undefined *)0x42f7fb;
  (*pcVar10)();
  puStack_8f8 = (undefined *)0x42f80a;
  puStack_8f8 = (undefined *)FloatToInt64();
  puStack_8fc = (undefined *)0x42f810;
  EncodeOutgoingPacketField();
  puStack_8f8 = &DAT_005a9068;
  puStack_8fc = (undefined *)0x42f817;
  (*pcVar11)();
  puStack_8e4 = (undefined *)(iStack_1c % 0x168);
  iVar4 = (int)puStack_8e4;
  if ((int)puStack_8e4 < 0) {
    iVar4 = (int)puStack_8e4 + 0x168;
  }
  puStack_8dc = *(undefined **)(&g_sineTable360 + iVar4 * 4);
  puStack_8fc = &DAT_005a9068;
  puStack_900 = (undefined *)0x42f84a;
  (*pcVar10)();
  puStack_900 = (undefined *)0x42f859;
  puStack_900 = (undefined *)FloatToInt64();
  puStack_904 = (undefined *)0x42f85f;
  EncodeOutgoingPacketField();
  puStack_900 = &DAT_005a9068;
  puStack_904 = (undefined *)0x42f866;
  (*pcVar11)();
  puVar5 = puStack_8e0;
  if ((int)puStack_8e0 < 0) {
    puVar5 = puStack_8e0 + 0x168;
  }
  puStack_8e4 = *(undefined **)(&g_sineTable360 + (int)puVar5 * 4);
  puStack_904 = &DAT_005a9068;
  puStack_908 = (undefined *)0x42f88b;
  (*pcVar10)();
  puStack_908 = (undefined *)0x42f89a;
  puStack_908 = (undefined *)FloatToInt64();
  puStack_90c = (undefined *)0x42f8a0;
  EncodeOutgoingPacketField();
  puStack_908 = &DAT_005a9068;
  puStack_90c = (undefined *)0x42f8a7;
  (*pcVar11)();
  if ((int)puStack_8f4 < 0) {
    puStack_8f4 = puStack_8f4 + 0x168;
  }
  puStack_8f4 = *(undefined **)(&g_sineTable360 + (int)puStack_8f4 * 4);
  puStack_90c = &DAT_005a9068;
  puStack_910 = (undefined *)0x42f8cc;
  (*pcVar10)();
  puStack_910 = (undefined *)0x42f8db;
  puStack_910 = (undefined *)FloatToInt64();
  puStack_914 = (undefined *)0x42f8e1;
  EncodeOutgoingPacketField();
  puStack_910 = &DAT_005a9068;
  puStack_914 = (undefined *)0x42f8e8;
  (*pcVar11)();
  puStack_914 = &DAT_005a9068;
  puStack_918 = (undefined *)0x42f8ef;
  (*pcVar10)();
  puStack_918 = (undefined *)0x42f8f4;
  iVar4 = _rand();
  *(char *)((int)piVar3 + 0xf3f) = (char)iVar4;
  puStack_918 = (undefined *)0x42f90d;
  iVar4 = _rand();
  *(byte *)(piVar3 + 0x3d0) = (byte)iVar4;
  puStack_918 = &DAT_005a9068;
  bVar9 = *(byte *)((int)piVar3 + 0xf3f) & 7;
  bVar9 = ~('\x01' << bVar9) & (byte)iVar4 | '\0' << bVar9;
  *(byte *)(piVar3 + 0x3d0) = bVar9;
  *(byte *)((int)piVar3 + 0xf41) = bVar9 + *(char *)((int)piVar3 + 0xf3f) + -0x34;
  puStack_91c = (undefined *)0x42f95c;
  (*pcVar11)();
  puStack_91c = &DAT_005a9068;
  puStack_920 = (undefined *)0x42f963;
  (*pcVar10)();
  puStack_920 = (undefined *)0x42f968;
  iVar4 = _rand();
  *(char *)((int)piVar3 + 0xf45) = (char)iVar4;
  puStack_920 = (undefined *)0x42f981;
  iVar4 = _rand();
  *(byte *)((int)piVar3 + 0xf46) = (byte)iVar4;
  puStack_920 = &DAT_005a9068;
  bVar9 = *(byte *)((int)piVar3 + 0xf45) & 7;
  bVar9 = ~('\x01' << bVar9) & (byte)iVar4 | '\0' << bVar9;
  *(byte *)((int)piVar3 + 0xf46) = bVar9;
  *(byte *)((int)piVar3 + 0xf47) = bVar9 + *(char *)((int)piVar3 + 0xf45) + -0x34;
  puStack_924 = (undefined *)0x42f9ce;
  (*pcVar11)();
  puStack_924 = &DAT_005a9068;
  (*pcVar10)();
  EncodeGuardedBool();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar10)();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar10)();
  EncodeGuardedBool();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar3[0xfe5] = iStack_40;
  (*pcVar10)();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar10)();
  iVar4 = _rand();
  *(char *)((int)piVar3 + 0x391b) = (char)iVar4;
  iVar4 = _rand();
  *(byte *)(piVar3 + 0xe47) = (byte)iVar4;
  bVar9 = *(byte *)((int)piVar3 + 0x391b) & 7;
  bVar9 = ~('\x01' << bVar9) & (byte)iVar4 | '\0' << bVar9;
  *(byte *)(piVar3 + 0xe47) = bVar9;
  *(byte *)((int)piVar3 + 0x391d) = bVar9 + *(char *)((int)piVar3 + 0x391b) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar10)();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  pcVar6 = (&PTR_s_101blast_xes_0056d2b4)[(uStack_6c & 0xff) * 0x10];
  pcVar12 = (char *)((int)piVar3 + 0x3813);
  do {
    cVar2 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    *pcVar12 = cVar2;
    pcVar12 = pcVar12 + 1;
  } while (cVar2 != '\0');
  if (DAT_0079352a != '\0') {
    QueueBroadcastEvent();
    (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 3;
    puVar5 = &DAT_00e9aacd + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *puVar5 = uStack_74;
    puVar5 = &DAT_00e9aacd + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *puVar5 = uStack_70;
    puVar5 = &DAT_00e9aacd + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *puVar5 = 0xff;
    puVar5 = &DAT_00e9aacd + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *puVar5 = (undefined1)uStack_6c;
    puVar1 = (undefined4 *)(&DAT_00e9aacd + g_dwBroadcastEventCursor);
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *puVar1 = uStack_64;
    puVar1 = (undefined4 *)(&DAT_00e9aad0 + g_dwBroadcastEventCursor);
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    *puVar1 = uStack_60;
    puVar1 = (undefined4 *)(&DAT_00e9aad0 + g_dwBroadcastEventCursor);
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    *puVar1 = uStack_5c;
    puVar1 = (undefined4 *)(&DAT_00e9aad0 + g_dwBroadcastEventCursor);
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    *puVar1 = 0xffffffff;
    puVar5 = &DAT_00e9aad0 + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    *puVar5 = 0xff;
    puVar5 = &DAT_00e9aacd + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *puVar5 = 0xff;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    (*pcVar10)();
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar7;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    (*pcVar10)(&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar7;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    (*pcVar10)(&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar7;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    (*pcVar10)(&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar7;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    (*pcVar10)(&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar7;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    (*pcVar10)(&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar7;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    BroadcastQueuedEvent();
  }
  FUN_0041da80(g_clientContext,piVar3,uStack_6c,uStack_4c);
  iVar4 = GetPlayerRecordBySlot();
  if ((iVar4 != 0) && (cVar2 = PeekPacketChecksumBool(), cVar2 != '\0')) {
    EncodeChecksumDeltaDiv(piVar3 + 0x930,&puStack_914);
    uStack_7c = 2;
    EmitChecksumSum();
    uStack_7c = 0xffffffff;
    if (puStack_900 != (undefined *)0x0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
    }
    EncodeChecksumDeltaDiv(piVar3 + 0x9b9,&puStack_914);
    uStack_7c = 3;
    EmitChecksumSum();
    uStack_7c = 0xffffffff;
    if (puStack_900 != (undefined *)0x0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
    }
    EncodeChecksumDeltaDiv(piVar3 + 0xa42,&puStack_914);
    uStack_7c = 4;
    EmitChecksumSum();
    uStack_7c = 0xffffffff;
    if (puStack_900 != (undefined *)0x0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
    }
  }
  cVar2 = PeekPacketChecksumBool();
  pcVar11 = (code *)LeaveCriticalSection;
  pcVar10 = (code *)EnterCriticalSection;
  if (cVar2 == '\x01') {
    puStack_924 = (undefined *)EncodeChecksumDeltaMul(piVar3 + 0x930,auStack_6f0);
    pcVar10 = (code *)EnterCriticalSection;
    uStack_7c = 5;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    pcVar11 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaDiv(puStack_924,&puStack_914);
    SUBFIELD(uStack_7c,0,undefined1) = 6;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_924 = (undefined *)PeekPacketChecksumState();
    PeekPacketChecksumState();
    EncodeOutgoingPacketField();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_7c = CONCAT31(SUBFIELD(uStack_7c,1,undefined3),5);
    if (puStack_900 != (undefined *)0x0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
      pcVar11 = (code *)LeaveCriticalSection;
    }
    uStack_7c = 0xffffffff;
    if (iStack_6dc != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
      pcVar11 = (code *)LeaveCriticalSection;
    }
    puStack_924 = (undefined *)EncodeChecksumDeltaMul(piVar3 + 0x9b9,&puStack_914);
    uStack_7c = 7;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaDiv(puStack_924,auStack_6f0);
    SUBFIELD(uStack_7c,0,undefined1) = 8;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_924 = (undefined *)PeekPacketChecksumState();
    PeekPacketChecksumState();
    EncodeOutgoingPacketField();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_7c = CONCAT31(SUBFIELD(uStack_7c,1,undefined3),7);
    if (iStack_6dc != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
      pcVar11 = (code *)LeaveCriticalSection;
    }
    uStack_7c = 0xffffffff;
    if (puStack_900 != (undefined *)0x0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
      pcVar11 = (code *)LeaveCriticalSection;
    }
    puStack_924 = (undefined *)EncodeChecksumDeltaMul(piVar3 + 0xa42,&puStack_914);
    uStack_7c = 9;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaDiv(puStack_924,auStack_6f0);
    SUBFIELD(uStack_7c,0,undefined1) = 10;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_924 = (undefined *)PeekPacketChecksumState();
    PeekPacketChecksumState();
    EncodeOutgoingPacketField();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_7c = CONCAT31(SUBFIELD(uStack_7c,1,undefined3),9);
    if (iStack_6dc != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
      pcVar11 = (code *)LeaveCriticalSection;
    }
    uStack_7c = 0xffffffff;
    if (puStack_900 != (undefined *)0x0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
      pcVar11 = (code *)LeaveCriticalSection;
    }
  }
  cVar2 = CheckGuardedBoolAnd();
  if (cVar2 != '\0') {
    (*pcVar10)();
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaMul(piVar3 + 0x930,&puStack_918,uVar7);
    uStack_80 = 0xb;
    (*pcVar10)(&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaDiv(uVar7,auStack_6f8,uVar8);
    iStack_84 = CONCAT31(SUBFIELD(iStack_84,1,undefined3),0xc);
    (*pcVar10)(&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar7);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_88 = CONCAT31(SUBFIELD(uStack_88,1,undefined3),0xb);
    if (iStack_6e8 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&stack0xfffff6d0);
      pcVar11 = (code *)LeaveCriticalSection;
    }
    uStack_88 = 0xffffffff;
    if (puStack_90c != (undefined *)0x0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&stack0xfffff6d0);
      pcVar11 = (code *)LeaveCriticalSection;
    }
    puVar13 = &DAT_005a9068;
    (*pcVar10)(&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaMul(piVar3 + 0x9b9,&puStack_924,uVar7);
    uStack_8c = 0xd;
    (*pcVar10)(&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaDiv(uVar7,auStack_704,uVar8);
    puVar5 = &DAT_005a9068;
    uStack_90 = 0xe;
    (*pcVar10)(&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar7);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_94 = CONCAT31(SUBFIELD(uStack_94,1,undefined3),0xd);
    if (iStack_6f4 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&stack0xfffff6c4);
      pcVar11 = (code *)LeaveCriticalSection;
    }
    uStack_94 = 0xffffffff;
    if (puStack_918 != (undefined *)0x0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&stack0xfffff6c4);
      pcVar11 = (code *)LeaveCriticalSection;
    }
    (*pcVar10)(&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar11)(&DAT_005a9068);
    EncodeChecksumDeltaMul(piVar3 + 0xa42,auStack_2c8,puVar13);
    uStack_9c = 0xf;
    (*pcVar10)(&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    (*pcVar11)(&DAT_005a9068);
    EncodeChecksumDeltaDiv(uVar7,auStack_4f4,puVar5);
    uStack_a4 = 0x10;
    (*pcVar10)(&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar7);
    (*pcVar11)(&DAT_005a9068);
    uStack_7c = CONCAT31(SUBFIELD(uStack_7c,1,undefined3),0xf);
    if (iStack_4b8 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
    }
    uStack_7c = 0xffffffff;
    if (iStack_294 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
    }
  }
  RegisterActiveObject();
  *unaff_FS_OFFSET = iStack_84;
  return;
}

