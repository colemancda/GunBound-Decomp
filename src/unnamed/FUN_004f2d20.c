/* FUN_004f2d20 - 0x004f2d20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_004f2d20(void)

{
  int extraout_EDX;
  
  FUN_004f2810();
  *(undefined4 *)(extraout_EDX + 0x3d8) = 0;
  return extraout_EDX;
}

