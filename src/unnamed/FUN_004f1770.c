/* FUN_004f1770 - 0x004f1770 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f1770(void)

{
  undefined4 *unaff_ESI;
  
  *unaff_ESI = &PTR_FUN_00557534;
  FUN_004f3060(unaff_ESI);
  if ((undefined4 *)unaff_ESI[1] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)unaff_ESI[1])(1);
  }
  return;
}

