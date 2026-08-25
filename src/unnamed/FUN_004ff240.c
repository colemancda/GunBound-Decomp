/* FUN_004ff240 - 0x004ff240 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-08-25): the DESTINATION of a ~0x1758-byte record copy.
 * Both call sites are in FUN_004fed40 -- one on the hot path, one in the cold
 * block past its epilogue -- and both set it with `lea eax,[esi+4]` where ESI
 * is the node the map find or insert just returned, i.e. the source's iVar2.
 * EDX (param_2) is the copy SOURCE and is FUN_004fed40's own second stack
 * parameter, read at [esp+0x20] on the hot path and [esp+0x1c] on the cold
 * one -- different offsets, the same E+8 slot.  ECX is a phantom.
 */
#include "ghidra_types.h"


void __fastcall FUN_004ff240(undefined4 param_1,undefined4 *param_2,undefined4 *regEax)

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
  regEax[0x5d4] = param_2[0x5d4];
  regEax[0x5d5] = param_2[0x5d5];
  *(undefined1 *)(regEax + 0x5d6) = *(undefined1 *)(param_2 + 0x5d6);
  return;
}

