/* FUN_00517690 - 0x00517690 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00517690(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  if (param_3 == 0) {
    iVar1 = 0x12;
    do {
      FUN_0051a430(param_1,&DAT_005af144 + DAT_005ae93c);
      FUN_0051aed0(&DAT_005af144,DAT_005ae93c,param_2);
      param_1 = param_1 + 0x80;
      param_2 = param_2 + 0x80;
      DAT_005ae93c = DAT_005ae93c - 0x20 & 0x1ff;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    return;
  }
  iVar1 = 0x12;
  param_2 = param_2 + 2;
  do {
    FUN_0051a430(param_1,&DAT_005ae940 + DAT_005af140);
    FUN_0051aed0(&DAT_005ae940,DAT_005af140,param_2);
    param_1 = param_1 + 0x80;
    DAT_005af140 = DAT_005af140 - 0x20 & 0x1ff;
    param_2 = param_2 + 0x80;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}

