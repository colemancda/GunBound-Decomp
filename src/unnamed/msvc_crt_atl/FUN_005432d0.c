/* FUN_005432d0 - 0x005432d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-10-30): atexit destructor thunk for one static
 * XFSArchive: `mov eax,0x796f10; jmp 0x4f0a20` - a static archive this
 * tree has no object for yet; named by its address (this directory is
 * not built).  FUN_004f0a20 takes the archive in EAX.
 */
#include "ghidra_types.h"
#include "xfs.h"

extern unsigned char DAT_00796f10[];  /* static XFSArchive, 0x10740 bytes */


void FUN_005432d0(void)

{
  FUN_004f0a20((int)DAT_00796f10);
  return;
}

