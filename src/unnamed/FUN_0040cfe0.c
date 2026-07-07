/* FUN_0040cfe0 - 0x0040cfe0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_0040cfe0(undefined4 param_1,uint param_2)

{
  uint uVar1;
  int in_EAX;
  int iVar2;
  uint unaff_ESI;
  
  iVar2 = *(int *)(*(int *)(in_EAX + 4) + 0x1c);
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
  if (unaff_ESI < uVar1) {
    return 0;
  }
  while (uVar1 != unaff_ESI) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar1 = *(uint *)(iVar2 + 8);
    if (unaff_ESI < uVar1) {
      return 0;
    }
  }
  if (iVar2 == 0) {
    return 0;
  }
  return iVar2 + 0x48;
}

