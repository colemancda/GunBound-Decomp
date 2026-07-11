/* FindItemGridCell - 0x004dc570 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FindItemGridCell(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int unaff_ESI;
  int unaff_EDI;
  
  iVar2 = 0;
  while( true ) {
    iVar3 = (iVar2 % 3) * 0x46;
    iVar1 = (iVar2 / 3) * 0x2d;
    if ((((iVar3 + 0x210 <= unaff_ESI) && (unaff_ESI <= iVar3 + 0x250)) &&
        (iVar1 + 0x193 <= unaff_EDI)) && (unaff_EDI <= iVar1 + 0x1be)) break;
    iVar2 = iVar2 + 1;
    if (8 < iVar2) {
      return -1;
    }
  }
  return iVar2;
}

