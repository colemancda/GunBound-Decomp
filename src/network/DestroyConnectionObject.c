/* DestroyConnectionObject - 0x004e5590 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* DROPPED-REGISTER FIX (2026-07-17): `unaff_ESI` (the connection
 * sub-object this destructor tears down) arrives in ESI - confirmed at both
 * call sites (orig 0x405979 `mov esi,[edi+0x2004]`, 0x4d2351 `mov esi,
 * [edi+0x84e0]` right before `call 0x4e5590`). The port read uninitialised
 * ESI and did wild SetEvent/DeleteCriticalSection/free - this hung the main
 * thread on the first socket-error teardown (PIEQ msg 0x65). Promoted to an
 * explicit parameter. */
void DestroyConnectionObject(undefined4 *conn)

{
  undefined4 *unaff_ESI = conn;
  
  *unaff_ESI = &PTR_FUN_005572e8;
  unaff_ESI[0x8b] = 1;
  if (unaff_ESI[9] != 0xffffffff) {
    closesocket(unaff_ESI[9]);
  }
  unaff_ESI[9] = 0xffffffff;
  *(undefined1 *)((int)unaff_ESI + 0x22a) = 0;
  *(undefined1 *)(unaff_ESI + 6) = 0;
  SetEvent((HANDLE)unaff_ESI[2]);
  if ((HANDLE)unaff_ESI[1] != (HANDLE)0x0) {
    WaitForSingleObject((HANDLE)unaff_ESI[1],1000);
  }
  unaff_ESI[0x9295] = &PTR_FUN_005572dc;
  DeleteCriticalSection((LPCRITICAL_SECTION)(unaff_ESI + 0x9296));
  if ((void *)unaff_ESI[0x9290] != (void *)0x0) {
    _free((void *)unaff_ESI[0x9290]);
  }
  ShutdownConnectionThread();
  return;
}

