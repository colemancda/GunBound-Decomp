/* EnterRoomNumberDialog_SubmitRoomNumber - 0x00506950 in the original binary.
 *
 * Called from EnterRoomNumberDialog_OnCommand's evt==0x1000/id==1 path.
 * Copies the dialog's two text-entry children, parses the first as a
 * decimal room number (clamped 0-499), and checks it against a
 * per-channel in-use room list at g_clientContext+... (piVar8 walk over
 * &DAT_005f3058+g_clientContext) - if the number is already taken or the
 * field is empty, flashes/refocuses the field (LAB_00506add) and
 * returns 1 (blocked); otherwise pushes a queued input event
 * (msg=0, param1=this, param2=0x21) for later processing and returns 0.
 * Raw/near-verbatim port of Ghidra's decompiler output otherwise, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for
 * status.
 */
#include "ghidra_types.h"


undefined4 EnterRoomNumberDialog_SubmitRoomNumber(undefined4 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  char *pcVar4;
  long lVar5;
  int iVar6;
  char *pcVar7;
  int *piVar8;
  int iVar9;
  
  uVar3 = Widget_FindChildIndex();
  if (uVar3 != 0xffffffff) {
    if ((uint)param_1[4] <= uVar3) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    pcVar7 = (char *)(*(int *)(param_1[3] + uVar3 * 4) + 0x38);
    pcVar4 = pcVar7;
    if (pcVar7 != (char *)0x0) {
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
    }
    FUN_004056c0(param_1 + 0x14,pcVar7);
  }
  uVar3 = Widget_FindChildIndex();
  if (uVar3 != 0xffffffff) {
    if ((uint)param_1[4] <= uVar3) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    pcVar7 = (char *)(*(int *)(param_1[3] + uVar3 * 4) + 0x38);
    pcVar4 = pcVar7;
    if (pcVar7 != (char *)0x0) {
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
    }
    FUN_004056c0(param_1 + 0x15,pcVar7);
  }
  lVar5 = _atol((char *)param_1[0x14]);
  if ((lVar5 + -1 < 499) && (lVar5 = _atol((char *)param_1[0x14]), lVar5 + -1 < 0)) {
    iVar6 = 0;
  }
  else {
    lVar5 = _atol((char *)param_1[0x14]);
    if (lVar5 + -1 < 499) {
      lVar5 = _atol((char *)param_1[0x14]);
      iVar6 = lVar5 + -1;
    }
    else {
      iVar6 = 499;
    }
  }
  if (*(int *)(param_1[0x14] + -0xc) == 0) {
LAB_00506add:
    uVar3 = Widget_FindChildIndex();
    if (uVar3 != 0xffffffff) {
      if ((uint)param_1[4] <= uVar3) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      (**(code **)**(undefined4 **)(param_1[3] + uVar3 * 4))(1);
    }
    return 1;
  }
  iVar9 = 0;
  if (0 < *(int *)(&DAT_005f3258 + g_clientContext)) {
    piVar8 = (int *)(&DAT_005f3058 + g_clientContext);
    do {
      if ((piVar8[-0x40] == *(int *)(g_clientContext + 0x3f804)) && (*piVar8 == iVar6))
      goto LAB_00506add;
      iVar9 = iVar9 + 1;
      piVar8 = piVar8 + 1;
    } while (iVar9 < *(int *)(&DAT_005f3258 + g_clientContext));
  }
  uVar2 = *param_1;
  uVar3 = g_inputEventQueueWriteIndex + 1 & 0x800001ff;
  if ((int)uVar3 < 0) {
    uVar3 = (uVar3 - 1 | 0xfffffe00) + 1;
  }
  if (uVar3 != g_inputEventQueueReadIndex) {
    *(undefined4 *)(g_inputEventMsgQueue + g_inputEventQueueWriteIndex * 4) = 0;
    *(undefined4 *)(g_inputEventParam1Queue + g_inputEventQueueWriteIndex * 4) = uVar2;
    *(undefined4 *)(g_inputEventParam2Queue + g_inputEventQueueWriteIndex * 4) = 0x21;
    g_inputEventQueueWriteIndex = uVar3;
  }
  return 0;
}

