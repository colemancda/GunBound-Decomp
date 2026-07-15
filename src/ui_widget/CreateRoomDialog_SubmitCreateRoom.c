/* CreateRoomDialog_SubmitCreateRoom - 0x00506480 in the original binary.
 *
 * Called from CCreateRoomDialog's (src/cxx/Widget.h, vtable 0x557c34)
 * own OnCommand override (sub_5065c0 in the original - not yet a
 * ported file; angr confirms it calls this address on the same
 * evt==0x1000/id==1 shape as EnterRoomNumberDialog_OnCommand, itself
 * at vtable slot 7/+0x1c, the CWidget::OnCommand slot - see that
 * file's header for the vtable-family derivation). Copies BOTH of
 * CCreateRoomDialog's text-entry children (room name at +0x14, room
 * password at +0x15 - matching its constructor's 2 CreateTextEntryWidget
 * calls at 0x60,0x2c "name" and 0x60,0x46 "password"). If the name
 * field is empty, flashes/refocuses it; otherwise pushes a queued input
 * event (msg=0, param1=this, param2=0x29) for later processing.
 * Raw/near-verbatim port of Ghidra's decompiler output otherwise, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for
 * status.
 */
#include "ghidra_types.h"


undefined4 CreateRoomDialog_SubmitCreateRoom(undefined4 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  uVar3 = Widget_FindChildIndex();
  if (uVar3 != 0xffffffff) {
    if ((uint)param_1[4] <= uVar3) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    pcVar5 = (char *)(*(int *)(param_1[3] + uVar3 * 4) + 0x38);
    pcVar4 = pcVar5;
    if (pcVar5 != (char *)0x0) {
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
    }
    FUN_004056c0(param_1 + 0x14,pcVar5);
  }
  uVar3 = Widget_FindChildIndex();
  if (uVar3 != 0xffffffff) {
    if ((uint)param_1[4] <= uVar3) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    pcVar5 = (char *)(*(int *)(param_1[3] + uVar3 * 4) + 0x38);
    pcVar4 = pcVar5;
    if (pcVar5 != (char *)0x0) {
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
    }
    FUN_004056c0(param_1 + 0x15,pcVar5);
  }
  if (*(int *)(param_1[0x14] + -0xc) == 0) {
    uVar3 = Widget_FindChildIndex();
    if (uVar3 != 0xffffffff) {
      if ((uint)param_1[4] <= uVar3) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      (**(code **)**(undefined4 **)(param_1[3] + uVar3 * 4))(1);
    }
  }
  else {
    uVar2 = *param_1;
    uVar3 = DAT_00795070 + 1 & 0x800001ff;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffe00) + 1;
    }
    if (uVar3 != DAT_00795074) {
      *(undefined4 *)(g_inputEventMsgQueue + DAT_00795070 * 4) = 0;
      *(undefined4 *)(g_inputEventParam1Queue + DAT_00795070 * 4) = uVar2;
      *(undefined4 *)(g_inputEventParam2Queue + DAT_00795070 * 4) = 0x29;
      DAT_00795070 = uVar3;
      return 1;
    }
  }
  return 1;
}

