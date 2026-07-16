/* ProcessInputEventQueue - 0x00412130 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-14): the CGameState::OnKeyInput dispatch (vtable slot 5,
 * +0x14 - see src/cxx/GameState.h) dropped its "this" argument entirely,
 * calling through the generic K&R `code()` cast with only the 3 real
 * stack args. Confirmed via angr disassembly at 0x412193-0x4121a4: `mov
 * ecx,[eax*4+0x5b33f8]` loads the current state object into ECX and it's
 * never touched again before `call [edx+0x14]` - a genuine __thiscall
 * dispatch (this in ECX), matching ChangeGameState.c's own already-fixed
 * OnEnter/OnExit slots. `push ebp; push esi; push edi` (right-to-left)
 * confirms the existing arg order (iVar1,uVar2,iVar3) was already correct
 * - only "this" was missing. Live-reproduced: a jump-to-NULL crash
 * (EIP=0x0) once this dispatch actually started firing (state 5's
 * SendSocketData fix let the client reach live per-tick UI event
 * processing for the first time) - with ECX holding whatever was last in
 * it rather than the real state object, the vtable read at an unrelated
 * address happened to be exactly 0.
 *
 * FIXED (2026-07-15): g_inputEventMsgQueue/g_inputEventParam1Queue/
 * g_inputEventParam2Queue (the msg/param1/param2 parallel arrays this
 * loop reads via `queue + g_inputEventQueueReadIndex*4`) were each declared as a
 * single uint8_t in globals.c - see globals.h's updated comment. With
 * only 1 byte reserved per array,
 * every read/write past index 0 landed on whatever unrelated global
 * happened to sit next in memory, so this queue could appear non-empty
 * (g_inputEventQueueReadIndex != g_inputEventQueueWriteIndex) from unrelated memory traffic alone,
 * and any event actually read back was garbage - independent of the
 * `this`-pointer fix above, and likely why that fix alone didn't fully
 * resolve live crashes once this dispatch started firing. */
#include "ghidra_types.h"

typedef void (__thiscall *OnKeyInputFn)(void *thisPtr,int msg,int a,int b);

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void ProcessInputEventQueue(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  void *pvVar4;
  void *stateObj;

LAB_00412140:
  do {
    while( true ) {
      if (g_inputEventQueueReadIndex == g_inputEventQueueWriteIndex) {
        return;
      }
      iVar1 = *(int *)(g_inputEventMsgQueue + g_inputEventQueueReadIndex * 4);
      uVar2 = *(uint *)(g_inputEventParam1Queue + g_inputEventQueueReadIndex * 4);
      iVar3 = *(int *)(g_inputEventParam2Queue + g_inputEventQueueReadIndex * 4);
      g_inputEventQueueReadIndex = g_inputEventQueueReadIndex + 1 & 0x800001ff;
      if ((int)g_inputEventQueueReadIndex < 0) {
        g_inputEventQueueReadIndex = (g_inputEventQueueReadIndex - 1 | 0xfffffe00) + 1;
      }
      if (((g_stateChangeInProgress == 0) || (999999 < uVar2)) && (DAT_0056d108 == -1)) {
        stateObj = g_gameStateVTableArray[g_currentGameState];
        ((OnKeyInputFn)(*(void ***)stateObj)[5])(stateObj,iVar1,uVar2,iVar3);
      }
      pvVar4 = DAT_007934f4;
      if (iVar1 == 0) goto LAB_004122c7;
      if (iVar1 == 0x32) break;
      if (iVar1 == 0x65) {
        if (uVar2 == 3) {
          if (DAT_007934f4 != (void *)0x0) {
            FUN_00405930();
            _free(pvVar4);
          }
          DAT_007934f4 = (void *)0x0;
          DAT_00793529 = 1;
        }
        else {
          ShowErrorDialog(1);
          pvVar4 = DAT_007934f4;
          if (DAT_007934f4 != (void *)0x0) {
            iVar1 = *(int *)((int)DAT_007934f4 + 0x2004);
            *(undefined4 *)(iVar1 + 0x22c) = 1;
            if (*(SOCKET *)(iVar1 + 0x24) != 0xffffffff) {
              closesocket(*(SOCKET *)(iVar1 + 0x24));
            }
            *(undefined4 *)(iVar1 + 0x24) = 0xffffffff;
            *(undefined1 *)(iVar1 + 0x22a) = 0;
            *(undefined1 *)((int)pvVar4 + 0x2009) = 0;
          }
        }
      }
    }
  } while (((uVar2 != 0x1c) && (uVar2 != 0x9c)) || (g_stateChangeInProgress == 0));
  goto LAB_0041225f;
LAB_004122c7:
  if ((uVar2 == 1000000) && (iVar3 == 1000000)) {
LAB_0041225f:
    g_stateChangeInProgress = 0;
    RemoveWidget();
    _DAT_00e53c24 = 0;
    _DAT_00e53c28 = 799;
    _DAT_00e53c2c = 0;
    _DAT_00e53c30 = 599;
    if (DAT_0079350c != '\0') {
      g_pendingGameState = 0xf;
      g_stateChangeRequested = 0;
      DAT_0056d108 = 0;
      _DAT_007934d8 = 1;
    }
  }
  goto LAB_00412140;
}

