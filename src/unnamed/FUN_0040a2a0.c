/* FUN_0040a2a0 - 0x0040a2a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void __fastcall FUN_0040a2a0(int param_1)

{
  undefined1 local_8 [8];
  
  if (*(int *)(param_1 + 0x14) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_8);
  }
  return;
}

