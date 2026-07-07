/* FUN_00406280 - 0x00406280 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_00406280(void)

{
  int *piVar1;
  int unaff_EBX;
  int *piVar2;
  
  piVar2 = (int *)(*(int **)(unaff_EBX + 4))[7];
  if (piVar2 != *(int **)(unaff_EBX + 4)) {
    do {
      for (piVar1 = (int *)piVar2[4]; piVar1 != piVar2; piVar1 = (int *)piVar1[4]) {
        (**(code **)(*piVar1 + 8))();
      }
      piVar2 = (int *)piVar2[7];
    } while (piVar2 != *(int **)(unaff_EBX + 4));
  }
  return;
}

