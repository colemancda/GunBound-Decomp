/* FUN_004e9b30 - 0x004e9b30 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_004e9b30(void)

{
  float fVar1;
  undefined4 *extraout_EDX;
  
  FUN_004f3150();
  fVar1 = _DAT_00588f54 / _DAT_00588f50;
  *extraout_EDX = &PTR_FUN_00557300;
  extraout_EDX[0xbd] = 0x3fa4bc6a;
  extraout_EDX[0xbf] = 0x3f800000;
  extraout_EDX[0xc0] = 0x447a0000;
  extraout_EDX[0xbe] = 0x3f24bc6a;
  extraout_EDX[0xc1] = fVar1;
  return extraout_EDX;
}

