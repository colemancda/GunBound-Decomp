/* CInputDevice_Release - 0x004ede20 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): this one address is slot 2 of BOTH device
 * vtables, 0x55745c (keyboard) and 0x557484 (mouse), so it is the shared
 * input-device base behaviour, hence the CInputDevice_ prefix of its
 * siblings CInputDevice_ScalarDeletingDestructor and
 * CInputDevice_BaseDestructor (slot 0 and the destructor in those
 * vtables). Its callee slots are IDirectInputDevice8::Unacquire
 * (vtbl+0x20) then Release (vtbl+8), after which the device pointer at
 * obj+4 is nulled and the acquired flag at obj+0x54, set by the Initialize
 * methods, is cleared.
 */
#include "ghidra_types.h"


void __fastcall CInputDevice_Release(int param_1)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 4);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x20))(piVar1);
    *(undefined1 *)(param_1 + 0x54) = 0;
    (**(code **)(**(int **)(param_1 + 4) + 8))(*(int **)(param_1 + 4));
    *(undefined4 *)(param_1 + 4) = 0;
  }
  return;
}

