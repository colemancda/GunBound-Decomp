/* FUN_00405f00 - 0x00405f00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00405f00(void)

{
  undefined4 *in_EAX;
  
  FUN_004f2e40();
  in_EAX[2] = 0;
  in_EAX[3] = 0;
  *(undefined1 *)(in_EAX + 5) = 0;
  *in_EAX = &PTR_FUN_00551e88;
  return;
}

