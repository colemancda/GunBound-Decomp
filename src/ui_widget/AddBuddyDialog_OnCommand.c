/* AddBuddyDialog_OnCommand - 0x00505700 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-30), CERTAIN: the add-buddy dialog's OnCommand
 * override. The original's vtable 0x557e68 holds this at slot 7
 * (+0x1c), the slot src/cxx/Widget.h declares as CWidget::OnCommand
 * (evt, id, arg); `this` arrives in ECX (`mov esi,ecx` at 0x505710),
 * every exit is `ret 0xc`, and both paths end in the base slot-7 body
 * Widget_OnCommandDefault. Vtable 0x557e68 is stored only by
 * FUN_00508b90 (0x508bf2), whose one caller is BuddyPanel_OnCommand on
 * the buddy panel's "Add" label (id 1, 0x505daf) - the "add buddy ID"
 * dialog of docs/widgets.md ("Add-buddy dialog - 0x557e68, id 10000",
 * runtime-confirmed). The ids handled match that dialog's children as
 * FUN_00508b90 builds them: label id 0 (ADD) or the edit box's Enter
 * (evt 0x1000) runs the submit FUN_00505580; label id 1 (CLOSE), or
 * evt 0x1001, sets the +0x1d close flag. There is no C++ class for
 * this dialog yet, so the prefix follows the docs' name for it.
 *
 * Noted, not fixed: the Widget_OnCommandDefault calls lack their
 * `this` (a tree-wide prototype problem).
 */
#include "ghidra_types.h"


void __thiscall AddBuddyDialog_OnCommand(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = param_3;
  if (param_2 != 0) {
    iVar1 = param_2 + -0x1000;
  }
  if (iVar1 == 0) {
    FUN_00505580(param_1);
  }
  else if (iVar1 == 1) {
    *(undefined1 *)(param_1 + 0x1d) = 1;
    Widget_OnCommandDefault(param_2,param_3,param_4);
    return;
  }
  Widget_OnCommandDefault(param_2,param_3,param_4);
  return;
}

