/* FUN_004d25e0 - 0x004d25e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __fastcall FUN_004d25e0(int param_1)

{
  uint uVar1;
  int iVar2;
  int unaff_EBX;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 local_5000 [5119];
  undefined4 uStack_4;
  
  uStack_4 = 0x4d25ea;
  iVar3 = *(int *)(unaff_EBX + 0x44d0) - param_1;
  FUN_004f70b0(*(undefined4 *)(unaff_EBX + 0x84e8),*(undefined2 *)(unaff_EBX + 0x4d4),local_5000,
               0x5000);
  uVar4 = ((iVar3 + 5) / 0xc) * 0x10;
  puVar5 = local_5000;
  puVar6 = (undefined4 *)(param_1 + 0x4d6 + unaff_EBX);
  for (uVar1 = (((int)uVar4 < 0) - 1 & uVar4) >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
    puVar6 = (undefined4 *)((int)puVar6 + 1);
  }
  *(uint *)(unaff_EBX + 0x44d0) = *(int *)(unaff_EBX + 0x44d0) + (uVar4 - (iVar3 + -6));
  return;
}

