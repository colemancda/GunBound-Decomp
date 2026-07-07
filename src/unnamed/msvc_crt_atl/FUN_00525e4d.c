/* FUN_00525e4d - 0x00525e4d in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


exception * __thiscall FUN_00525e4d(exception *param_1,byte param_2)

{
  exception::~exception(param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

