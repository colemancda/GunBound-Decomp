/* FUN_00530661 - 0x00530661 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __handle_exc
   
   Library: Visual Studio 2003 Release */

bool __handle_exc(uint param_1,double *param_2,uint param_3)

{
  double dVar1;
  bool bVar2;
  uint uVar3;
  bool bVar4;
  float10 fVar5;
  undefined8 local_14;
  int local_c;
  uint local_8;
  
  uVar3 = param_1 & 0x1f;
  bVar2 = true;
  local_8 = uVar3;
  if (((param_1 & 8) != 0) && ((param_3 & 1) != 0)) {
    FUN_00530bff(1);
    uVar3 = param_1 & 0x17;
    goto LAB_00530863;
  }
  if (((param_1 & 4) != 0) && ((param_3 & 4) != 0)) {
    FUN_00530bff(4);
    uVar3 = param_1 & 0x1b;
    goto LAB_00530863;
  }
  if (((param_1 & 1) == 0) || ((param_3 & 8) == 0)) {
    if (((param_1 & 2) != 0) && ((param_3 & 0x10) != 0)) {
      bVar4 = (param_1 & 0x10) != 0;
      if (*param_2 != _DAT_005456a0) {
        fVar5 = (float10)__decomp(*param_2,&local_c);
        dVar1 = (double)fVar5;
        local_c = local_c + -0x600;
        if (local_c < -0x432) {
          local_14 = dVar1 * _DAT_005456a0;
          bVar4 = bVar2;
        }
        else {
          local_14 = (double)((ulonglong)dVar1 & 0xfffffffffffff | 0x10000000000000);
          if (local_c < -0x3fd) {
            local_c = -0x3fd - local_c;
            do {
              if ((((ulonglong)local_14 & 1) != 0) && (!bVar4)) {
                bVar4 = bVar2;
              }
              uVar3 = (uint)local_14 >> 1;
              if (((ulonglong)local_14 & 0x100000000) != 0) {
                local_14._3_1_ = (byte)((ulonglong)local_14 >> 0x18) >> 1;
                local_14._0_3_ = (undefined3)uVar3;
                local_14._0_4_ = CONCAT13(local_14._3_1_,(undefined3)local_14) | 0x80000000;
                uVar3 = (uint)local_14;
              }
              local_14._0_4_ = uVar3;
              local_14 = (double)CONCAT44(local_14._4_4_ >> 1,(uint)local_14);
              local_c = local_c + -1;
            } while (local_c != 0);
          }
          if (dVar1 < _DAT_005456a0) {
            local_14 = -local_14;
          }
        }
        *param_2 = local_14;
        bVar2 = bVar4;
      }
      if (bVar2) {
        FUN_00530bff(0x10);
      }
      uVar3 = local_8 & 0xfffffffd;
      local_8 = uVar3;
    }
    goto LAB_00530863;
  }
  FUN_00530bff(8);
  uVar3 = param_3 & 0xc00;
  dVar1 = _DAT_0056cb58;
  if (uVar3 == 0) {
    if (*param_2 <= _DAT_005456a0) {
      dVar1 = -_DAT_0056cb58;
    }
LAB_0053077f:
    *param_2 = dVar1;
  }
  else {
    if (uVar3 == 0x400) {
      dVar1 = _DAT_0056cb68;
      if (*param_2 <= _DAT_005456a0) {
        dVar1 = -_DAT_0056cb58;
      }
      goto LAB_0053077f;
    }
    if (uVar3 == 0x800) {
      if (*param_2 <= _DAT_005456a0) {
        dVar1 = -_DAT_0056cb68;
      }
      goto LAB_0053077f;
    }
    if (uVar3 == 0xc00) {
      dVar1 = _DAT_0056cb68;
      if (*param_2 <= _DAT_005456a0) {
        dVar1 = -_DAT_0056cb68;
      }
      goto LAB_0053077f;
    }
  }
  uVar3 = param_1 & 0x1e;
LAB_00530863:
  if (((param_1 & 0x10) != 0) && ((param_3 & 0x20) != 0)) {
    FUN_00530bff(0x20);
    uVar3 = uVar3 & 0xffffffef;
  }
  return uVar3 == 0;
}

