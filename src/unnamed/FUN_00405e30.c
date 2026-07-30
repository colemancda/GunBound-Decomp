/* FUN_00405e30 - 0x00405e30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-ARGS + SPLIT-ARRAY FIX (2026-07-30): its own header already
 * said "referenced by at least one already-ported function" - that
 * caller is HandleActiveObjectMouseMove.c's `xor eax,eax; call
 * 0x405e30`, confirmed via objdump (orig 0x40620a-0x40620c): ECX (still
 * holding `piVar1`, the widget losing hover) is this function's real
 * `this`/param_1, EAX=0 is a state-table index, and the call site was
 * dropping BOTH - `FUN_00405e30();` with zero args, live-reproduced as
 * a crash on the AVATAR button's hover-out (any mouse move off ANY
 * previously-hovered widget takes this path, so this bug fires
 * constantly, not just for AVATAR - AVATAR was just the first widget
 * whose hover state actually got exercised in live testing so far).
 * `local_18[4]` + `local_8` + `local_4` are Ghidra's split view of one
 * real 6-element `char*[6]` state-name table (their stack offsets -0x18,
 * -0x18+0x10=-0x8, -0x18+0x14=-0x4 line up exactly) - reading
 * `local_18[in_EAX]` for `in_EAX` up to 5 was undefined behaviour in C
 * even before the dropped-args fix; coalesced into one real array.
 * The vtable dispatch itself is CButtonWidget::SetState (slot 1, same
 * as HandleActiveObjectMouseMove's own two calls) - real __thiscall,
 * fixed with the same __fastcall+dummy-EDX idiom already established
 * there.
 */
#include "ghidra_types.h"

typedef void (__fastcall *WidgetSetStateFn)(void *thisPtr, int dummyEDX, void *name);


void __fastcall FUN_00405e30(int *param_1,int stateIndex)

{
  char *stateNames[6];

  stateNames[0] = s_ready_00551e80;
  stateNames[1] = &DAT_00551e78;
  stateNames[2] = s_mouse_00551e70;
  stateNames[3] = s_disable_00551e68;
  stateNames[4] = s_select_00551e60;
  stateNames[5] = s_active_00551e58;
  if ((stateIndex == 0) && ((char)param_1[0x13] == '\x01')) {
    (*(WidgetSetStateFn *)(*param_1 + 4))(param_1,0,s_active_00551e58);
    return;
  }
  (*(WidgetSetStateFn *)(*param_1 + 4))(param_1,0,stateNames[stateIndex]);
  return;
}
