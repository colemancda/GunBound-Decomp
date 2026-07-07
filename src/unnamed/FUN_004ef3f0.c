/* FUN_004ef3f0 - 0x004ef3f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ef3f0(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_00537bd8;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &PTR_LAB_005574e8;
  local_4 = 0;
  *(undefined1 *)(param_1 + 4) = 0;
  SetEvent((HANDLE)param_1[2]);
  FUN_004ef5b0();
  DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 8));
  FUN_004ef820();
  *unaff_FS_OFFSET = local_c;
  return;
}

