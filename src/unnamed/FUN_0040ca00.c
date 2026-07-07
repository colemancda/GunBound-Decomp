/* FUN_0040ca00 - 0x0040ca00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void * __thiscall FUN_0040ca00(void *param_1,byte param_2)

{
  FUN_004711e0();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

