/* FUN_004aafc0 - 0x004aafc0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004aafc0(void)

{
  undefined4 *in_EAX;
  
  *in_EAX = &PTR_FUN_005565ac;
  DestroyProjectile(in_EAX);
  return;
}

