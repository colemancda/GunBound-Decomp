/* FUN_00503f10 - 0x00503f10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX and EBX RECOVERED (2026-08-25): another of the vector _Insert_n helpers
 * around FUN_00504030.  ECX is a phantom (`mov ecx,0xd` before any read) so the
 * call passes 0 there; EDX and EAX are the range this walks, and EBX is the
 * by-value element buffer in the caller's frame.
 */
#include "ghidra_types.h"


void __fastcall FUN_00503f10(undefined4 param_1,undefined4 *param_2,undefined4 *regEax,
                             undefined4 *regEbx)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  while (regEbx != param_2) {
    param_2 = param_2 + -0xd;
    regEax = regEax + -0xd;
    puVar2 = param_2;
    puVar3 = regEax;
    for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  return;
}

