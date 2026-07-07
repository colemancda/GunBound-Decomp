/* FUN_0050e420 - 0x0050e420 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_0050e420(undefined4 *param_1,int param_2,int param_3)

{
  char cVar1;
  undefined1 uVar2;
  
  uVar2 = 0;
  if ((((*(char *)((int)param_1 + 0x1e) == '\0') && ((int)param_1[10] < param_2)) &&
      (param_2 < (int)(param_1[0xc] + param_1[10]))) &&
     (((int)param_1[0xb] < param_3 && (param_3 < (int)(param_1[0xd] + param_1[0xb]))))) {
    uVar2 = 1;
  }
  *(undefined1 *)(param_1 + 1) = uVar2;
  cVar1 = FUN_0050e8e0(param_2,param_3);
  if ((*(char *)(param_1 + 1) == '\0') && (cVar1 == '\0')) {
    (**(code **)*param_1)(0);
  }
  if (((*(char *)(param_1 + 1) == '\x01') && (cVar1 == '\0')) && (*(char *)(param_1 + 0xe) == '\0'))
  {
    *(undefined1 *)((int)param_1 + 0x39) = 1;
  }
  else {
    *(undefined1 *)((int)param_1 + 0x39) = 0;
  }
  param_1[0xf] = param_2;
  param_1[0x10] = param_3;
  if ((*(char *)(param_1 + 1) == '\0') && (cVar1 == '\0')) {
    return 0;
  }
  return 1;
}

