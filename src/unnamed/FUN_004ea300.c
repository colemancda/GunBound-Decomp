/* FUN_004ea300 - 0x004ea300 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void InitLZHUFTree(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  undefined4 *unaff_EDI;
  
  *unaff_EDI = 0;
  unaff_EDI[1] = 0;
  *(undefined2 *)(unaff_EDI + 0x3dac) = 0;
  *(undefined1 *)((int)unaff_EDI + 0xf6b2) = 0;
  *(undefined2 *)(unaff_EDI + 0x3dad) = 0;
  *(undefined1 *)((int)unaff_EDI + 0xf6b6) = 0;
  iVar3 = 0;
  piVar5 = unaff_EDI + 0x3b39;
  do {
    piVar5[-0x13a] = iVar3;
    piVar5[-0x621] = 1;
    *piVar5 = iVar3 + 0x273;
    iVar3 = iVar3 + 1;
    piVar5 = piVar5 + 1;
  } while (iVar3 < 0x13a);
  iVar6 = 0;
  iVar3 = 0x13a;
  piVar5 = unaff_EDI + 0x3c73;
  piVar4 = unaff_EDI + 0x3518;
  do {
    iVar1 = piVar4[1];
    iVar2 = *piVar4;
    *piVar5 = iVar6;
    piVar5[-0x621] = iVar1 + iVar2;
    piVar4[0x275] = iVar3;
    piVar4[0x274] = iVar3;
    iVar6 = iVar6 + 2;
    piVar4 = piVar4 + 2;
    iVar3 = iVar3 + 1;
    piVar5 = piVar5 + 1;
  } while (iVar3 < 0x273);
  unaff_EDI[0x39fe] = 0;
  unaff_EDI[0x378b] = 0xffff;
  return;
}

