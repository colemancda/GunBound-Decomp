/* FUN_00503c40 - 0x00503c40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

undefined4 __thiscall FUN_00503c40(undefined4 *param_1,ushort *param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 unaff_EBX;
  int unaff_ESI;
  undefined4 *puVar7;
  ushort *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 local_2ee8 [1498];
  undefined1 auStack_1780 [8];
  undefined4 local_1778 [1499];
  undefined4 uStack_c;
  
  uStack_c = 0x503c50;
  uVar4 = param_1[0x5dd];
  if ((((uVar4 == 0) && (2 < param_3)) && (*param_2 == param_3)) && (param_3 < 0x1771)) {
    puVar7 = local_2ee8;
    for (uVar4 = param_3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar7 = *(undefined4 *)param_2;
      param_2 = param_2 + 2;
      puVar7 = puVar7 + 1;
    }
    param_1 = (undefined4 *)*param_1;
    for (uVar4 = param_3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(char *)puVar7 = (char)*param_2;
      param_2 = (ushort *)((int)param_2 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
    iVar1 = (*(code *)*param_1)(local_2ee8,param_3);
    if (iVar1 != 0) {
      return 1;
    }
    return 0;
  }
  if (uVar4 < 2) {
    if (uVar4 + param_3 < 2) goto LAB_00503de7;
    uVar2 = 2 - uVar4;
    puVar8 = param_2;
    puVar7 = (undefined4 *)(uVar4 + 4 + (int)param_1);
    for (uVar5 = uVar2 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *puVar7 = *(undefined4 *)puVar8;
      puVar8 = puVar8 + 2;
      puVar7 = puVar7 + 1;
    }
    param_2 = (ushort *)((int)param_2 + uVar2);
    for (uVar4 = uVar2 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(char *)puVar7 = (char)*puVar8;
      puVar8 = (ushort *)((int)puVar8 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
    param_3 = param_3 - uVar2;
    param_1[0x5dd] = param_1[0x5dd] + uVar2;
    if (param_3 == 0) {
      return 1;
    }
  }
  uVar2 = (uint)*(ushort *)(param_1 + 1);
  if ((6000 < uVar2) || (uVar4 = param_1[0x5dd], uVar2 < uVar4)) {
    return 0;
  }
  if (uVar2 <= uVar4 + param_3) {
    uVar5 = uVar2 - uVar4;
    if (uVar4 == 2) {
      SUBFIELD(local_2ee8[0],0,undefined2) = *(undefined2 *)(param_1 + 1);
    }
    else {
      puVar9 = local_2ee8;
      puVar7 = param_1;
      for (uVar6 = uVar4 >> 2; puVar7 = puVar7 + 1, uVar6 != 0; uVar6 = uVar6 - 1) {
        *puVar9 = *puVar7;
        puVar9 = puVar9 + 1;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined1 *)puVar9 = *(undefined1 *)puVar7;
        puVar7 = (undefined4 *)((int)puVar7 + 1);
        puVar9 = (undefined4 *)((int)puVar9 + 1);
      }
    }
    puVar8 = param_2;
    puVar7 = (undefined4 *)((int)local_2ee8 + param_1[0x5dd]);
    for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar7 = *(undefined4 *)puVar8;
      puVar8 = puVar8 + 2;
      puVar7 = puVar7 + 1;
    }
    for (uVar4 = uVar5 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(char *)puVar7 = (char)*puVar8;
      puVar8 = (ushort *)((int)puVar8 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
    puVar7 = (undefined4 *)*param_1;
    param_1[0x5dd] = 0;
    puVar9 = (undefined4 *)(uVar5 + (int)param_2);
    puVar10 = local_1778;
    for (uVar4 = param_3 - uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar10 = *puVar9;
      puVar9 = puVar9 + 1;
      puVar10 = puVar10 + 1;
    }
    for (uVar4 = param_3 - uVar5 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined1 *)puVar10 = *(undefined1 *)puVar9;
      puVar9 = (undefined4 *)((int)puVar9 + 1);
      puVar10 = (undefined4 *)((int)puVar10 + 1);
    }
    iVar1 = (*(code *)*puVar7)(local_2ee8,uVar2);
    if (iVar1 != 0) {
      if ((int)param_3 <= unaff_ESI) {
        return 1;
      }
      /* Ghidra dropped the recursive call's 3rd arg (the count/length
       * param_3, guarded against unaff_ESI just above). Restored so this
       * __thiscall(3-param) recursion matches its own signature. */
      uVar3 = FUN_00503c40(auStack_1780,unaff_EBX,param_3);
      return uVar3;
    }
    return 0;
  }
LAB_00503de7:
  puVar7 = (undefined4 *)(uVar4 + 4 + (int)param_1);
  for (uVar2 = param_3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar7 = *(undefined4 *)param_2;
    param_2 = param_2 + 2;
    puVar7 = puVar7 + 1;
  }
  for (uVar4 = param_3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(char *)puVar7 = (char)*param_2;
    param_2 = (ushort *)((int)param_2 + 1);
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  param_1[0x5dd] = param_1[0x5dd] + param_3;
  return 1;
}

