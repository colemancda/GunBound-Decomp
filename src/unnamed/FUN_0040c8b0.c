/* FUN_0040c8b0 - 0x0040c8b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * param_1 FILLED.  `ret 0`, so param_1 is ECX, and the sole call site
 * (0x004d65ff) passed nothing: `mov ecx,[0x7934e4]`.  The body uses it as
 * *(HWND *)(param_1 + 4), so an unsupplied param_1 meant SetWindowTextA was
 * handed a window handle read from a garbage address.
 *
 * in_EAX stays open.  It is the text argument, and at the call site it is
 * `lea eax,[esp+0x58]` -- the address of a caller stack local, the string the
 * preceding `rep movsb` had just assembled.  Naming a caller spill slot needs
 * a stack-depth model this tree does not have, so it is left as a local
 * rather than guessed at; the NULL check above it means the wrong value shows
 * up as the wrong caption, not as a crash.
 */
#include "ghidra_types.h"


void __fastcall FUN_0040c8b0(int param_1)

{
  LPCSTR in_EAX;
  
  if (in_EAX == (LPCSTR)0x0) {
    SetWindowTextA(*(HWND *)(param_1 + 4),&DAT_00551cb1);
    return;
  }
  SetWindowTextA(*(HWND *)(param_1 + 4),in_EAX);
  return;
}

