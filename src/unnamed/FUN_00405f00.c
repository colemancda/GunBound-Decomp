/* FUN_00405f00 - 0x00405f00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00405f00(undefined4 *regEax)

{
  
  ActiveObjectRegistry_BaseConstructor(regEax);
  regEax[2] = 0;
  regEax[3] = 0;
  *(undefined1 *)(regEax + 5) = 0;
  *regEax = &PTR_FUN_00551e88;
  return;
}

