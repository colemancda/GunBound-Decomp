/* FUN_00534bec - 0x00534bec in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00534bec(int param_1)

{
  int unaff_EBP;
  
  if (*(int *)(unaff_EBP + -0x1c) != param_1) {
    FUN_00529015(param_1);
  }
  return;
}

