/* RestorePlayerStateSnapshot - 0x00463e50 in the original binary.
 *
 * RENAMED (2026-08-13, from FUN_00463e50). Restores the seven guarded
 * state cells SavePlayerStateSnapshot saved (snapshot block
 * +0xc2b0..+0xcfb0 back into +0x90c/+0xb30/+0x1c54/+0x6fd4/+0x4d90/
 * +0x51d8/+0x4948), then re-derives dependent state: it re-scrambles
 * the GuardedBool block and calls AlignMobileToTerrain so the tilt
 * matches the restored position.  Run for all 8 slots by FUN_0043c860
 * after its simulation pass.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 9 argless PeekPacketChecksumState() calls (peek status
 * "clean", 9 C : 9 orig), from tools/guard_cell_resolve.py over
 * 0x463e50-0x46408a.  Straight-line, so the sites order-zip.
 *
 * The function is a pure copy loop: each Peek reads a cell high in the
 * object (+0xc2b0 / +0xc4d4 / +0xc6f8 / +0xc944 / +0xcb68 / +0xcd8c /
 * +0xcfb0, plus +0x90c and +0xb30) and the Encode on the next line
 * writes it to a low one.  All of them share the base unaff_ESI, which
 * the 2026-07-15 Encode sweep already established for the write side -
 * so every Peek here sits directly beside an Encode whose base was
 * derived independently.
 */
#include "ghidra_types.h"


void RestorePlayerStateSnapshot(void)

{
  undefined4 uVar1;
  int unaff_ESI;
  
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at 0x463e72/
   * 0x463e99/0x463ebe/0x463edf/0x463f04/0x463fd5/0x464000/0x464025/
   * 0x46404a (edi loaded from esi+0x90c/esi+0x15e4/esi+0xb30/esi+0x1808/
   * esi+0x1c54/esi+0x6fd4/esi+0x4d90/esi+0x51d8/esi+0x4948 respectively).
   * esi is this file's own `unaff_ESI` (the base already used for the
   * byte copies below, e.g. `unaff_ESI + 0x24`); `unaff_ESI` is plain
   * `int`, so `unaff_ESI + N` is already byte-precise. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_ESI + 0xc2b0));
  EncodeOutgoingPacketField(unaff_ESI + 0x90c, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_ESI + 0x90c));
  EncodeOutgoingPacketField(unaff_ESI + 0x15e4, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_ESI + 0xc4d4));
  EncodeOutgoingPacketField(unaff_ESI + 0xb30, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_ESI + 0xb30));
  EncodeOutgoingPacketField(unaff_ESI + 0x1808, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_ESI + 0xc6f8));
  EncodeOutgoingPacketField(unaff_ESI + 0x1c54, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  *(undefined4 *)(unaff_ESI + 0x24) = *(undefined4 *)(unaff_ESI + 0xc91c);
  *(undefined4 *)(unaff_ESI + 0x28) = *(undefined4 *)(unaff_ESI + 0xc920);
  *(undefined4 *)(unaff_ESI + 0x30) = *(undefined4 *)(unaff_ESI + 0xc928);
  *(undefined4 *)(unaff_ESI + 0x2c) = *(undefined4 *)(unaff_ESI + 0xc924);
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_ESI + 0xc944));
  EncodeOutgoingPacketField(unaff_ESI + 0x6fd4, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  AlignMobileToTerrain(unaff_ESI);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_ESI + 0xcb68));
  EncodeOutgoingPacketField(unaff_ESI + 0x4d90, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_ESI + 0xcd8c));
  EncodeOutgoingPacketField(unaff_ESI + 0x51d8, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_ESI + 0xcfb0));
  EncodeOutgoingPacketField(unaff_ESI + 0x4948, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return;
}

