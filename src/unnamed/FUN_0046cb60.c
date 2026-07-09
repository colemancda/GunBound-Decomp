/* FUN_0046cb60 - 0x0046cb60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_0046cb60(void)

{
  undefined4 in_EAX;
  undefined4 *unaff_ESI;
  
  FUN_00458b80(unaff_ESI,in_EAX);
  *unaff_ESI = &PTR_FUN_00555e54;
  unaff_ESI[0x2ffc] = 2;
  return;
}

