/* FUN_0041f200 - 0x0041f200 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0041f200(void)

{
  undefined2 *puVar1;
  undefined *puVar2;
  short *psVar3;
  undefined1 uVar4;
  byte bVar5;
  short sVar6;
  int in_EAX;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  undefined4 *puVar14;
  undefined4 *puVar15;
  bool bVar16;
  uint uStack00000004;
  int local_20;
  int local_1c;
  int local_c;
  uint local_8;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar16 = iVar7 % iVar8 != 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1c = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_20 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_c = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = g_replayEventCursor;
  if ((iVar8 == 3) && (!bVar16)) {
    local_20 = local_8 + local_20;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar9 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar9 < local_20) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar9 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_20 = local_20 - iVar9;
    }
    local_1c = local_c;
    if (local_20 < 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar9 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_20 = local_20 + iVar9;
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar9 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar10 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar9 + 1) % iVar10 == 0) {
    local_c = _rand();
    local_c = local_c % 0x1b;
    iVar9 = _rand();
    local_8 = iVar9 % 0xb4;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar11 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((uVar11 & 0x10000) != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = uVar11 & 0x80000007;
    if ((int)uVar11 < 0) {
      uVar11 = (uVar11 - 1 | 0xfffffff8) + 1;
    }
    local_1c = local_1c + *(int *)(&DAT_0056d440 + uVar11 * 4);
    if (local_1c < 0x1b) {
      if (local_1c < 0) {
        local_1c = 0;
      }
    }
    else {
      local_1c = 0x1a;
    }
  }
  (&g_replayEventBuffer)[g_replayEventCursor] = (char)local_1c;
  puVar1 = (undefined2 *)(&DAT_00e9aacd + g_replayEventCursor);
  g_replayEventCursor = g_replayEventCursor + 1;
  *puVar1 = (undefined2)local_20;
  puVar2 = &DAT_00e9aace + g_replayEventCursor;
  g_replayEventCursor = g_replayEventCursor + 2;
  *puVar2 = (undefined1)local_c;
  puVar2 = &DAT_00e9aacd + g_replayEventCursor;
  g_replayEventCursor = g_replayEventCursor + 1;
  *puVar2 = (undefined1)local_8;
  g_replayEventCursor = g_replayEventCursor + 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (&g_replayEventBuffer)[g_replayEventCursor] = uVar4;
  if ((iVar8 != 0) || (bVar16)) {
    puVar2 = &DAT_00e9aacd + g_replayEventCursor;
    g_replayEventCursor = g_replayEventCursor + 1;
    *puVar2 = 0xff;
    g_replayEventCursor = g_replayEventCursor + 1;
    if ((iVar8 != 1) || (bVar16)) goto LAB_0041f7e9;
    uVar11 = FUN_004217b0(0);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = (uVar11 & 7) * 0x224;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar9 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar10 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar9 - iVar10 < 1) {
      uStack00000004 = 1;
    }
    else {
      iVar9 = FUN_0040a4d0(in_EAX + 0x475c8);
      iVar9 = FUN_0040a4d0((iVar9 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar8 +
                           0x1a45d0 + in_EAX);
      iVar10 = FUN_0040a4d0(in_EAX + 0x475c8);
      iVar8 = FUN_0040a4d0((iVar10 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar8 +
                           0x1a34b0 + in_EAX);
      uStack00000004 = iVar9 - iVar8;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    sVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = FUN_004217b0(1);
    (&g_replayEventBuffer)[g_replayEventCursor] = 0;
    g_replayEventCursor = g_replayEventCursor + 1;
    bVar5 = FUN_004217b0(2);
    (&g_replayEventBuffer)[g_replayEventCursor] = (bVar5 & 0x3f) + 0x40;
    psVar3 = (short *)(&DAT_00e9aacd + g_replayEventCursor);
    g_replayEventCursor = g_replayEventCursor + 1;
    *psVar3 = (short)(uVar11 % uStack00000004) + sVar6;
    g_replayEventCursor = g_replayEventCursor + 2;
LAB_0041fb05:
    (&g_replayEventBuffer)[g_replayEventCursor] = 0xff;
    g_replayEventCursor = g_replayEventCursor + 1;
  }
  else {
    g_replayEventCursor = g_replayEventCursor + 1;
    uVar11 = FUN_004217b0(0);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar9 = (uVar11 & 7) * 0x224;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar10 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar12 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar10 - iVar12 < 1) {
      local_8 = 1;
    }
    else {
      iVar10 = FUN_0040a4d0(in_EAX + 0x475c8);
      iVar10 = FUN_0040a4d0((iVar10 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar9 +
                            0x1a6810 + in_EAX);
      iVar12 = FUN_0040a4d0(in_EAX + 0x475c8);
      iVar9 = FUN_0040a4d0((iVar12 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar9 +
                           0x1a56f0 + in_EAX);
      local_8 = iVar10 - iVar9;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    sVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = FUN_004217b0(1);
    (&g_replayEventBuffer)[g_replayEventCursor] = 0;
    g_replayEventCursor = g_replayEventCursor + 1;
    bVar5 = FUN_004217b0(2);
    (&g_replayEventBuffer)[g_replayEventCursor] = (bVar5 & 0x3f) + 0x40;
    psVar3 = (short *)(&DAT_00e9aacd + g_replayEventCursor);
    g_replayEventCursor = g_replayEventCursor + 1;
    *psVar3 = (short)(uVar11 % local_8) + sVar6;
    g_replayEventCursor = g_replayEventCursor + 2;
LAB_0041f7e9:
    (&g_replayEventBuffer)[g_replayEventCursor] = 0xff;
    g_replayEventCursor = g_replayEventCursor + 1;
    if ((iVar8 != 2) || (bVar16)) goto LAB_0041fb05;
    uVar11 = FUN_004217b0(0);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = (uVar11 & 7) * 0x224;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar9 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar10 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar9 - iVar10 < 1) {
      uStack00000004 = 1;
    }
    else {
      iVar9 = FUN_0040a4d0(in_EAX + 0x475c8);
      iVar9 = FUN_0040a4d0((iVar9 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar8 +
                           0x1a8a50 + in_EAX);
      iVar10 = FUN_0040a4d0(in_EAX + 0x475c8);
      iVar8 = FUN_0040a4d0((iVar10 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar8 +
                           0x1a7930 + in_EAX);
      uStack00000004 = iVar9 - iVar8;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    sVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = FUN_004217b0(1);
    (&g_replayEventBuffer)[g_replayEventCursor] = 0;
    g_replayEventCursor = g_replayEventCursor + 1;
    bVar5 = FUN_004217b0(2);
    (&g_replayEventBuffer)[g_replayEventCursor] = (bVar5 & 0x3f) + 0x40;
    psVar3 = (short *)(&DAT_00e9aacd + g_replayEventCursor);
    g_replayEventCursor = g_replayEventCursor + 1;
    *psVar3 = (short)(uVar11 % uStack00000004) + sVar6;
    g_replayEventCursor = g_replayEventCursor + 2;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar8 == 3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar8 < 6) {
      (&g_replayEventBuffer)[g_replayEventCursor] = 0;
      g_replayEventCursor = g_replayEventCursor + 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar9 = _rand();
      (&g_replayEventBuffer)[g_replayEventCursor] = (char)(iVar9 % iVar8);
      g_replayEventCursor = g_replayEventCursor + 1;
      iVar8 = _rand();
      *(short *)(&g_replayEventBuffer + g_replayEventCursor) = (short)iVar8;
      g_replayEventCursor = g_replayEventCursor + 2;
      goto LAB_0041fd16;
    }
  }
  (&g_replayEventBuffer)[g_replayEventCursor] = 0xff;
  g_replayEventCursor = g_replayEventCursor + 1;
LAB_0041fd16:
  uVar13 = g_replayEventCursor - iVar7;
  puVar14 = (undefined4 *)(&g_replayEventBuffer + iVar7);
  puVar15 = (undefined4 *)(in_EAX + 0xeba78);
  for (uVar11 = uVar13 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
    *puVar15 = *puVar14;
    puVar14 = puVar14 + 1;
    puVar15 = puVar15 + 1;
  }
  for (uVar13 = uVar13 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
    *(undefined1 *)puVar15 = *(undefined1 *)puVar14;
    puVar14 = (undefined4 *)((int)puVar14 + 1);
    puVar15 = (undefined4 *)((int)puVar15 + 1);
  }
  return;
}

