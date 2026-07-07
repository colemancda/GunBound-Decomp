/* FUN_004eb890 - 0x004eb890 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004eb890(void)

{
  int in_EAX;
  int iVar1;
  
  if ((DAT_0079352c != 0) && (-1 < in_EAX)) {
    iVar1 = FUN_004f30c0();
    if (iVar1 != 0) {
      if (*(char *)(iVar1 + 0x18) == '\x01') {
        BlitSprite16bpp();
        return;
      }
      BlitSpriteClipped();
    }
  }
  return;
}

