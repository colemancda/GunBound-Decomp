/* FUN_004048e0 - 0x004048e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_004048e0(int *regEax,int regEbx)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (regEbx != 0) {
    iVar1 = regEax[5];
    iVar2 = regEbx;
    if ((*(int *)(regEbx + 0x108) != iVar1) && (*(int *)(regEbx + 0x10c) != iVar1)) {
      iVar2 = FUN_004050a0(regEax,regEbx);
    }
    iVar3 = *(int *)(iVar2 + 0x108);
    if (iVar3 == iVar1) {
      iVar3 = *(int *)(iVar2 + 0x10c);
    }
    *(undefined4 *)(iVar3 + 0x110) = *(undefined4 *)(iVar2 + 0x110);
    iVar1 = *(int *)(iVar2 + 0x110);
    if (iVar1 == regEax[5]) {
      *regEax = iVar3;
    }
    else if (iVar2 == *(int *)(iVar1 + 0x108)) {
      *(int *)(iVar1 + 0x108) = iVar3;
    }
    else {
      *(int *)(iVar1 + 0x10c) = iVar3;
    }
    if (*(int *)(iVar2 + 0x104) == 1) {
      FUN_00404e60();
    }
    if (iVar2 != regEbx) {
      TreeReplaceNode((int)regEbx,regEax,iVar2);
    }
    if (*regEax != 0) {
      *(int *)(*regEax + 0x110) = regEax[5];
    }
    thunk_FUN_00405320();
    iVar1 = regEax[2];
    *(int *)(regEbx + 0x108) = iVar1;
    regEax[1] = regEax[1] + -1;
    regEax[2] = regEbx;
    return CONCAT31((int3)((uint)iVar1 >> 8),1);
  }
  return (uint)regEax & 0xffffff00;
}

