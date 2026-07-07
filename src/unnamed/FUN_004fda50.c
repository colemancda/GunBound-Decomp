/* FUN_004fda50 - 0x004fda50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_004fda50(int param_1,char *param_2)

{
  undefined4 uVar1;
  char local_10 [16];
  
  if (*(char *)(param_1 + 0x1a70) == '\0') {
    return 0;
  }
  _strncpy(local_10,param_2,0x10);
  uVar1 = FUN_00502500(0x3010);
  return uVar1;
}

