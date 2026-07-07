/* FUN_00426810 - 0x00426810 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_00426810(int param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_005380ab;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  local_4 = 0;
  if (*(int *)(param_1 + 0x240) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4 = 0xffffffff;
  if (*(int *)(param_1 + 0x1c) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

