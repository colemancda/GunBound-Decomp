/* FUN_00507090 - 0x00507090 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_00507090(int param_1,int param_2)

{
  SHORT SVar1;
  
  if (*(char *)(param_1 + 4) == '\0') {
    return 0;
  }
  if (param_2 == 9) {
    SVar1 = GetKeyState(0x10);
    if (SVar1 < 0) {
      if ((*(int *)(param_1 + 8) != 0) && (DAT_007934c4 == '\0')) {
        (**(code **)(**(int **)(param_1 + 8) + 0x1c))(0x1101,*(undefined4 *)(param_1 + 0x24),0);
        return 1;
      }
    }
    else if ((*(int *)(param_1 + 8) != 0) && (DAT_007934c4 == '\0')) {
      (**(code **)(**(int **)(param_1 + 8) + 0x1c))(0x1102,*(undefined4 *)(param_1 + 0x24),0);
    }
  }
  else if (param_2 == 0xd) {
    if ((*(int *)(param_1 + 8) != 0) && (DAT_007934c4 == '\0')) {
      (**(code **)(**(int **)(param_1 + 8) + 0x1c))(0x1100,*(undefined4 *)(param_1 + 0x24),0);
      return 1;
    }
  }
  else if (((param_2 == 0x1b) && (*(int *)(param_1 + 8) != 0)) && (DAT_007934c4 == '\0')) {
    (**(code **)(**(int **)(param_1 + 8) + 0x1c))(0x1001,*(undefined4 *)(param_1 + 0x24),0);
    return 1;
  }
  return 1;
}

