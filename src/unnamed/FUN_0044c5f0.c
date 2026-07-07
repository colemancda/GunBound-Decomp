/* FUN_0044c5f0 - 0x0044c5f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_0044c5f0(void)

{
  int iVar1;
  int iVar2;
  int *unaff_EDI;
  
  iVar2 = *unaff_EDI;
  if (iVar2 != 0) {
    for (iVar1 = unaff_EDI[1]; iVar1 != 0; iVar1 = iVar1 + -1) {
      FUN_00426810(iVar2);
      iVar2 = iVar2 + 0x450;
    }
    _free((void *)*unaff_EDI);
    *unaff_EDI = 0;
  }
  unaff_EDI[1] = 0;
  unaff_EDI[2] = 0;
  return;
}

