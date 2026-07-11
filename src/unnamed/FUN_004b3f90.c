/* FUN_004b3f90 - 0x004b3f90 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_004b3f90(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_00537d13;
  *unaff_FS_OFFSET = &local_c;
  local_4 = 0;
  *param_1 = &vtable_State11_InBattle;
  InitGuardedBool();
  _eh_vector_constructor_iterator_(param_1 + 0x477,0x224,8,InitGuardSlot,ScrubChecksumGuard);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),1);
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  _eh_vector_constructor_iterator_((void *)((int)param_1 + 0x23d7),3,0x10,InitGuardedBool,NoOpMethod)
  ;
  *(undefined1 *)(param_1 + 0x474) = 0;
  param_1[0x475] = 0xffffffff;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

