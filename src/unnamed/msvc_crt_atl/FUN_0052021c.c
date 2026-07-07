/* FUN_0052021c - 0x0052021c in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


BOOL ImmSetCompositionWindow(HIMC param_1,LPCOMPOSITIONFORM lpCompForm)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0052021c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = ImmSetCompositionWindow(param_1,lpCompForm);
  return BVar1;
}

