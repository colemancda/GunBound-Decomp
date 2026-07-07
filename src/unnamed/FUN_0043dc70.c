/* FUN_0043dc70 - 0x0043dc70 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_0043dc70(void)

{
  int *piVar1;
  undefined *puVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_00537938;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  puVar3 = (undefined4 *)(**(code **)(DAT_005b1444 + 0xc))();
  uStack_4 = 0;
  iVar4 = FUN_0043e060();
  puVar2 = PTR_DAT_0056d460;
  if (iVar4 != 0) {
    FUN_0043ddb0();
    uStack_4 = 0xffffffff;
    piVar1 = puVar3 + 3;
    LOCK();
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 == 1 || iVar4 + -1 < 0) {
      (**(code **)(*(int *)*puVar3 + 4))(puVar3);
    }
    *unaff_FS_OFFSET = uStack_c;
    return puVar3 + 4;
  }
  uStack_4 = 0xffffffff;
  piVar1 = puVar3 + 3;
  LOCK();
  iVar4 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar4 == 1 || iVar4 + -1 < 0) {
    (**(code **)(*(int *)*puVar3 + 4))(puVar3);
  }
  *unaff_FS_OFFSET = uStack_c;
  return (undefined4 *)puVar2;
}

