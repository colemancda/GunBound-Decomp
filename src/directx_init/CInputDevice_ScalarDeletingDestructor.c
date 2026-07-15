/* CInputDevice_ScalarDeletingDestructor - 0x004ee1d0 in the original
 * binary.
 *
 * Renamed with confidence: scalar-deleting-destructor-shaped wrapper
 * (calls the base destructor, then frees `this` if bit 0 of the flags
 * arg is set) for the same DirectInput device-wrapper class as
 * CInputDevice_BaseDestructor.c - see that file for the full vtable/
 * thunk evidence.
 *
 * FIXED (2026-07-15): dropped `self` arg on the base-destructor call -
 * confirmed via direct disassembly at 0x4ee1d3: the original binary's
 * `call 0x4ee1f0` only works because ECX (holding `this`) happens to be
 * unclobbered since `mov esi,ecx` two instructions earlier - the same
 * coincidental-register-reuse trap behind most of this session's
 * calling-convention fixes.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output otherwise, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for
 * status.
 */
#include "ghidra_types.h"


void * __thiscall CInputDevice_ScalarDeletingDestructor(void *param_1,int param_2)

{
  CInputDevice_BaseDestructor(param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}
