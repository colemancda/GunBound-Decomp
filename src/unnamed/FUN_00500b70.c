/* FUN_00500b70 - 0x00500b70 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_00500b70(int *param_1)

{
  uint uVar1;
  int *piVar2;
  
  if (param_1[1] == 0) {
    return 0;
  }
  uVar1 = 0;
  if (param_1[2] != 0) {
    piVar2 = (int *)*param_1;
    do {
      if (*piVar2 != 0) {
        return ((int *)*param_1)[uVar1];
      }
      uVar1 = uVar1 + 1;
      piVar2 = piVar2 + 1;
    } while (uVar1 < (uint)param_1[2]);
  }
  return 0;
}

