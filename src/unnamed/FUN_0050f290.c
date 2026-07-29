/* FUN_0050f290 - 0x0050f290 in the original binary.
 *
 * No confirmed real name/purpose - the panel manager's per-tick pending-
 * destroy sweep: walks a list rooted at param_1+4 (a widget "free/destroy
 * queue" separate from the manager's main panel list at param_1+8), and
 * for any entry with its destroy flag (+0x1d) set, unlinks it from both
 * the queue and the manager's live count, recycles the node onto a free
 * list, and tears the widget down.
 *
 * DROPPED-ARGUMENT FIX (2026-07-29): FOUR calls in this function had their
 * register-passed arguments dropped by Ghidra, confirmed via objdump at
 * 0x50f290-0x50f30a:
 *   - `(**(code**)(*_Memory + 0x20))()` (0x50f2b0, `call [eax+0x20]`) -
 *     `this`=_Memory (`mov ecx,ebx` at 0x50f2ae; ebx==_Memory).
 *   - `PanelManager_ReleasePool()` (0x50f2f5) - `this`=ebp==piVar1
 *     (`mov ecx,ebp` at 0x50f2f3; ebp was set to `param_1+4` at entry).
 *   - `(**(code**)(*param_1 + 0x18))()` (0x50f300, `call [edx+0x18]`) -
 *     `this`=param_1 (`mov ecx,[esp+0x10]` at 0x50f2fa reloads the
 *     original incoming ECX saved at function entry).
 *   - `WidgetChildArray_Destroy()` (0x50f305) - `this`=_Memory
 *     (`mov ecx,ebx` at 0x50f303).
 * All four are real C++ __thiscall/vtable dispatches (this in ECX), so
 * the two raw vtable calls use the codebase's established
 * `(*(FnT *)(*(int *)obj + N))(obj, 0, ...)` idiom for an erased-
 * __thiscall vtable slot (ghidra_types.h keeps __fastcall real under
 * MSVC but erases __thiscall - see WndProc.c's StateSlot6DispatchFn /
 * PanelManager_DispatchKeyDown.c's PanelKeyHandlerFn for the same
 * pattern), and the two named callees (already declared __fastcall with
 * a real leading param) are simply passed their argument explicitly.
 * NOTE: an earlier attempt at this fix used `((FnT)(*(int*)*obj + N))(obj,0)`
 * - WRONG: that reads the function pointer stored at vtable SLOT 0 (the
 * destructor) instead of the vtable base, adds N to a *function pointer*
 * instead of the vtable base address, and skips the final dereference
 * through the slot address entirely - it compiles clean but calls through
 * garbage, reproducing the exact "EIP lands on raw stack/heap bytes"
 * crash this whole investigation was chasing. Caught by re-deriving the
 * idiom from WndProc.c/PanelManager_DispatchKeyDown.c and comparing
 * side-by-side before reapplying.
 *
 * This function's OWN incoming `param_1` was ALSO dropped at its sole
 * call site (GameTick.c: orig 0x41329a `mov ecx,0xe53c40` =
 * &g_uiPanelManager immediately before `call 0x50f290`) - see GameTick.c's
 * own fix comment. With param_1 undefined, this whole function walked
 * whatever widget pointer PanelManager_DispatchKeyDown happened to leave
 * in ECX as if it were g_uiPanelManager, treating unrelated widget memory
 * as a linked list and eventually indirect-calling through garbage - the
 * root cause of a lobby-wide "any keypress crashes the game ~1s later"
 * bug, reproduced live (EIP lands on raw stack bytes at a constant
 * ESP-relative offset, the classic wild-call-through-garbage-pointer
 * signature already seen elsewhere in this codebase).
 */
#include "ghidra_types.h"

typedef void (__fastcall *VtableSlot8Fn)(void *thisPtr, int dummyEDX);
typedef void (__fastcall *VtableSlot6Fn)(void *thisPtr, int dummyEDX);

void __fastcall FUN_0050f290(int *param_1)

{
  int *piVar1;
  int *_Memory;
  int *piVar2;
  int iVar3;
  int *piVar4;

  piVar1 = param_1 + 1;
  piVar2 = (int *)*piVar1;
  while (piVar4 = piVar2, piVar4 != (int *)0x0) {
    _Memory = (int *)piVar4[2];
    piVar2 = (int *)*piVar4;
    (*(VtableSlot8Fn *)(*(int *)_Memory + 0x20))(_Memory,0);
    if (*(char *)((int)_Memory + 0x1d) != '\0') {
      if (piVar4 == (int *)*piVar1) {
        *piVar1 = *piVar4;
      }
      else {
        *(int *)piVar4[1] = *piVar4;
      }
      if (piVar4 == (int *)param_1[2]) {
        param_1[2] = piVar4[1];
      }
      else {
        *(int *)(*piVar4 + 4) = piVar4[1];
      }
      *piVar4 = param_1[5];
      iVar3 = param_1[3];
      param_1[5] = (int)piVar4;
      param_1[3] = iVar3 + -1;
      if (iVar3 + -1 == 0) {
        PanelManager_ReleasePool((undefined4 *)piVar1);
      }
      (*(VtableSlot6Fn *)(*(int *)param_1 + 0x18))(param_1,0);
      WidgetChildArray_Destroy((undefined4 *)_Memory);
      _free(_Memory);
    }
  }
  return;
}

