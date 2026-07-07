/* FUN_00405890 - 0x00405890 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00405890(void)

{
  int iVar1;
  int *unaff_ESI;
  
  iVar1 = (**(code **)(**(int **)(*unaff_ESI + -0x10) + 8))(*unaff_ESI + -0x10);
  if (iVar1 == 0) {
    FUN_004058b0();
    return;
  }
  *unaff_ESI = iVar1 + 0x10;
  return;
}

