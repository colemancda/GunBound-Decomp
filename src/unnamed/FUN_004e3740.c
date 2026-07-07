/* FUN_004e3740 - 0x004e3740 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


undefined4 * FUN_004e3740(void)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined1 auStack_14 [4];
  undefined1 auStack_10 [4];
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_00537b38;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  puVar2 = (undefined4 *)(**(code **)(DAT_005b1444 + 0xc))();
  uStack_4 = 0;
  iVar3 = FUN_00426780(auStack_10,auStack_14,&stack0x00000004);
  if (iVar3 != 0) {
    FUN_0043ddb0();
    uStack_4 = 0xffffffff;
    piVar1 = puVar2 + 3;
    LOCK();
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 == 1 || iVar3 + -1 < 0) {
      (**(code **)(*(int *)*puVar2 + 4))(puVar2);
    }
    *unaff_FS_OFFSET = uStack_c;
    return puVar2 + 4;
  }
  uStack_4 = 0xffffffff;
  piVar1 = puVar2 + 3;
  LOCK();
  iVar3 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar3 == 1 || iVar3 + -1 < 0) {
    (**(code **)(*(int *)*puVar2 + 4))(puVar2);
  }
  *unaff_FS_OFFSET = uStack_c;
  return (undefined4 *)0x0;
}

