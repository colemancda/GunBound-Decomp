/* FUN_004ff640 - 0x004ff640 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004ff640(int *param_1,int regEbx)

{
  int *in_EAX;
  int *piVar1;
  
  (**(code **)(*param_1 + 4))();
  if ((regEbx != 0) && (piVar1 = (int *)param_1[1], piVar1 != (int *)0x0)) {
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

