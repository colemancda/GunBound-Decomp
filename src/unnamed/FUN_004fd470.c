/* FUN_004fd470 - 0x004fd470 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall
FUN_004fd470(int param_1,undefined4 param_2,undefined4 param_3,char *param_4,char *param_5)

{
  char cVar1;
  int iVar2;
  
  if (*(char *)(param_1 + 0x1a71) == '\0') {
    do {
      cVar1 = *param_4;
      param_4 = param_4 + 1;
    } while (cVar1 != '\0');
    FUN_005051e0();
    do {
      cVar1 = *param_5;
      param_5 = param_5 + 1;
    } while (cVar1 != '\0');
    FUN_005051e0();
    FUN_004fe060();
    if (*(char *)(param_1 + 0x1a70) == '\0') {
      iVar2 = FUN_004fdd30(param_1 + 4,param_3);
      *(int *)(param_1 + 0x1a74) = iVar2;
      if (iVar2 == 0) {
        return 0;
      }
    }
    else {
      FUN_005024a0(0x1000);
    }
  }
  return 1;
}

