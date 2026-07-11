/* FUN_004b1800 - 0x004b1800 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004b1800(void)

{
  undefined4 *in_EAX;
  
  *in_EAX = &PTR_FUN_00556680;
  DestroyProjectile(in_EAX);
  return;
}

