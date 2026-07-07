/* FUN_00503eb0 - 0x00503eb0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00503eb0(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *in_EAX;
  
  for (; in_EAX != param_1; in_EAX = (undefined4 *)((int)in_EAX + 0x12)) {
    *in_EAX = *param_2;
    in_EAX[1] = param_2[1];
    in_EAX[2] = param_2[2];
    in_EAX[3] = param_2[3];
    *(undefined2 *)(in_EAX + 4) = *(undefined2 *)(param_2 + 4);
  }
  return;
}

