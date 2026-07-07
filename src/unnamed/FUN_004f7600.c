/* FUN_004f7600 - 0x004f7600 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f7600(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int unaff_EBX;
  byte *pbVar5;
  uint uVar6;
  undefined4 *puVar7;
  
  iVar2 = (int)*(uint *)(unaff_EBX + 0x5c) >> 2;
  uVar3 = *(uint *)(unaff_EBX + 0x5c) & 3;
  pbVar5 = &DAT_00551b78;
  iVar1 = unaff_EBX + 0x1c;
  if (uVar3 == 0) {
    uVar6 = 0;
switchD_004f7624_switchD:
    switch(uVar3) {
    case 0:
      uVar6 = 0x80000000;
      pbVar5 = &DAT_00551b79;
    case 1:
      uVar6 = uVar6 | (uint)*pbVar5 << 0x10;
      pbVar5 = pbVar5 + 1;
    case 2:
      uVar6 = uVar6 | (uint)*pbVar5 << 8;
      pbVar5 = pbVar5 + 1;
    case 3:
      uVar6 = uVar6 | *pbVar5;
    }
  }
  else {
    uVar6 = *(uint *)(iVar1 + iVar2 * 4);
    if (uVar3 < 4) goto switchD_004f7624_switchD;
  }
  *(uint *)(iVar1 + iVar2 * 4) = uVar6;
  iVar2 = iVar2 + 1;
  if (iVar2 < 0xf) {
    if (0xd < iVar2) goto LAB_004f7684;
  }
  else {
    if (iVar2 < 0x10) {
      *(undefined4 *)(iVar1 + iVar2 * 4) = 0;
    }
    FUN_004f76f0(1);
    iVar2 = 0;
  }
  puVar7 = (undefined4 *)(iVar1 + iVar2 * 4);
  for (iVar4 = 0xe - iVar2; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
LAB_004f7684:
  *(undefined4 *)(unaff_EBX + 0x54) = *(undefined4 *)(unaff_EBX + 0x18);
  *(undefined4 *)(unaff_EBX + 0x58) = *(undefined4 *)(unaff_EBX + 0x14);
  FUN_004f76f0(1);
  *(undefined4 *)(unaff_EBX + 0x5c) = 0;
  return;
}

