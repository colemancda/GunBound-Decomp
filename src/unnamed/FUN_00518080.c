/* FUN_00518080 - 0x00518080 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00518080(float *param_1,int param_2,int param_3)

{
  float *pfVar1;
  
  if (0 < param_3) {
    pfVar1 = param_1;
    do {
      param_3 = param_3 + -1;
      *pfVar1 = *(float *)((param_2 - (int)param_1) + (int)pfVar1) + *pfVar1;
      pfVar1 = pfVar1 + 1;
    } while (param_3 != 0);
  }
  return;
}

