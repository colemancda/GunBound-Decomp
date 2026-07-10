/* FUN_004f4350 - 0x004f4350 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_004f4350(void)

{
  undefined1 *puVar1;
  int unaff_ESI;
  
  puVar1 = operator_new(0x118);
  if (puVar1 == (undefined1 *)0x0) {
    puVar1 = (undefined1 *)0x0;
  }
  else {
    *puVar1 = 0;
    *(undefined4 *)(puVar1 + 0x110) = 0;
  }
  if (*(int *)(unaff_ESI + 0x118) == 0) {
    *(undefined1 **)(unaff_ESI + 0x114) = puVar1;
    *(undefined4 *)(puVar1 + 0x114) = 0;
    *(undefined1 **)(unaff_ESI + 0x118) = puVar1;
    /* Ghidra emitted a bare `return;` in a value-returning function;
     * MSVC falls through with whatever's in EAX, gcc 14 rejects it
     * (-Wreturn-mismatch). This path's result is unused by callers -
     * return 0 to satisfy both toolchains without inventing a value. */
    return 0;
  }
  *(undefined1 **)(*(int *)(unaff_ESI + 0x118) + 0x114) = puVar1;
  *(undefined4 *)(puVar1 + 0x114) = 0;
  *(undefined1 **)(unaff_ESI + 0x118) = puVar1;
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

