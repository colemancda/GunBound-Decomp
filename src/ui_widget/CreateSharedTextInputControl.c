/* CreateSharedTextInputControl - 0x0040c670 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_0040c670 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: Sole caller
 * InitGame hands it a freshly allocated 0x10-byte block and stores that
 * same block in g_sharedTextInputControl; this function fills it in:
 * block[0] = parent HWND, block[1] = the child created by CreateWindowExA
 * with class DAT_00552084 (the Win32 edit control class, bytes 'edit' in
 * the original .rdata), size 800x24, block[3] = its original WndProc, then
 * subclasses it with 0x40c6f0 (SharedTextInputControlWndProc), SetFocus,
 * marks the block ready at +8 and calls ImmDisableIME. The block is what
 * CommitActiveTextInput, SyncActiveTextInput and
 * TextEntry_PushTextToControl read as g_sharedTextInputControl (HWND at
 * +4, active flag at +8), so this is the creator of the one shared text
 * input control. Calling convention is unchanged (__fastcall: hInstance,
 * block, hWndParent).
 *
 * FIXED (2026-07-14): both `unaff_ESI` (the caller's freshly-allocated
 * 0x10-byte block, built into a sub-window control wrapper: [0]=parent
 * HWND, [1]=child HWND, [2] byte=ready flag, [3]=old wndproc) and
 * `in_EAX` (the parent HWND passed to CreateWindowExA) were dropped
 * registers. Confirmed via objdump at InitGame's own call site (orig
 * 0x40f36c-0x40f385): `call 0x52022d` (operator_new(0x10)) / `mov
 * esi,eax` (the block, left untouched - a pure passthrough register,
 * not reloaded before the call) / `mov ecx,[esp+0x428]` (InitGame's own
 * hInstance param) / `mov eax,ebp` (InitGame's own hWnd param, kept live
 * in EBP) / `call 0x40c670`. Promoted `block`/`hWndParent` to explicit
 * parameters; this is the ONLY call site.
 *
 * UNDER-SIZED GLOBAL FIX (2026-07-29): DAT_00552084 (the CreateWindowExA
 * class-name arg) was a zeroed 1-byte placeholder - the real orig .rdata
 * bytes are "edit\0", the Win32 EDIT-control class name. Passing an empty
 * string as the class name makes CreateWindowExA fail
 * (ERROR_CANNOT_FIND_WND_CLASS -> NULL HWND), so this control never
 * actually existed: every call below (GetWindowLongA/SetWindowLongA/
 * SetFocus) silently no-ops or fails on the NULL block[1], `*(block+2)=1`
 * still marks the block "ready" regardless, and keyboard focus never
 * leaves the main window - this is why the lobby's chat edit box never
 * received real keystrokes (confirmed live: GetFocus() at WM_KEYDOWN time
 * returns the main window's own HWND, and block[1] reads 0 throughout).
 * See globals.c's own comment on DAT_00552084. */
#include "ghidra_types.h"


void __fastcall CreateSharedTextInputControl(HINSTANCE param_1,undefined4 *block,HWND hWndParent)

{
  HWND hWnd;
  LONG LVar1;

  DAT_005b1c48 = block;
  *block = (undefined4)hWndParent;
  hWnd = CreateWindowExA(0,DAT_00552084,(LPCSTR)0x0,0x40800000,0,0,800,0x18,hWndParent,(HMENU)0x0,
                         param_1,(LPVOID)0x0);
  block[1] = (undefined4)hWnd;
  LVar1 = GetWindowLongA(hWnd,-4);
  block[3] = LVar1;
  SetWindowLongA((HWND)block[1],-4,(LONG)SharedTextInputControlWndProc);
  SetFocus((HWND)block[1]);
  *(undefined1 *)(block + 2) = 1;
  if (DAT_005b3438 == 1) {
    ImmDisableIME(0);
  }
  return;
}

