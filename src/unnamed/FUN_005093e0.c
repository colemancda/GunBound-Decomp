/* FUN_005093e0 - 0x005093e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_005093e0(void)

{
  int iVar1;
  int in_EAX;
  int *piVar2;
  
  piVar2 = *(int **)(in_EAX + 4);
  if (piVar2 != (int *)0x0) {
    while( true ) {
      iVar1 = piVar2[2];
      piVar2 = (int *)*piVar2;
      if ((*(int *)(iVar1 + 0x20) == 0) && (*(int *)(iVar1 + 0x24) == 20000)) break;
      if (piVar2 == (int *)0x0) {
        return;
      }
    }
    *(undefined1 *)(iVar1 + 0x1d) = 1;
  }
  return;
}

