/* FUN_00528bc0 - 0x00528bc0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00528bc0(void)

{
  undefined4 unaff_FS_OFFSET;
  undefined1 auStack_c [12];
  
  *(undefined1 **)unaff_FS_OFFSET = auStack_c;
  return;
}

