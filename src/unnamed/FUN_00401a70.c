/* FUN_00401a70 - 0x00401a70 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00401a70(undefined4 *param_1)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  void *_Memory;
  undefined4 *puVar4;
  int iVar5;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  uint local_4;
  
  uStack_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_00537922;
  *unaff_FS_OFFSET = &uStack_c;
  *param_1 = &PTR_FUN_00551cf0;
  param_1[2] = &PTR_LAB_00551cb8;
  local_4 = 2;
  puVar4 = param_1 + 0x56b;
  iVar5 = 0x80;
  do {
    if ((void *)*puVar4 != (void *)0x0) {
      _free((void *)*puVar4);
    }
    puVar4 = puVar4 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  if ((int *)param_1[0x6f7] != (int *)0x0) {
    (**(code **)(*(int *)param_1[0x6f7] + 4))();
  }
  param_1[0x6f7] = 0;
  FUN_00404b90();
  local_4 = local_4 & 0xffffff00;
  piVar2 = (int *)param_1[0x6f9];
  if (piVar2 != (int *)param_1[0x6fe]) {
    FUN_004054c0(piVar2[0x42]);
    FUN_004054c0(piVar2[0x43]);
    puVar4 = (undefined4 *)(*piVar2 + -0x10);
    piVar1 = (int *)(*piVar2 + -4);
    LOCK();
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 == 1 || iVar5 + -1 < 0) {
      (**(code **)(*(int *)*puVar4 + 4))(puVar4);
    }
    piVar2[0x42] = param_1[0x6fb];
    param_1[0x6fb] = piVar2;
    param_1[0x6fa] = param_1[0x6fa] + -1;
  }
  param_1[0x6fa] = 0;
  puVar4 = (undefined4 *)param_1[0x6fc];
  while (puVar4 != (undefined4 *)0x0) {
    puVar3 = (undefined4 *)*puVar4;
    _free(puVar4);
    puVar4 = puVar3;
  }
  _Memory = (void *)param_1[0x6fe];
  param_1[0x6fc] = 0;
  param_1[0x6fb] = 0;
  param_1[0x6f9] = _Memory;
  if (_Memory != (void *)0x0) {
    _free(_Memory);
  }
  local_4 = 0xffffffff;
  *param_1 = &PTR_FUN_00557534;
  FUN_004f3060(param_1);
  if ((undefined4 *)param_1[1] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)param_1[1])(1);
  }
  *unaff_FS_OFFSET = uStack_c;
  return;
}

