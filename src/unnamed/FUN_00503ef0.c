/* FUN_00503ef0 - 0x00503ef0 in the original binary.
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


void __fastcall FUN_00503ef0(undefined4 param_1,undefined4 *param_2,undefined4 *regEax,
                             undefined4 *regEbx)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  while (regEax != param_2) {
    puVar1 = regEax + 0xd;
    puVar3 = regEbx;
    puVar4 = regEax;
    for (iVar2 = 0xd; regEax = puVar1, iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
  }
  return;
}

