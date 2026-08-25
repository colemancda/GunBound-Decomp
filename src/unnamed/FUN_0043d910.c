/* FUN_0043d910 - 0x0043d910 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0043d910(undefined4 *regEax)

{
  
  FUN_0043d970(regEax);
  *regEax = &PTR_LAB_00554000;
  regEax[5] = 0;
  return;
}

