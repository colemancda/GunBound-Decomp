/* FUN_004fd960 - 0x004fd960 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_004fd960(int param_1,char *param_2,char *param_3)

{
  undefined4 uVar1;
  char local_28 [20];
  char local_14 [20];
  
  if (*(char *)(param_1 + 0x1a70) == '\0') {
    return 0;
  }
  _strncpy(local_28,param_2,0x14);
  _strncpy(local_14,param_3,0x14);
  uVar1 = FUN_00502500(0x3006);
  return uVar1;
}

