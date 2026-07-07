/* FUN_0040c8f0 - 0x0040c8f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0040c8f0(int param_1,LONG param_2,int param_3)

{
  undefined4 *in_EAX;
  LRESULT LVar1;
  HIMC pHVar2;
  int *unaff_ESI;
  int unaff_EDI;
  tagCOMPOSITIONFORM *lpCompForm;
  tagCOMPOSITIONFORM local_1c;
  
  if (*(char *)(unaff_EDI + 8) != '\0') {
    LVar1 = SendMessageA(*(HWND *)(unaff_EDI + 4),0xb0,(WPARAM)unaff_ESI,(LPARAM)in_EAX);
    if (LVar1 == -1) {
      *in_EAX = 0;
      *unaff_ESI = 0;
    }
    local_1c.ptCurrentPos.x = param_1 + (*unaff_ESI - param_3) * 6;
    lpCompForm = &local_1c;
    local_1c.dwStyle = 2;
    local_1c.ptCurrentPos.y = param_2;
    pHVar2 = ImmGetContext(*(HWND *)(unaff_EDI + 4));
    ImmSetCompositionWindow(pHVar2,lpCompForm);
    return;
  }
  *in_EAX = 0;
  *unaff_ESI = 0;
  return;
}

