/* FUN_004eeb10 - 0x004eeb10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void __fastcall FUN_004eeb10(undefined4 param_1,int param_2)

{
  if (DAT_00793549 != '\0') {
    (**(code **)(*(int *)*DAT_00793558 + 0x3c))((int *)*DAT_00793558,(param_2 + -100) * 100);
  }
  return;
}

