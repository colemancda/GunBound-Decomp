/* FUN_00504880 - 0x00504880 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_00504880(char *param_1)

{
  uint uVar1;
  char local_10 [16];
  
  uVar1 = FUN_00504790(param_1);
  if ((char)uVar1 != '\0') {
    return uVar1 & 0xffffff00;
  }
  _strncpy(local_10,param_1,0x10);
  uVar1 = FUN_00502500(0x3010);
  return uVar1;
}

