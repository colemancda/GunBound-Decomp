/* FUN_00518120 - 0x00518120 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00518120(float *param_1,int param_2)

{
  float fVar1;
  
  if (0 < param_2) {
    do {
      param_2 = param_2 + -1;
      fVar1 = *param_1;
      *param_1 = param_1[0x480] + *param_1;
      param_1[0x480] = fVar1 - param_1[0x480];
      param_1 = param_1 + 1;
    } while (param_2 != 0);
  }
  return;
}

