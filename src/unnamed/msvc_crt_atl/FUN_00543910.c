/* FUN_00543910 - 0x00543910 in the original binary.
 * (Historical notes below: FUN_004f0a20 is now XFSArchive_Destruct.)
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-10-30): atexit destructor thunk for one static
 * XFSArchive: `mov eax,0xf11dd0; jmp 0x4f0a20` - g_graphicsArchive.
 * FUN_004f0a20 takes the archive in EAX.
 */
#include "ghidra_types.h"
#include "xfs.h"


void FUN_00543910(void)

{
  XFSArchive_Destruct((int)&g_graphicsArchive);
  return;
}

