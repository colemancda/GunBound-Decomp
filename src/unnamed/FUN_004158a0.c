/* FUN_004158a0 - 0x004158a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_004158a0(int param_1,int param_2)

{
  if (param_2 != *(int *)(param_1 + 0x14)) {
    FUN_004158a0(*(undefined4 *)(param_2 + 0xc));
    FUN_004158a0(*(undefined4 *)(param_2 + 0x10));
    thunk_FUN_004158f0();
    *(undefined4 *)(param_2 + 0xc) = *(undefined4 *)(param_1 + 8);
    *(int *)(param_1 + 8) = param_2;
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + -1;
  }
  return;
}

