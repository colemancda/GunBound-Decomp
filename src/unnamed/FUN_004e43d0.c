/* FUN_004e43d0 - 0x004e43d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_004e43d0(int param_1,int param_2)

{
  int iVar1;
  int in_EAX;
  
  if ((-1 < in_EAX) && (in_EAX < *(int *)(param_2 + 0x1c))) {
    iVar1 = *(int *)(param_2 + 0x18);
    if (iVar1 <= param_1) {
      param_1 = iVar1 + -1;
    }
    if (-1 < param_1) {
      for (; *(char *)(iVar1 * in_EAX + *(int *)(param_2 + 0x34) + param_1) == '\0';
          param_1 = param_1 + -1) {
      }
      return param_1;
    }
  }
  return -10000;
}

