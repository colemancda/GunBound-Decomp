/* FUN_0040d1b0 - 0x0040d1b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * MAP PASSED THROUGH (2026-10-30): 0x40d1b0 is a bare `jmp 0x415600`, so
 * the map FUN_00415600 reads from EAX is whatever this thunk's caller put
 * there.  Its one caller, FUN_00543300 (the atexit destructor), sets
 * `mov eax,0xe9bea8` at 0x543300.  The port now takes the map as
 * (int *regEax) and forwards it instead of calling FUN_00415600() with
 * nothing.
 */
#include "ghidra_types.h"


void thunk_FUN_00415600(int *regEax)

{
  FUN_00415600(regEax);
  return;
}

