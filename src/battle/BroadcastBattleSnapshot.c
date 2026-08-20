/* BroadcastBattleSnapshot - 0x004dc200 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 11 argless PeekPacketChecksumState() calls (peek status
 * "clean", 11 C : 11 orig).  Cells from tools/guard_cell_resolve.py over
 * 0x4dc200-0x4dc556; straight-line plus two do-whiles, so the sites
 * order-zip.
 *
 * Four cells are inside the two loops and are index-scaled: EBX is the
 * loop counter (`xor ebx,ebx` at 0x4dc398 and 0x4dc42f, `add ebx,0x224`
 * at 0x4dc417/0x4dc4a8), which is exactly the C's own iVar5 - same
 * initial value, same 0x224 step, same 0x2ad0 bound - so the cells are
 * g_clientContext + base + iVar5 with base 0x23bd8/0x266a8 in the first
 * loop and 0x2e718/0x311e8 in the second.  The stride being 0x224 says
 * these are per-slot CValueGuard arrays walked one cell per iteration.
 * The other seven cells are fixed g_clientContext offsets plus one
 * &DAT_00e525e8.
 */
#include "ghidra_types.h"


void BroadcastBattleSnapshot(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  int iVar5;
  
  QueueBroadcastEvent(0x8400,(int)&g_replayContext);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState((void *)&DAT_00e525e8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined2 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar3;
  iVar2 = g_dwBroadcastEventCursor;
  iVar5 = g_clientContext;
  puVar1 = (undefined4 *)(&DAT_00e9aace + g_dwBroadcastEventCursor);
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
  *puVar1 = *(undefined4 *)(g_clientContext + 0x2331c);
  *(undefined4 *)(&DAT_00e9aad2 + iVar2) = *(undefined4 *)(iVar5 + 0x23320);
  *(undefined4 *)(&DAT_00e9aad6 + iVar2) = *(undefined4 *)(iVar5 + 0x23324);
  *(undefined4 *)(&DAT_00e9aada + iVar2) = *(undefined4 *)(iVar5 + 0x23328);
  iVar2 = g_dwBroadcastEventCursor;
  puVar1 = (undefined4 *)(&DAT_00e9aadc + g_dwBroadcastEventCursor);
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 0x10;
  *puVar1 = *(undefined4 *)(iVar5 + 0x23330);
  *(undefined4 *)(&DAT_00e9aae0 + iVar2) = *(undefined4 *)(iVar5 + 0x23334);
  *(undefined4 *)(&DAT_00e9aae4 + iVar2) = *(undefined4 *)(iVar5 + 0x23338);
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 0xc;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x239b4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined2 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar3;
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0x23348));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0x2356c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0x23790));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
  iVar5 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0x23bd8 + iVar5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0x266a8 + iVar5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    iVar5 = iVar5 + 0x224;
  } while (iVar5 < 0x2ad0);
  iVar5 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0x2e718 + iVar5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0x311e8 + iVar5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    iVar5 = iVar5 + 0x224;
  } while (iVar5 < 0x2ad0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0x39258));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0x3947c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
  if (param_1 == -1) {
    BroadcastQueuedEvent();
    return;
  }
  FUN_004e7140();
  return;
}

