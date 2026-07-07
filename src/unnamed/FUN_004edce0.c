/* FUN_004edce0 - 0x004edce0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004edce0(void)

{
  int *piVar1;
  char unaff_BL;
  int unaff_ESI;
  
  piVar1 = *(int **)(unaff_ESI + 4);
  if (piVar1 != (int *)0x0) {
    if (unaff_BL != '\0') {
      (**(code **)(*piVar1 + 0x1c))();
      *(char *)(unaff_ESI + 0x54) = unaff_BL;
      return;
    }
    (**(code **)(*piVar1 + 0x20))(piVar1);
  }
  *(char *)(unaff_ESI + 0x54) = unaff_BL;
  return;
}

