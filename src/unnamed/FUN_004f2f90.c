/* FUN_004f2f90 - 0x004f2f90 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_004f2f90(undefined4 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  int in_EAX;
  
  iVar1 = *(int *)(*(int *)(in_EAX + 4) + 0x1c);
  uVar2 = *(uint *)(iVar1 + 4);
  while( true ) {
    if (param_2 < uVar2) {
      return 0;
    }
    if (uVar2 == param_2) break;
    iVar1 = *(int *)(iVar1 + 0x1c);
    uVar2 = *(uint *)(iVar1 + 4);
  }
  return iVar1;
}

