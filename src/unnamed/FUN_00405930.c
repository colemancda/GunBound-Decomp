/* FUN_00405930 - 0x00405930 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00405930(void)

{
  int iVar1;
  void *_Memory;
  int unaff_EDI;
  
  iVar1 = *(int *)(unaff_EDI + 0x2004);
  *(undefined4 *)(iVar1 + 0x22c) = 1;
  if (*(SOCKET *)(iVar1 + 0x24) != 0xffffffff) {
    closesocket(*(SOCKET *)(iVar1 + 0x24));
  }
  *(undefined4 *)(iVar1 + 0x24) = 0xffffffff;
  *(undefined1 *)(iVar1 + 0x22a) = 0;
  iVar1 = *(int *)(unaff_EDI + 0x2004);
  *(undefined1 *)(unaff_EDI + 0x2009) = 0;
  *(undefined1 *)(iVar1 + 0x18) = 0;
  SetEvent(*(HANDLE *)(iVar1 + 8));
  _Memory = *(void **)(unaff_EDI + 0x2004);
  if (_Memory != (void *)0x0) {
    FUN_004e5590();
    _free(_Memory);
  }
  return;
}

