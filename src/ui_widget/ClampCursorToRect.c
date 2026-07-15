/* ClampCursorToRect - 0x004ee200 in the original binary.
 *
 * Clamps the mouse cursor into a rectangle stored on the target object
 * (+0x58c..+0x5a0) via SetCursorPos - used e.g. to snap the pointer onto
 * a modal dialog. `x`/`y` (Ghidra dropped these as unaff_EBX/unaff_EDI -
 * confirmed via direct disassembly of this function's own body at
 * 0x4ee200: ECX=self/param_1, EBX=x, EDI=y, matching the real fastcall
 * calling convention plus 2 extra non-standard registers, same bug class
 * as DrawHLine/EncodeOutgoingPacketField) are the desired cursor
 * position to clamp-and-snap-to; every confirmed caller passes the
 * DirectInput mouse device singleton (g_mouseDeviceTimerBlock, 0xe53698)
 * as `self`. Raw/near-verbatim port of Ghidra's decompiler output
 * otherwise, not hand-verified. See src/README.md's "Raw/verbatim
 * ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall ClampCursorToRect(int param_1,int x,int y)

{
  int iVar1;
  int iVar2;
  int iVar3;

  iVar2 = *(int *)(param_1 + 0x58c);
  iVar3 = iVar2;
  if (iVar2 <= x) {
    iVar3 = x;
  }
  iVar1 = *(int *)(param_1 + 0x590);
  if ((iVar3 <= iVar1) && (iVar1 = iVar2, iVar2 <= x)) {
    iVar1 = x;
  }
  *(int *)(param_1 + 0x59c) = iVar1;
  iVar2 = *(int *)(param_1 + 0x594);
  iVar3 = iVar2;
  if (iVar2 <= y) {
    iVar3 = y;
  }
  if (iVar3 <= *(int *)(param_1 + 0x598)) {
    if (iVar2 <= y) {
      iVar2 = y;
    }
    *(int *)(param_1 + 0x5a0) = iVar2;
    SetCursorPos(x,y);
    return;
  }
  *(int *)(param_1 + 0x5a0) = *(int *)(param_1 + 0x598);
  SetCursorPos(x,y);
  return;
}

