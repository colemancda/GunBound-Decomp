/* FUN_005030a0 - 0x005030a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_005030a0(void)

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
  FUN_0040bee0(s_vector<T>_too_long_00557260,0x12);
  local_4 = 0;
  FUN_00409fd0(local_50);
  local_34[0] = &PTR_FUN_00544b68;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_34,&DAT_0055841c);
}

