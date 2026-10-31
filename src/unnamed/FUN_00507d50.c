/* FUN_00507d50 - 0x00507d50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * SetFocus `this` RECOVERED (2026-10-30): when no type-2 child (a
 * CEditBox) has its +4 focus flag set, the first one is focused with
 * `mov eax,[ecx+0xc] / mov ecx,[eax+edx*4] / mov edx,[ecx] / push 1 /
 * call [edx]` (0x507da2-0x507dac): slot 0, SetFocus(1), with the child in
 * ECX. The raw `code *` call pushed only the flag and left ECX unset; it
 * now uses the __fastcall + dummy-EDX idiom.
 */
#include "ghidra_types.h"

/* Slot 0 (+0x00) of a CWidget: SetFocus(bool), a one-argument __thiscall.
 * The child found here is a CEditBox (type id 2), a C++ class whose slot 0
 * (0x506fb0) takes `this` in ECX and ends in ret 4, so the call goes
 * through a __fastcall pointer with a dummy EDX. */
typedef void (__fastcall *WidgetSetFocusFn)(void *thisPtr, int dummyEDX, int active);


void __fastcall FUN_00507d50(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = 0xffffffff;
  uVar1 = 0;
  if (*(uint *)(param_1 + 0x10) != 0) {
    do {
      if (*(uint *)(param_1 + 0x10) <= uVar1) goto LAB_00507d98;
      if (*(int *)(*(int *)(*(int *)(param_1 + 0xc) + uVar1 * 4) + 0x20) == 2) {
        if (uVar2 == 0xffffffff) {
          uVar2 = uVar1;
        }
        if (*(uint *)(param_1 + 0x10) <= uVar1) goto LAB_00507d98;
        if (*(char *)(*(int *)(*(int *)(param_1 + 0xc) + uVar1 * 4) + 4) != '\0') {
          return;
        }
      }
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)(param_1 + 0x10));
    if (uVar2 != 0xffffffff) {
      if (*(uint *)(param_1 + 0x10) <= uVar2) {
LAB_00507d98:
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      ((WidgetSetFocusFn)(*(void ***)*(void **)(*(int *)(param_1 + 0xc) + uVar2 * 4))[0])
          (*(void **)(*(int *)(param_1 + 0xc) + uVar2 * 4),0,1);
    }
  }
  return;
}

