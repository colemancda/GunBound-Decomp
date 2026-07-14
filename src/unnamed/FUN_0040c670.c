/* FUN_0040c670 - 0x0040c670 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
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
 */
#include "ghidra_types.h"


void __fastcall FUN_0040c670(HINSTANCE param_1,undefined4 *block,HWND hWndParent)

{
  HWND hWnd;
  LONG LVar1;

  DAT_005b1c48 = block;
  *block = (undefined4)hWndParent;
  hWnd = CreateWindowExA(0,&DAT_00552084,(LPCSTR)0x0,0x40800000,0,0,800,0x18,hWndParent,(HMENU)0x0,
                         param_1,(LPVOID)0x0);
  block[1] = (undefined4)hWnd;
  LVar1 = GetWindowLongA(hWnd,-4);
  block[3] = LVar1;
  SetWindowLongA((HWND)block[1],-4,0x40c6f0);
  SetFocus((HWND)block[1]);
  *(undefined1 *)(block + 2) = 1;
  if (DAT_005b3438 == 1) {
    ImmDisableIME(0);
  }
  return;
}

