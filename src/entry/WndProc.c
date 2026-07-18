/* WndProc - 0x00410040 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FIXED (2026-07-13): the five __thiscall mouse/key handlers below
 * (FUN_0050f230/f020/f1b0/f1f0/f150) were all called WITHOUT their `this`
 * pointer - Ghidra dropped the ECX register argument, so each received the
 * mouse X coordinate in its `this` slot and dereferenced it as an object
 * (crashing on `*(this+4)` with a near-null address like 0x2de = 734, a
 * plausible mouse X). Confirmed via objdump: every one of the five call
 * sites in the original loads `mov ecx,0xe53c40` (g_uiPanelManager, the
 * global UI panel/dialog container) immediately before its `call` -
 * 0x410190 (f230), 0x41022d (f020), 0x41032b (f1b0), 0x410369 (f1f0),
 * 0x41037f (f150). Passed explicitly now.
 *
 * FIXED (2026-07-14): FUN_00507ea0 (the 0x201/WM_LBUTTONDOWN handler) was
 * NOT actually an exception to the above - the previous note ("genuinely
 * takes 2 stack args and no `this`") only checked FUN_00507ea0's OWN entry,
 * which is correct as far as it goes, but missed that FUN_00507ea0 itself
 * calls the __thiscall FUN_0050f060 and silently forwards whatever's in ECX
 * as ITS `this`. The original sets `mov ecx,0xe53c40` (g_uiPanelManager)
 * right before `call 0x507ea0` too (confirmed via objdump at 0x4102c9), and
 * that value survives untouched all the way into FUN_0050f060's own call in
 * the original's straight-line asm - but a recompiled C call gives no such
 * register-survival guarantee (ECX is caller-saved), so this was a real
 * near-null `this` crash (NULL+4 deref) reproduced live under wine 7.
 * FUN_00507ea0 now takes and forwards the panel-manager pointer explicitly.
 */

/* CGameState vtable slot 6 (+0x18) - keydown/mouse-message dispatch,
 * called as (this, msg, wParam, lParam). MSVC 7.1 forbids explicit
 * __thiscall on a function-pointer typedef (C4234), so this is declared
 * __fastcall with a literal-0 dummy EDX slot in place of the (unused,
 * since the real args are all stack-passed here) 2nd fastcall register -
 * same idiom as ChangeGameState.c's GameStateVirtualFn. */
typedef void (__fastcall *StateSlot6DispatchFn)(void *thisPtr,int dummyEDX,uint msg,uint wParam,
                                                 uint lParam);

LRESULT __stdcall WndProc(HWND param_1,uint param_2,WPARAM param_3,uint param_4)

