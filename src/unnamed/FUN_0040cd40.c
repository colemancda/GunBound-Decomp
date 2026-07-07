/* FUN_0040cd40 - 0x0040cd40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0040cd40(void)

{
  undefined4 *in_EAX;
  
  FUN_004f2e40();
  *in_EAX = &PTR_FUN_005520a0;
  in_EAX[2] = 0;
  return;
}

