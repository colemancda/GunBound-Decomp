/* FUN_0042f4b0 - 0x0042f4b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-16): this function's 5 real call sites (all in
 * FUN_00480310.c) already pass 12 cdecl arguments each, but only the
 * first 3 were ever surfaced as real parameters (param_1/param_2/
 * param_3 - param_2 itself unused) - the other 9 were silently
 * dropped, most visibly the value half of most of this function's 19
 * EncodeOutgoingPacketField calls (see those fixes below). angr-
 * confirmed the frame layout (param_1's own read, `movzx eax,byte ptr
 * [esp+0x8c4]` at 0x42f6b7, occurs only after all 4 prologue register
 * pushes complete, unlike param_3's read which happens mid-prologue
 * after only one push - the two reads are at different effective
 * stack depths despite the small numeric difference between their
 * offsets, an easy trap when computing this by hand) - param_1..12
 * sit at consecutive +4 stack slots once that's accounted for, so
 * param_1/param_2/param_3's existing bindings were already correct;
 * only param_4..param_12 needed adding.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x0042f6d4) */

void FUN_0042f4b0(undefined4 param_1,undefined4 param_2,int param_3,int param_4,int param_5,
                   int param_6,int param_7,int param_8,int param_9,int param_10,int param_11,
                   int param_12)

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
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42f6f1
   * (`lea edi,[ebp + 0xf54]`, ebp = this file's own local object pointer
   * `piVar3`): cell is piVar3+0x3d5 (== piVar3+0xf54 bytes) - matches the
   * same offset family established for the sibling functions in this
   * batch (e.g. src/battle/SpawnSuperShot.c). See
   * tools/encodeoutgoingpacketfield_sites.json. */
  (*pcVar10)();
  EncodeOutgoingPacketField(piVar3 + 0x3d5, param_5);
  (*pcVar11)();
  puStack_8d0 = (undefined *)0x42f704;
  (*pcVar10)();
  puStack_8d0 = (undefined *)0x42f70b;
  puStack_8d0 = (undefined *)PeekPacketChecksumState();
  puStack_8d4 = (undefined *)0x42f717;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42f712
   * (`lea edi,[ebp + 0x3b48]`): cell is piVar3+0xed2 (== piVar3+0x3b48
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(piVar3 + 0xed2, PeekPacketChecksumState());
  puStack_8d0 = &DAT_005a9068;
  puStack_8d4 = (undefined *)0x42f71e;
  (*pcVar11)();
  puStack_8d4 = &DAT_005a9068;
  puStack_8d8 = (undefined *)0x42f72b;
  (*pcVar10)();
  puStack_8d8 = (undefined *)param_1;
  puStack_8dc = (undefined *)0x42f738;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42f733
   * (`lea edi,[ebp + 0x1178]`): cell is piVar3+0x45e (== piVar3+0x1178
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(piVar3 + 0x45e, param_6);
  puStack_8d8 = &DAT_005a9068;
  puStack_8dc = (undefined *)0x42f73f;
  (*pcVar11)();
  puStack_8dc = &DAT_005a9068;
  puStack_8e0 = (undefined *)0x42f749;
  (*pcVar10)();
  puStack_8e0 = (undefined *)((int)puStack_8 << 8);
  puStack_8e4 = (undefined *)0x42f759;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42f754
   * (`lea edi,[ebp + 0x40]`): cell is piVar3+0x10 (== piVar3+0x40 bytes).
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(piVar3 + 0x10, param_5 << 8);
  puStack_8e0 = &DAT_005a9068;
  puStack_8e4 = (undefined *)0x42f760;
  (*pcVar11)();
  puStack_8e4 = &DAT_005a9068;
  puStack_8e8 = (undefined *)0x42f76d;
  (*pcVar10)();
  puStack_8e8 = (undefined *)(iStack_c << 8);
  puStack_8ec = (undefined *)0x42f77d;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42f778
   * (`lea edi,[ebp + 0x264]`): cell is piVar3+0x99 (== piVar3+0x264
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(piVar3 + 0x99, param_6 << 8);
  puStack_8e8 = &DAT_005a9068;
  puStack_8ec = (undefined *)0x42f784;
  (*pcVar11)();
  puStack_8ec = &DAT_005a9068;
  puStack_8f0 = (undefined *)0x42f7ba;
  (*pcVar10)();
  puStack_8f0 = (undefined *)0x42f7c9;
  puStack_8f0 = (undefined *)FloatToInt64();
  puStack_8f4 = (undefined *)0x42f7cf;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42f7ca
   * (`lea edi,[ebp + 0x488]`): cell is piVar3+0x122 (== piVar3+0x488
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(piVar3 + 0x122, (unsigned int)puStack_8f0);
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
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42f80b
   * (`lea edi,[ebp + 0x8d0]`): cell is piVar3+0x234 (== piVar3+0x8d0
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(piVar3 + 0x234, (unsigned int)puStack_8f8);
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
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42f85a
   * (`lea edi,[ebp + 0x6ac]`): cell is piVar3+0x1ab (== piVar3+0x6ac
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(piVar3 + 0x1ab, (unsigned int)puStack_900);
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
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42f89b
   * (`lea edi,[ebp + 0xaf4]`): cell is piVar3+0x2bd (== piVar3+0xaf4
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(piVar3 + 0x2bd, (unsigned int)puStack_908);
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
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42f8dc
   * (`lea edi,[ebp + 0xd18]`): cell is piVar3+0x346 (== piVar3+0xd18
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(piVar3 + 0x346, (unsigned int)puStack_910);
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
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42fa0a
   * (`lea edi,[ebp + 0x17e4]`): cell is piVar3+0x5f9 (== piVar3+0x17e4
   * bytes) - matches the same `+0x17e4` field established for the
   * sibling functions in this batch (e.g. src/battle/SpawnSuperShot.c).
   * See tools/encodeoutgoingpacketfield_sites.json. */
  (*pcVar10)();
  EncodeGuardedBool();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar10)();
  EncodeOutgoingPacketField(piVar3 + 0x5f9, param_8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar10)();
  EncodeGuardedBool();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar3[0xfe5] = iStack_40;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42fa5f
   * (`lea edi,[ebp + 0x1a08]`): cell is piVar3+0x682 (== piVar3+0x1a08
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  (*pcVar10)();
  EncodeOutgoingPacketField(piVar3 + 0x682, param_10);
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
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42faec
   * (`lea edi,[ebp + 0x3920]`): cell is piVar3+0xe48 (== piVar3+0x3920
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  (*pcVar10)();
  EncodeOutgoingPacketField(piVar3 + 0xe48, 0);
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
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42ff92
     * (`lea edi,[ebp + 0x24c0]`): cell is piVar3+0x930 (== piVar3+0x24c0
     * bytes) - the same cell explicitly passed to EncodeChecksumDeltaMul
     * above. See tools/encodeoutgoingpacketfield_sites.json.
     * FIXED (2026-07-16): also merged the value arg (sum of the two
     * adjacent PeekPacketChecksumState() calls, matching the disasm's
     * `add eax,ecx` between them). */
    EncodeOutgoingPacketField(piVar3 + 0x930, PeekPacketChecksumState() + PeekPacketChecksumState());
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
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x430099
     * (`lea edi,[ebp + 0x26e4]`): cell is piVar3+0x9b9 (== piVar3+0x26e4
     * bytes) - the same cell explicitly passed to EncodeChecksumDeltaMul
     * above. See tools/encodeoutgoingpacketfield_sites.json.
     * FIXED (2026-07-16): also merged the value arg - see piVar3+0x930's
     * note above. */
    EncodeOutgoingPacketField(piVar3 + 0x9b9, PeekPacketChecksumState() + PeekPacketChecksumState());
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
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4301a0
     * (`lea edi,[ebp + 0x2908]`): cell is piVar3+0xa42 (== piVar3+0x2908
     * bytes) - the same cell explicitly passed to EncodeChecksumDeltaMul
     * above. See tools/encodeoutgoingpacketfield_sites.json.
     * FIXED (2026-07-16): also merged the value arg - see piVar3+0x930's
     * note above. */
    EncodeOutgoingPacketField(piVar3 + 0xa42, PeekPacketChecksumState() + PeekPacketChecksumState());
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
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4302df
     * (`lea edi,[ebp + 0x24c0]`): cell is piVar3+0x930 (== piVar3+0x24c0
     * bytes) - the same cell explicitly passed to EncodeChecksumDeltaMul
     * above. See tools/encodeoutgoingpacketfield_sites.json. */
    (*pcVar10)(&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(piVar3 + 0x930,uVar7);
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
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4303f4
     * (`lea edi,[ebp + 0x26e4]`): cell is piVar3+0x9b9 (== piVar3+0x26e4
     * bytes) - the same cell explicitly passed to EncodeChecksumDeltaMul
     * above. See tools/encodeoutgoingpacketfield_sites.json. */
    (*pcVar10)(&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(piVar3 + 0x9b9,uVar7);
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
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x43050c
     * (`lea edi,[ebp + 0x2908]`): cell is piVar3+0xa42 (== piVar3+0x2908
     * bytes) - the same cell explicitly passed to EncodeChecksumDeltaMul
     * above. See tools/encodeoutgoingpacketfield_sites.json. */
    (*pcVar10)(&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(piVar3 + 0xa42,uVar7);
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
  RegisterActiveObject(0, 0, (undefined4 *)0);
  *unaff_FS_OFFSET = iStack_84;
  return;
}

