/* FUN_00503ef0 - 0x00503ef0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00503ef0(undefined4 param_1,undefined4 *param_2)

{
  undefined4 *in_EAX;
  undefined4 *puVar1;
  int iVar2;
  undefined4 *unaff_EBX;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  while (in_EAX != param_2) {
    puVar1 = in_EAX + 0xd;
    puVar3 = unaff_EBX;
    puVar4 = in_EAX;
    for (iVar2 = 0xd; in_EAX = puVar1, iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
  }
  return;
}

