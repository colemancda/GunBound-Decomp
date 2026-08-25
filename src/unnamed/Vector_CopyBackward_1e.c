/* Vector_CopyBackward_1e - 0x00504030 in the original binary.
 *
 * _Copy_backward over 0x1e-byte elements: walk both ranges downward so an
 * overlapping shift-up cannot clobber what it has yet to read.
 *
 * EAX and EBX RECOVERED (2026-08-25): a vector _Insert_n's copy-backward over
 * 0x1e-byte elements.  EAX is _Oldend (the destination end), EDX _Oldend minus
 * the inserted count, EBX _Where -- the loop's stop pointer.  ECX is a phantom
 * (`mov ecx,7` before any read), so the call passes 0 for that slot.
 */
#include "ghidra_types.h"


void __fastcall Vector_CopyBackward_1e(undefined4 param_1,undefined4 *param_2,undefined4 *regEax,
                             undefined4 *regEbx)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  while (regEbx != param_2) {
    param_2 = (undefined4 *)((int)param_2 + -0x1e);
    regEax = (undefined4 *)((int)regEax + -0x1e);
    puVar2 = param_2;
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

