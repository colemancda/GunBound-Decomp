/* FUN_004fd7c0 - 0x004fd7c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined1 __thiscall FUN_004fd7c0(int param_1,undefined4 param_2,char param_3)

{
  char cVar1;
  
  if (*(char *)(param_1 + 0x1a70) == '\0') {
    return 0;
  }
  cVar1 = FUN_004fcf10(&param_3,1);
  if (cVar1 == '\0') {
    return 0;
  }
  if (param_3 != '\0') {
    FUN_004fcee0();
  }
  return 1;
}

