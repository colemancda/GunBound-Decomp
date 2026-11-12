/* CriticalSection_ScalarDtor - 0x004e5430 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * The only slot of the lock-object vtable 0x5572dc (globals.c
 * PTR_FUN_005572dc). The object is a vtable pointer followed by a
 * CRITICAL_SECTION at +4, and the callers show it: every store of 0x5572dc
 * in the image sits next to an InitializeCriticalSection (constructor
 * side) or DeleteCriticalSection (destructor side) on this+4. The
 * destructor-side callers inline exactly this function's first half
 * (re-stamp 0x5572dc, then DeleteCriticalSection(this+4)):
 * ReplayContext_Destructor and ClientContext_Destructor on embedded
 * members, the connection object constructor and destroyer, LoadSoundConfig
 * and LoadFourWordList on stack locals, and the CRT atexit stub
 * FUN_005431e0 on the static at 0x5a9080. This slot is that
 * same sequence plus the scalar-deleting tail (free the block when bit 0 of
 * the flag word is set, return this); no dispatch through it was found,
 * so it is the compiler-emitted deleting destructor of the lock wrapper
 * class.
 */
#include "ghidra_types.h"


undefined4 * __thiscall CriticalSection_ScalarDtor(undefined4 *param_1,int param_2)

{
  *param_1 = &PTR_FUN_005572dc;
  DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

