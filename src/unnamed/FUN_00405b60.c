/* FUN_00405b60 - 0x00405b60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00405b60(undefined2 *param_1)

{
  if (*(char *)((int)param_1 + 0x2009) != '\0') {
    *(undefined4 *)(param_1 + 0x1000) = 4;
    param_1[1] = 0xa502;
    *param_1 = param_1[0x1000];
    FUN_004e5ac0(*(undefined4 *)(param_1 + 0x1002),4);
  }
  return;
}

