/* FUN_00500940 - 0x00500940 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00500940(int *param_1,undefined4 *param_2)

{
  char cVar1;
  undefined4 in_EAX;
  int iVar2;
  undefined1 local_4 [4];
  
  iVar2 = FUN_005013c0(local_4);
  if (iVar2 == 0) {
    if (*param_1 == 0) {
      cVar1 = FUN_00500c00(param_1,param_1[2],1);
      if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
        FUN_004010c0(0x8007000e);
      }
    }
    iVar2 = FUN_00501560(in_EAX,param_1);
  }
  *(undefined4 *)(iVar2 + 4) = *param_2;
  *(undefined4 *)(iVar2 + 8) = param_2[1];
  return;
}

