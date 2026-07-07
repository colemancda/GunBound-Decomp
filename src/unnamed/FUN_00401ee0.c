/* FUN_00401ee0 - 0x00401ee0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00401ee0(int param_1)

{
  int *piVar1;
  undefined4 in_EAX;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  puVar2 = (undefined4 *)FUN_00401bb0(param_1);
  if (puVar2 != (undefined4 *)0x0) {
    iVar3 = FUN_00401c50(param_1,in_EAX);
    if (iVar3 < 0x7f) {
      puVar6 = (undefined4 *)(param_1 + 0x15b0 + iVar3 * 4);
      puVar7 = (undefined4 *)(param_1 + 0x15ac + iVar3 * 4);
      for (iVar5 = 0x7f - iVar3; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar7 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar7 = puVar7 + 1;
      }
    }
    if (*(void **)(param_1 + 0x17a8) != (void *)0x0) {
      _free(*(void **)(param_1 + 0x17a8));
      *(undefined4 *)(param_1 + 0x17a8) = 0;
    }
    *(undefined4 *)(puVar2[3] + 0x10) = puVar2[4];
    *(undefined4 *)(puVar2[4] + 0xc) = puVar2[3];
    (**(code **)*puVar2)(1);
    iVar3 = *(int *)(param_1 + 0xc10) + -1;
    *(int *)(param_1 + 0xc10) = iVar3;
    piVar4 = DAT_00e53c44;
    if (DAT_00e53c44 != (int *)0x0) {
      while( true ) {
        piVar1 = (int *)*piVar4;
        if ((*(int *)(piVar4[2] + 0x20) == 0) && (*(int *)(piVar4[2] + 0x24) == 20000)) break;
        piVar4 = piVar1;
        if (piVar1 == (int *)0x0) {
          return;
        }
      }
      FUN_00505520(iVar3,7);
    }
  }
  return;
}

