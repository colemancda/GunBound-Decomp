/* FUN_004fd3c0 - 0x004fd3c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004fd3c0(void *param_1)

{
  int *piVar1;
  
  piVar1 = (int *)((int)param_1 + 0x1a6c);
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == 0) {
    FUN_004fd230(param_1);
    _free(param_1);
  }
  return;
}

