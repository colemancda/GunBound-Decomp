/* FUN_004f11a0 - 0x004f11a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_004f11a0(void)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int unaff_EBX;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar4 = *(uint *)(unaff_EBX + 8);
  uVar5 = uVar4 >> 1;
  bVar1 = false;
  uVar6 = 0;
  while ((iVar2 = *(int *)(unaff_EBX + 0x40 + (uVar5 >> 10) * 4), iVar2 != 0 &&
         ((uVar5 & 0x3ff) * 0x80 + iVar2 != 0))) {
    iVar2 = FUN_004f0990();
    if (iVar2 == 0) {
      return uVar5;
    }
    uVar7 = uVar5;
    if (iVar2 < 0) {
      uVar4 = uVar5;
      uVar7 = uVar6;
    }
    uVar3 = uVar4 - uVar7 >> 1;
    uVar5 = uVar3 + uVar7;
    uVar6 = uVar7;
    if (uVar3 == 0) {
      if (bVar1) {
        return 0xffffffff;
      }
      bVar1 = true;
    }
  }
  return 0xffffffff;
}

