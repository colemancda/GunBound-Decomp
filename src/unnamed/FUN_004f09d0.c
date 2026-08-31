/* FUN_004f09d0 - 0x004f09d0 in the original binary.
 *
 * The XFSArchive constructor: installs the vtable at +0x10714
 * (&PTR_FUN_005572dc), initialises the CRITICAL_SECTION at +0x10718,
 * zeroes the 0x1000-byte entry table at +0x40, and sets handle
 * (+0x1040) = -1 (XFS_CLOSED), +0x1044 = 0, +8 = 0, +0x1045 = 1 -
 * exactly the "closed, ready to open" state xfs.h documents for
 * OpenXFSArchive (0x4f0a50, directly after it in the binary).
 *
 * DROPPED-REG FIX (2026-08-31): `this` arrives in ESI, promoted to
 * regEsi. Its three binary call sites are all CRT static-initializer
 * thunks (0x540ec0, 0x5428a0, 0x542930: `push esi / mov esi,<obj> /
 * call 0x4f09d0 / push <atexit dtor thunk> / call _atexit`), one per
 * static archive - 0x796f10, 0xea0f50, and 0xf11dd0 =
 * g_graphicsArchive - so they have no C source counterpart. The port
 * runs it from the .CRT$XCU hook in crt_shims_msvc.c instead, which
 * previously replicated only the handle = -1 store.
 * Raw/near-verbatim port of Ghidra's decompiler output otherwise, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for
 * status.
 */
#include "ghidra_types.h"


void FUN_004f09d0(int regEsi)

{
  int iVar1;
  undefined4 *puVar2;
  
  *(undefined ***)(regEsi + 0x10714) = &PTR_FUN_005572dc;
  InitializeCriticalSection((LPCRITICAL_SECTION)(regEsi + 0x10718));
  puVar2 = (undefined4 *)(regEsi + 0x40);
  for (iVar1 = 0x400; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)(regEsi + 0x1044) = 0;
  *(undefined4 *)(regEsi + 8) = 0;
  *(undefined4 *)(regEsi + 0x1040) = 0xffffffff;
  *(undefined1 *)(regEsi + 0x1045) = 1;
  return;
}

