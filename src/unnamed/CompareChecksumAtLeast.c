/* CompareChecksumAtLeast - 0x0040b450 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_0040b450 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: Disasm
 * 0x40b450-0x40b485: locks g_valueGuardLock, peeks both guarded cells, cmp
 * esi,eax / setge (p1 >= p2), ret 8. It fills the gap in the comparator
 * family laid out at 0x10 byte spacing: CompareChecksumMatch (0x40b390,
 * ==), CompareChecksumExceeds (0x40b410, p1 > p2), this (0x40b450, p1 >=
 * p2), CompareChecksumPair (0x40b490, p1 < p2), CompareChecksumAtMost
 * (0x40b4d0, p1 <= p2). The caller IsProjectileInBounds independently
 * reads it as a greater-or-equal test (its header: y >= Peek(ctx +
 * 0x6aa1e4), the bottom bound).
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): declared `(void)` by
 * Ghidra but the original loads two stack cells (`mov eax,[esp+0xc]` /
 * `[esp+0x10]` after two pushes) and returns with `ret 8` - the
 * greater-or-equal twin of CompareChecksumPair.  All callers already pass two.
 */
#include "ghidra_types.h"


bool CompareChecksumAtLeast(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(param_1));
  iVar2 = PeekPacketChecksumState((void *)(param_2));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return iVar2 <= iVar1;
}

