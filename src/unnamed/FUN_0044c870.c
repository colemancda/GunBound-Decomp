/* FUN_0044c870 - 0x0044c870 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0044c870(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined1 local_8;
  undefined3 uStack_7;
  
  puStack_c = &LAB_0053ac45;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  uStack_7 = 0;
  for (uVar2 = 0; uVar2 < param_2; uVar2 = uVar2 + 1) {
    iVar1 = uVar2 * 0x450 + param_1;
    local_8 = 1;
    if (iVar1 != 0) {
      FUN_00428550(iVar1);
    }
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

