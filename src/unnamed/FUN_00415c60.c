/* FUN_00415c60 - 0x00415c60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_00415c60(void)

{
  int iVar1;
  
  iVar1 = DAT_005b3480 * 0xda003 + 0x5703b11;
  DAT_005b3480 = DAT_005b3480 + (iVar1 * 0x61 + 0x61U) % 0xf4241;
  return iVar1;
}

