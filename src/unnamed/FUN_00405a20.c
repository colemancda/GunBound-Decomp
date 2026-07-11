/* FUN_00405a20 - 0x00405a20 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00405a20(undefined2 *param_1)

{
  *param_1 = param_1[0x1000];
  SendSocketData(*(undefined4 *)(param_1 + 0x1002),*(undefined4 *)(param_1 + 0x1000));
  return;
}

