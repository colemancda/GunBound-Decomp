/* FUN_004e5a50 - 0x004e5a50 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e5a50(int param_1)

{
  char cVar1;
  int iVar2;
  int unaff_ESI;
  char *unaff_EDI;
  
  *(undefined4 *)(unaff_ESI + 0x22c) = 1;
  if (*(SOCKET *)(unaff_ESI + 0x24) != 0xffffffff) {
    closesocket(*(SOCKET *)(unaff_ESI + 0x24));
  }
  *(undefined2 *)(unaff_ESI + 0x228) = param_1;
  *(undefined4 *)(unaff_ESI + 0x24) = 0xffffffff;
  *(undefined1 *)(unaff_ESI + 0x22a) = 0;
  iVar2 = (unaff_ESI + 0x28) - (int)unaff_EDI;
  do {
    cVar1 = *unaff_EDI;
    unaff_EDI[iVar2] = cVar1;
    unaff_EDI = unaff_EDI + 1;
  } while (cVar1 != '\0');
  *(undefined4 *)(unaff_ESI + 0x22c) = 3;
                    /* WARNING: Could not recover jumptable at 0x004e5aab. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SetEvent(*(HANDLE *)(unaff_ESI + 0x10));
  return;
}

