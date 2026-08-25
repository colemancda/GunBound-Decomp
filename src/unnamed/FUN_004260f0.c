/* FUN_004260f0 - 0x004260f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-08-25) by uniformity: every call site in the original
 * loads the same value into it (`mov eax,[0x5b3484]`), so no site pairing is
 * needed -- there is nothing to match up, and the answer cannot be corrupted
 * by Ghidra's block reordering.  All 2 sites.  ESI and EDI here stay open.
 */
#include "ghidra_types.h"


void FUN_004260f0(int regEax)

{
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  
  FUN_00426620(&DAT_006aa41c + regEax,unaff_ESI);
  FUN_00426620(&DAT_006aa44c + regEax,unaff_EDI);
  return;
}

