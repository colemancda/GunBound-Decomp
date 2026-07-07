/* FUN_0043d910 - 0x0043d910 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0043d910(void)

{
  undefined4 *in_EAX;
  
  FUN_0043d970();
  *in_EAX = &PTR_LAB_00554000;
  in_EAX[5] = 0;
  return;
}

