/* FUN_0040d020 - 0x0040d020 in the original binary.
 *
 * Keyboard navigation (Tab/Shift+Tab focus cycling, Enter/Escape) among a
 * widget list's siblings, gated on the message being WM_KEYDOWN.
 *
 * FIXED (2026-07-13): `in_EAX` is a dropped register, not garbage -
 * confirmed via objdump that it's compared before anything else runs
 * (`cmp eax,0x100` is instruction #1, no prior write to EAX). Sole caller
 * is WndProc at 0x410057; objdump there shows the ACTUAL bug is in the
 * caller, not just Ghidra's read: `mov ecx,esi[[wParam]]; mov
 * eax,edi[uMsg]; push 0xe9c0fc; call 0x40d020` - the raw C port
 * (src/entry/WndProc.c) had dropped BOTH the uMsg and wParam arguments,
 * calling `FUN_0040d020(&DAT_00e9c0fc)` with only the stack arg (which
 * itself landed in the wrong parameter slot). Added `message` as an
 * explicit trailing parameter and fixed the call site to pass all three.
 */
#include "ghidra_types.h"


void __thiscall FUN_0040d020(int param_1,int param_2,int message)

{
  SHORT SVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;

  if ((message == 0x100) && (*(int *)(param_2 + 8) != 0)) {
    if (param_1 == 9) {
      SVar1 = GetKeyState(0x10);
      iVar3 = *(int *)(param_2 + 8);
      if (SVar1 < 0) {
        iVar2 = *(int *)(iVar3 + 0xc);
        if (*(char *)(iVar2 + 0x15) != '\0') {
          iVar2 = *(int *)(iVar2 + 0xc);
        }
      }
      else {
        iVar2 = *(int *)(iVar3 + 0x10);
        if (*(char *)(iVar2 + 0x15) != '\0') {
          iVar2 = *(int *)(iVar2 + 0x10);
        }
      }
      if (((iVar2 == iVar3) || (*(int *)(iVar2 + 8) == -1)) &&
         (EnqueueInputEvent(10,0,0), *(int *)(param_2 + 8) != 0)) {
        FUN_0040ccf0();
        *(undefined4 *)(param_2 + 8) = 0;
      }
      if ((*(int *)(param_2 + 8) != 0) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
        FUN_0040ccf0();
        *(int *)(param_2 + 8) = iVar3;
        FUN_0040cc50();
        return;
      }
    }
    else {
      if (param_1 == 0xd) {
        if (*(char *)(*(int *)(*(int *)(param_2 + 8) + 0x10) + 0x15) == '\0') {
          iVar3 = FindSpriteFrame();
          if (iVar3 == 0) {
            return;
          }
          FUN_0040ccf0();
          *(int *)(param_2 + 8) = iVar3;
          FUN_0040cc50();
          return;
        }
        uVar4 = 10;
      }
      else {
        if (param_1 != 0x1b) {
          return;
        }
        uVar4 = 0xb;
      }
      EnqueueInputEvent(uVar4,0,0);
      if (*(int *)(param_2 + 8) != 0) {
        FUN_0040ccf0();
        *(undefined4 *)(param_2 + 8) = 0;
      }
    }
  }
  return;
}

