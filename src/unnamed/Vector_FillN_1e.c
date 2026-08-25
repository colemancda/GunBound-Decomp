/* Vector_FillN_1e - 0x00504010 in the original binary.
 *
 * _Ufill over 0x1e-byte elements: copy the one element at EBX into every
 * slot from EAX up to param_2.
 *
 * EAX and EBX RECOVERED (2026-08-25): another of the vector _Insert_n helpers
 * around Vector_CopyBackward_1e.  ECX is a phantom (`mov ecx,7` before any read) so the
 * call passes 0 there; EDX and EAX are the range this walks, and EBX is the
 * by-value element buffer in the caller's frame.
 */
#include "ghidra_types.h"


void __fastcall Vector_FillN_1e(undefined4 param_1,undefined4 *param_2,undefined4 *regEax,
                             undefined4 *regEbx)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  for (; regEax != param_2; regEax = (undefined4 *)((int)regEax + 0x1e)) {
    puVar2 = regEbx;
    puVar3 = regEax;
    for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    *(undefined2 *)puVar3 = *(undefined2 *)puVar2;
  }
  return;
}

