/* FUN_005042f0 - 0x005042f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_005042f0(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *in_EAX;
  
  while (param_2 != param_1) {
    *(undefined4 *)((int)in_EAX + -0x12) = *(undefined4 *)((int)param_1 + -0x12);
    *(undefined4 *)((int)in_EAX + -0xe) = *(undefined4 *)((int)param_1 + -0xe);
    *(undefined4 *)((int)in_EAX + -10) = *(undefined4 *)((int)param_1 + -10);
    *(undefined4 *)((int)in_EAX + -6) = *(undefined4 *)((int)param_1 + -6);
    *(undefined2 *)((int)in_EAX + -2) = *(undefined2 *)((int)param_1 + -2);
    param_1 = (undefined4 *)((int)param_1 + -0x12);
    in_EAX = (undefined4 *)((int)in_EAX + -0x12);
  }
  return;
}

