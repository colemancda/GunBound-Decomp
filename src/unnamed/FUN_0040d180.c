/* FUN_0040d180 - 0x0040d180 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): this is a one-line wrapper that
 * forwards its EAX to HashMap_Construct as the object being constructed.  Its two
 * callers are static-initialiser thunks that name the object outright --
 * `mov eax,0x794e14` in FUN_00540f00 and `mov eax,0xe9bea8` in FUN_00540f20,
 * each the first instruction of the thunk.
 *
 * Wiring it required resizing both globals first: HashMap_Construct writes 0x30
 * bytes and globals.c had them as a 1-byte and a 4-byte cell, so passing the
 * address before the resize would have traded an uninitialised pointer for a
 * deterministic overrun.  They now live in globals_sized.c at their real
 * extent.
 */
#include "ghidra_types.h"


void FUN_0040d180(undefined4 *regEax)

{
  HashMap_Construct(0xa,0x3f400000,0x3e800000,0x40100000,0x11,regEax);
  return;
}

