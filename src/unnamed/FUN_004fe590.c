/* FUN_004fe590 - 0x004fe590 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-08-25): the SOURCE record.  This is the same 0x1750-byte
 * record copy as CArray_CopyElement_1750 with the two ends swapped -- there
 * EAX is the destination, here it is what is read -- and at the single site
 * (0x4fe30a in FUN_004fe110) it is &local_2eb8, the record that function has
 * just assembled, copied out into auStack_1768.  ECX is a phantom
 * (`mov ecx,eax` before any read), so the call passes 0 for that slot.
 */
#include "ghidra_types.h"


void __fastcall FUN_004fe590(undefined4 param_1,undefined4 *param_2,undefined4 *regEax)

{
  ushort uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  *param_2 = *regEax;
  param_2[1] = regEax[1];
  param_2[2] = regEax[2];
  *(undefined2 *)(param_2 + 3) = *(undefined2 *)(regEax + 3);
  uVar1 = *(ushort *)((int)regEax + 0xe);
  *(ushort *)((int)param_2 + 0xe) = uVar1;
  puVar3 = regEax + 4;
  puVar4 = param_2 + 4;
  for (uVar2 = (uint)(uVar1 >> 2); uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  for (uVar2 = uVar1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined1 *)puVar4 = *(undefined1 *)puVar3;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  }
  return;
}

