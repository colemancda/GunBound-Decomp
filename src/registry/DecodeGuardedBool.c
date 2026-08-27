/* DecodeGuardedBool - 0x00406860 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * CELL ARGUMENT RECOVERED (2026-08-26).  This takes its guard cell in EAX and
 * every ported call site dropped it: the body read an uninitialised
 * `byte *cell` and functions.h declared it K&R-empty, so 38 argless calls
 * compiled without a word.  It is the NEGATED twin of PeekPacketChecksumBool
 * (0x4065a0) -- byte-for-byte the same code with `sete al` on the result --
 * and takes its cell exactly the same way, which is why adding 0x406860 to
 * tools/guard_cell_resolve.py's FAMILY table resolved all 35 binary sites at
 * once.  The prototype below is deliberately real, not K&R: it is what makes
 * a missed call site a compile error rather than a silent wild read.
 */
#include "ghidra_types.h"


bool DecodeGuardedBool(byte *cell)

{
  byte bVar1;
  byte bVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  bVar1 = *cell;
  bVar2 = cell[1];
  if ((byte)((bVar1 + bVar2) - 0x34) != cell[2]) {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    return true;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return (bVar2 >> (bVar1 & 7) & 1) != 1;
}

