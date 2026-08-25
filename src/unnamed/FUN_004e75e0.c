/* FUN_004e75e0 - 0x004e75e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * SHORT CALLS + EAX (2026-08-25).  `ret 4` and two declared parameters mean
 * ECX is param_1 and only param_2 is pushed -- but both source sites passed a
 * single argument, so the pushed value was sitting in param_1's slot.  Both
 * sites are now written in full.
 *
 * ECX is the same field in both callers, `lea ecx,[esi+0x44dec]`, which
 * FUN_004e7140's source has already given a name two lines above its call
 * (`puVar1 = (undefined2 *)(regEax + 0x44dec)`).  EAX is the broadcast/replay
 * context base -- replayCtx in one caller, regEax in the other.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_004e75e0(ushort *param_1,int param_2,int regEax)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  if (7 < param_2) {
    return 1;
  }
  uVar3 = *(int *)(regEax + 0x40bd0) + 1U & 0x800001ff;
  if ((int)uVar3 < 0) {
    uVar3 = (uVar3 - 1 | 0xfffffe00) + 1;
  }
  if (uVar3 != *(uint *)(regEax + 0x40bd4)) {
    uVar1 = *param_1;
    puVar4 = (undefined4 *)(*(int *)(regEax + 0x40bd0) * 0x200 + 0x3d0 + regEax);
    for (uVar2 = (uint)(uVar1 >> 2); uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar4 = *(undefined4 *)param_1;
      param_1 = param_1 + 2;
      puVar4 = puVar4 + 1;
    }
    for (uVar2 = uVar1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(char *)puVar4 = (char)*param_1;
      param_1 = (ushort *)((int)param_1 + 1);
      puVar4 = (undefined4 *)((int)puVar4 + 1);
    }
    *(int *)(regEax + 0x403d0 + *(int *)(regEax + 0x40bd0) * 4) = param_2;
    *(uint *)(regEax + 0x40bd0) = uVar3;
    return 1;
  }
  return 0;
}

