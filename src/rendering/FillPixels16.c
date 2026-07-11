/* FillPixels16 - 0x004f26f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FillPixels16(undefined4 *param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  
  if (param_3 != 0) {
    if (param_1 != (undefined4 *)0x1) {
      if ((-(int)param_1 & 2U) != 0) {
        param_3 = param_3 - 1;
        *(char *)param_1 = (char)param_2;
        *(char *)((int)param_1 + 1) = (char)((uint)param_2 >> 8);
        param_1 = (undefined4 *)((int)param_1 + 2);
      }
      param_2 = CONCAT22((short)param_2,(short)param_2);
      uVar1 = param_3 >> 1;
      if (uVar1 != 0) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *param_1 = param_2;
          param_1 = param_1 + 1;
        }
        if ((param_3 & 1) == 0) {
          return;
        }
      }
    }
    *(char *)param_1 = (char)param_2;
    *(char *)((int)param_1 + 1) = (char)((uint)param_2 >> 8);
  }
  return;
}

