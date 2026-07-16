/* FUN_004305c0 - 0x004305c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-16): this function's own 13 incoming cdecl stack
 * parameters were entirely dropped (declared `void FUN_004305c0(void)`,
 * matching the K&R-empty style in functions.h) even though its 8 real
 * call sites in FUN_0047ca40.c already pass 13 arguments each against
 * that stale K&R declaration. angr-confirmed the frame layout
 * (`sub esp,0x8a8` + 4 pushes before the first real body instruction,
 * so param N sits at caller-relative [esp+0x8c4+4*N] within the body) -
 * param 8 was the only one Ghidra itself already recognized as a
 * parameter (as `in_stack_00000020`, since 0x20 == the caller-relative
 * offset of the 8th cdecl arg, 4+4*7); the other 12 were silently
 * dropped from every use, most visibly the value half of 9 of this
 * function's 20 EncodeOutgoingPacketField calls (see those fixes
 * below) - same root bug as the self-argument drops elsewhere in this
 * migration, just manifesting as a whole-function parameter list this
 * time instead of a single register.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x0043089b) */
/* WARNING: Removing unreachable block (ram,0x004309a5) */
/* WARNING: Removing unreachable block (ram,0x00430a35) */
/* WARNING: Removing unreachable block (ram,0x00430a76) */

