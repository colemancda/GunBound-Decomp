/* TextEntry_PushTextToControl - 0x0040c8b0 in the original binary.
 *
 * Writes a text-entry object's string into its Win32 control.
 *
 * param_1 is the entry object (its HWND is at +4) and regEax is the string,
 * with NULL substituted by the empty string at DAT_00551cb1.  That NULL
 * fallback is what identifies it: TextEntry_SetControlText does the same
 * substitution against the same empty-string global, on the same
 * g_sharedTextInputControl + 4 handle.  This is the primitive that takes the object
 * explicitly; TextEntry_SetControlText is the larger routine that also copies
 * the string into the object's own buffer at +0x38.
 *
 * param_1 FILLED.  `ret 0`, so param_1 is ECX, and the sole call site
 * (0x004d65ff) passed nothing: `mov ecx,[0x7934e4]`.  The body uses it as
 * *(HWND *)(param_1 + 4), so an unsupplied param_1 meant SetWindowTextA was
 * handed a window handle read from a garbage address.
 *
 * regEax stays open.  It is the text argument, and at the call site it is
 * `lea eax,[esp+0x58]` -- the address of a caller stack local, the string the
 * preceding `rep movsb` had just assembled.  Naming a caller spill slot needs
 * a stack-depth model this tree does not have, so it is left as a local
 * rather than guessed at; the NULL check above it means the wrong value shows
 * up as the wrong caption, not as a crash.
 */
#include "ghidra_types.h"


void __fastcall TextEntry_PushTextToControl(int param_1,LPCSTR regEax)

{
  
  if (regEax == (LPCSTR)0x0) {
    SetWindowTextA(*(HWND *)(param_1 + 4),&DAT_00551cb1);
    return;
  }
  SetWindowTextA(*(HWND *)(param_1 + 4),regEax);
  return;
}

