/* FUN_004e9ad0 - 0x004e9ad0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX PROMOTED (2026-08-25) so its callee's argument can be written.  This
 * function has no call sites and no data references anywhere in the image --
 * not merely no ported ones: an E8-relative scan and a whole-image search for
 * the literal 0x4e9ad0 both come back empty -- so there is no caller to derive
 * the value from and none to update.
 */
#include "ghidra_types.h"


void FUN_004e9ad0(undefined4 *regEax)

{
  FUN_004e9af0(regEax);
  FUN_004e9520();
  return;
}

