/* FUN_0052020a - 0x0052020a in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


HIMC ImmGetContext(HWND param_1)

{
  HIMC pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0052020a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = ImmGetContext(param_1);
  return pHVar1;
}

