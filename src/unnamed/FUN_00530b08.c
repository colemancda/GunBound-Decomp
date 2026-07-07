/* FUN_00530b08 - 0x00530b08 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __decomp
   
   Library: Visual Studio 2003 Release */

float10 __thiscall __decomp(undefined4 param_1,uint param_2,uint param_3,int *param_4)

{
  bool bVar1;
  int iVar2;
  int extraout_EDX;
  float10 fVar3;
  
  if ((double)CONCAT17(param_3._3_1_,CONCAT16(param_3._2_1_,CONCAT24((ushort)param_3,param_2))) ==
      _DAT_005456a0) {
    fVar3 = (float10)0;
    iVar2 = 0;
  }
  else if (((param_3 & 0x7ff00000) == 0) && (((param_3 & 0xfffff) != 0 || (param_2 != 0)))) {
    if (_DAT_005456a0 <=
        (double)CONCAT17(param_3._3_1_,CONCAT16(param_3._2_1_,CONCAT24((ushort)param_3,param_2)))) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    while ((param_3._2_1_ & 0x10) == 0) {
      iVar2 = CONCAT13(param_3._3_1_,CONCAT12(param_3._2_1_,(ushort)param_3)) << 1;
      param_3._0_2_ = (ushort)iVar2;
      param_3._2_1_ = (byte)((uint)iVar2 >> 0x10);
      param_3._3_1_ = (byte)((uint)iVar2 >> 0x18);
      if ((param_2 & 0x80000000) != 0) {
        param_3._0_2_ = (ushort)param_3 | 1;
      }
      param_2 = param_2 << 1;
    }
    if (bVar1) {
      param_3._3_1_ = param_3._3_1_ | 0x80;
    }
    fVar3 = (float10)__set_exp(CONCAT17(param_3._3_1_,
                                        CONCAT16(param_3._2_1_,CONCAT24((ushort)param_3,param_2))) &
                               0xffefffffffffffff,0,param_1,param_1);
    iVar2 = extraout_EDX;
  }
  else {
    fVar3 = (float10)__set_exp(CONCAT17(param_3._3_1_,
                                        CONCAT16(param_3._2_1_,CONCAT24((ushort)param_3,param_2))),0
                               ,param_1,param_1);
    iVar2 = ((param_3 >> 0x10 & 0x7ff0) >> 4) - 0x3fe;
  }
  *param_4 = iVar2;
  return (float10)(double)fVar3;
}

