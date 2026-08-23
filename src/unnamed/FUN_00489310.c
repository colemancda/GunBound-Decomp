/* FUN_00489310 - 0x00489310 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 8 argless PeekPacketChecksumState() calls (8 C : 8 orig,
 * goto-free zip), from tools/guard_cell_resolve.py over
 * 0x489310-0x4894b8.  Cell-for-cell twin of FUN_004aa520: &DAT_00794bf0,
 * &DAT_00e9bed8, then two rounds of g_clientContext+0x5b1ac / +0x5af88 /
 * &DAT_00e9ba40.  All plain globals, no bases or chained returns.
 */
#include "ghidra_types.h"


void __fastcall FUN_00489310(int param_1)

{
  int iVar1;
  
  *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)&DAT_00794bf0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar1 < *(int *)(param_1 + 0x40)) {
    *(undefined1 *)(param_1 + 0x14) = 1;
  }
  *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x44) + 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x44) % iVar1;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(g_clientContext + 0x5b1ac));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(g_clientContext + 0x5af88));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)&DAT_00e9ba40);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = FloatToInt64();
  *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + iVar1;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(g_clientContext + 0x5b1ac));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(g_clientContext + 0x5af88));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)&DAT_00e9ba40);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = FloatToInt64();
  *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + (-5 - iVar1);
  return;
}

