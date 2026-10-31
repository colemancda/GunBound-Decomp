/* RoomPasswordDialog_OnCommand - 0x00506cf0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-31 (was FUN_00506cf0). Slot 7 (OnCommand, +0x1c) of
 * vtable 0x557dc8, which only BuildRoomPasswordDialog installs (the
 * store at 0x508970); CRoomPasswordDialog::OnCommand in src/cxx/Panel.cpp
 * forwards here. Label 1 or evt 0x1000 runs
 * RoomPasswordDialog_SubmitPassword (0x506d80), whose event 0x1f
 * State03_GameRoomList_OnCommand turns into the 0x2110 join carrying the
 * typed password; label 0 and evt 0x1001 post event 0x1e, which only
 * closes the dialog. Named after the class, like
 * EnterRoomNumberDialog_OnCommand and AddBuddyDialog_OnCommand.
 *
 * (FUN_00506bf0 below is now RoomPasswordDialog_SubmitPassword.)
 * Earlier note, kept: CWidget::OnCommand override (vtable slot 7, +0x1c)
 * for a single-text-field dialog class (constructor at
 * 0x508910, `this->vtable = &PTR_LAB_00557dc8`, object size 0x90,
 * sprite outer/inner key 0x2714/0, labels string IDs 0x5dc/0x5dd).
 * Confirmed via the
 * same Ghidra xref/PTR_LAB vtable-family derivation documented in
 * src/ui_widget/EnterRoomNumberDialog_OnCommand.c's header. This
 * class's PanelManager dedup "type id" (constructor's puVar5[9]) is a
 * fixed literal 2, sequential with CCreateRoomDialog(0)/
 * CEnterRoomNumberDialog(1). Calls FUN_00506bf0 on evt==0x1000/id==1.
 *
 * WIRED (2026-10-30): the builder 0x508910 now lives in src/cxx/Panel.cpp
 * and builds a C++ CRoomPasswordDialog (vtable 0x557dc8) whose OnCommand
 * forwards here with `this` first. SendJoinRoomChecked opens it instead
 * of the 0x2110 join when the room's +0x449ae private/password flag is
 * set, which makes it the room-password prompt.
 */
#include "ghidra_types.h"


void __thiscall RoomPasswordDialog_OnCommand(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (param_2 == 0) {
    if (param_3 == 0) {
      /* 0x506d99-0x506da5: push 0x1e / push [esi] / push 0, eax = 0x795070. */
      EnqueueInputEvent((uint *)g_inputEventRing,0,*param_1,0x1e);
    }
    else if (param_3 == 1) goto LAB_00506d7f;
  }
  else {
    if (param_2 == 0x1000) {
LAB_00506d7f:
      RoomPasswordDialog_SubmitPassword(param_1);
      Widget_OnCommandDefault((int)param_1,param_2,param_3,param_4);
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
        Widget_OnCommandDefault((int)param_1,0x1001,param_3,param_4);
        return;
      }
    }
  }
  Widget_OnCommandDefault((int)param_1,param_2,param_3,param_4);
  return;
}

