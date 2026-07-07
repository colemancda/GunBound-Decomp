/* FUN_004f3a30 - 0x004f3a30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f3a30(void)

{
  undefined4 *puVar1;
  
  puVar1 = &DAT_006b9100;
  do {
    if ((void *)*puVar1 != (void *)0x0) {
      _free((void *)*puVar1);
    }
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  } while ((int)puVar1 < 0x6ba100);
  return;
}

