/* CommitActiveTextInput - 0x0040ccf0 in the original binary.
 *
 * RENAMED (2026-07-30): given a "background active object" (the same
 * g_activeObjectRegistry2-registered, +0x448-flagged class HandleBackgroundActive
 * ObjectMouseDown works with), commits the real Win32 edit control's
 * current text into that object's own +0x48 text buffer (or clears it),
 * resets the Win32 control, and clears the object's +0x448 "focused"
 * flag - the counterpart called when a differently-focused (or no)
 * object is about to take over text-input focus. Raw/near-verbatim port
 * of Ghidra's decompiler output otherwise, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-ARGUMENT FIX (2026-07-30): `unaff_EDI` is this function's real
 * (and only) argument - `this`, the background active object being
 * un-focused (same +0x448 flag field HandleBackgroundActiveObjectMouseDown
 * already documents as belonging to g_activeObjectRegistry2's larger, not-yet-
 * identified object class). Confirmed via objdump (orig 0x40ccf0-0x40cd37):
 * `lea esi,[edi+0x48]` is the very first instruction, EDI live-in with no
 * prior write; the function also writes `[edi+0x448]=0` right before its
 * plain `ret` (no stack cleanup - cdecl, matching a single register arg).
 * Commits the focused edit control's text into `this+0x48` (or clears it
 * on failure/inactive), resets the real Win32 edit control's text, then
 * clears `this+0x448` (the "focused" flag). Every real call site still
 * calls this with zero args, reading uninitialised `unaff_EDI` and
 * writing 128 bytes + a dword through it - a genuine wild write whenever
 * reached.
 *
 * ALL 9 CALL SITES NOW PASS EDI (2026-10-30): HandleBackgroundActiveObject
 * MouseDown (0x40ce81), FUN_0040cf80 (0x40cfc6), FUN_0040d020 x4
 * (0x40d094/0x40d0be/0x40d113/0x40d141), State09_ReadyRoom_ProcessPacket
 * (0x4d39dd) and State09_ReadyRoom_OnCommand x2 (0x4d550a/0x4d55c9). Each
 * loads EDI from the registry's +8 focus slot just before the call. The
 * functions.h prototype is now the real `void CommitActiveTextInput(int)`.
 */
#include "ghidra_types.h"


void CommitActiveTextInput(int thisObj)

{
  int iVar1;
  int unaff_EDI = thisObj;

  if (*(char *)(g_sharedTextInputControl + 8) != '\0') {
    iVar1 = GetWindowTextA(*(HWND *)(g_sharedTextInputControl + 4),(LPSTR)(unaff_EDI + 0x48),0x80);
    if (iVar1 != 0) goto LAB_0040cd17;
  }
  *(LPSTR)(unaff_EDI + 0x48) = '\0';
LAB_0040cd17:
  SetWindowTextA(*(HWND *)(g_sharedTextInputControl + 4),&DAT_00551cb1);
  *(undefined4 *)(unaff_EDI + 0x448) = 0;
  return;
}
