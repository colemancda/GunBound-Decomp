/* FUN_0040b450 - 0x0040b450 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): declared `(void)` by
 * Ghidra but the original loads two stack cells (`mov eax,[esp+0xc]` /
 * `[esp+0x10]` after two pushes) and returns with `ret 8` - the
 * greater-or-equal twin of CompareChecksumPair.  All callers already pass two.
 */
#include "ghidra_types.h"


bool FUN_0040b450(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState((void *)(param_1));
  iVar2 = PeekPacketChecksumState((void *)(param_2));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return iVar2 <= iVar1;
}

