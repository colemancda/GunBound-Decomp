/* State03_GameRoomList_HandleMouseInput - 0x00428b90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * CALLING-CONVENTION FIX (2026-07-31): same bug and same fix as
 * State02_ServerSelect_HandleKeyInput.c's own "CALLING-CONVENTION FIX"
 * (see that file's header for the full writeup). WndProc dispatches this
 * vtable slot 6 via StateSlot6DispatchFn, a __fastcall(this, dummyEDX,
 * msg, wParam, lParam) - `this` in ECX, a dead EDX slot, then the three
 * message dwords on the stack, callee-cleaned (`ret 0xc`). This port was
 * declared __thiscall, which ghidra_types.h erases to plain cdecl under
 * MSVC (`this` read off the stack as if it were `msg`, every other param
 * shifted one slot late, caller-cleaned via a bare `ret` with NO cleanup
 * at all since the callee never runs any `ret N`). Confirmed via
 * disassembly of the compiled callee (reads its 2nd param off [esp+8]
 * checking it against msg constants 0x100/0x201/0x203/0x204 - i.e. reads
 * `wParam`'s stack slot expecting `msg` - and both exit points are a bare
 * `ret`) live-reproduced with winedbg: the caller's 3 pushed stack dwords
 * (12 bytes) are never popped by either side, permanently corrupting
 * WndProc's own stack for the rest of its execution - this IS the
 * long-standing AVATAR/BUDDY lobby-hover crash (EIP lands on the stack
 * inside WndProc's own epilogue once the accumulated 12-byte skew reaches
 * its saved registers/return address; fires whenever nothing in the
 * panel tree or active-object registry claims the mouse message, i.e.
 * any bare-background hover or a registry-dispatched button like
 * AVATAR/BUDDY). Declared __fastcall + dummy-EDX to match, exactly like
 * State01_Title_HandleKeyInput / State06_Logo2_HandleKeyInput /
 * State02_ServerSelect_HandleKeyInput. The original's `ret 0xc` now
 * matches (3 stack args, callee-cleaned).
 */
#include "ghidra_types.h"


void __fastcall State03_GameRoomList_HandleMouseInput(int param_1,int dummyEDX,uint param_2,undefined4 param_3,uint param_4)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;

  (void)dummyEDX;
  if (param_2 < 0x204) {
    if (param_2 == 0x203) {
      iVar3 = RoomCardHitTest(param_4 >> 0x10,0,param_4 & 0xffff);
      if (iVar3 != -1) {
        cVar2 = FUN_00406400(0,0,(int)&g_activeObjectRegistry,5);
        if (cVar2 == '\x01') {
          EnqueueInputEvent();
          return;
        }
      }
    }
    else if ((param_2 != 0x100) && (param_2 == 0x201)) {
      iVar3 = RoomCardHitTest(param_4 >> 0x10,0,param_4 & 0xffff);
      if (iVar3 != -1) {
        *(int *)(param_1 + 4) = iVar3;
        InvokeWidget(5,1);
      }
      *(undefined4 *)(param_1 + 0x124) = 0xffffffff;
      FUN_00507d50();
      return;
    }
  }
  else if (param_2 == 0x204) {
    iVar4 = RoomCardHitTest(param_4 >> 0x10,1,param_4 & 0xffff);
    iVar1 = g_connectionContextA;
    iVar3 = g_clientContext;
    if ((iVar4 != -1) && (*(int *)(g_clientContext + 0x4464c + iVar4 * 4) == 1)) {
      *(undefined4 *)(g_connectionContextA + 0x44d0) = 6;
      *(undefined2 *)(iVar1 + 0x4d4) = 0x2104;
      *(undefined2 *)(iVar1 + 0x4d6) = *(undefined2 *)(iVar3 + 0x44664 + iVar4 * 4);
      *(int *)(iVar1 + 0x44d0) = *(int *)(iVar1 + 0x44d0) + 2;
      SendOutgoingPacket(iVar1);
      *(int *)(param_1 + 0x124) = iVar4;
      puVar5 = (undefined4 *)(param_1 + 0x220);
      for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      puVar5 = (undefined4 *)(param_1 + 0x1b8);
      for (iVar3 = 0x1a; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      return;
    }
    *(undefined4 *)(param_1 + 0x124) = 0xffffffff;
  }
  return;
}

