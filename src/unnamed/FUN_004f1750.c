/* FUN_004f1750 - 0x004f1750 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f1750(undefined4 *regEax)

{
  
  ActiveObjectRegistry_BaseConstructor(regEax);
  *regEax = &PTR_FUN_00557528;
  return;
}

