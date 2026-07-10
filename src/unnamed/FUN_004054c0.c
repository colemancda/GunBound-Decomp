/* FUN_004054c0 - 0x004054c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_004054c0(int param_1,int param_2)

{
  if (param_2 != *(int *)(param_1 + 0x14)) {
    /* Ghidra dropped the recursive calls' `this` (param_1) arg - this is
     * a binary-tree walk: same container `this`, left/right child nodes
     * at param_2+0x108/+0x10c passed as the node argument. */
    FUN_004054c0(param_1,*(undefined4 *)(param_2 + 0x108));
    FUN_004054c0(param_1,*(undefined4 *)(param_2 + 0x10c));
    thunk_FUN_00405320();
    *(undefined4 *)(param_2 + 0x108) = *(undefined4 *)(param_1 + 8);
    *(int *)(param_1 + 8) = param_2;
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + -1;
  }
  return;
}

