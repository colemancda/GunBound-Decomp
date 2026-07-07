/* FUN_004907d0 - 0x004907d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004907d0(void)

{
  undefined4 *unaff_ESI;
  
  FUN_00454dc0(unaff_ESI,0x186a2);
  *unaff_ESI = &PTR_FUN_00556360;
  return;
}

