/* FUN_00504030 - 0x00504030 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00504030(undefined4 param_1,undefined4 *param_2)

{
  undefined4 *in_EAX;
  int iVar1;
  undefined4 *unaff_EBX;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  while (unaff_EBX != param_2) {
    param_2 = (undefined4 *)((int)param_2 + -0x1e);
    in_EAX = (undefined4 *)((int)in_EAX + -0x1e);
    puVar2 = param_2;
    puVar3 = in_EAX;
    for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    *(undefined2 *)puVar3 = *(undefined2 *)puVar2;
  }
  return;
}

