/* FUN_004260f0 - 0x004260f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004260f0(void)

{
  int in_EAX;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  
  FUN_00426620(&DAT_006aa41c + in_EAX,unaff_ESI);
  FUN_00426620(&DAT_006aa44c + in_EAX,unaff_EDI);
  return;
}

