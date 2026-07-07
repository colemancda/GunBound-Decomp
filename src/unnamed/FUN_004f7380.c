/* FUN_004f7380 - 0x004f7380 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f7380(int param_1,byte *param_2)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte bVar5;
  uint *puVar6;
  uint in_EAX;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  
  if (in_EAX == 0) {
    return;
  }
  uVar8 = *(uint *)(param_1 + 0x14) + in_EAX * 8;
  if (uVar8 < *(uint *)(param_1 + 0x14)) {
    *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + 1;
  }
  uVar10 = *(uint *)(param_1 + 0x5c);
  *(uint *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + (in_EAX >> 0x1d);
  *(uint *)(param_1 + 0x14) = uVar8;
  if (uVar10 != 0) {
    uVar8 = uVar10 + in_EAX;
    iVar7 = (int)uVar10 >> 2;
    uVar10 = uVar10 & 3;
    iVar1 = param_1 + 0x1c;
    if (uVar8 < 0x40) {
      *(uint *)(param_1 + 0x5c) = uVar8;
      uVar11 = *(uint *)(iVar1 + iVar7 * 4);
      if (3 < uVar10 + in_EAX) {
        uVar9 = uVar8 & 3;
        switch(uVar10) {
        case 0:
          uVar11 = (uint)*param_2 << 0x18;
          param_2 = param_2 + 1;
        case 1:
          uVar11 = uVar11 | (uint)*param_2 << 0x10;
          param_2 = param_2 + 1;
        case 2:
          uVar11 = uVar11 | (uint)*param_2 << 8;
          param_2 = param_2 + 1;
        case 3:
          uVar11 = uVar11 | *param_2;
          param_2 = param_2 + 1;
        }
        *(uint *)(iVar1 + iVar7 * 4) = uVar11;
        while (iVar7 = iVar7 + 1, iVar7 < (int)uVar8 >> 2) {
          bVar5 = *param_2;
          pbVar2 = param_2 + 1;
          pbVar3 = param_2 + 2;
          pbVar4 = param_2 + 3;
          param_2 = param_2 + 4;
          *(uint *)(iVar1 + iVar7 * 4) =
               (uint)bVar5 << 0x18 | (uint)*pbVar2 << 0x10 | (uint)*pbVar3 << 8 | (uint)*pbVar4;
        }
        if (uVar9 == 0) {
          return;
        }
        uVar8 = 0;
        param_2 = param_2 + uVar9;
        if (uVar9 != 1) {
          if (uVar9 != 2) {
            if (uVar9 != 3) goto LAB_004f75ce;
            param_2 = param_2 + -1;
            uVar8 = (uint)*param_2 << 8;
          }
          pbVar2 = param_2 + -1;
          param_2 = param_2 + -1;
          uVar8 = uVar8 | (uint)*pbVar2 << 0x10;
        }
        uVar8 = uVar8 | (uint)param_2[-1] << 0x18;
LAB_004f75ce:
        *(uint *)(iVar1 + iVar7 * 4) = uVar8;
        return;
      }
      if (uVar10 == 0) {
        uVar11 = (uint)*param_2 << 0x18;
        param_2 = param_2 + 1;
        in_EAX = in_EAX - 1;
        if (in_EAX == 0) goto LAB_004f7529;
LAB_004f7517:
        uVar11 = uVar11 | (uint)*param_2 << 0x10;
        param_2 = param_2 + 1;
        if (in_EAX == 1) goto LAB_004f7529;
      }
      else {
        if (uVar10 == 1) goto LAB_004f7517;
        if (uVar10 != 2) {
          *(uint *)(iVar1 + iVar7 * 4) = uVar11;
          return;
        }
      }
      uVar11 = uVar11 | (uint)*param_2 << 8;
LAB_004f7529:
      *(uint *)(iVar1 + iVar7 * 4) = uVar11;
      return;
    }
    uVar8 = *(uint *)(iVar1 + iVar7 * 4);
    switch(uVar10) {
    case 0:
      uVar8 = (uint)*param_2 << 0x18;
      param_2 = param_2 + 1;
    case 1:
      uVar8 = uVar8 | (uint)*param_2 << 0x10;
      param_2 = param_2 + 1;
    case 2:
      uVar8 = uVar8 | (uint)*param_2 << 8;
      param_2 = param_2 + 1;
    case 3:
      uVar8 = uVar8 | *param_2;
      param_2 = param_2 + 1;
    default:
      *(uint *)(iVar1 + iVar7 * 4) = uVar8;
      while (iVar7 = iVar7 + 1, iVar7 < 0x10) {
        bVar5 = *param_2;
        pbVar2 = param_2 + 1;
        pbVar3 = param_2 + 2;
        pbVar4 = param_2 + 3;
        param_2 = param_2 + 4;
        *(uint *)(iVar1 + iVar7 * 4) =
             (uint)bVar5 << 0x18 | (uint)*pbVar2 << 0x10 | (uint)*pbVar3 << 8 | (uint)*pbVar4;
      }
      FUN_004f76f0(1);
      in_EAX = (in_EAX - 0x40) + *(int *)(param_1 + 0x5c);
      *(undefined4 *)(param_1 + 0x5c) = 0;
    }
  }
  uVar8 = in_EAX >> 6;
  if (uVar8 != 0) {
    FUN_004f9fa0(uVar8);
    param_2 = param_2 + uVar8 * 0x40;
    in_EAX = in_EAX + uVar8 * -0x40;
  }
  if (in_EAX == 0) {
    return;
  }
  *(uint *)(param_1 + 0x5c) = in_EAX;
  uVar10 = in_EAX & 3;
  puVar6 = (uint *)(param_1 + 0x1c);
  for (uVar8 = in_EAX >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *puVar6 = (uint)*param_2 << 0x18 | (uint)param_2[1] << 0x10 | (uint)param_2[2] << 8 |
              (uint)param_2[3];
    param_2 = param_2 + 4;
    puVar6 = puVar6 + 1;
  }
  uVar8 = 0;
  param_2 = param_2 + uVar10;
  if (uVar10 != 1) {
    if (uVar10 != 2) {
      if (uVar10 != 3) goto LAB_004f74df;
      uVar8 = (uint)param_2[-1] << 8;
      param_2 = param_2 + -1;
    }
    pbVar2 = param_2 + -1;
    param_2 = param_2 + -1;
    uVar8 = uVar8 | (uint)*pbVar2 << 0x10;
  }
  uVar8 = uVar8 | (uint)param_2[-1] << 0x18;
LAB_004f74df:
  *puVar6 = uVar8;
  return;
}

