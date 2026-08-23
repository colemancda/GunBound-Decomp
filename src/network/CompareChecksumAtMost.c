/* CompareChecksumAtMost - 0x0040b4d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): Ghidra declared this
 * `(void)` but the original is a TWO-CELL comparator - it loads its cells with
 * `mov eax,[esp+0xc]` and `mov eax,[esp+0x10]`, which with the two prologue
 * pushes are the first and second stack arguments, and it returns with `ret 8`.
 * The signature is recovered accordingly and the two internal peeks name
 * param_1 and param_2; the 150+ call sites that already pass two arguments
 * were right all along.
 */
#include "ghidra_types.h"


bool CompareChecksumAtMost(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(param_1));
  iVar2 = PeekPacketChecksumState((void *)(param_2));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return iVar1 <= iVar2;
}

