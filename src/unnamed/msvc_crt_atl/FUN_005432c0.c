/* FUN_005432c0 - 0x005432c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"
#include "globals.h"


void FUN_005432c0(void)

{
  /* atexit destructor thunk for the static animated-cursor object: the
   * original is `mov eax, 0x7a7644 / jmp ScrubObjectVtable` -- a tail call
   * with the object in the (now explicit) EAX parameter.  DAT_007a7644's
   * sized storage is in globals_sized.c. */
  ScrubObjectVtable((undefined4 *)DAT_007a7644);
  return;
}

