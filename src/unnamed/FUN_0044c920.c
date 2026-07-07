/* FUN_0044c920 - 0x0044c920 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void * __thiscall FUN_0044c920(void *param_1,int param_2)

{
  FUN_0044c940();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

