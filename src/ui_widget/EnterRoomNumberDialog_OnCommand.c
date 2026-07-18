/* EnterRoomNumberDialog_OnCommand - 0x00506b20 in the original binary.
 *
 * CWidget::OnCommand override (vtable slot 7, +0x1c) for CEnterRoomNumberDialog
 * (src/cxx/Widget.h, vtable 0x557df0). Confirmed via Ghidra's own
 * xref-derived PTR_LAB_ data labels in ghidra_proj/: every widget vtable
 * in the 0x557b90-0x557f40 family is a uniform 10-slot (0x28-byte)
 * table, and this function's own address (0x506b20) is the sole raw
 * occurrence at 0x557df0+0x1c = slot 7 of CEnterRoomNumberDialog's
 * table - matching CWidget's documented slot 7 (OnCommand). evt==0x1000
 * (or evt==0/id==1) forwards to EnterRoomNumberDialog_SubmitRoomNumber;
 * evt==0x1001 pushes a distinct queued event (param2=0x20) directly.
 * Raw/near-verbatim port of Ghidra's decompiler output otherwise, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for
 * status.
 */
#include "ghidra_types.h"


void __thiscall EnterRoomNumberDialog_OnCommand(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (param_2 == 0) {
    if (param_3 == 0) {
      EnqueueInputEvent(0,*param_1,0x20);
    }
    else if (param_3 == 1) goto LAB_00506baf;
  }
  else {
    if (param_2 == 0x1000) {
LAB_00506baf:
      EnterRoomNumberDialog_SubmitRoomNumber(param_1);
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
        *(undefined4 *)(g_inputEventParam2Queue + g_inputEventQueueWriteIndex * 4) = 0x20;
        g_inputEventQueueWriteIndex = uVar2;
        Widget_OnCommandDefault(0x1001,param_3,param_4);
        return;
      }
    }
  }
  Widget_OnCommandDefault(param_2,param_3,param_4);
  return;
}

