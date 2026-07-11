/* FUN_0049cc60 - 0x0049cc60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0049cc60(void)

{
  undefined4 *in_EAX;
  
  *in_EAX = &PTR_FUN_00556468;
  DestroyProjectile(in_EAX);
  return;
}

