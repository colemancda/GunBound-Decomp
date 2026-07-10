/* FUN_0048b3f0 - 0x0048b3f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_0048b3f0(void)

{
  undefined4 *unaff_ESI;
  
  FUN_00454dc0(unaff_ESI,0x186a2);
  *(undefined1 *)(unaff_ESI + 0xfe7) = 0;
  unaff_ESI[0xfe8] = 0;
  *unaff_ESI = &PTR_FUN_00556284;
  unaff_ESI[0xfe9] = 4;
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

