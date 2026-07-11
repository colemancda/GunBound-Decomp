/* BroadcastBattleSnapshot - 0x004dc200 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void BroadcastBattleSnapshot(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  int iVar5;
  
  QueueBroadcastEvent(0x8400);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
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
  uVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined2 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar3;
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
  iVar5 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    iVar5 = iVar5 + 0x224;
  } while (iVar5 < 0x2ad0);
  iVar5 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    iVar5 = iVar5 + 0x224;
  } while (iVar5 < 0x2ad0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
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