void FUN_004305c0(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                   int param_7,int param_8,int param_9,int param_10,int param_11,int param_12,
                   int param_13)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffff6a0;
  undefined stack0xfffff6b8;
  undefined stack0xfffff6c0;
  undefined4 *puVar1;
  char cVar2;
  int *piVar3;
  int iVar4;
  char *pcVar5;
  undefined4 uVar6;
  byte bVar7;
  byte bVar8;
  code *pcVar9;
  code *pcVar10;
  char *pcVar11;
  undefined4 *unaff_FS_OFFSET;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined4 uStack_914;
  undefined4 uStack_90c;
  undefined1 auStack_724 [12];
  int iStack_718;
  int iStack_700;
  int iStack_6f0;
  int iStack_6e8;
  undefined1 auStack_518 [84];
  int iStack_4c4;
  undefined1 auStack_2ec [76];
  int iStack_2a0;
  undefined1 uStack_c8;
  undefined4 uStack_c0;
  undefined4 uStack_b8;
  undefined1 uStack_b0;
  undefined4 uStack_a8;
  undefined4 uStack_a0;
  undefined1 uStack_98;
  undefined1 uStack_94;
  undefined4 uStack_90;
  undefined1 uStack_8c;
  undefined4 uStack_88;
  undefined1 uStack_80;
  undefined1 uStack_7c;
  uint uStack_78;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  int iStack_48;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053cd43;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  piVar3 = operator_new(0x3fa4);
  local_4 = 0;
  if (piVar3 == (int *)0x0) {
    piVar3 = (int *)0x0;
  }
  else {
    InitProjectile();
    *piVar3 = (int)&PTR_FUN_00556008;
    piVar3[0xfe8] = 0;
  }
  local_4 = 0xffffffff;
  if (*(char *)(g_clientContext + 0x45578) == '\0') {
    piVar3[6] = 0x19c8;
    piVar3[0xe] = 0x19ca;
    piVar3[0xe25] = 0x19c9;
    iVar4 = FindPreloadedTextureByName();
    piVar3[7] = iVar4;
    piVar3[0xe26] = SUBFIELD(s_flame_00553d2c,0,undefined4);
    *(undefined2 *)(piVar3 + 0xe27) = SUBFIELD(s_flame_00553d2c,4,undefined2);
    _sprintf((char *)(piVar3 + 0xe26),s_knightflame_00553d20);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = _rand();
    *(char *)(piVar3 + 0xe04) = (char)iVar4;
    iVar4 = _rand();
    *(byte *)((int)piVar3 + 0x3811) = (byte)iVar4;
    bVar7 = *(byte *)(piVar3 + 0xe04) & 7;
    bVar7 = ~('\x01' << bVar7) & (byte)iVar4 | '\0' << bVar7;
    *(byte *)((int)piVar3 + 0x3811) = bVar7;
    *(byte *)((int)piVar3 + 0x3812) = bVar7 + *(byte *)(piVar3 + 0xe04) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    (**(code **)(*piVar3 + 4))();
    pcVar9 = (code *)EnterCriticalSection;
    pcVar10 = (code *)LeaveCriticalSection;
  }
  else {
    pcVar9 = (code *)EnterCriticalSection;
    pcVar10 = (code *)LeaveCriticalSection;
    if (*(char *)(g_clientContext + 0x45578) == '\x01') {
      piVar3[6] = 6000;
      piVar3[0xe] = 0x17d4;
      piVar3[0xe25] = 8000;
      iVar4 = FindPreloadedTextureByName();
      pcVar9 = (code *)EnterCriticalSection;
      piVar3[7] = iVar4;
      piVar3[0xe26] = SUBFIELD(s_flameevent1_00553e2c,0,undefined4);
      piVar3[0xe27] = SUBFIELD(s_flameevent1_00553e2c,4,undefined4);
      piVar3[0xe28] = SUBFIELD(s_flameevent1_00553e2c,8,undefined4);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = _rand();
      *(char *)(piVar3 + 0xe04) = (char)iVar4;
      iVar4 = _rand();
      *(byte *)((int)piVar3 + 0x3811) = (byte)iVar4;
      pcVar10 = (code *)LeaveCriticalSection;
      bVar7 = ~('\x01' << (*(byte *)(piVar3 + 0xe04) & 7)) & (byte)iVar4 |
              '\0' << (*(byte *)(piVar3 + 0xe04) & 7);
      *(byte *)((int)piVar3 + 0x3811) = bVar7;
      *(byte *)((int)piVar3 + 0x3812) = bVar7 + (char)piVar3[0xe04] + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      (**(code **)(*piVar3 + 4))();
    }
  }
  (*pcVar9)();
  iVar4 = _rand();
  *(char *)((int)piVar3 + 0xf42) = (char)iVar4;
  iVar4 = _rand();
  *(byte *)((int)piVar3 + 0xf43) = (byte)iVar4;
  bVar7 = *(byte *)((int)piVar3 + 0xf42) & 7;
  bVar7 = ~('\x01' << bVar7) & (byte)iVar4 | '\0' << bVar7;
  *(byte *)((int)piVar3 + 0xf43) = bVar7;
  *(byte *)(piVar3 + 0x3d1) = *(byte *)((int)piVar3 + 0xf42) + bVar7 + -0x34;
  (*pcVar10)();
  piVar3[0xfe7] = param_8;
  *(byte *)(piVar3 + 0xf) = (byte)local_4 & 7;
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at 0x4308b8
   * .. 0x430aa3 (`lea edi,[ebp + OFFSET]`, ebp = this file's own local
   * object pointer `piVar3`): the offsets/order (0xf54, 0x3b48, 0x1178,
   * 0x40, 0x264, 0x488, 0x8d0, 0x6ac, 0xaf4, 0xd18) exactly match the
   * same field family already established for the sibling functions in
   * this batch (src/battle/SpawnSuperShot.c, src/unnamed/FUN_0042f4b0.c,
   * src/unnamed/FUN_004388e0.c). See
   * tools/encodeoutgoingpacketfield_sites.json. */
  (*pcVar9)();
  EncodeOutgoingPacketField(piVar3 + 0x3d5, param_5);
  (*pcVar10)();
  (*pcVar9)();
  EncodeOutgoingPacketField(piVar3 + 0xed2, PeekPacketChecksumState());
  (*pcVar10)();
  (*pcVar9)();
  EncodeOutgoingPacketField(piVar3 + 0x45e, param_6);
  (*pcVar10)();
  (*pcVar9)();
  EncodeOutgoingPacketField(piVar3 + 0x10, param_5 << 8);
  (*pcVar10)();
  (*pcVar9)();
  EncodeOutgoingPacketField(piVar3 + 0x99, param_6 << 8);
  (*pcVar10)();
  (*pcVar9)();
  EncodeOutgoingPacketField(piVar3 + 0x122, FloatToInt64());
  (*pcVar10)();
  (*pcVar9)();
  EncodeOutgoingPacketField(piVar3 + 0x234, FloatToInt64());
  (*pcVar10)();
  (*pcVar9)();
  EncodeOutgoingPacketField(piVar3 + 0x1ab, FloatToInt64());
  (*pcVar10)();
  (*pcVar9)();
  EncodeOutgoingPacketField(piVar3 + 0x2bd, FloatToInt64());
  (*pcVar10)();
  (*pcVar9)();
  EncodeOutgoingPacketField(piVar3 + 0x346, FloatToInt64());
  (*pcVar10)();
  (*pcVar9)();
  iVar4 = _rand();
  *(char *)((int)piVar3 + 0xf3f) = (char)iVar4;
  iVar4 = _rand();
  bVar7 = *(byte *)((int)piVar3 + 0xf3f);
  uStack_90c = CONCAT13(bVar7,0x5a9068);
  *(byte *)(piVar3 + 0x3d0) = (byte)iVar4;
  bVar8 = ~('\x01' << (bVar7 & 7)) & (byte)iVar4 | '\0' << (bVar7 & 7);
  *(byte *)(piVar3 + 0x3d0) = bVar8;
  *(byte *)((int)piVar3 + 0xf41) = bVar7 + bVar8 + -0x34;
  (*pcVar10)();
  (*pcVar9)();
  iVar4 = _rand();
  *(char *)((int)piVar3 + 0xf45) = (char)iVar4;
  iVar4 = _rand();
  bVar7 = *(byte *)((int)piVar3 + 0xf45);
  uStack_914 = CONCAT13(bVar7,0x5a9068);
  *(byte *)((int)piVar3 + 0xf46) = (byte)iVar4;
  bVar8 = ~('\x01' << (bVar7 & 7)) & (byte)iVar4 | '\0' << (bVar7 & 7);
  *(byte *)((int)piVar3 + 0xf46) = bVar8;
  *(byte *)((int)piVar3 + 0xf47) = bVar7 + bVar8 + -0x34;
  (*pcVar10)();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x430bd1
   * (`lea edi,[ebp + 0x17e4]`): cell is piVar3+0x5f9 (== piVar3+0x17e4
   * bytes) - matches the same field established for the sibling
   * functions in this batch. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  (*pcVar9)();
  EncodeGuardedBool();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar9)();
  EncodeOutgoingPacketField(piVar3 + 0x5f9, param_8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x430c19
   * (`lea edi,[ebp + 0x1c2c]`): cell is piVar3+0x70b (== piVar3+0x1c2c
   * bytes) - matches the same `+0x1c2c` field established elsewhere in
   * this batch (e.g. src/unnamed/FUN_00452cc0.c, .../FUN_004513b0.c). See
   * tools/encodeoutgoingpacketfield_sites.json. */
  (*pcVar9)();
  EncodeGuardedBool();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar9)();
  EncodeOutgoingPacketField(piVar3 + 0x70b, param_7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puVar14 = &DAT_005a9068;
  piVar3[0xfe4] = 4;
  piVar3[0xfe5] = iStack_48;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x430c51
   * (`lea edi,[ebp + 0x1a08]`): cell is piVar3+0x682 (== piVar3+0x1a08
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  (*pcVar9)();
  EncodeOutgoingPacketField(piVar3 + 0x682, param_11);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar9)();
  iVar4 = _rand();
  *(char *)((int)piVar3 + 0x391b) = (char)iVar4;
  iVar4 = _rand();
  *(byte *)(piVar3 + 0xe47) = (byte)iVar4;
  bVar7 = *(byte *)((int)piVar3 + 0x391b) & 7;
  bVar7 = ~('\x01' << bVar7) & (byte)iVar4 | '\0' << bVar7;
  *(byte *)(piVar3 + 0xe47) = bVar7;
  *(byte *)((int)piVar3 + 0x391d) = *(byte *)((int)piVar3 + 0x391b) + bVar7 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x430cdf
   * (`lea edi,[ebp + 0x3920]`): cell is piVar3+0xe48 (== piVar3+0x3920
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  (*pcVar9)();
  EncodeOutgoingPacketField(piVar3 + 0xe48, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  pcVar5 = (&PTR_s_151blast_xes_0056d2c8)[(uStack_78 & 0xff) * 0x10];
  pcVar11 = (char *)((int)piVar3 + 0x3813);
  do {
    cVar2 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    *pcVar11 = cVar2;
    pcVar11 = pcVar11 + 1;
  } while (cVar2 != '\0');
  if (DAT_0079352a != '\0') {
    QueueBroadcastEvent();
    (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 4;
    puVar13 = &DAT_00e9aacd + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *puVar13 = uStack_80;
    puVar13 = &DAT_00e9aacd + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *puVar13 = uStack_7c;
    puVar13 = &DAT_00e9aacd + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *puVar13 = 0xff;
    puVar13 = &DAT_00e9aacd + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *puVar13 = (undefined1)uStack_78;
    puVar1 = (undefined4 *)(&DAT_00e9aacd + g_dwBroadcastEventCursor);
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *puVar1 = uStack_70;
    puVar1 = (undefined4 *)(&DAT_00e9aad0 + g_dwBroadcastEventCursor);
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    *puVar1 = uStack_6c;
    puVar1 = (undefined4 *)(&DAT_00e9aad0 + g_dwBroadcastEventCursor);
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    *puVar1 = uStack_68;
    puVar1 = (undefined4 *)(&DAT_00e9aad0 + g_dwBroadcastEventCursor);
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    *puVar1 = 0xffffffff;
    puVar13 = &DAT_00e9aad0 + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    *puVar13 = 0xff;
    puVar13 = &DAT_00e9aacd + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *puVar13 = 0xff;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    (*pcVar9)();
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar6;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    (*pcVar9)();
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar6;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    (*pcVar9)();
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar6;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    (*pcVar9)();
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar6;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    (*pcVar9)();
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar6;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    (*pcVar9)();
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar6;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    BroadcastQueuedEvent();
  }
  FUN_0041da80();
  iVar4 = GetPlayerRecordBySlot();
  if ((iVar4 != 0) && (cVar2 = PeekPacketChecksumBool(), cVar2 != '\0')) {
    EncodeChecksumDeltaDiv();
    uStack_88 = 1;
    EmitChecksumSum();
    uStack_88 = 0xffffffff;
    if (uStack_90c != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
    }
    EncodeChecksumDeltaDiv();
    uStack_88 = 2;
    EmitChecksumSum();
    uStack_88 = 0xffffffff;
    if (uStack_90c != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
    }
    EncodeChecksumDeltaDiv();
    uStack_88 = 3;
    EmitChecksumSum();
    uStack_88 = 0xffffffff;
    if (uStack_90c != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
    }
  }
  cVar2 = PeekPacketChecksumBool();
  pcVar10 = (code *)LeaveCriticalSection;
  pcVar9 = (code *)EnterCriticalSection;
  if (cVar2 == '\x01') {
    EncodeChecksumDeltaMul();
    pcVar9 = (code *)EnterCriticalSection;
    uStack_88 = 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    pcVar10 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaDiv();
    SUBFIELD(uStack_88,0,undefined1) = 5;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x431184
     * (`lea edi,[ebp + 0x24c0]`): cell is piVar3+0x930 (== piVar3+0x24c0
     * bytes) - matches the identical, explicitly-confirmed pattern in
     * the sibling functions in this batch (src/unnamed/FUN_0042f4b0.c,
     * .../FUN_004388e0.c). See tools/encodeoutgoingpacketfield_sites.json.
     * FIXED (2026-07-16): also merged the value arg (sum of the two
     * adjacent PeekPacketChecksumState() calls, matching the disasm's
     * `add eax,ecx` between them). */
    EncodeOutgoingPacketField(piVar3 + 0x930, PeekPacketChecksumState() + PeekPacketChecksumState());
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_88 = CONCAT31(SUBFIELD(uStack_88,1,undefined3),4);
    if (uStack_90c != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
      pcVar10 = (code *)LeaveCriticalSection;
    }
    uStack_88 = 0xffffffff;
    if (iStack_6e8 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
      pcVar10 = (code *)LeaveCriticalSection;
    }
    EncodeChecksumDeltaMul();
    uStack_88 = 6;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar10)();
    EncodeChecksumDeltaDiv();
    uStack_8c = 7;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x43128b
     * (`lea edi,[ebp + 0x26e4]`): cell is piVar3+0x9b9 (== piVar3+0x26e4
     * bytes). See tools/encodeoutgoingpacketfield_sites.json.
     * FIXED (2026-07-16): also merged the value arg - see piVar3+0x930's
     * note above. */
    EncodeOutgoingPacketField(piVar3 + 0x9b9, PeekPacketChecksumState() + PeekPacketChecksumState());
    (*pcVar10)();
    uStack_90 = CONCAT31(SUBFIELD(uStack_90,1,undefined3),6);
    if (iStack_6f0 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
      pcVar10 = (code *)LeaveCriticalSection;
    }
    uStack_90 = 0xffffffff;
    if (uStack_914 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
      pcVar10 = (code *)LeaveCriticalSection;
    }
    EncodeChecksumDeltaMul();
    uStack_90 = 8;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puVar14 = (undefined *)PeekPacketChecksumState();
    (*pcVar10)();
    EncodeChecksumDeltaDiv();
    uStack_94 = 9;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x431392
     * (`lea edi,[ebp + 0x2908]`): cell is piVar3+0xa42 (== piVar3+0x2908
     * bytes). See tools/encodeoutgoingpacketfield_sites.json.
     * FIXED (2026-07-16): also merged the value arg - see piVar3+0x930's
     * note above. */
    EncodeOutgoingPacketField(piVar3 + 0xa42, PeekPacketChecksumState() + PeekPacketChecksumState());
    (*pcVar10)();
    uStack_88 = CONCAT31(SUBFIELD(uStack_88,1,undefined3),8);
    if (iStack_6e8 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
      pcVar10 = (code *)LeaveCriticalSection;
    }
    uStack_88 = 0xffffffff;
    if (uStack_90c != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
      pcVar10 = (code *)LeaveCriticalSection;
    }
  }
  cVar2 = CheckGuardedBoolAnd();
  if (cVar2 != '\0') {
    (*pcVar9)();
    iVar4 = PeekPacketChecksumState();
    (*pcVar10)();
    EncodeChecksumDeltaMul();
    uStack_90 = 10;
    (*pcVar9)();
    PeekPacketChecksumState();
    puVar13 = &DAT_005a9068;
    (*pcVar10)();
    EncodeChecksumDeltaDiv(puVar14);
    uStack_98 = 0xb;
    (*pcVar9)();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4314d1
     * (`lea edi,[ebp + 0x24c0]`): cell is piVar3+0x930 (== piVar3+0x24c0
     * bytes) - matches the identical, explicitly-confirmed pattern in
     * the sibling functions in this batch, and the two explicitly-
     * confirmed sites immediately following (0x4315e6/0x4316fe). See
     * tools/encodeoutgoingpacketfield_sites.json.
     * FIXED (2026-07-16): also merged the value arg - single (not
     * summed) PeekPacketChecksumState() here, unlike the earlier three
     * 0x930/0x9b9/0xa42 sites. */
    EncodeOutgoingPacketField(piVar3 + 0x930, PeekPacketChecksumState());
    puVar14 = &DAT_005a9068;
    (*pcVar10)();
    uStack_a0 = CONCAT31(SUBFIELD(uStack_a0,1,undefined3),10);
    if (iStack_700 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&stack0xfffff6b8);
    }
    uStack_a0 = 0xffffffff;
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&stack0xfffff6b8);
    pcVar10 = (code *)LeaveCriticalSection;
    (*pcVar9)(&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaMul(piVar3 + 0x9b9,&stack0xfffff6c0,puVar13);
    uStack_a8 = 0xc;
    (*pcVar9)(&DAT_005a9068);
    PeekPacketChecksumState();
    puVar12 = &DAT_005a9068;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaDiv(puVar13,auStack_724,puVar14);
    uStack_b0 = 0xd;
    (*pcVar9)(&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4315e6
     * (`lea edi,[ebp + 0x26e4]`): cell is piVar3+0x9b9 (== piVar3+0x26e4
     * bytes) - the same cell explicitly passed to EncodeChecksumDeltaMul
     * above. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField(piVar3 + 0x9b9,uVar6);
    puVar14 = &DAT_005a9068;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_b8 = CONCAT31(SUBFIELD(uStack_b8,1,undefined3),0xc);
    if (iStack_718 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&stack0xfffff6a0);
      pcVar10 = (code *)LeaveCriticalSection;
    }
    uStack_b8 = 0xffffffff;
    if (iVar4 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&stack0xfffff6a0);
      pcVar10 = (code *)LeaveCriticalSection;
    }
    (*pcVar9)(&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar10)(&DAT_005a9068);
    EncodeChecksumDeltaMul(piVar3 + 0xa42,auStack_2ec,puVar12);
    uStack_c0 = 0xe;
    (*pcVar9)(&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar10)(&DAT_005a9068);
    EncodeChecksumDeltaDiv(puVar12,auStack_518,puVar14);
    uStack_c8 = 0xf;
    (*pcVar9)(&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4316fe
     * (`lea edi,[ebp + 0x2908]`): cell is piVar3+0xa42 (== piVar3+0x2908
     * bytes) - the same cell explicitly passed to EncodeChecksumDeltaMul
     * above. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField(piVar3 + 0xa42,uVar6);
    (*pcVar10)(&DAT_005a9068);
    uStack_88 = CONCAT31(SUBFIELD(uStack_88,1,undefined3),0xe);
    if (iStack_4c4 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
    }
    uStack_88 = 0xffffffff;
    if (iStack_2a0 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound();
    }
  }
  RegisterActiveObject(0, 0, (undefined4 *)0);
  *unaff_FS_OFFSET = uStack_90;
  return;
}

