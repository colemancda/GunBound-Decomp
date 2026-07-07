/* FUN_00503f10 - 0x00503f10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00503f10(undefined4 param_1,undefined4 *param_2)

{
  undefined4 *in_EAX;
  int iVar1;
  undefined4 *unaff_EBX;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  while (unaff_EBX != param_2) {
    param_2 = param_2 + -0xd;
    in_EAX = in_EAX + -0xd;
    puVar2 = param_2;
    puVar3 = in_EAX;
    for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  return;
}

