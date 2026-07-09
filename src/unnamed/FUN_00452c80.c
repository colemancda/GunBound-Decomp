/* FUN_00452c80 - 0x00452c80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00452c80(void)

{
  undefined4 *unaff_ESI;
  
  FUN_00454dc0(unaff_ESI,0x186a2);
  *unaff_ESI = &PTR_FUN_00555bf0;
  FUN_00406440();
  FUN_00406440();
  unaff_ESI[0xfe7] = 0;
  unaff_ESI[0xfeb] = 0xffffffff;
  return;
}

