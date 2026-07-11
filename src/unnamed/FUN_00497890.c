/* FUN_00497890 - 0x00497890 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00497890(undefined4 *param_1)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined1 auStack_14 [8];
  undefined4 uStack_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_00539826;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  *param_1 = &PTR_FUN_005563f0;
  local_4 = 2;
  iVar1 = param_1[0xff3];
  if (DAT_00793549 != '\0') {
    if (iVar1 != -1) {
      (**(code **)(**(int **)(DAT_00793554 + iVar1 * 4) + 0xc))();
    }
    if (iVar1 == 0) {
      DAT_00793568 = 0;
    }
  }
  SUBFIELD(local_4,0,undefined1) = 1;
  param_1[0xff3] = 0xffffffff;
  if (param_1[0x1083] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(auStack_14);
  }
  local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
  if (param_1[0xffa] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(auStack_14);
  }
  local_4 = 0xffffffff;
  DestroyProjectile(param_1);
  *unaff_FS_OFFSET = uStack_c;
  return;
}

