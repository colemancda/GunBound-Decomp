/* FUN_004e39b0 - 0x004e39b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e39b0(int *regEsi)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  uVar1 = regEsi[4] - *regEsi;
  uVar3 = regEsi[5] - regEsi[1];
  iVar5 = 4;
  if (((*(char *)((int)regEsi + 0x2d) != '\0') && ((char)regEsi[0x219] != '\0')) &&
     ((200 < (int)((uVar1 ^ (int)uVar1 >> 0x1f) - ((int)uVar1 >> 0x1f)) ||
      (iVar5 = 8, 200 < (int)((uVar3 ^ (int)uVar3 >> 0x1f) - ((int)uVar3 >> 0x1f)))))) {
    iVar5 = 6;
  }
  if ((int)uVar1 < 0) {
    iVar2 = uVar1 + (1 - iVar5);
  }
  else {
    iVar2 = (uVar1 - 1) + iVar5;
  }
  if ((int)uVar3 < 0) {
    iVar4 = uVar3 + (1 - iVar5);
  }
  else {
    iVar4 = (uVar3 - 1) + iVar5;
  }
  iVar2 = *regEsi + iVar2 / iVar5;
  regEsi[2] = iVar2;
  *regEsi = iVar2;
  iVar5 = regEsi[1] + iVar4 / iVar5;
  regEsi[3] = iVar5;
  regEsi[1] = iVar5;
  if ((regEsi[0x12] != 0) && (iVar5 = regEsi[0x13], iVar5 != 0)) {
    iVar2 = iVar5;
    if ((char)regEsi[0x14] != '\0') {
      iVar4 = _rand();
      iVar2 = regEsi[0x13];
      regEsi[2] = regEsi[2] + (iVar4 % iVar5 - iVar5 / 2);
      iVar5 = _rand();
      regEsi[3] = regEsi[3] + (iVar5 % iVar2 - iVar2 / 2);
    }
    regEsi[0x12] = regEsi[0x12] + -1;
    regEsi[0x13] = iVar2 + -1;
  }
  FUN_004507d0();
  return;
}

