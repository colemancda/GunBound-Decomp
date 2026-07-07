/* FUN_00527f3d - 0x00527f3d in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_00527f3d(uint param_1,uint param_2)

{
  uint uVar1;
  bool in_ZF;
  short in_FPUControlWord;
  
  if (in_ZF) {
    if (((param_2 & 0xfffff) != 0) || (param_1 != 0)) {
      uVar1 = FUN_0052fd9c();
      goto LAB_00527fbb;
    }
    param_1 = param_2 & 0x80000000;
    param_2 = 0;
joined_r0x00527fac:
    if (param_1 == 0) {
LAB_00527f5e:
      if (DAT_005b1764 != 0) {
        return param_2;
      }
      uVar1 = __math_exit();
      return uVar1;
    }
  }
  else {
    if (in_FPUControlWord != 0x27f) {
      param_2 = FUN_0052fd85();
    }
    if ((param_2 & 0x80000000) == 0) goto LAB_00527f5e;
    if (((param_2 & 0x7ff00000) == 0) && ((param_2 & 0xfffff) == 0)) goto joined_r0x00527fac;
  }
  uVar1 = 1;
LAB_00527fbb:
  if (DAT_005b1764 != 0) {
    return uVar1;
  }
  uVar1 = __startOneArgErrorHandling();
  return uVar1;
}

