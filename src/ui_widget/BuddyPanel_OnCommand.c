/* BuddyPanel_OnCommand - 0x00505d20 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-30), CERTAIN: CBuddyPanel's OnCommand override.
 * The original's vtable 0x557be4 holds this at slot 7 (+0x1c); that
 * vtable is installed only by BuildBuddyPanel (0x50916d), and
 * src/cxx/Widget.h records it as CBuddyPanel's (slot 9 is the
 * CBuddyPanel::Update that Panel.cpp ports). Widget.h declares slot 7
 * as CWidget::OnCommand(evt, id, arg): every exit is `ret 0xc` with
 * `this` in ECX, ending in the base slot-7 body Widget_OnCommandDefault.
 * The ids it handles are the three labels BuildBuddyPanel creates
 * (Panel.cpp): id 0 close-X sets the +0x1d close flag, id 1 "Add"
 * opens the add-buddy dialog (FUN_00508b90, the only installer of
 * vtable 0x557e68), and id 2 "Del" acts on the buddy selected at
 * +0x90. Same `<Panel>_OnCommand` form as WorldListPanel_OnCommand.
 *
 * FIXED (2026-10-30): the Widget_OnCommandDefault calls now pass `this`
 * (ECX = esi = this at 0x505d56, 0x505d9e, 0x505dbd, 0x505dd6).
 *
 * Noted, not fixed: Panel.cpp declares no CBuddyPanel::OnCommand, so the C++
 * build never reaches this body.
 */
#include "ghidra_types.h"


void __thiscall BuddyPanel_OnCommand(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_2 == 0) {
    if (param_3 == 0) {
      *(undefined1 *)(param_1 + 0x1d) = 1;
    }
    else {
      if (param_3 == 1) {
        FUN_00508b90((int)&g_uiPanelManager);
        Widget_OnCommandDefault(param_1,0,1,param_4);
        return;
      }
      if ((param_3 == 2) && (*(int *)(param_1 + 0x90) != -1)) {
        /* DROPPED-REG FIX 2026-08-28: the ordinal is EDI, loaded at
           0x505d6f as *(param_1 + 0x90) - the same field the guard above
           tests against -1. */
        iVar1 = FindActiveObjectByIndex((int)&DAT_00e53e88,*(int *)(param_1 + 0x90));
        if (iVar1 != 0) {
          FUN_00508ea0(&g_uiPanelManager,(uchar *)(iVar1 + 0x21));
          Widget_OnCommandDefault(param_1,0,2,param_4);
          return;
        }
      }
    }
  }
  else if ((param_2 == 0x2000) && (param_3 == 0)) {
    DAT_00e54da8 = param_4;
    Widget_OnCommandDefault(param_1,0x2000,0,param_4);
    return;
  }
  Widget_OnCommandDefault(param_1,param_2,param_3,param_4);
  return;
}

