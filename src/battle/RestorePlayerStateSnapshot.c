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
 * writes it to a low one.  All of them share the base regEsi, which
 * the 2026-07-15 Encode sweep already established for the write side -
 * so every Peek here sits directly beside an Encode whose base was
 * derived independently.
 */
#include "ghidra_types.h"


void RestorePlayerStateSnapshot(int regEsi)

{
  undefined4 uVar1;
  
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at 0x463e72/
   * 0x463e99/0x463ebe/0x463edf/0x463f04/0x463fd5/0x464000/0x464025/
   * 0x46404a (edi loaded from esi+0x90c/esi+0x15e4/esi+0xb30/esi+0x1808/
   * esi+0x1c54/esi+0x6fd4/esi+0x4d90/esi+0x51d8/esi+0x4948 respectively).
   * esi is this file's own `regEsi` (the base already used for the
   * byte copies below, e.g. `regEsi + 0x24`); `regEsi` is plain
   * `int`, so `regEsi + N` is already byte-precise. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(regEsi + 0xc2b0));
  EncodeOutgoingPacketField(regEsi + 0x90c, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(regEsi + 0x90c));
  EncodeOutgoingPacketField(regEsi + 0x15e4, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(regEsi + 0xc4d4));
  EncodeOutgoingPacketField(regEsi + 0xb30, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(regEsi + 0xb30));
  EncodeOutgoingPacketField(regEsi + 0x1808, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(regEsi + 0xc6f8));
  EncodeOutgoingPacketField(regEsi + 0x1c54, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  *(undefined4 *)(regEsi + 0x24) = *(undefined4 *)(regEsi + 0xc91c);
  *(undefined4 *)(regEsi + 0x28) = *(undefined4 *)(regEsi + 0xc920);
  *(undefined4 *)(regEsi + 0x30) = *(undefined4 *)(regEsi + 0xc928);
  *(undefined4 *)(regEsi + 0x2c) = *(undefined4 *)(regEsi + 0xc924);
  CopyGuardedBool((byte *)(regEsi + 0xbfbe),(byte *)(regEsi + 0xc92c));
  CopyGuardedBool((byte *)(regEsi + 0xbfc1),(byte *)(regEsi + 0xc92f));
  CopyGuardedBool((byte *)(regEsi + 0xbfc4),(byte *)(regEsi + 0xc932));
  CopyGuardedBool((byte *)(regEsi + 0xbfc7),(byte *)(regEsi + 0xc935));
  CopyGuardedBool((byte *)(regEsi + 0xbfca),(byte *)(regEsi + 0xc938));
  CopyGuardedBool((byte *)(regEsi + 0xbfcd),(byte *)(regEsi + 0xc93b));
  CopyGuardedBool((byte *)(regEsi + 0xbfd0),(byte *)(regEsi + 0xc93e));
  CopyGuardedBool((byte *)(regEsi + 0x8bb7),(byte *)(regEsi + 0xc941));
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(regEsi + 0xc944));
  EncodeOutgoingPacketField(regEsi + 0x6fd4, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  AlignMobileToTerrain(regEsi);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(regEsi + 0xcb68));
  EncodeOutgoingPacketField(regEsi + 0x4d90, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(regEsi + 0xcd8c));
  EncodeOutgoingPacketField(regEsi + 0x51d8, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(regEsi + 0xcfb0));
  EncodeOutgoingPacketField(regEsi + 0x4948, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return;
}

