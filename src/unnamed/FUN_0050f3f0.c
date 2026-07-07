/* FUN_0050f3f0 - 0x0050f3f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_0050f3f0(void)

{
  int iVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int unaff_ESI;
  
  iVar6 = *(int *)(unaff_ESI + 0x34);
  iVar2 = in_EAX - *(int *)(unaff_ESI + 0x2c);
  iVar1 = *(int *)(unaff_ESI + 0x38);
  iVar4 = iVar6;
  if (0 < iVar1) {
    iVar3 = (*(int *)(unaff_ESI + 0x3c) * iVar6) / iVar1;
    iVar4 = 10;
    if (9 < iVar3) {
      iVar4 = iVar3;
    }
    iVar4 = (iVar4 / 5) * 5;
  }
  iVar6 = iVar6 - iVar4;
  uVar5 = iVar1 - *(int *)(unaff_ESI + 0x3c);
  uVar5 = uVar5 & ((int)uVar5 < 0) - 1;
  if (iVar2 < 1) {
    return 0;
  }
  if (iVar2 < iVar6) {
    if (iVar6 < 1) {
      iVar6 = 1;
    }
    uVar5 = (int)(uVar5 * iVar2) / iVar6;
  }
  return uVar5;
}

