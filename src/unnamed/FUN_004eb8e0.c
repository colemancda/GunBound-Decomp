/* FUN_004eb8e0 - 0x004eb8e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_004eb8e0(uint param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  while( true ) {
    if (param_2 < uVar1) {
      return;
    }
    if (uVar1 == param_2) break;
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar1 = *(uint *)(iVar2 + 4);
  }
  iVar2 = *(int *)(iVar2 + 0x10);
  uVar1 = *(uint *)(iVar2 + 8);
  if (param_1 < uVar1) {
    return;
  }
  while (uVar1 != param_1) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar1 = *(uint *)(iVar2 + 8);
    if (param_1 < uVar1) {
      return;
    }
  }
  if ((int)param_1 < 0) {
    return;
  }
  if (*(char *)(iVar2 + 0x18) == '\x01') {
    FUN_004ed870();
    return;
  }
  FUN_004ebaf0();
  return;
}

