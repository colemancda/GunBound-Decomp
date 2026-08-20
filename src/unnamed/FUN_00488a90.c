/* FUN_00488a90 - 0x00488a90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void * __thiscall FUN_00488a90(void *param_1,int param_2)

{
  Mobile01_Destructor();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

