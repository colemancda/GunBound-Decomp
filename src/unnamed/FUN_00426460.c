/* FUN_00426460 - 0x00426460 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_00426460(void)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_50 [4];
  undefined1 local_4c;
  undefined4 local_3c;
  undefined4 local_38;
  undefined **local_34 [10];
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00537a38;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_38 = 0xf;
  local_3c = 0;
  local_4c = 0;
  FUN_0040bee0(s_invalid_bitset<N>_position_00552c4c,0x1a);
  local_4 = 0;
  FUN_00409fd0(local_50);
  local_34[0] = &PTR_FUN_00544b74;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_34,&DAT_00558458);
}

