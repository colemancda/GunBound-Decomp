/* FUN_004ff1a0 - 0x004ff1a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ff1a0(void)

{
  int unaff_EDI;
  
  FUN_004fe420(0x3f400000,0x3e800000,0x40100000);
  FUN_004fe420(0x3f400000,0x3e800000,0x40100000);
  *(undefined4 *)(unaff_EDI + 0x80) = 0;
  *(undefined4 *)(unaff_EDI + 0x84) = 0;
  *(undefined4 *)(unaff_EDI + 0x88) = 0;
  *(undefined4 *)(unaff_EDI + 0x8c) = 0;
  return;
}

