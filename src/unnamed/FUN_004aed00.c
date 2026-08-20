/* FUN_004aed00 - 0x004aed00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void * __thiscall FUN_004aed00(void *param_1,int param_2)

{
  Mobile11_Destructor();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

