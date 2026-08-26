/* FUN_0040cfe0 - 0x0040cfe0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ESI RECOVERED (2026-08-25): an immediate at all three sites -- 0 twice and 1
 * once.  The two FUN_00445450 sites are the pair that needed care: they are
 * adjacent source lines separated only by an inline string-copy loop, so that
 * loop's own `jne` is the only branch between them and neither call can be
 * reached without the other.  VA order is source order there, which makes the
 * first 0 and the second 1.
 */
#include "ghidra_types.h"


int __fastcall FUN_0040cfe0(undefined4 param_1,uint param_2,int regEax,uint regEsi)
{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(*(int *)(regEax + 4) + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  while( true ) {
    if (param_2 < uVar1) {
      return 0;
    }
    if (uVar1 == param_2) break;
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar1 = *(uint *)(iVar2 + 4);
  }
  iVar2 = *(int *)(iVar2 + 0x10);
  uVar1 = *(uint *)(iVar2 + 8);
  if (regEsi < uVar1) {
    return 0;
  }
  while (uVar1 != regEsi) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar1 = *(uint *)(iVar2 + 8);
    if (regEsi < uVar1) {
      return 0;
    }
  }
  if (iVar2 == 0) {
    return 0;
  }
  return iVar2 + 0x48;
}

