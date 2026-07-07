/* FUN_00529d91 - 0x00529d91 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00529d91(void)

{
  int unaff_EBP;
  int unaff_EDI;
  
  if (*(int *)(unaff_EBP + 0x10) != unaff_EDI) {
    FUN_00529015(8);
  }
  return;
}

