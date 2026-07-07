/* FUN_00543870 - 0x00543870 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00543870(void)

{
  int iVar1;
  
  iVar1 = DAT_00e9c9e0;
  if (DAT_00e9c9dc != (void *)0x0) {
    for (; iVar1 != 0; iVar1 = iVar1 + -1) {
      FUN_00405320();
    }
    _free(DAT_00e9c9dc);
  }
  return;
}

