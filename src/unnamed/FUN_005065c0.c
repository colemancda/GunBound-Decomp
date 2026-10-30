/* FUN_005065c0 - 0x005065c0 in the original binary.
 *
 * CCreateRoomDialog's OnCommand (vtable 0x557c34 slot 7, +0x1c), the
 * create-room dialog's two radio groups plus its OK/cancel paths.
 * Carved 2026-10-30 from the disassembly: 596 bytes of code
 * (0x5065c0-0x506813) and a 10-entry jump table at 0x506814 for the
 * evt-0 ids.
 *
 * Prologue: ebx = ECX = this (0x5065d0), esi = evt, edi = id; every
 * path ends in `mov ecx,ebx / call 0x50eb10` with (evt, id, arg), i.e.
 * Widget_OnCommandDefault, then ret 0xc.
 *
 *   evt 0, id 0-3 (0x50665d/0x506681/0x5066a5/0x5066c9):
 *       push id / call 0x506840 (RadioGroup_SelectLowChild, EBX = this),
 *       then `mov byte [[ebx+0x98]],2/4/6/8`.
 *   evt 0, id 4-7 (0x5066ed/0x50671e/0x50675b/0x506798):
 *       push id / [ebx+0x90] = 1..4 / call 0x506890
 *       (RadioGroup_SelectHighChild, EBX = this), then
 *       `and dword [[ebx+0x94]],0xff03ffff`, and for ids 5-7
 *       `or` 0x80000 / 0x440000 / 0xc0000.
 *   evt 0, id 8 (0x5067d5): push 0x28 / push [ebx] / push 0 /
 *       mov eax,0x795070 / call 0x4f2da0 - EnqueueInputEvent(ring,
 *       0, *this, 0x28).
 *   evt 0, id 9 (0x5067fa) and evt 0x1000 (je at 0x5065d9):
 *       push ebx / call 0x506480 - CreateRoomDialog_SubmitCreateRoom(this).
 *   evt 0x1001 (0x5065e6-0x50663d): the same ring push written inline
 *       (write index [0x795070], read index [0x795074], records at
 *       0x795078/0x795878/0x796078) with (0, *this, 0x28), skipped when
 *       the ring is full - as FUN_00506310 transcribes its own.
 *   evt 0 with id > 9 (ja at 0x506650), and any other evt: only the
 *       default.
 *
 * __thiscall in the original, erased to cdecl here (`this` first), like
 * the sibling OnCommand ports. Wired as CCreateRoomDialog::OnCommand in
 * src/cxx/Panel.cpp.
 */
#include "ghidra_types.h"


void __thiscall FUN_005065c0(undefined4 *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;

  iVar1 = (int)param_1;
  if (param_2 == 0) {
    switch (param_3) {
    case 0:
      RadioGroup_SelectLowChild(0,iVar1);
      **(undefined1 **)(iVar1 + 0x98) = 2;
      break;
    case 1:
      RadioGroup_SelectLowChild(1,iVar1);
      **(undefined1 **)(iVar1 + 0x98) = 4;
      break;
    case 2:
      RadioGroup_SelectLowChild(2,iVar1);
      **(undefined1 **)(iVar1 + 0x98) = 6;
      break;
    case 3:
      RadioGroup_SelectLowChild(3,iVar1);
      **(undefined1 **)(iVar1 + 0x98) = 8;
      break;
    case 4:
      *(undefined4 *)(iVar1 + 0x90) = 1;
      RadioGroup_SelectHighChild(4,iVar1);
      **(uint **)(iVar1 + 0x94) = **(uint **)(iVar1 + 0x94) & 0xff03ffff;
      break;
    case 5:
      *(undefined4 *)(iVar1 + 0x90) = 2;
      RadioGroup_SelectHighChild(5,iVar1);
      **(uint **)(iVar1 + 0x94) = **(uint **)(iVar1 + 0x94) & 0xff03ffff;
      **(uint **)(iVar1 + 0x94) = **(uint **)(iVar1 + 0x94) | 0x80000;
      break;
    case 6:
      *(undefined4 *)(iVar1 + 0x90) = 3;
      RadioGroup_SelectHighChild(6,iVar1);
      **(uint **)(iVar1 + 0x94) = **(uint **)(iVar1 + 0x94) & 0xff03ffff;
      **(uint **)(iVar1 + 0x94) = **(uint **)(iVar1 + 0x94) | 0x440000;
      break;
    case 7:
      *(undefined4 *)(iVar1 + 0x90) = 4;
      RadioGroup_SelectHighChild(7,iVar1);
      **(uint **)(iVar1 + 0x94) = **(uint **)(iVar1 + 0x94) & 0xff03ffff;
      **(uint **)(iVar1 + 0x94) = **(uint **)(iVar1 + 0x94) | 0xc0000;
      break;
    case 8:
      EnqueueInputEvent((uint *)g_inputEventRing,0,*param_1,0x28);
      break;
    case 9:
      CreateRoomDialog_SubmitCreateRoom(param_1);
      break;
    }
  }
  else if (param_2 == 0x1000) {
    CreateRoomDialog_SubmitCreateRoom(param_1);
  }
  else if (param_2 == 0x1001) {
    uVar2 = *param_1;
    uVar3 = g_inputEventQueueWriteIndex + 1 & 0x800001ff;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffe00) + 1;
    }
    if (uVar3 != g_inputEventQueueReadIndex) {
      *(undefined4 *)(g_inputEventMsgQueue + g_inputEventQueueWriteIndex * 4) = 0;
      *(undefined4 *)(g_inputEventParam1Queue + g_inputEventQueueWriteIndex * 4) = uVar2;
      *(undefined4 *)(g_inputEventParam2Queue + g_inputEventQueueWriteIndex * 4) = 0x28;
      g_inputEventQueueWriteIndex = uVar3;
    }
  }
  Widget_OnCommandDefault(iVar1,param_2,param_3,param_4);
  return;
}
