/* HashMap_InitHashTable - 0x00500c00 in the original binary.
 *
 * MFC's CMap::InitHashTable(nHashSize, bAllocNow), and the signature matches
 * that exactly: free any existing bucket array, allocate and zero nHashSize
 * pointers when bAllocNow is set, store the bucket count at +8, and compute
 * the two load-factor thresholds at +0x18 and +0x1c (the second cleared when
 * it lands under 0x11).  Every map insert calls it with (map, map[2], 1) the
 * first time the bucket array is null.
 */
#include "ghidra_types.h"


undefined4 HashMap_InitHashTable(undefined4 *param_1,int param_2,int param_3)

{
  void *pvVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00537710;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if ((void *)*param_1 != (void *)0x0) {
    _free((void *)*param_1);
    *param_1 = 0;
  }
  if (param_3 != '\0') {
    local_8 = 0;
    pvVar1 = operator_new(param_2 * 4);
    *param_1 = pvVar1;
    puVar5 = (undefined4 *)*param_1;
    iVar4 = param_2;
    if (puVar5 == (undefined4 *)0x0) {
      *unaff_FS_OFFSET = local_10;
      return 0;
    }
    for (; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
  }
  param_1[2] = param_2;
  uVar2 = FloatToInt64();
  param_1[6] = uVar2;
  uVar3 = FloatToInt64();
  param_1[7] = uVar3;
  if (uVar3 < 0x11) {
    param_1[7] = 0;
  }
  *unaff_FS_OFFSET = local_10;
  return 1;
}

