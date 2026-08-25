/* FUN_005040d0 - 0x005040d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_005040d0(undefined4 *param_1,undefined4 *param_2,undefined4 *regEax)

{
  
  for (; param_1 != param_2; param_1 = (undefined4 *)((int)param_1 + 0x12)) {
    *regEax = *param_1;
    regEax[1] = param_1[1];
    regEax[2] = param_1[2];
    regEax[3] = param_1[3];
    *(undefined2 *)(regEax + 4) = *(undefined2 *)(param_1 + 4);
    regEax = (undefined4 *)((int)regEax + 0x12);
  }
  return;
}

