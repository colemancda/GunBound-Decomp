/* FUN_004e6df0 - 0x004e6df0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004e6df0(void)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int unaff_EBX;
  undefined4 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 local_400 [256];
  
  DAT_0056dc97 = *(undefined1 *)(unaff_EBX + 0x44df4);
  DAT_0056dc95 = *(undefined1 *)(unaff_EBX + 0x44dee);
  DAT_0056dc9a = *(undefined1 *)(unaff_EBX + 0x44def);
  iVar3 = 0x21;
  cVar1 = *(char *)(unaff_EBX + 0x44dee) + *(char *)(unaff_EBX + 0x44def) +
          *(char *)(unaff_EBX + 0x44df4) + -0x34;
  if (0x21 < *(int *)(unaff_EBX + 0x44fec)) {
    do {
      cVar1 = cVar1 + *(char *)(unaff_EBX + 0x44dec + iVar3);
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)(unaff_EBX + 0x44fec));
  }
  *(char *)(unaff_EBX + 0x44df0) = cVar1;
  *(undefined1 *)(unaff_EBX + 0x44ff4) = 1;
  FUN_004f48b0(1);
  iVar3 = *(int *)(unaff_EBX + 0x44fec) + -0x12;
  iVar5 = 0;
  if (0 < (int)(iVar3 + (iVar3 >> 0x1f & 0xfU)) >> 4) {
    puVar4 = local_400;
    do {
      FUN_004f4d10(puVar4,unaff_EBX + 0x44ff8);
      iVar3 = *(int *)(unaff_EBX + 0x44fec) + -0x12;
      iVar5 = iVar5 + 1;
      puVar4 = puVar4 + 4;
    } while (iVar5 < (int)(iVar3 + (iVar3 >> 0x1f & 0xfU)) >> 4);
  }
  iVar3 = *(int *)(unaff_EBX + 0x44fec) + -0x12;
  uVar2 = ((int)(iVar3 + (iVar3 >> 0x1f & 0xfU)) >> 4) * 0x10;
  *(uint *)(unaff_EBX + 0x44fec) = uVar2 + 0x21;
  puVar4 = local_400;
  puVar6 = (undefined4 *)(unaff_EBX + 0x44e0d);
  for (uVar2 = (((int)uVar2 < 0) - 1 & uVar2) >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar6 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar6 = puVar6 + 1;
  }
  for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
    *(undefined1 *)puVar6 = *(undefined1 *)puVar4;
    puVar4 = (undefined4 *)((int)puVar4 + 1);
    puVar6 = (undefined4 *)((int)puVar6 + 1);
  }
  return;
}

