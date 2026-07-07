/* FUN_00406120 - 0x00406120 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00406120(void)

{
  int iVar1;
  int *piVar2;
  int unaff_EDI;
  
  piVar2 = (int *)FUN_0040cea0();
  if ((piVar2 != (int *)0x0) && ((*(char *)(unaff_EDI + 0x14) == '\0' || (piVar2[1] == 1000000)))) {
    iVar1 = piVar2[9];
    if ((iVar1 != 3) && ((iVar1 != 4 && (iVar1 != 5)))) {
      *(int **)(unaff_EDI + 0xc) = piVar2;
      (**(code **)(*piVar2 + 4))(&DAT_00551e78);
    }
    return 1;
  }
  return 0;
}

