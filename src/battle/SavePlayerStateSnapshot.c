/* SavePlayerStateSnapshot - 0x00463c80 in the original binary.
 *
 * RENAMED (2026-08-13, from FUN_00463c80). Saves seven guarded state
 * cells of one player record (+0x90c/+0xb30/+0x1c54/+0x6fd4/+0x4d90/
 * +0x51d8/+0x4948) into the record's snapshot block (+0xc2b0..+0xcfb0).
 * Inverse of RestorePlayerStateSnapshot, which copies the same seven
 * cells back.  Its caller FUN_0043c860 runs it for all 8 slots before
 * a simulation pass and restores afterwards.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 7 argless PeekPacketChecksumState() calls (7 C : 7 orig,
 * goto-free zip), from tools/guard_cell_resolve.py over
 * 0x463c80-0x463e50.  This is RestorePlayerStateSnapshot's INVERSE: that function
 * reads the high cells (+0xc2b0..+0xcfb0) and writes the low ones; this
 * one reads the low cells (+0x90c/+0xb30/+0x1c54/+0x6fd4/+0x4d90/
 * +0x51d8/+0x4948) and writes the same high ones - a save/restore pair
 * over the identical seven-cell set, each Peek sitting beside the
 * already-fixed Encode of its high twin.
 */
#include "ghidra_types.h"


void SavePlayerStateSnapshot(void)

{
  undefined4 uVar1;
  int unaff_ESI;
  
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at 0x463ca2/
   * 0x463ccd/0x463cf2 (edi loaded from esi+0xc2b0/esi+0xc4d4/esi+0xc6f8).
   * esi is this file's own `unaff_ESI` (the base already used for the
   * byte writes below, e.g. `unaff_ESI + 0xc91c`); these 3 offsets are an
   * array of 3 CValueGuard cells (stride 0x224 = sizeof(CValueGuard)) at
   * unaff_ESI+0xc2b0. `unaff_ESI` is plain `int`, so `unaff_ESI + N` is
   * already byte-precise. See tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_ESI + 0x90c));
  EncodeOutgoingPacketField(unaff_ESI + 0xc2b0, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_ESI + 0xb30));
  EncodeOutgoingPacketField(unaff_ESI + 0xc4d4, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_ESI + 0x1c54));
  EncodeOutgoingPacketField(unaff_ESI + 0xc6f8, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  *(undefined4 *)(unaff_ESI + 0xc91c) = *(undefined4 *)(unaff_ESI + 0x24);
  *(undefined4 *)(unaff_ESI + 0xc920) = *(undefined4 *)(unaff_ESI + 0x28);
  *(undefined4 *)(unaff_ESI + 0xc928) = *(undefined4 *)(unaff_ESI + 0x30);
  *(undefined4 *)(unaff_ESI + 0xc924) = *(undefined4 *)(unaff_ESI + 0x2c);
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at 0x463dc3/
   * 0x463de8/0x463e0d/0x463e32 (edi loaded from esi+0xc944/esi+0xcb68/
   * esi+0xcd8c/esi+0xcfb0). Same `unaff_ESI` base as above; a second array
   * of 4 CValueGuard cells (stride 0x224) at unaff_ESI+0xc944. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_ESI + 0x6fd4));
  EncodeOutgoingPacketField(unaff_ESI + 0xc944, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_ESI + 0x4d90));
  EncodeOutgoingPacketField(unaff_ESI + 0xcb68, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_ESI + 0x51d8));
  EncodeOutgoingPacketField(unaff_ESI + 0xcd8c, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_ESI + 0x4948));
  EncodeOutgoingPacketField(unaff_ESI + 0xcfb0, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return;
}

