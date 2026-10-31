/* TextBoxWidget_ScalarDelete - slot 0 of the text-box vtable (orig .data
 * 0x55208c; the slot's real target is DeletePoisonedBaseObject, 0x40ca00).
 *
 * A convention adapter, NOT a port of a separate original function, in the
 * same way AvatarWidget_SetNamedState adapts 0x461c60. 0x40ca00 is
 * __thiscall with one callee-cleaned stack argument (`mov esi,ecx` at
 * 0x40ca01, `test byte [esp+8],1`, `ret 4` at 0x40ca1d). Its C port,
 * DeletePoisonedBaseObject, is erased-__thiscall cdecl with `this` first,
 * which is right for its direct callers. The text boxes, though, live in
 * g_activeObjectRegistry2, and that registry's slot-0 dispatchers share
 * code with the button registry, whose nodes are C++ CButtonWidgets.
 * SweepActiveObjectRegistry already calls slot 0 as __fastcall(this, dummy
 * EDX, flag), and RemoveTextBoxWidget now does the same. So the table entry
 * must take `this` in ECX and clean the flag itself, which is what this
 * adapter does, before forwarding to the cdecl port.
 */
#include "ghidra_types.h"

void * __fastcall TextBoxWidget_ScalarDelete(void *thisPtr, int dummyEDX, int freeFlag)

{
  (void)dummyEDX;
  return DeletePoisonedBaseObject(thisPtr,freeFlag);
}
