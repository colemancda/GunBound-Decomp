/* FUN_005439c0 - 0x005439c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_005439c0(void)

{
  HRESULT HVar1;
  
  HVar1 = VariantClear((VARIANTARG *)&DAT_00569d50);
  if (HVar1 < 0) {
    FUN_00520110(HVar1);
  }
  return;
}

