/* RenderScreenBackdrop - 0x00443570 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void RenderScreenBackdrop(void)

{
  int iVar1;
  
  if (DAT_0079352c != 0) {
    iVar1 = FindSpriteFrame();
    if (iVar1 != 0) {
      if (*(char *)(iVar1 + 0x18) == '\x01') {
        BlitSprite16bpp(0);
        return;
      }
      BlitSpriteClipped(0);
    }
  }
  return;
}

