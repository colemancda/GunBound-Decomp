/* RoomPasswordDialog_SubmitPassword - 0x00506bf0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-31 (was FUN_00506bf0). The submit helper of the
 * room-password dialog (vtable 0x557dc8, CRoomPasswordDialog, built by
 * BuildRoomPasswordDialog with dedup id 2); its sole caller is that
 * dialog's slot-7 handler at 0x506cf0, on label 1 or evt 0x1000 (call
 * at 0x506d80). It copies the edit box into +0x50 and posts input event
 * 0x1f, or 0x1e when the text is empty (stores at 0x506cd4 / 0x506c8d).
 * State03_GameRoomList_OnCommand routes 0x1f to SendJoinRoomSelected,
 * which finds panel id 2, copies its +0x50 string into the u32 payload
 * of the 0x2110 join - the field the reference server's JoinRoomRequest
 * calls `password` - and closes the dialog; 0x1e goes to FUN_00429fb0,
 * which only unregisters panel 2. "SubmitPassword" follows
 * EnterRoomNumberDialog_SubmitRoomNumber, the same shape on a sibling
 * dialog.
 *
 * (FUN_00506cf0 below is the slot-7 handler above.)
 * Earlier note, kept: the "submit" push-helper called by FUN_00506cf0
 * (that file's own header has the full vtable-family derivation for
 * their shared unnamed dialog class, vtable 0x557dc8). If the single
 * text-entry child is empty, pushes a queued event with param2=0x1e;
 * otherwise param2=0x1f.
 */
#include "ghidra_types.h"


undefined4 RoomPasswordDialog_SubmitPassword(undefined4 *param_1)

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
      *(undefined4 *)(g_inputEventParam2Queue + g_inputEventQueueWriteIndex * 4) = 0x1e;
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
      *(undefined4 *)(g_inputEventParam2Queue + g_inputEventQueueWriteIndex * 4) = 0x1f;
      g_inputEventQueueWriteIndex = uVar3;
    }
  }
  return CONCAT31((int3)(uVar3 >> 8),1);
}

