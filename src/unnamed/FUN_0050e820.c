/* FUN_0050e820 - 0x0050e820 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EBX and EDI RECOVERED (2026-08-25): `mov ebx,esi` at 0x506e7e where ESI is
 * ActivateLegacyTextInputField's own incoming EAX (its source spells that
 * `in_EAX = thisObj`), and EDI is `mov edi,[esi+8]` -- the field the line
 * above the call already tests as `*(int *)(in_EAX + 8) != 0`.
 *
 * SIBLING SetFocus(0) GETS ITS `this` (2026-10-30): EDI is the focused
 * field's parent and EBX the field (a CEditBox, from its slot-0/slot-2
 * virtuals via ActivateLegacyTextInputField). For every child other than
 * EBX the loop does `mov ecx,[edi+0xc] / mov ecx,[ecx+esi*4] /
 * mov edx,[ecx] / push 0 / call [edx]` (0x50e83b-0x50e845): slot 0,
 * SetFocus(false), a one-argument __thiscall with ECX = the child. The
 * port called `(**(code **)*child)(0)`, with no `this` and caller-clean.
 * The children are C++ CWidgets, so the call now goes through a
 * __fastcall pointer with a dummy EDX (ECX = this, the flag on the stack,
 * callee-clean of 4 bytes), the 5b858ff7 idiom.
 */
#include "ghidra_types.h"

/* Slot 0 (+0x00) of a CWidget: SetFocus(bool), a one-argument __thiscall,
 * dispatched as __fastcall with a dummy EDX - see the header. */
typedef void (__fastcall *WidgetSetFocusFn)(void *thisPtr, int dummyEDX, int active);


void FUN_0050e820(int regEbx,int regEdi)

{
  uint uVar1;
  
  uVar1 = 0;
  if (*(int *)(regEdi + 0x10) != 0) {
    if (*(int *)(regEdi + 0x10) == 0) {
LAB_0050e851:
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    do {
      if (*(int *)(*(int *)(regEdi + 0xc) + uVar1 * 4) != regEbx) {
        if (*(uint *)(regEdi + 0x10) <= uVar1) goto LAB_0050e851;
        {
          void *child = *(void **)(*(int *)(regEdi + 0xc) + uVar1 * 4);
          ((WidgetSetFocusFn)(*(void ***)child)[0])(child, 0, 0);
        }
      }
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)(regEdi + 0x10));
  }
  return;
}

