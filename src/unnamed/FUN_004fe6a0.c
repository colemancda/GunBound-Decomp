/* FUN_004fe6a0 - 0x004fe6a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004fe6a0(undefined4 param_1,int *param_2)

{
  int *in_EAX;
  int *piVar1;
  
  (**(code **)(*param_2 + 8))(param_1);
  piVar1 = (int *)param_2[1];
  if (piVar1 != (int *)0x0) {
    while (in_EAX != piVar1) {
      piVar1 = (int *)*piVar1;
      if (piVar1 == (int *)0x0) {
        return;
      }
    }
    if (in_EAX[2] != 0xffffffff) {
      closesocket(in_EAX[2]);
    }
    FUN_004ff720();
  }
  return;
}

