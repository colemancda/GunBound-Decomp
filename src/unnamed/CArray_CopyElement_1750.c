/* CArray_CopyElement_1750 - 0x004ff2c0 in the original binary.
 *
 * Copies one 0x1750-byte record into an array slot for CArray_Add_1750:
 * four header dwords, then a byte-count-driven block copy, then the trailing
 * dword at +0x174c.
 *
 * EAX RECOVERED (2026-08-25): the DESTINATION.  Its one call site
 * (0x4fee06, in CArray_Add_1750) computes `eax = uVar1 * 0x1750 + *regEax` --
 * the address of element uVar1 in the vector -- and param_2 (EDX) is the
 * record to copy in, which CArray_Add_1750 received as its own param_1.
 * ECX stays a phantom: the entry's `mov ecx,edx` at 0x4ff2c3 overwrites it
 * before any read, so the call passes 0 for that slot.
 */
#include "ghidra_types.h"


void __fastcall CArray_CopyElement_1750(undefined4 param_1,undefined4 *param_2,undefined4 *regEax)

{
  ushort uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  *regEax = *param_2;
  regEax[1] = param_2[1];
  regEax[2] = param_2[2];
  *(undefined2 *)(regEax + 3) = *(undefined2 *)(param_2 + 3);
  uVar1 = *(ushort *)((int)param_2 + 0xe);
  *(ushort *)((int)regEax + 0xe) = uVar1;
  puVar3 = param_2 + 4;
  puVar4 = regEax + 4;
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
  regEax[0x5d3] = param_2[0x5d3];
  return;
}

