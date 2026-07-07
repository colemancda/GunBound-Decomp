/* FUN_0041b6b0 - 0x0041b6b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0041b6b0(void)

{
  int iVar1;
  int *piVar2;
  int unaff_ESI;
  int *piVar3;
  
  piVar2 = (int *)(unaff_ESI + 0x44248);
  piVar3 = piVar2;
  for (iVar1 = 0x100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar3 = -1;
    piVar3 = piVar3 + 1;
  }
  iVar1 = 0;
  do {
    if (*(char *)(unaff_ESI + 0x41345 + iVar1) != '\0') {
      *piVar2 = iVar1;
      piVar2 = piVar2 + 1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x100);
  return;
}

