/* FUN_004ea3b0 - 0x004ea3b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ea3b0(void)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  uint *puVar5;
  uint uVar6;
  int *piVar7;
  uint *puVar8;
  uint *puVar9;
  int unaff_EBX;
  int iVar10;
  size_t _Size;
  int local_10;
  int local_c;
  
  piVar4 = (int *)(unaff_EBX + 0xece4);
  puVar5 = (uint *)(unaff_EBX + 0xd460);
  local_10 = 0xd1;
  piVar7 = piVar4;
  puVar8 = puVar5;
  do {
    if (0x272 < *piVar4) {
      *puVar8 = piVar4[-0x621] + 1U >> 1;
      *piVar7 = *piVar4;
      puVar8 = puVar8 + 1;
      piVar7 = piVar7 + 1;
    }
    if (0x272 < piVar4[1]) {
      *puVar8 = piVar4[-0x620] + 1U >> 1;
      *piVar7 = piVar4[1];
      puVar8 = puVar8 + 1;
      piVar7 = piVar7 + 1;
    }
    if (0x272 < piVar4[2]) {
      *puVar8 = piVar4[-0x61f] + 1U >> 1;
      *piVar7 = piVar4[2];
      puVar8 = puVar8 + 1;
      piVar7 = piVar7 + 1;
    }
    piVar4 = piVar4 + 3;
    local_10 = local_10 + -1;
  } while (local_10 != 0);
  puVar8 = (uint *)(unaff_EBX + 0xd944);
  local_c = 0;
  iVar10 = 0x13a;
  do {
    uVar6 = *puVar5 + puVar5[1];
    puVar8[1] = uVar6;
    uVar2 = *puVar8;
    puVar9 = puVar8;
    iVar3 = iVar10;
    while (uVar6 < uVar2) {
      puVar1 = puVar9 + -1;
      puVar9 = puVar9 + -1;
      iVar3 = iVar3 + -1;
      uVar2 = *puVar1;
    }
    _Size = (iVar10 - iVar3) * 4;
    puVar9 = (uint *)(unaff_EBX + 0xd460 + iVar3 * 4);
    _memmove((void *)(unaff_EBX + 0xd464 + iVar3 * 4),puVar9,_Size);
    *puVar9 = uVar6;
    piVar4 = (int *)(unaff_EBX + 0xece4 + iVar3 * 4);
    _memmove((void *)(unaff_EBX + 0xece8 + iVar3 * 4),piVar4,_Size);
    puVar5 = puVar5 + 2;
    *piVar4 = local_c;
    local_c = local_c + 2;
    iVar10 = iVar10 + 1;
    puVar8 = puVar8 + 1;
  } while (iVar10 < 0x273);
  piVar4 = (int *)(unaff_EBX + 0xece8);
  iVar10 = 2;
  do {
    iVar3 = piVar4[-1];
    *(int *)(unaff_EBX + 0xde30 + iVar3 * 4) = iVar10 + -2;
    if (iVar3 < 0x273) {
      *(int *)(unaff_EBX + 0xde34 + iVar3 * 4) = iVar10 + -2;
    }
    iVar3 = *piVar4;
    *(int *)(unaff_EBX + 0xde30 + iVar3 * 4) = iVar10 + -1;
    if (iVar3 < 0x273) {
      *(int *)(unaff_EBX + 0xde34 + iVar3 * 4) = iVar10 + -1;
    }
    iVar3 = piVar4[1];
    *(int *)(unaff_EBX + 0xde30 + iVar3 * 4) = iVar10;
    if (iVar3 < 0x273) {
      *(int *)(unaff_EBX + 0xde34 + iVar3 * 4) = iVar10;
    }
    iVar3 = iVar10 + 1;
    piVar4 = piVar4 + 3;
    iVar10 = iVar10 + 3;
  } while (iVar3 < 0x273);
  return;
}

