/* FUN_00421870 - 0x00421870 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00421870(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *unaff_EBX;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  iVar1 = 0;
  for (; param_1 != 0; param_1 = param_1 + -1) {
    iVar1 = iVar1 + 1 + (int)*(char *)(iVar1 + param_2);
  }
  if (unaff_EBX != (undefined4 *)0x0) {
    if (*(char *)(iVar1 + param_2) < '\0') {
      uVar2 = 0;
    }
    else {
      uVar2 = (uint)*(char *)(iVar1 + param_2);
    }
    puVar4 = (undefined4 *)(iVar1 + 1 + param_2);
    puVar5 = unaff_EBX;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
    *(undefined1 *)((int)*(char *)(iVar1 + param_2) + (int)unaff_EBX) = 0;
  }
  return;
}

