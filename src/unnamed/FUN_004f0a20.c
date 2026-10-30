/* FUN_004f0a20 - 0x004f0a20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ARCHIVE RECOVERED (2026-10-30): the XFSArchive destructor - it closes
 * the file if open, re-stamps the base vtable 0x5572dc at +0x10714 and
 * deletes the +0x10718 critical section, the reverse of
 * XFSArchive_Construct.  The archive arrives in EAX (`mov esi,eax` at
 * 0x4f0a21, read before any write); it is now the parameter regEax.
 * The CloseXFSArchive (FUN_004f0d70) call at 0x4f0a2c takes the archive
 * in ESI, which is that same EAX value, so it now passes it; it was
 * called with nothing.  Its three callers are the CRT atexit thunks in
 * msvc_crt_atl/ (`mov eax,<archive>; jmp 0x4f0a20`: 0x5432d0 = 0x796f10,
 * 0x543900 = 0xea0f50, 0x543910 = 0xf11dd0 = g_graphicsArchive).
 */
#include "ghidra_types.h"
#include "xfs.h"


void FUN_004f0a20(int regEax)

{
  int in_EAX = regEax;
  
  if (*(int *)(in_EAX + 0x1040) != -1) {
    FUN_004f0d70((XFSArchive *)in_EAX);
  }
  *(undefined ***)(in_EAX + 0x10714) = &PTR_FUN_005572dc;
  DeleteCriticalSection((LPCRITICAL_SECTION)(in_EAX + 0x10718));
  return;
}

