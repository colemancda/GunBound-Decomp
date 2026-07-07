/* FUN_004f14e0 - 0x004f14e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f14e0(void)

{
  undefined4 *unaff_ESI;
  
  *unaff_ESI = &PTR_FUN_00557524;
  if ((void *)unaff_ESI[0xd] != (void *)0x0) {
    _free((void *)unaff_ESI[0xd]);
  }
  unaff_ESI[0xd] = 0;
  if ((void *)unaff_ESI[0xe] != (void *)0x0) {
    _free((void *)unaff_ESI[0xe]);
  }
  unaff_ESI[0xe] = 0;
  *unaff_ESI = &PTR_LAB_0055752c;
  return;
}

