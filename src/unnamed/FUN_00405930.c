/* FUN_00405930 - 0x00405930 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* DROPPED-REGISTER FIX (2026-07-17): `unaff_EDI` (the connection OWNER
 * object, e.g. DAT_007934f4) arrives in EDI - confirmed at both call sites
 * (orig 0x4121cc `mov edi,esi`(=[0x7934f4]), 0x40fe86 `mov edi,[0x7934f4]`
 * right before `call 0x405930`). The port read uninitialised EDI ->
 * *(garbage+0x2004) wild derefs; the first socket-error event (PIEQ 0x65)
 * hung the main thread here. Promoted to a parameter; the inner
 * FUN_004e5590 call gets the conn sub-object per orig 0x405979. */
void FUN_00405930(int connOwner)

{
  int iVar1;
  void *_Memory;
  int unaff_EDI = connOwner;
  
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
    FUN_004e5590((undefined4 *)_Memory);
    _free(_Memory);
  }
  return;
}

