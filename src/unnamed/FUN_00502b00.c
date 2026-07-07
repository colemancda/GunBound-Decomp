/* FUN_00502b00 - 0x00502b00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int * FUN_00502b00(int *param_1,int param_2)

{
  int iVar1;
  int unaff_EDI;
  
  iVar1 = *(int *)(unaff_EDI + 4);
  if (iVar1 != 0) {
    if ((*(int *)(unaff_EDI + 8) - iVar1) / 0x1e != 0) {
      iVar1 = (param_2 - iVar1) / 0x1e;
      goto LAB_00502b4b;
    }
  }
  iVar1 = 0;
LAB_00502b4b:
  FUN_005033e0(unaff_EDI,param_2);
  *param_1 = iVar1 * 0x1e + *(int *)(unaff_EDI + 4);
  return param_1;
}

