/* RoomTitleDialog_SubmitTitle - 0x00506210 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-31 (was FUN_00506210). The submit helper of the
 * room-title dialog (vtable 0x557c0c, CRoomTitleDialog, built by
 * BuildRoomTitleDialog with dedup id 3); its sole caller is that
 * dialog's slot-7 RoomTitleDialog_OnCommand, on label 1 or on evt
 * 0x1000 (call at 0x5063a0). It copies the dialog's edit-box text into +0x50
 * and posts input event 8, or 9 when the text is empty (stores at
 * 0x5062f4 / 0x5062ad). Both codes land in State09_ReadyRoom_OnCommand:
 * case 8 finds panel id 3 through the panel manager, copies its +0x50
 * string and sends it as opcode 0x3104 (GB_OP_ROOM_SET_TITLE_COMMAND,
 * SVC_ROOM_CHANGE_TITLE) before unregistering the dialog; case 9 only
 * unregisters it. "SubmitTitle" follows EnterRoomNumberDialog_
 * SubmitRoomNumber, the same shape on a sibling dialog.
 *
 * (FUN_00506310 below is now RoomTitleDialog_OnCommand.)
 * Earlier note, kept: the "submit" push-helper called by FUN_00506310
 * (that file's own header has the full vtable-family derivation for
 * their shared unnamed dialog class, vtable 0x557c0c). If the single
 * text-entry child is empty, pushes a queued event with param2=9;
 * otherwise param2=8.
 */
#include "ghidra_types.h"


undefined4 RoomTitleDialog_SubmitTitle(undefined4 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  uVar3 = Widget_FindChildIndex((int)param_1,0,2);
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
    AssignStringBuffer(param_1 + 0x14,pcVar5);
  }
  uVar2 = *param_1;
  if (*(int *)(param_1[0x14] + -0xc) == 0) {
    uVar3 = g_inputEventQueueWriteIndex + 1 & 0x800001ff;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffe00) + 1;
    }
    if (uVar3 != g_inputEventQueueReadIndex) {
      *(undefined4 *)(g_inputEventMsgQueue + g_inputEventQueueWriteIndex * 4) = 0;
      *(undefined4 *)(g_inputEventParam1Queue + g_inputEventQueueWriteIndex * 4) = uVar2;
      *(undefined4 *)(g_inputEventParam2Queue + g_inputEventQueueWriteIndex * 4) = 9;
      g_inputEventQueueWriteIndex = uVar3;
      return CONCAT31((int3)(uVar3 >> 8),1);
    }
  }
  else {
    uVar3 = g_inputEventQueueWriteIndex + 1 & 0x800001ff;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffe00) + 1;
    }
    if (uVar3 != g_inputEventQueueReadIndex) {
      *(undefined4 *)(g_inputEventMsgQueue + g_inputEventQueueWriteIndex * 4) = 0;
      *(undefined4 *)(g_inputEventParam1Queue + g_inputEventQueueWriteIndex * 4) = uVar2;
      *(undefined4 *)(g_inputEventParam2Queue + g_inputEventQueueWriteIndex * 4) = 8;
      g_inputEventQueueWriteIndex = uVar3;
    }
  }
  return CONCAT31((int3)(uVar3 >> 8),1);
}

