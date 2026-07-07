/* FUN_00502a20 - 0x00502a20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int * FUN_00502a20(int *param_1,int param_2)

{
  int iVar1;
  int unaff_EDI;
  
  iVar1 = *(int *)(unaff_EDI + 4);
  if (iVar1 != 0) {
    if ((*(int *)(unaff_EDI + 8) - iVar1) / 0x34 != 0) {
      iVar1 = (param_2 - iVar1) / 0x34;
      goto LAB_00502a67;
    }
  }
  iVar1 = 0;
LAB_00502a67:
  FUN_00502e20(unaff_EDI,param_2);
  *param_1 = iVar1 * 0x34 + *(int *)(unaff_EDI + 4);
  return param_1;
}

