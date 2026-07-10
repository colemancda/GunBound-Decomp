/* FUN_004e4410 - 0x004e4410 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_004e4410(int param_1,int param_2)

{
  int in_EAX;
  
  if ((-1 < param_1) && (param_1 < *(int *)(param_2 + 0x1c))) {
    if (in_EAX < 0) {
      in_EAX = 0;
    }
    if (in_EAX < *(int *)(param_2 + 0x18)) {
      for (; *(char *)(*(int *)(param_2 + 0x18) * param_1 + *(int *)(param_2 + 0x34) + in_EAX) ==
             '\0'; in_EAX = in_EAX + 1) {
      }
    }
  }
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

