/* FUN_00405fb0 - 0x00405fb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00405fb0(undefined4 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint unaff_ESI;
  int unaff_EDI;
  
  iVar1 = *(int *)(*(int *)(unaff_EDI + 4) + 0x1c);
  uVar2 = *(uint *)(iVar1 + 4);
  while (uVar2 <= param_2) {
    if (uVar2 == param_2) {
      puVar3 = *(undefined4 **)(iVar1 + 0x10);
      uVar2 = puVar3[2];
      if (uVar2 <= unaff_ESI) goto LAB_00405fd5;
      break;
    }
    iVar1 = *(int *)(iVar1 + 0x1c);
    uVar2 = *(uint *)(iVar1 + 4);
  }
  goto LAB_00405fe1;
  while( true ) {
    puVar3 = (undefined4 *)puVar3[4];
    uVar2 = puVar3[2];
    if (unaff_ESI < uVar2) break;
LAB_00405fd5:
    if (uVar2 == unaff_ESI) goto LAB_00405fe3;
  }
LAB_00405fe1:
  puVar3 = (undefined4 *)0x0;
LAB_00405fe3:
  if (puVar3 == *(undefined4 **)(unaff_EDI + 8)) {
    *(undefined4 *)(unaff_EDI + 8) = 0;
  }
  if (puVar3 == *(undefined4 **)(unaff_EDI + 0xc)) {
    *(undefined4 *)(unaff_EDI + 0xc) = 0;
  }
  if (puVar3 != (undefined4 *)0x0) {
    *(undefined4 *)(puVar3[3] + 0x10) = puVar3[4];
    *(undefined4 *)(puVar3[4] + 0xc) = puVar3[3];
    (**(code **)*puVar3)(1);
  }
  return;
}

