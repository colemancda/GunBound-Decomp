/* FUN_004e5430 - 0x004e5430 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * __thiscall FUN_004e5430(undefined4 *param_1,byte param_2)

{
  *param_1 = &PTR_FUN_005572dc;
  DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

