/* FUN_0050e350 - 0x0050e350 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0050e350(int *param_1)

{
  uint uVar1;
  
  if (((char)param_1[0xe] != '\0') && ((char)param_1[7] != '\0')) {
    (**(code **)(*param_1 + 0x1c))(1,param_1[9],0);
  }
  uVar1 = 0;
  if (param_1[4] != 0) {
    if (param_1[4] == 0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    do {
      (**(code **)(**(int **)(param_1[3] + uVar1 * 4) + 0x20))();
      uVar1 = uVar1 + 1;
    } while (uVar1 < (uint)param_1[4]);
  }
  return;
}

