/* FUN_00524e80 - 0x00524e80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00524e80(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_84;
  char local_80 [64];
  char local_40 [64];
  
  _sprintf(local_80,(char *)&PTR_DAT_0056ae7c,param_3);
  FUN_00524ef0(param_1,param_2,local_80,local_40,0x40,param_4);
  local_84 = 0;
  _sscanf(local_40,(char *)&PTR_DAT_0056ae7c,&local_84);
  return local_84;
}

