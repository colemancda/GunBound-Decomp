/* FUN_005202d1 - 0x005202d1 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_005202d1(exception *param_1)

{
  *(undefined ***)param_1 = &PTR_FUN_00544ba8;
  exception::~exception(param_1);
  return;
}

