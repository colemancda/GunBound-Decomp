/* FUN_00429c30 - 0x00429c30 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00429c30(int param_1)

{
  *(undefined4 *)(param_1 + 0x110) = 0x62b2;
  *(undefined1 *)(param_1 + 0x114) = 8;
  FUN_00508190(&DAT_00e53c40,(undefined4 *)(param_1 + 0x110),(undefined1 *)(param_1 + 0x114),
               &DAT_005b3368);
  return;
}

