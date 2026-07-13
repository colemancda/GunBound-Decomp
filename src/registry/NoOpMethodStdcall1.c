/* NoOpMethodStdcall1 - 0x004038b0 in the original binary.
 *
 * A no-op vtable slot filler that takes one stack argument and cleans
 * it up itself (`ret 0x4`), unlike the plain-ret NoOpMethod (0x429800).
 * Used as the "refill"/tick no-op for DirectSound streaming objects
 * that aren't yet bound to a real channel (see PTR_LAB_005574e0/e8/cc's
 * slot 0 in globals.c).
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall NoOpMethodStdcall1(void *thisPtr, undefined4 param_1)

{
  (void)thisPtr;
  (void)param_1;
  return;
}
