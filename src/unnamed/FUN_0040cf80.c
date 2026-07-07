/* FUN_0040cf80 - 0x0040cf80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0040cf80(undefined4 param_1,uint param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  uint unaff_ESI;
  
  iVar2 = *(int *)(*(int *)(param_3 + 4) + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  if (uVar1 <= param_2) {
    while (uVar1 != param_2) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar1 = *(uint *)(iVar2 + 4);
      if (param_2 < uVar1) {
        return;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar1 = *(uint *)(iVar2 + 8);
    if (uVar1 <= unaff_ESI) {
      while (uVar1 != unaff_ESI) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar1 = *(uint *)(iVar2 + 8);
        if (unaff_ESI < uVar1) {
          return;
        }
      }
      if (*(int *)(param_3 + 8) != 0) {
        FUN_0040ccf0();
      }
      *(int *)(param_3 + 8) = iVar2;
      FUN_0040cc50();
    }
  }
  return;
}

