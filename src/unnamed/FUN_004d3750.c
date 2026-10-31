/* FUN_004d3750 - 0x004d3750 in the original binary.
 *
 * Slot 2 (the per-frame tick) of vtable 0x556a40, the 0x38-byte objects
 * State09_ReadyRoom_OnEnter allocates into the state's +0x6fc slot array
 * (one per room slot, paired with the avatar widget at +0x700).
 * find_vtable_refs.py finds 0x4d3750 only at 0x556a48, and callsite_regs.py
 * finds no direct calls. CARVED 2026-10-30 from the disassembly
 * (27 bytes, plain ret):
 *
 *   0x4d3750 mov eax,ecx / call 0x450730      ; AdvanceSpriteAnimation, EAX = this
 *   0x4d3757 mov cl,[eax+0x34] / test / je ret ; the animation's end flag
 *   0x4d375e mov edx,[eax] / push 0x552230 / mov ecx,eax / call [edx+4]
 *                                              ; this->slot1("normal")
 *
 * AdvanceSpriteAnimation leaves EAX as it found it (every path addresses
 * the object through EAX and none writes it), so the +0x34 test and the
 * slot-1 call are on `this`. It is the first half of the avatar widget's
 * slot 2 (FUN_0044fcb0): advance, and when the animation has finished,
 * drop back to the "normal" state. Both slot-2 bodies are dispatched by
 * the same loop in State09_ReadyRoom_OnTick, so this one is ported the
 * same way, __fastcall(int *this), and slot 1 is called with the
 * __fastcall + dummy-EDX idiom that FUN_0044fcb0 uses for the same
 * slot-1 target (0x461c60, AvatarWidget_SetNamedState in the port's
 * tables).
 */
#include "ghidra_types.h"

/* Slot 1 of this object's vtable: __thiscall(name), one callee-cleaned
 * stack argument - __fastcall + dummy EDX, as in FUN_0044fcb0.c. */
typedef void (__fastcall *VtableSlot1StrFn)(void *thisPtr, int dummyEDX, const char *str);

void __fastcall FUN_004d3750(int *param_1)

{
  AdvanceSpriteAnimation((int)param_1);
  if ((char)param_1[0xd] != '\0') {
    ((VtableSlot1StrFn)*(code **)(*param_1 + 4))((void *)param_1,0,s_normal_00552230);
  }
  return;
}
