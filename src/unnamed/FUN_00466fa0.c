/* FUN_00466fa0 - 0x00466fa0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void * __thiscall FUN_00466fa0(void *param_1,int param_2)

{
  FUN_00466fc0();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

