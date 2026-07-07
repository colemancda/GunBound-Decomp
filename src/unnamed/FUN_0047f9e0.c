/* FUN_0047f9e0 - 0x0047f9e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0047f9e0(void)

{
  undefined4 *unaff_ESI;
  
  FUN_00454dc0(unaff_ESI,0x186a5);
  unaff_ESI[0xfec] = 0;
  unaff_ESI[0xfea] = 0;
  unaff_ESI[0xfeb] = 0;
  *(undefined1 *)(unaff_ESI + 0xfe8) = 0;
  unaff_ESI[0xfef] = 0;
  *(undefined1 *)(unaff_ESI + 0xff1) = 0;
  *(undefined1 *)(unaff_ESI + 0xff8) = 0;
  *unaff_ESI = &PTR_FUN_00556110;
  unaff_ESI[0xff0] = 0xffffffff;
  return;
}

