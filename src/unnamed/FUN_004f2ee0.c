/* FUN_004f2ee0 - 0x004f2ee0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004f2ee0(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_00557534;
  FUN_004f3060(param_1);
  if ((undefined4 *)param_1[1] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)param_1[1])(1);
  }
  return;
}

