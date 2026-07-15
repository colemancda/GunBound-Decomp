/* FUN_004f2e20 - 0x004f2e20 in the original binary.
 *
 * Scalar-deleting-destructor-shaped wrapper: matches the exact idiom
 * already named in CGameState_ScalarDeletingDestructor.c (calls the
 * base destructor, then frees `this` if bit 0 of the flags arg is
 * set). No confirmed owning class - the vtable this sits in (0x557530,
 * confirmed via a whole-binary scan for that address as a DWORD
 * literal) has no other named members, and its poison targets
 * (PTR_LAB_0055752c / PTR_FUN_00557534) are both generic sentinels
 * shared by a dozen+ unrelated classes, so neither identifies it.
 *
 * FIXED (2026-07-15): dropped `self` arg on the FUN_004f2e10() call -
 * confirmed via direct disassembly at 0x4f2e23: the original binary's
 * `call 0x4f2e10` only works because ECX (holding `this`) happens to
 * be unclobbered since `mov esi,ecx` two instructions earlier - the
 * same coincidental-register-reuse trap behind most of this session's
 * calling-convention fixes. See src/unnamed/FUN_004f2e10.c.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output otherwise, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for
 * status.
 */
#include "ghidra_types.h"


void * __thiscall FUN_004f2e20(void *param_1,int param_2)

{
  FUN_004f2e10(param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

