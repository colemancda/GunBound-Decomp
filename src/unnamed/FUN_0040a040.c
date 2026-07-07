/* FUN_0040a040 - 0x0040a040 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0040a040(exception *param_1)

{
  *(undefined ***)param_1 = &PTR_FUN_00544b5c;
  if (0xf < *(uint *)(param_1 + 0x24)) {
    _free(*(void **)(param_1 + 0x10));
  }
  *(undefined4 *)(param_1 + 0x24) = 0xf;
  *(undefined4 *)(param_1 + 0x20) = 0;
  param_1[0x10] = (exception)0x0;
  exception::~exception(param_1);
  return;
}

