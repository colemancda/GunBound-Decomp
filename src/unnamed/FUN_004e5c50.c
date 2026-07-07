/* FUN_004e5c50 - 0x004e5c50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_004e5c50(int *param_1)

{
  uint in_EAX;
  
  if ((uint)param_1[1] <= in_EAX) {
                    /* WARNING: Subroutine does not return */
    FUN_004010c0(0x80070057);
  }
  return in_EAX * 0x4004 + *param_1;
}

