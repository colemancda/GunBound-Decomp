/* FUN_00405510 - 0x00405510 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int * __thiscall FUN_00405510(char *param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  iVar2 = DAT_005b1444;
  uStack_c = *unaff_FS_OFFSET;
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005378e8;
  *unaff_FS_OFFSET = &uStack_c;
  iVar2 = (**(code **)(iVar2 + 0xc))();
  *param_2 = iVar2 + 0x10;
  uStack_4 = 0;
  if (param_1 != (char *)0x0) {
    pcVar3 = param_1;
    if (((uint)param_1 & 0xffff0000) == 0) {
      iVar2 = FUN_00401880((uint)param_1 & 0xffff,0);
      if (iVar2 != 0) {
        FUN_004055f0(param_2);
      }
      goto LAB_00405592;
    }
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
  }
  FUN_004056c0(param_2,param_1);
LAB_00405592:
  *unaff_FS_OFFSET = uStack_c;
  return param_2;
}

