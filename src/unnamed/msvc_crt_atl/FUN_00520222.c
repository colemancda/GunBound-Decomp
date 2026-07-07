/* FUN_00520222 - 0x00520222 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


BOOL ImmGetOpenStatus(HIMC param_1)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00520222. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = ImmGetOpenStatus(param_1);
  return BVar1;
}

