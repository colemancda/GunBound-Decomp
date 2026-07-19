/* SetGuardedBool - 0x00406500 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
/* DROPPED-REGISTER FIX (2026-07-19): the guarded-bool cell pointer arrives
 * in EAX and is forwarded to EncodeGuardedBool in ESI - orig 0x406506
 * `mov esi,eax` with the value taken from the stack at 0x40650e, and
 * 0x406523 `mov eax,esi` returning the pointer. Ghidra dropped both the
 * incoming pointer and the return value. Promoted to an explicit parameter.
 *
 * UNRECOVERED CALL SITES: the original has 260 call sites for this function
 * and each passes a DIFFERENT cell address (mostly `g_clientContext + off`).
 * Only the sites actually exercised by the bring-up login path have had
 * their pointer recovered so far; every other site passes
 * GB_GUARD_UNRECOVERED, a shared scratch cell, so that it neither faults nor
 * silently corrupts an unrelated field. Those sites are greppable by that
 * macro name and still need per-site recovery - while they share one cell,
 * the guarded booleans they set alias each other and read back wrong. */
#include "ghidra_types.h"


int SetGuardedBool(undefined4 param_1,int guardPtr)

{
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool(param_1,(byte *)guardPtr);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return guardPtr;
}

