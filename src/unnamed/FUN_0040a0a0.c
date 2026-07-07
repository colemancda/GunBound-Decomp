/* FUN_0040a0a0 - 0x0040a0a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int * FUN_0040a0a0(int *param_1)

{
  void *pvVar1;
  int iVar2;
  DWORD DVar3;
  int iVar4;
  undefined4 *unaff_FS_OFFSET;
  int local_18;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00537b5b;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  pvVar1 = operator_new(0x100000);
  *param_1 = (int)pvVar1;
  iVar2 = FUN_0040c110();
  param_1[2] = iVar2;
  *(undefined1 *)(iVar2 + 0x11) = 1;
  *(int *)(param_1[2] + 4) = param_1[2];
  *(int *)param_1[2] = param_1[2];
  *(int *)(param_1[2] + 8) = param_1[2];
  param_1[3] = 0;
  local_4 = 0;
  param_1[4] = 0;
  DVar3 = GetTickCount();
  FUN_00525c42(DVar3);
  local_18 = 0;
  do {
    iVar2 = 0;
    do {
      iVar4 = _rand();
      *(char *)(*param_1 + local_18 * 0x10 + iVar2) = (char)iVar4;
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x10);
    if (local_18 != 0) {
      FUN_0040b540(local_14);
    }
    local_18 = local_18 + 1;
  } while (local_18 < 0x10000);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

