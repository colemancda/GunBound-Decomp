/* FUN_00543900 - 0x00543900 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-10-30): atexit destructor thunk for one static
 * XFSArchive: `mov eax,0xea0f50; jmp 0x4f0a20` - the sound archive,
 * which this tree opens as g_xfsScratch (see InitDirectSound.c).
 * FUN_004f0a20 takes the archive in EAX.
 */
#include "ghidra_types.h"
#include "xfs.h"


void FUN_00543900(void)

{
  FUN_004f0a20((int)&g_xfsScratch);
  return;
}

