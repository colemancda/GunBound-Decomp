/* FUN_0052ff6a - 0x0052ff6a in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __powhlp
   
   Library: Visual Studio 2003 Release */

undefined4 __powhlp(int param_1,int param_2,double param_3,double *param_4)

{
  double dVar1;
  double dVar2;
  int iVar3;
  undefined4 uVar4;
  
  dVar1 = (double)CONCAT44(param_2,param_1);
  uVar4 = 0;
  if (dVar1 < _DAT_005456a0) {
    dVar1 = -dVar1;
  }
  dVar2 = _DAT_0056cb58;
  if (param_3._4_4_ == 0x7ff00000) {
    if (param_3._0_4_ != 0) goto LAB_00530015;
    if (_DAT_00544e38 < dVar1) goto LAB_005300c5;
    if (_DAT_00544e38 <= dVar1) goto LAB_0052ffc8;
  }
  else {
    if ((param_3._4_4_ == -0x100000) && (param_3._0_4_ == 0)) {
      if (_DAT_00544e38 < dVar1) {
        dVar2 = 0.0;
        goto LAB_005300c5;
      }
      if (dVar1 < _DAT_00544e38) goto LAB_005300c5;
LAB_0052ffc8:
      uVar4 = 1;
      dVar2 = _DAT_0056cb60;
      goto LAB_005300c5;
    }
LAB_00530015:
    if (param_2 != 0x7ff00000) {
      if (param_2 != -0x100000) {
        return 0;
      }
      if (param_1 != 0) {
        return 0;
      }
      iVar3 = __d_inttype(param_3);
      if (param_3 <= _DAT_005456a0) {
        if (_DAT_005456a0 <= param_3) {
          dVar2 = 1.0;
        }
        else {
          dVar2 = _DAT_0056cb78;
          if (iVar3 != 1) {
            dVar2 = 0.0;
          }
        }
      }
      else {
        dVar2 = _DAT_0056cb58;
        if (iVar3 == 1) {
          dVar2 = -_DAT_0056cb58;
        }
      }
      goto LAB_005300c5;
    }
    if (param_1 != 0) {
      return 0;
    }
    if (_DAT_005456a0 < param_3) goto LAB_005300c5;
    if (_DAT_005456a0 <= param_3) {
      dVar2 = 1.0;
      goto LAB_005300c5;
    }
  }
  dVar2 = 0.0;
LAB_005300c5:
  *param_4 = dVar2;
  return uVar4;
}

