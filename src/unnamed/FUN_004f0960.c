/* FUN_004f0960 - 0x004f0960 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004f0960(int param_1)

{
  if (*(char *)(param_1 + 0x1018) != '\0') {
    *(undefined4 *)(param_1 + 0x1010) = *(undefined4 *)(*(int *)(param_1 + 0x1004) + 0x74);
    *(undefined4 *)(param_1 + 0x1014) = 0;
    if (*(int *)(*(int *)(param_1 + 0x1004) + 0x70) == 0) {
      DecodeXFSEntryBlock();
      return;
    }
  }
  return;
}

