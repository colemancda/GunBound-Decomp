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
 *
 * SetFocus `this` RECOVERED (2026-10-30): the empty-name refocus is
 * `mov ecx,[ebp+0xc] / mov eax,[ecx+eax*4] / mov edx,[eax] / push 1 /
 * mov ecx,eax / call [edx]` (0x5065a7-0x5065b3): slot 0 of the name
 * CEditBox, SetFocus(1), with the child in ECX. The raw `code *` call
 * pushed only the flag and left ECX unset; it now uses the __fastcall +
 * dummy-EDX idiom.
 */
#include "ghidra_types.h"

/* Slot 0 (+0x00) of a CWidget: SetFocus(bool), a one-argument __thiscall.
 * The child found here is a CEditBox (type id 2), a C++ class whose slot 0
 * (0x506fb0) takes `this` in ECX and ends in ret 4, so the call goes
 * through a __fastcall pointer with a dummy EDX. */
typedef void (__fastcall *WidgetSetFocusFn)(void *thisPtr, int dummyEDX, int active);


undefined4 CreateRoomDialog_SubmitCreateRoom(undefined4 *param_1)

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
  uVar3 = Widget_FindChildIndex((int)param_1,1,2);
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
    AssignStringBuffer(param_1 + 0x15,pcVar5);
  }
  if (*(int *)(param_1[0x14] + -0xc) == 0) {
    uVar3 = Widget_FindChildIndex((int)param_1,0,2);
    if (uVar3 != 0xffffffff) {
      if ((uint)param_1[4] <= uVar3) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      ((WidgetSetFocusFn)(*(void ***)*(void **)(param_1[3] + uVar3 * 4))[0])
          (*(void **)(param_1[3] + uVar3 * 4),0,1);
    }
  }
  else {
    uVar2 = *param_1;
    uVar3 = g_inputEventQueueWriteIndex + 1 & 0x800001ff;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffe00) + 1;
    }
    if (uVar3 != g_inputEventQueueReadIndex) {
      *(undefined4 *)(g_inputEventMsgQueue + g_inputEventQueueWriteIndex * 4) = 0;
      *(undefined4 *)(g_inputEventParam1Queue + g_inputEventQueueWriteIndex * 4) = uVar2;
      *(undefined4 *)(g_inputEventParam2Queue + g_inputEventQueueWriteIndex * 4) = 0x29;
      g_inputEventQueueWriteIndex = uVar3;
      return 1;
    }
  }
  return 1;
}

