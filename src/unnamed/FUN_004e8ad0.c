/* FUN_004e8ad0 - 0x004e8ad0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e8ad0(int *param_1)

{
  char cVar1;
  int *piVar2;
  
  cVar1 = *(char *)((int)param_1 + 0xf);
  while (cVar1 == '\0') {
    FUN_004e8ad0(param_1[2]);
    piVar2 = (int *)*param_1;
    _free(param_1);
    param_1 = piVar2;
    cVar1 = *(char *)((int)piVar2 + 0xf);
  }
  return;
}

