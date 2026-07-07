/* FUN_0040c8b0 - 0x0040c8b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
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

