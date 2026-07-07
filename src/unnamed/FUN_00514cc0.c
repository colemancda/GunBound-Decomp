/* FUN_00514cc0 - 0x00514cc0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00514cc0(undefined4 param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int *local_8;
  undefined4 *local_4;
  
  iVar2 = 0;
  if (0 < DAT_005ae7dc) {
    local_8 = (int *)(&DAT_005ae7cc + param_2 * 8);
    local_4 = (undefined4 *)(&DAT_005ae7cc + (param_2 ^ 1) * 8);
    piVar3 = &DAT_005ae814 + param_2 * 0x24;
    puVar5 = &DAT_00f25f00 + param_2 * 0x240;
    puVar4 = &DAT_00f25f00 + (param_2 ^ 1) * 0x240;
    do {
      iVar1 = *local_8;
      param_2 = iVar1;
      if ((*piVar3 == 2) && (param_2 = 0, piVar3[1] != 0)) {
        param_2 = *(uint *)(&DAT_00f25d3c + DAT_005aba28 * 4);
      }
      if (DAT_00563d8c < (int)param_2) {
        param_2 = DAT_00563d8c;
      }
      if (DAT_00563d8c < iVar1) {
        iVar1 = DAT_00563d8c;
      }
      iVar1 = FUN_00517d10(puVar5,puVar4,&DAT_005ada3c,*piVar3,param_2,iVar1,*local_4);
      *local_8 = iVar1;
      FUN_005180b0(&DAT_005ada3c,iVar1);
      (*(code *)PTR_FUN_00563da0)(&DAT_005ada3c,param_1,iVar2);
      local_4 = local_4 + 1;
      local_8 = local_8 + 1;
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 0x12;
      puVar4 = puVar4 + 0x480;
      puVar5 = puVar5 + 0x480;
    } while (iVar2 < DAT_005ae7dc);
  }
  return;
}

