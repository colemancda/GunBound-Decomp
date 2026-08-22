/* FUN_004f1d80 - 0x004f1d80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f1d80(int regEsi)

{
  
  FUN_004f1c40();
  *(undefined4 *)(regEsi + 0x15c) = 0;
  return;
}

