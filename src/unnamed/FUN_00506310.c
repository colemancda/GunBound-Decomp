/* FUN_00506310 - 0x00506310 in the original binary.
 *
 * NOT YET NAMED - CWidget::OnCommand override (vtable slot 7, +0x1c)
 * for an UNNAMED single-text-field dialog class (constructor at
 * 0x508a7d, `this->vtable = &PTR_LAB_00557c0c`, object size 0x90,
 * sprite outer/inner key 10000/8, labels string IDs 0x4ba/0x4bb -
 * unresolved without the localized string table). Confirmed via the
 * same Ghidra xref/PTR_LAB vtable-family derivation documented in
 * src/ui_widget/EnterRoomNumberDialog_OnCommand.c's header. Distinctive:
 * unlike the sibling dialogs, this class's PanelManager dedup "type id"
 * (constructor's puVar2[9]) is a caller-supplied PARAMETER, not a fixed
 * literal - i.e. this is a REUSABLE dialog template instantiated for
 * more than one purpose, not a singleton. Calls FUN_00506210 on
 * evt==0x1000/id==1. Raw/near-verbatim port of Ghidra's decompiler
 * output otherwise, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00506310(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (param_2 == 0) {
    if (param_3 == 0) {
      EnqueueInputEvent(0,*param_1,8);
    }
    else if (param_3 == 1) goto LAB_0050639f;
  }
  else {
    if (param_2 == 0x1000) {
LAB_0050639f:
      FUN_00506210(param_1);
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
        *(undefined4 *)(g_inputEventParam2Queue + g_inputEventQueueWriteIndex * 4) = 9;
        g_inputEventQueueWriteIndex = uVar2;
        Widget_OnCommandDefault(0x1001,param_3,param_4);
        return;
      }
    }
  }
  Widget_OnCommandDefault(param_2,param_3,param_4);
  return;
}

