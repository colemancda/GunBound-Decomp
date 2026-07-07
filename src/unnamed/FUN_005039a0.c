/* FUN_005039a0 - 0x005039a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_005039a0(int param_1,undefined4 param_2,int *param_3)

{
  int *piVar1;
  char cVar2;
  undefined4 in_EAX;
  undefined4 unaff_EBX;
  undefined4 unaff_EDI;
  
  piVar1 = param_3;
  cVar2 = FUN_004fe860(unaff_EDI,&param_3);
  if ((((cVar2 != '\0') && (*param_3 != 0)) && (param_3[2] == param_1)) &&
     ((((short)param_3[3] == (short)param_2 && ((int *)param_3[4] == piVar1)) &&
      ((short)param_3[5] == (short)unaff_EBX)))) {
    *(undefined1 *)(param_3 + 7) = 0;
    return;
  }
  FUN_004fe8d0(in_EAX,param_1,param_2,piVar1,unaff_EBX);
  return;
}

