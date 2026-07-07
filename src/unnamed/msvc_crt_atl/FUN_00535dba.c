/* FUN_00535dba - 0x00535dba in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___ld12mul
   
   Library: Visual Studio 2003 Release */

void ___ld12mul(int *param_1,int *param_2)

{
  short sVar1;
  int iVar2;
  ushort uVar3;
  int *piVar4;
  int *piVar5;
  ushort uVar6;
  int iVar7;
  ushort uVar8;
  uint uVar9;
  ushort uVar10;
  int local_2c;
  ushort *local_28;
  ushort *local_24;
  int local_20;
  int local_1c;
  short *local_18;
  byte local_14;
  undefined1 uStack_13;
  undefined2 uStack_12;
  short local_10;
  undefined2 uStack_e;
  undefined2 local_c;
  undefined1 uStack_a;
  byte bStack_9;
  undefined4 local_8;
  
  piVar5 = param_2;
  piVar4 = param_1;
  local_8 = DAT_0056bfd4;
  local_20 = 0;
  local_14 = 0;
  uStack_13 = 0;
  uStack_12 = 0;
  local_10 = 0;
  uStack_e = 0;
  local_c = 0;
  uStack_a = 0;
  bStack_9 = 0;
  uVar8 = *(ushort *)((int)param_2 + 10) & 0x7fff;
  uVar6 = *(ushort *)((int)param_1 + 10) & 0x7fff;
  uVar10 = (*(ushort *)((int)param_2 + 10) ^ *(ushort *)((int)param_1 + 10)) & 0x8000;
  uVar3 = uVar8 + uVar6;
  if (((uVar6 < 0x7fff) && (uVar8 < 0x7fff)) && (uVar3 < 0xbffe)) {
    if (uVar3 < 0x3fc0) goto LAB_00535e67;
    if (uVar6 == 0) {
      uVar3 = uVar3 + 1;
      uVar6 = 0;
      if ((((param_1[2] & 0x7fffffffU) != 0) || (param_1[1] != 0)) || (*param_1 != 0))
      goto LAB_00535e51;
    }
    else {
LAB_00535e51:
      if (((uVar8 == 0) && (uVar3 = uVar3 + 1, (param_2[2] & 0x7fffffffU) == 0)) &&
         ((param_2[1] == 0 && (*param_2 == 0)))) {
LAB_00535e67:
        param_1[2] = 0;
        param_1[1] = 0;
        *param_1 = 0;
        return;
      }
      local_1c = 0;
      local_18 = &local_10;
      param_2 = (int *)0x5;
      do {
        if (0 < (int)param_2) {
          local_28 = (ushort *)(local_1c * 2 + (int)param_1);
          local_24 = (ushort *)(piVar5 + 2);
          local_2c = (int)param_2;
          do {
            iVar7 = ___addl(*(undefined4 *)(local_18 + -2),(uint)*local_24 * (uint)*local_28,
                            local_18 + -2);
            if (iVar7 != 0) {
              *local_18 = *local_18 + 1;
            }
            local_28 = local_28 + 1;
            local_24 = local_24 + -1;
            local_2c = local_2c + -1;
          } while (local_2c != 0);
        }
        local_18 = local_18 + 1;
        local_1c = local_1c + 1;
        param_2 = (int *)((int)param_2 + -1);
      } while (0 < (int)param_2);
      param_1._0_2_ = uVar3 + 0xc002;
      if ((short)(ushort)param_1 < 1) {
LAB_00535f1b:
        param_1._0_2_ = (ushort)param_1 - 1;
        if ((short)(ushort)param_1 < 0) {
          uVar9 = (uint)(ushort)-(ushort)param_1;
          param_1._0_2_ = 0;
          do {
            if ((local_14 & 1) != 0) {
              local_20 = local_20 + 1;
            }
            ___shr_12(&local_14);
            uVar9 = uVar9 - 1;
          } while (uVar9 != 0);
          if (local_20 != 0) {
            local_14 = local_14 | 1;
          }
        }
      }
      else {
        do {
          if ((bStack_9 & 0x80) != 0) break;
          ___shl_12(&local_14);
          param_1._0_2_ = (ushort)param_1 - 1;
        } while (0 < (short)(ushort)param_1);
        if ((short)(ushort)param_1 < 1) goto LAB_00535f1b;
      }
      if ((0x8000 < CONCAT11(uStack_13,local_14)) ||
         (sVar1 = CONCAT11(bStack_9,uStack_a), iVar2 = CONCAT22(local_c,uStack_e),
         iVar7 = CONCAT22(local_10,uStack_12),
         (CONCAT22(uStack_12,CONCAT11(uStack_13,local_14)) & 0x1ffff) == 0x18000)) {
        if (CONCAT22(local_10,uStack_12) == -1) {
          iVar7 = 0;
          if (CONCAT22(local_c,uStack_e) == -1) {
            if (CONCAT11(bStack_9,uStack_a) == -1) {
              param_1._0_2_ = (ushort)param_1 + 1;
              sVar1 = -0x8000;
              iVar2 = 0;
              iVar7 = 0;
            }
            else {
              sVar1 = CONCAT11(bStack_9,uStack_a) + 1;
              iVar2 = 0;
              iVar7 = 0;
            }
          }
          else {
            sVar1 = CONCAT11(bStack_9,uStack_a);
            iVar2 = CONCAT22(local_c,uStack_e) + 1;
          }
        }
        else {
          iVar7 = CONCAT22(local_10,uStack_12) + 1;
          sVar1 = CONCAT11(bStack_9,uStack_a);
          iVar2 = CONCAT22(local_c,uStack_e);
        }
      }
      local_10 = (short)((uint)iVar7 >> 0x10);
      uStack_12 = (undefined2)iVar7;
      local_c = (undefined2)((uint)iVar2 >> 0x10);
      uStack_e = (undefined2)iVar2;
      bStack_9 = (byte)((ushort)sVar1 >> 8);
      uStack_a = (undefined1)sVar1;
      if (0x7ffe < (ushort)param_1) goto LAB_00535fc4;
      *(undefined2 *)piVar4 = uStack_12;
      *(uint *)((int)piVar4 + 2) = CONCAT22(uStack_e,local_10);
      *(uint *)((int)piVar4 + 6) = CONCAT13(bStack_9,CONCAT12(uStack_a,local_c));
      uVar6 = (ushort)param_1 | uVar10;
    }
    *(ushort *)((int)piVar4 + 10) = uVar6;
  }
  else {
LAB_00535fc4:
    piVar4[1] = 0;
    *piVar4 = 0;
    piVar4[2] = (-(uint)(uVar10 != 0) & 0x80000000) + 0x7fff8000;
  }
  return;
}

