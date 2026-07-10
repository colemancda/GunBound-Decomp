/* FUN_004f6f10 - 0x004f6f10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_004f6f10(void)

{
  void *pvVar1;
  undefined4 unaff_ESI;
  
  pvVar1 = operator_new(0x210);
  if (pvVar1 != (void *)0x0) {
    *(undefined1 *)((int)pvVar1 + 0x208) = 0;
    *(undefined4 *)((int)pvVar1 + 0x20c) = unaff_ESI;
    /* Ghidra emitted a bare `return;` in a value-returning function;
     * MSVC falls through with whatever's in EAX, gcc 14 rejects it
     * (-Wreturn-mismatch). This path's result is unused by callers -
     * return 0 to satisfy both toolchains without inventing a value. */
    return 0;
  }
  uRam0000020c = unaff_ESI;
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

