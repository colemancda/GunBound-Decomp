/* ScrubChecksumGuard - 0x0040a2a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall ScrubChecksumGuard(int param_1)

{
  undefined1 local_8 [8];
  
  if (*(int *)(param_1 + 0x14) != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_8);
  }
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

