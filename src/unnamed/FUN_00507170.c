/* FUN_00507170 - 0x00507170 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00507170(int param_1,undefined4 param_2)

{
  if (*(char *)(param_1 + 4) != '\0') {
    Widget_DispatchKeyToChildren(param_2);
  }
  Widget_DispatchMouseToChildren(param_2);
  return;
}

