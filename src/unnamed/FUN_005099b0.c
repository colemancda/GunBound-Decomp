/* FUN_005099b0 - 0x005099b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_005099b0(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int in_EAX;
  
  puVar2 = *(undefined4 **)(in_EAX + 4);
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*puVar2;
    *(undefined1 *)(puVar2[2] + 0x1e) = 0;
    puVar2 = puVar1;
  }
  return;
}

