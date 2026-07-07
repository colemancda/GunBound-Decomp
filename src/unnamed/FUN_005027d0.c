/* FUN_005027d0 - 0x005027d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_005027d0(undefined4 param_1)

{
  undefined4 *unaff_EBX;
  int unaff_ESI;
  
  FUN_005040d0(param_1);
  *(int *)(unaff_ESI + 8) = *(int *)(unaff_ESI + 8) + -0x12;
  *unaff_EBX = param_1;
  return;
}

