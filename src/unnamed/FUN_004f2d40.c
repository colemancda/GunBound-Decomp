/* FUN_004f2d40 - 0x004f2d40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX PROMOTED (2026-08-25) so its callee's argument can be written.  This
 * function has no call sites and no data references anywhere in the image --
 * not merely no ported ones: an E8-relative scan and a whole-image search for
 * the literal 0x4f2d40 both come back empty -- so there is no caller to derive
 * the value from and none to update.
 */
#include "ghidra_types.h"


void FUN_004f2d40(int regEax)

{
  FUN_004f2d60(regEax);
  FUN_004f2a10();
  return;
}

