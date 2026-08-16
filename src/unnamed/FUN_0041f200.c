/* FUN_0041f200 - 0x0041f200 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 39 argless PeekPacketChecksumState() calls (39 C : 39
 * orig).  Cells from tools/guard_cell_resolve.py over 0x41f200-0x41fcc0
 * plus a full read of the index arithmetic; the C is goto-shuffled at
 * the tail, so the last five sites were landmark-matched (the `cmp
 * eax,3` / `cmp eax,6` / `idiv` consumers pin +0x45354 / +0x6a7f94 /
 * &DAT_00796aa0 to the C's `== 3` / `< 6` / `% iVar8` tests, and the
 * two sites the C places before them are the else-branch's +0x475c8 /
 * 0x1a7930 pair) - a first draft zipped them in line order and had the
 * five cells rotated.
 *
 * The context arrives in EAX (`mov edi,eax` at 0x41f212), which the
 * decompile already names in_EAX and dereferences throughout.  Two cell
 * shapes needed reconstruction:
 *  - the per-category array ctx+0x595d8+k*0x224 (k in 0..7), indexed
 *    by (turnCounter / turnLimit) % 8 - and the divisor is a Peek result
 *    the C DISCARDED (lines ~45, ~127/130), now captured (iVar14-16);
 *  - the per-map/per-weather cells ctx + BASE + (weatherId*0xb +
 *    mapIdx)*0x7d28 + slot*0x224, BASE in {0x1a6810, 0x1a56f0, 0x1a8a50,
 *    0x1a7930, 0x1a45d0, 0x1a34b0}, mapIdx = byte ctx+0x475c4, slot from
 *    FUN_004217b0(0) & 7 - written in the exact idiom the 2026-07
 *    UnderLock sweep already used for the neighbouring
 *    PeekChecksumStateUnderLock sites in this same file, with the
 *    weatherId being the discarded +0x475c8 Peek immediately before each
 *    (captured, iVar13).
 * The rest are the turn/limit cells +0xeba98/+0x473a0, the per-turn
 * shot-parameter quartet +0x5af88/+0x5b1ac/+0x5b5f4/+0x5b3d0, the mode
 * word +0x4111c, three &DAT_00e9bed8 and the battle-mode/+0x6a7f94 pair.
 * This function assembles the per-turn broadcast that BeginNewTurn's
 * seeded values feed.
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
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
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
  iVar7 = PeekPacketChecksumState((void *)(in_EAX + 0xeba98));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = PeekPacketChecksumState((void *)(in_EAX + 0x473a0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar16 = iVar7 % iVar8 != 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar14 = PeekPacketChecksumState((void *)(in_EAX + 0x473a0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = PeekPacketChecksumState((void *)(in_EAX + 0x595d8 + (iVar7 / iVar14) % 8 * 0x224));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1c = PeekPacketChecksumState((void *)(in_EAX + 0x5af88));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_20 = PeekPacketChecksumState((void *)(in_EAX + 0x5b1ac));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8 = PeekPacketChecksumState((void *)(in_EAX + 0x5b5f4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_c = PeekPacketChecksumState((void *)(in_EAX + 0x5b3d0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = g_dwBroadcastEventCursor;
  if ((iVar8 == 3) && (!bVar16)) {
    local_20 = local_8 + local_20;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar9 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar9 < local_20) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar9 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_20 = local_20 - iVar9;
    }
    local_1c = local_c;
    if (local_20 < 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar9 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_20 = local_20 + iVar9;
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar9 = PeekPacketChecksumState((void *)(in_EAX + 0xeba98));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar10 = PeekPacketChecksumState((void *)(in_EAX + 0x473a0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar9 + 1) % iVar10 == 0) {
    local_c = _rand();
    local_c = local_c % 0x1b;
    iVar9 = _rand();
    local_8 = iVar9 % 0xb4;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar11 = PeekPacketChecksumState((void *)(in_EAX + 0x4111c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((uVar11 & 0x10000) != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = PeekPacketChecksumState((void *)(in_EAX + 0xeba98));
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
  (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = (char)local_1c;
  puVar1 = (undefined2 *)(&DAT_00e9aacd + g_dwBroadcastEventCursor);
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
  *puVar1 = (undefined2)local_20;
  puVar2 = &DAT_00e9aace + g_dwBroadcastEventCursor;
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
  *puVar2 = (undefined1)local_c;
  puVar2 = &DAT_00e9aacd + g_dwBroadcastEventCursor;
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
  *puVar2 = (undefined1)local_8;
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar15 = PeekPacketChecksumState((void *)(in_EAX + 0xeba98));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar16 = PeekPacketChecksumState((void *)(in_EAX + 0x473a0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState((void *)(in_EAX + 0x595d8 + (iVar15 + 1) / iVar16 % 8 * 0x224));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = uVar4;
  if ((iVar8 != 0) || (bVar16)) {
    puVar2 = &DAT_00e9aacd + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *puVar2 = 0xff;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    if ((iVar8 != 1) || (bVar16)) goto LAB_0041f7e9;
    uVar11 = FUN_004217b0(0);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar13 = PeekPacketChecksumState((void *)(in_EAX + 0x475c8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = (uVar11 & 7) * 0x224;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar9 = PeekPacketChecksumState((void *)((iVar13 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar8 + 0x1a6810 + in_EAX));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar13 = PeekPacketChecksumState((void *)(in_EAX + 0x475c8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar10 = PeekPacketChecksumState((void *)((iVar13 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar8 + 0x1a56f0 + in_EAX));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar9 - iVar10 < 1) {
      uStack00000004 = 1;
    }
    else {
      iVar9 = PeekChecksumStateUnderLock(in_EAX + 0x475c8);
      iVar9 = PeekChecksumStateUnderLock((iVar9 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar8 +
                           0x1a45d0 + in_EAX);
      iVar10 = PeekChecksumStateUnderLock(in_EAX + 0x475c8);
      iVar8 = PeekChecksumStateUnderLock((iVar10 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar8 +
                           0x1a34b0 + in_EAX);
      uStack00000004 = iVar9 - iVar8;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar13 = PeekPacketChecksumState((void *)(in_EAX + 0x475c8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    sVar6 = PeekPacketChecksumState((void *)((iVar13 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar8 + 0x1a56f0 + in_EAX));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = FUN_004217b0(1);
    (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 0;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    bVar5 = FUN_004217b0(2);
    (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = (bVar5 & 0x3f) + 0x40;
    psVar3 = (short *)(&DAT_00e9aacd + g_dwBroadcastEventCursor);
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *psVar3 = (short)(uVar11 % uStack00000004) + sVar6;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
LAB_0041fb05:
    (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 0xff;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
  }
  else {
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    uVar11 = FUN_004217b0(0);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar13 = PeekPacketChecksumState((void *)(in_EAX + 0x475c8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar9 = (uVar11 & 7) * 0x224;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar10 = PeekPacketChecksumState((void *)((iVar13 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar9 + 0x1a8a50 + in_EAX));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar13 = PeekPacketChecksumState((void *)(in_EAX + 0x475c8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar12 = PeekPacketChecksumState((void *)((iVar13 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar9 + 0x1a7930 + in_EAX));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar10 - iVar12 < 1) {
      local_8 = 1;
    }
    else {
      iVar10 = PeekChecksumStateUnderLock(in_EAX + 0x475c8);
      iVar10 = PeekChecksumStateUnderLock((iVar10 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar9 +
                            0x1a6810 + in_EAX);
      iVar12 = PeekChecksumStateUnderLock(in_EAX + 0x475c8);
      iVar9 = PeekChecksumStateUnderLock((iVar12 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar9 +
                           0x1a56f0 + in_EAX);
      local_8 = iVar10 - iVar9;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar13 = PeekPacketChecksumState((void *)(in_EAX + 0x475c8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    sVar6 = PeekPacketChecksumState((void *)((iVar13 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar9 + 0x1a45d0 + in_EAX));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = FUN_004217b0(1);
    (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 0;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    bVar5 = FUN_004217b0(2);
    (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = (bVar5 & 0x3f) + 0x40;
    psVar3 = (short *)(&DAT_00e9aacd + g_dwBroadcastEventCursor);
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *psVar3 = (short)(uVar11 % local_8) + sVar6;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
LAB_0041f7e9:
    (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 0xff;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    if ((iVar8 != 2) || (bVar16)) goto LAB_0041fb05;
    uVar11 = FUN_004217b0(0);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar13 = PeekPacketChecksumState((void *)(in_EAX + 0x475c8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = (uVar11 & 7) * 0x224;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar9 = PeekPacketChecksumState((void *)((iVar13 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar8 + 0x1a34b0 + in_EAX));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar13 = PeekPacketChecksumState((void *)(in_EAX + 0x475c8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar10 = PeekPacketChecksumState((void *)((iVar13 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar8 + 0x1a34b0 + in_EAX));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar9 - iVar10 < 1) {
      uStack00000004 = 1;
    }
    else {
      iVar9 = PeekChecksumStateUnderLock(in_EAX + 0x475c8);
      iVar9 = PeekChecksumStateUnderLock((iVar9 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar8 +
                           0x1a8a50 + in_EAX);
      iVar10 = PeekChecksumStateUnderLock(in_EAX + 0x475c8);
      iVar8 = PeekChecksumStateUnderLock((iVar10 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar8 +
                           0x1a7930 + in_EAX);
      uStack00000004 = iVar9 - iVar8;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar13 = PeekPacketChecksumState((void *)(in_EAX + 0x475c8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    sVar6 = PeekPacketChecksumState((void *)((iVar13 * 0xb + (uint)*(byte *)(in_EAX + 0x475c4)) * 0x7d28 + iVar8 + 0x1a7930 + in_EAX));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = FUN_004217b0(1);
    (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 0;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    bVar5 = FUN_004217b0(2);
    (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = (bVar5 & 0x3f) + 0x40;
    psVar3 = (short *)(&DAT_00e9aacd + g_dwBroadcastEventCursor);
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *psVar3 = (short)(uVar11 % uStack00000004) + sVar6;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar8 == 3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = PeekPacketChecksumState((void *)(g_clientContext + 0x6a7f94));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar8 < 6) {
      (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 0;
      g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = PeekPacketChecksumState((void *)&DAT_00796aa0);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar9 = _rand();
      (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = (char)(iVar9 % iVar8);
      g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
      iVar8 = _rand();
      *(short *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = (short)iVar8;
      g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
      goto LAB_0041fd16;
    }
  }
  (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 0xff;
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
LAB_0041fd16:
  uVar13 = g_dwBroadcastEventCursor - iVar7;
  puVar14 = (undefined4 *)(&g_abBroadcastEventBuffer + iVar7);
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

