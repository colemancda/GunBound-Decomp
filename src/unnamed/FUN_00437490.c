/* FUN_00437490 - 0x00437490 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): in_EAX is param_4 at all four
 * call sites, and both callers pin it the same way.  SpawnMine's
 * `dec edi / or edi,0xfffffff8 / inc edi` at 0x437629 is character for
 * character its own `param_4 = (param_4 - 1 | 0xfffffff8) + 1;`, so edi is
 * param_4 there; SpawnSuperMine loads edi from [esp+0x2c], which under its
 * SEH triple plus four prologue saves is E+0x10, i.e. param_4 -- witnessed by
 * the same prologue's `mov eax,[esp+0x10]` = E+4 = param_1, the argument its
 * PeekPacketChecksumBool(param_1 + 4) on the next line takes.  Both callers
 * then do `mov eax,edi` immediately before each call, including the retry
 * inside the `while (iVar2 == -1)` loop.
 */
#include "ghidra_types.h"


uint FUN_00437490(int regEax)

{
  uint uVar1;
  int in_EAX = regEax;
  uint uVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  
  uVar2 = in_EAX << 3;
  iVar4 = 0;
  do {
    uVar1 = *(uint *)(*(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c) + 4);
    iVar3 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    if (0x186a3 < uVar1) {
      return uVar2;
    }
    while (uVar1 != 0x186a3) {
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar1 = *(uint *)(iVar3 + 4);
      if (0x186a3 < uVar1) {
        return uVar2;
      }
    }
    iVar3 = *(int *)(iVar3 + 0x10);
    bVar5 = *(uint *)(iVar3 + 8) == uVar2;
    if (uVar2 <= *(uint *)(iVar3 + 8) && !bVar5) {
      return uVar2;
    }
    while (!bVar5) {
      iVar3 = *(int *)(iVar3 + 0x10);
      bVar5 = *(uint *)(iVar3 + 8) == uVar2;
      if (uVar2 < *(uint *)(iVar3 + 8)) {
        return uVar2;
      }
    }
    iVar4 = iVar4 + 1;
    uVar2 = uVar2 + 1;
  } while (iVar4 < 8);
  return 0xffffffff;
}

