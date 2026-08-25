/* FUN_0040c8f0 - 0x0040c8f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EDI RECOVERED (2026-08-25) by uniformity: every call site in the original
 * loads the same value into it (`mov edi,[0x7934e4]`), so no site pairing is
 * needed -- there is nothing to match up, and the answer cannot be corrupted
 * by Ghidra's block reordering.  All 4 binary sites agree; 3 are ported and
 * the fourth, 0x40cab2, sits in a function that has not been carved.
 */
#include "ghidra_types.h"


void FUN_0040c8f0(int param_1,LONG param_2,int param_3,int regEdi)

{
  undefined4 *in_EAX;
  LRESULT LVar1;
  HIMC pHVar2;
  int *unaff_ESI;
  tagCOMPOSITIONFORM *lpCompForm;
  tagCOMPOSITIONFORM local_1c;
  
  if (*(char *)(regEdi + 8) != '\0') {
    LVar1 = SendMessageA(*(HWND *)(regEdi + 4),0xb0,(WPARAM)unaff_ESI,(LPARAM)in_EAX);
    if (LVar1 == -1) {
      *in_EAX = 0;
      *unaff_ESI = 0;
    }
    local_1c.ptCurrentPos.x = param_1 + (*unaff_ESI - param_3) * 6;
    lpCompForm = &local_1c;
    local_1c.dwStyle = 2;
    local_1c.ptCurrentPos.y = param_2;
    pHVar2 = ImmGetContext(*(HWND *)(regEdi + 4));
    ImmSetCompositionWindow(pHVar2,lpCompForm);
    return;
  }
  *in_EAX = 0;
  *unaff_ESI = 0;
  return;
}

