/* FUN_004fe490 - 0x004fe490 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004fe490(int param_1,undefined4 regEdi,int *regEsi)

{
  char cVar1;
  int iVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4 [4];
  
  iVar2 = StringMap_Find_1c((char *)regEdi,(uint *)&local_c,(undefined4 *)local_4,regEsi,
                       (uint *)&local_8);
  if (iVar2 != 0) {
    *(undefined1 *)(iVar2 + 0x12) = param_1;
    return;
  }
  if (*regEsi == 0) {
    cVar1 = HashMap_InitHashTable(regEsi,regEsi[2],1);
    if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
  }
  iVar2 = StringMap_Insert_1c(local_8,local_c,(undefined4 *)regEdi,regEsi);
  *(undefined1 *)(iVar2 + 0x12) = param_1;
  return;
}

