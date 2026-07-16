/* FUN_00506cf0 - 0x00506cf0 in the original binary.
 *
 * NOT YET NAMED - CWidget::OnCommand override (vtable slot 7, +0x1c)
 * for an UNNAMED single-text-field dialog class (constructor at
 * 0x508910, `this->vtable = &PTR_LAB_00557dc8`, object size 0x90,
 * sprite outer/inner key 0x2714/0, labels string IDs 0x5dc/0x5dd -
 * unresolved without the localized string table). Confirmed via the
 * same Ghidra xref/PTR_LAB vtable-family derivation documented in
 * src/ui_widget/EnterRoomNumberDialog_OnCommand.c's header. This
 * class's PanelManager dedup "type id" (constructor's puVar5[9]) is a
 * fixed literal 2, sequential with CCreateRoomDialog(0)/
 * CEnterRoomNumberDialog(1) - plausibly another room-list-family
 * dialog (e.g. an enter-password prompt) but NOT confirmed, don't
 * assume. Calls FUN_00506bf0 on evt==0x1000/id==1. Raw/near-verbatim
 * port of Ghidra's decompiler output otherwise, not hand-verified.
 * See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00506cf0(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (param_2 == 0) {
    if (param_3 == 0) {
      FUN_004f2da0(0,*param_1,0x1e);
    }
    else if (param_3 == 1) goto LAB_00506d7f;
  }
  else {
    if (param_2 == 0x1000) {
LAB_00506d7f:
      FUN_00506bf0(param_1);
      Widget_OnCommandDefault(param_2,param_3,param_4);
      return;
    }
    if (param_2 == 0x1001) {
      uVar1 = *param_1;
      uVar2 = g_inputEventQueueWriteIndex + 1 & 0x800001ff;
      if ((int)uVar2 < 0) {
        uVar2 = (uVar2 - 1 | 0xfffffe00) + 1;
      }
      if (uVar2 != g_inputEventQueueReadIndex) {
        *(undefined4 *)(g_inputEventMsgQueue + g_inputEventQueueWriteIndex * 4) = 0;
        *(undefined4 *)(g_inputEventParam1Queue + g_inputEventQueueWriteIndex * 4) = uVar1;
        *(undefined4 *)(g_inputEventParam2Queue + g_inputEventQueueWriteIndex * 4) = 0x1e;
        g_inputEventQueueWriteIndex = uVar2;
        Widget_OnCommandDefault(0x1001,param_3,param_4);
        return;
      }
    }
  }
  Widget_OnCommandDefault(param_2,param_3,param_4);
  return;
}

