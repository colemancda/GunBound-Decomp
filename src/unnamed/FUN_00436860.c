/* FUN_00436860 - 0x00436860 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00436860(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  void *pvVar3;
  
  cVar1 = FUN_004065a0();
  if (cVar1 == '\0') {
    if (param_1 != -1) {
      iVar2 = FindSpriteFrame();
      if (iVar2 != 0) {
        *(undefined4 *)(iVar2 + 0x40) = 0;
        *(int *)(iVar2 + 0x48) = *(int *)(iVar2 + 0x48) + param_2;
        return;
      }
    }
    pvVar3 = operator_new(0x50);
    if (pvVar3 == (void *)0x0) {
      iVar2 = 0;
    }
    else {
      FUN_00468620();
    }
    *(undefined4 *)(iVar2 + 0x3c) = param_4;
    *(int *)(iVar2 + 0x48) = param_2;
    *(undefined4 *)(iVar2 + 0x38) = param_3;
    RegisterActiveObject();
  }
  return;
}

