/* FUN_004dfff0 - 0x004dfff0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004dfff0(void)

{
  int in_EAX;
  int iVar1;
  undefined4 *unaff_EDI;
  
  for (iVar1 = in_EAX - (int)unaff_EDI; 1 < iVar1 >> 2; iVar1 = iVar1 + -4) {
    *(undefined4 *)((int)unaff_EDI + iVar1 + -4) = *unaff_EDI;
    FUN_004e01b0(0);
  }
  return;
}

