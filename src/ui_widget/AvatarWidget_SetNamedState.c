/* AvatarWidget_SetNamedState - slot 1 of the State07-embedded
 * avatar-preview widget's vtable (orig .data 0x555b38; the slot's real
 * target is ResolveNamedState, 0x461c60).
 *
 * A convention-correct adapter, NOT a port of 0x461c60's body:
 * ResolveNamedState is deliberately stubbed to a no-op for bring-up
 * (see its header - the named-state lookup is cosmetic animation
 * plumbing), and its C symbol is declared with a different, K&R-empty
 * convention that the ~25 existing direct call sites depend on - so the
 * vtable cannot point at it without unbalancing the stack at every
 * virtual dispatch. The original slot target is __thiscall with ONE
 * callee-cleaned stack arg (`mov esi,ecx` + `mov ebx,[esp+0x10]`,
 * `ret 4`), which under this project's idiom for genuine C++ vtable
 * methods is __fastcall + dummy EDX. Both dispatch sites
 * (State07_AvatarStore_OnEnter's VtableSlot1StrFn and FUN_0044fcb0's
 * update-path calls) use exactly that shape, so this adapter keeps
 * every ESP balanced while preserving the established no-op bypass.
 * When ResolveNamedState is ever really ported, this body should
 * forward to it. */
#include "ghidra_types.h"

void __fastcall AvatarWidget_SetNamedState(void *thisPtr, int dummyEDX, const char *name)

{
  (void)thisPtr;
  (void)dummyEDX;
  (void)name;
  return;
}
