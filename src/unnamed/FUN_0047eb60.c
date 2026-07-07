/* FUN_0047eb60 - 0x0047eb60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0047eb60(void)

{
  undefined4 *unaff_ESI;
  
  FUN_00454dc0(unaff_ESI,0x186a2);
  unaff_ESI[0xfe7] = 0;
  unaff_ESI[0x1028] = 0;
  *unaff_ESI = &PTR_FUN_005560d0;
  return;
}

