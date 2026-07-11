/* FUN_004ae370 - 0x004ae370 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_004ae370(void)

{
  undefined4 *unaff_ESI;
  
  InitProjectile(unaff_ESI,0x186a2);
  *unaff_ESI = &PTR_FUN_0055661c;
  unaff_ESI[0xfe7] = 0;
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