{
  char cVar1;
  LRESULT LVar2;
  uint uVar3;
  uint uVar4;
  
  cVar1 = '\x01';
  FUN_0040d020(param_3, &DAT_00e9c0fc, param_2);
  if (param_2 < 0x106) {
    if (param_2 == 0x105) {
      if (param_3 == 0x79) {
        BuildBuddyPanel();
      }
    }
    else if (param_2 < 0x21) {
      if (param_2 == 0x20) {
        SetCursor((HCURSOR)(&g_edgeCursors[0])[g_cursorDirection]);
        return 1;
      }
      if (param_2 == 2) {
        PostQuitMessage(0);
        return 0;
      }
      if (param_2 == 7) {
        /* WM_SETFOCUS -> forward focus to the comm notify window. In bring-up
         * that window may not exist yet (*(DAT_007934e4+4) NULL/garbage), and
         * under a wine virtual desktop SetFocus(NULL/self) makes the focus
         * bounce straight back as another WM_SETFOCUS -> WndProc re-entered
         * until the stack overflows (confirmed from a core dump: the
         * overflowed stack is a WndProc+0x69/WndProc+0x2f1 cycle, then a wild
         * jump into .data at DAT_00588f54+2). Only forward to a real, other
         * window. */
        if (DAT_007934e4 != 0) {
          HWND focusTarget = *(HWND *)(DAT_007934e4 + 4);
          if (focusTarget != (HWND)0x0 && focusTarget != param_1 &&
              IsWindow(focusTarget)) {
            SetFocus(focusTarget);
          }
        }
      }
      else if (param_2 == 0x1c) {
        LONG lVar1 = InterlockedExchange((LONG *)&DAT_00e9c348,param_3);
        /* orig 0x4100a8 `setne bl` off the exchange's (pre-update) return
         * value; 0x4100ab/0x4100b5 load the keyboard/mouse device addresses -
         * UpdateDeviceAcquisition's args were dropped by Ghidra as
         * unaff_ESI/unaff_BL. Both devices are unconstructed in bring-up, so
         * point at the same zeroed backing GameTick.c uses for them - see
         * that file's own comment. */
        UpdateDeviceAcquisition((int)g_keyboardDeviceTimerBlock, lVar1 != 0);
        UpdateDeviceAcquisition((int)g_mouseDeviceTimerBlock, lVar1 != 0);
        if (DAT_007934f4 != 0) {
          if (param_3 == 1) {
            FUN_00405b20();
          }
          else {
            FUN_00405b60();
          }
        }
        DAT_007934cc = param_3 == 1;
        return 0;
      }
    }
    else if (param_2 == 0x100) {
      if (DAT_007934c4 == '\0') {
        cVar1 = FUN_0050f230((int)&g_uiPanelManager,param_3);
        goto LAB_00410384;
      }
    }
    else if (param_2 == 0x101) {
      if (DAT_007934c4 == '\0') {
        /* Dropped the manager `this` (2026-07-17): the original passes
         * &g_uiPanelManager in ECX like the WM_KEYDOWN FUN_0050f230 call
         * above; this site only passed the VK, so FUN_0050f260 read its
         * panel list off *(VK+4). See FUN_0050f260.c. */
        cVar1 = FUN_0050f260((int)&g_uiPanelManager,param_3);
        cVar1 = '\x01' - (cVar1 != '\0');
      }
      uVar4 = g_cursorAnchorX;
      uVar3 = g_cursorAnchorY;
      if (param_3 == 0x7a) {
        DAT_00793520 = 1;
      }
      goto LAB_0041038c;
    }
    goto switchD_004101d3_caseD_113;
  }
  switch(param_2) {
  case 0x112:
    if (param_3 == 0xf060) {
      if ((g_currentGameState != 7) && (g_currentGameState != 0xb)) {
        g_pendingGameState = 0xf;
        g_stateChangeRequested = 0;
        DAT_0056d108 = 0;
        _DAT_007934d8 = 1;
      }
      return 0;
    }
    break;
  case 0x200:
    uVar4 = param_4 & 0xffff;
    uVar3 = param_4 >> 0x10;
    cVar1 = FUN_0050f020((int)&g_uiPanelManager,uVar4,uVar3);
    cVar1 = cVar1 == '\0';
    if ((bool)cVar1) {
      HandleActiveObjectMouseMove(&DAT_00e9be90, uVar4, uVar3);
    }
    DAT_00e536c0 = DAT_00e536c0 + (uVar4 - g_cursorAnchorX);
    DAT_00e536c4 = DAT_00e536c4 + (uVar3 - g_cursorAnchorY);
    if ((DAT_00e53c3c == '\0') && ((g_cursorAnchorX != uVar4 || (g_cursorAnchorY != uVar3)))) {
      SetCursorPos(g_cursorAnchorX,g_cursorAnchorY);
      uVar4 = g_cursorAnchorX;
      uVar3 = g_cursorAnchorY;
    }
    goto LAB_0041038c;
  case 0x201:
    cVar1 = FUN_00507ea0((int)&g_uiPanelManager,param_4 & 0xffff,param_4 >> 0x10);
    if (cVar1 != '\0') {
      DAT_00e9bea4 = 1;
      HandleActiveObjectMouseDown(&DAT_00e9be90, param_4 & 0xffff, param_4 >> 0x10);
      DAT_00e9bea4 = 0;
      goto LAB_004103ac;
    }
    HandleActiveObjectMouseDown(&DAT_00e9be90, param_4 & 0xffff, param_4 >> 0x10);
    HandleBackgroundActiveObjectMouseDown(&DAT_00e9c0fc, param_4 & 0xffff, param_4 >> 0x10);
    break;
  case 0x202:
    DAT_00e9bea4 = FUN_0050f1b0((int)&g_uiPanelManager,param_4 & 0xffff,param_4 >> 0x10);
    cVar1 = DAT_00e9bea4 != '\x01';
    HandleActiveObjectMouseUp(&DAT_00e9be90, param_4 & 0xffff, param_4 >> 0x10);
    DAT_00e9bea4 = 0;
    uVar4 = g_cursorAnchorX;
    uVar3 = g_cursorAnchorY;
    goto LAB_0041038c;
  case 0x203:
    cVar1 = FUN_0050f1f0((int)&g_uiPanelManager,param_4 & 0xffff,param_4 >> 0x10);
    goto LAB_00410384;
  case 0x204:
    cVar1 = FUN_0050f150((int)&g_uiPanelManager,param_4 & 0xffff,param_4 >> 0x10);
LAB_00410384:
    cVar1 = '\x01' - (cVar1 != '\0');
    uVar4 = g_cursorAnchorX;
    uVar3 = g_cursorAnchorY;
LAB_0041038c:
    g_cursorAnchorY = uVar3;
    g_cursorAnchorX = uVar4;
    if (cVar1 == '\0') goto LAB_004103ac;
  }
switchD_004101d3_caseD_113:
  if ((g_currentGameState != 0) && ((int *)g_gameStateVTableArray[g_currentGameState] != (int *)0x0)
     ) {
    /* FIXED (2026-07-13): dropped `this` - confirmed via objdump at
     * 0x410399-0x4103a9: `mov ecx,[eax*4+0x5b33f8]` (the current state
     * object) stays live in ECX all the way to `call [edx+0x18]`, with
     * (lParam, wParam, msg) pushed on top - this call was invoking the
     * vtable slot with only the 3 message args and no `this` at all,
     * reading every field off garbage/null. Also see State02_ServerSelect_HandleKeyInput.c
     * (State02's slot-6 target) for the matching RET-size fix this
     * needed on the callee side. */
    (*(StateSlot6DispatchFn *)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x18))
              (g_gameStateVTableArray[g_currentGameState],0,param_2,param_3,param_4);
  }
LAB_004103ac:
  if ((0x200 < param_2) && (param_2 < 0x203)) {
    return 0;
  }
  LVar2 = DefWindowProcA(param_1,param_2,param_3,param_4);
  return LVar2;
}

