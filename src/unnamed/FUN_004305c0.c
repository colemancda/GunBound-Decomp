/* FUN_004305c0 - 0x004305c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x0043089b) */
/* WARNING: Removing unreachable block (ram,0x004309a5) */
/* WARNING: Removing unreachable block (ram,0x00430a35) */
/* WARNING: Removing unreachable block (ram,0x00430a76) */

void FUN_004305c0(void)

{
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
  int in_stack_00000020;
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
    FUN_00454dc0();
    *piVar3 = (int)&PTR_FUN_00556008;
    piVar3[0xfe8] = 0;
  }
  local_4 = 0xffffffff;
  if (*(char *)(DAT_005b3484 + 0x45578) == '\0') {
    piVar3[6] = 0x19c8;
    piVar3[0xe] = 0x19ca;
    piVar3[0xe25] = 0x19c9;
    iVar4 = FindPreloadedTextureByName();
    piVar3[7] = iVar4;
    piVar3[0xe26] = s_flame_00553d2c._0_4_;
    *(undefined2 *)(piVar3 + 0xe27) = s_flame_00553d2c._4_2_;
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
    if (*(char *)(DAT_005b3484 + 0x45578) == '\x01') {
      piVar3[6] = 6000;
      piVar3[0xe] = 0x17d4;
      piVar3[0xe25] = 8000;
      iVar4 = FindPreloadedTextureByName();
      pcVar9 = (code *)EnterCriticalSection;
      piVar3[7] = iVar4;
      piVar3[0xe26] = s_flameevent1_00553e2c._0_4_;
      piVar3[0xe27] = s_flameevent1_00553e2c._4_4_;
      piVar3[0xe28] = s_flameevent1_00553e2c._8_4_;
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
  piVar3[0xfe7] = in_stack_00000020;
  *(byte *)(piVar3 + 0xf) = (byte)local_4 & 7;
  (*pcVar9)();
  EncodeOutgoingPacketField();
  (*pcVar10)();
  (*pcVar9)();
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  (*pcVar10)();
  (*pcVar9)();
  EncodeOutgoingPacketField();
  (*pcVar10)();
  (*pcVar9)();
  EncodeOutgoingPacketField();
  (*pcVar10)();
  (*pcVar9)();
  EncodeOutgoingPacketField();
  (*pcVar10)();
  (*pcVar9)();
  FUN_0053753c();
  EncodeOutgoingPacketField();
  (*pcVar10)();
  (*pcVar9)();
  FUN_0053753c();
  EncodeOutgoingPacketField();
  (*pcVar10)();
  (*pcVar9)();
  FUN_0053753c();
  EncodeOutgoingPacketField();
  (*pcVar10)();
  (*pcVar9)();
  FUN_0053753c();
  EncodeOutgoingPacketField();
  (*pcVar10)();
  (*pcVar9)();
  FUN_0053753c();
  EncodeOutgoingPacketField();
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
  (*pcVar9)();
  FUN_004064a0();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar9)();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar9)();
  FUN_004064a0();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar9)();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puVar14 = &DAT_005a9068;
  piVar3[0xfe4] = 4;
  piVar3[0xfe5] = iStack_48;
  (*pcVar9)();
  EncodeOutgoingPacketField();
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
  (*pcVar9)();
  EncodeOutgoingPacketField();
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
    Replay_AppendEvent();
    (&g_replayEventBuffer)[g_replayEventCursor] = 4;
    puVar13 = &DAT_00e9aacd + g_replayEventCursor;
    g_replayEventCursor = g_replayEventCursor + 1;
    *puVar13 = uStack_80;
    puVar13 = &DAT_00e9aacd + g_replayEventCursor;
    g_replayEventCursor = g_replayEventCursor + 1;
    *puVar13 = uStack_7c;
    puVar13 = &DAT_00e9aacd + g_replayEventCursor;
    g_replayEventCursor = g_replayEventCursor + 1;
    *puVar13 = 0xff;
    puVar13 = &DAT_00e9aacd + g_replayEventCursor;
    g_replayEventCursor = g_replayEventCursor + 1;
    *puVar13 = (undefined1)uStack_78;
    puVar1 = (undefined4 *)(&DAT_00e9aacd + g_replayEventCursor);
    g_replayEventCursor = g_replayEventCursor + 1;
    *puVar1 = uStack_70;
    puVar1 = (undefined4 *)(&DAT_00e9aad0 + g_replayEventCursor);
    g_replayEventCursor = g_replayEventCursor + 4;
    *puVar1 = uStack_6c;
    puVar1 = (undefined4 *)(&DAT_00e9aad0 + g_replayEventCursor);
    g_replayEventCursor = g_replayEventCursor + 4;
    *puVar1 = uStack_68;
    puVar1 = (undefined4 *)(&DAT_00e9aad0 + g_replayEventCursor);
    g_replayEventCursor = g_replayEventCursor + 4;
    *puVar1 = 0xffffffff;
    puVar13 = &DAT_00e9aad0 + g_replayEventCursor;
    g_replayEventCursor = g_replayEventCursor + 4;
    *puVar13 = 0xff;
    puVar13 = &DAT_00e9aacd + g_replayEventCursor;
    g_replayEventCursor = g_replayEventCursor + 1;
    *puVar13 = 0xff;
    g_replayEventCursor = g_replayEventCursor + 1;
    (*pcVar9)();
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar6;
    g_replayEventCursor = g_replayEventCursor + 4;
    (*pcVar9)();
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar6;
    g_replayEventCursor = g_replayEventCursor + 4;
    (*pcVar9)();
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar6;
    g_replayEventCursor = g_replayEventCursor + 4;
    (*pcVar9)();
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar6;
    g_replayEventCursor = g_replayEventCursor + 4;
    (*pcVar9)();
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar6;
    g_replayEventCursor = g_replayEventCursor + 4;
    (*pcVar9)();
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar6;
    g_replayEventCursor = g_replayEventCursor + 4;
    Replay_FlushEvent();
  }
  FUN_0041da80();
  iVar4 = GetPlayerRecordBySlot();
  if ((iVar4 != 0) && (cVar2 = FUN_004065a0(), cVar2 != '\0')) {
    FUN_0040a8c0();
    uStack_88 = 1;
    FUN_0040afb0();
    uStack_88 = 0xffffffff;
    if (uStack_90c != 0) {
      FUN_0040a240();
      FUN_0040b540();
    }
    FUN_0040a8c0();
    uStack_88 = 2;
    FUN_0040afb0();
    uStack_88 = 0xffffffff;
    if (uStack_90c != 0) {
      FUN_0040a240();
      FUN_0040b540();
    }
    FUN_0040a8c0();
    uStack_88 = 3;
    FUN_0040afb0();
    uStack_88 = 0xffffffff;
    if (uStack_90c != 0) {
      FUN_0040a240();
      FUN_0040b540();
    }
  }
  cVar2 = FUN_004065a0();
  pcVar10 = (code *)LeaveCriticalSection;
  pcVar9 = (code *)EnterCriticalSection;
  if (cVar2 == '\x01') {
    FUN_0040a7d0();
    pcVar9 = (code *)EnterCriticalSection;
    uStack_88 = 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    pcVar10 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0040a8c0();
    uStack_88._0_1_ = 5;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    PeekPacketChecksumState();
    EncodeOutgoingPacketField();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_88 = CONCAT31(uStack_88._1_3_,4);
    if (uStack_90c != 0) {
      FUN_0040a240();
      FUN_0040b540();
      pcVar10 = (code *)LeaveCriticalSection;
    }
    uStack_88 = 0xffffffff;
    if (iStack_6e8 != 0) {
      FUN_0040a240();
      FUN_0040b540();
      pcVar10 = (code *)LeaveCriticalSection;
    }
    FUN_0040a7d0();
    uStack_88 = 6;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar10)();
    FUN_0040a8c0();
    uStack_8c = 7;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    PeekPacketChecksumState();
    EncodeOutgoingPacketField();
    (*pcVar10)();
    uStack_90 = CONCAT31(uStack_90._1_3_,6);
    if (iStack_6f0 != 0) {
      FUN_0040a240();
      FUN_0040b540();
      pcVar10 = (code *)LeaveCriticalSection;
    }
    uStack_90 = 0xffffffff;
    if (uStack_914 != 0) {
      FUN_0040a240();
      FUN_0040b540();
      pcVar10 = (code *)LeaveCriticalSection;
    }
    FUN_0040a7d0();
    uStack_90 = 8;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puVar14 = (undefined *)PeekPacketChecksumState();
    (*pcVar10)();
    FUN_0040a8c0();
    uStack_94 = 9;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    PeekPacketChecksumState();
    EncodeOutgoingPacketField();
    (*pcVar10)();
    uStack_88 = CONCAT31(uStack_88._1_3_,8);
    if (iStack_6e8 != 0) {
      FUN_0040a240();
      FUN_0040b540();
      pcVar10 = (code *)LeaveCriticalSection;
    }
    uStack_88 = 0xffffffff;
    if (uStack_90c != 0) {
      FUN_0040a240();
      FUN_0040b540();
      pcVar10 = (code *)LeaveCriticalSection;
    }
  }
  cVar2 = FUN_00406610();
  if (cVar2 != '\0') {
    (*pcVar9)();
    iVar4 = PeekPacketChecksumState();
    (*pcVar10)();
    FUN_0040a7d0();
    uStack_90 = 10;
    (*pcVar9)();
    PeekPacketChecksumState();
    puVar13 = &DAT_005a9068;
    (*pcVar10)();
    FUN_0040a8c0(puVar14);
    uStack_98 = 0xb;
    (*pcVar9)();
    PeekPacketChecksumState();
    EncodeOutgoingPacketField();
    puVar14 = &DAT_005a9068;
    (*pcVar10)();
    uStack_a0 = CONCAT31(uStack_a0._1_3_,10);
    if (iStack_700 != 0) {
      FUN_0040a240();
      FUN_0040b540(&stack0xfffff6b8);
    }
    uStack_a0 = 0xffffffff;
    FUN_0040a240();
    FUN_0040b540(&stack0xfffff6b8);
    pcVar10 = (code *)LeaveCriticalSection;
    (*pcVar9)(&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0040a7d0(piVar3 + 0x9b9,&stack0xfffff6c0,puVar13);
    uStack_a8 = 0xc;
    (*pcVar9)(&DAT_005a9068);
    PeekPacketChecksumState();
    puVar12 = &DAT_005a9068;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0040a8c0(puVar13,auStack_724,puVar14);
    uStack_b0 = 0xd;
    (*pcVar9)(&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar6);
    puVar14 = &DAT_005a9068;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_b8 = CONCAT31(uStack_b8._1_3_,0xc);
    if (iStack_718 != 0) {
      FUN_0040a240();
      FUN_0040b540(&stack0xfffff6a0);
      pcVar10 = (code *)LeaveCriticalSection;
    }
    uStack_b8 = 0xffffffff;
    if (iVar4 != 0) {
      FUN_0040a240();
      FUN_0040b540(&stack0xfffff6a0);
      pcVar10 = (code *)LeaveCriticalSection;
    }
    (*pcVar9)(&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar10)(&DAT_005a9068);
    FUN_0040a7d0(piVar3 + 0xa42,auStack_2ec,puVar12);
    uStack_c0 = 0xe;
    (*pcVar9)(&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar10)(&DAT_005a9068);
    FUN_0040a8c0(puVar12,auStack_518,puVar14);
    uStack_c8 = 0xf;
    (*pcVar9)(&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar6);
    (*pcVar10)(&DAT_005a9068);
    uStack_88 = CONCAT31(uStack_88._1_3_,0xe);
    if (iStack_4c4 != 0) {
      FUN_0040a240();
      FUN_0040b540();
    }
    uStack_88 = 0xffffffff;
    if (iStack_2a0 != 0) {
      FUN_0040a240();
      FUN_0040b540();
    }
  }
  RegisterActiveObject();
  *unaff_FS_OFFSET = uStack_90;
  return;
}

