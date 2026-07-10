/* BlitSpriteClipped - 0x004eb9c0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


undefined4 BlitSpriteClipped(int param_1)

{
  int in_EAX;
  int iVar1;
  int iVar2;
  int local_4;
  
  if (((DAT_0079352c != 0) && (-1 < param_1)) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
    iVar2 = in_EAX + *(int *)(iVar1 + 0x2c);
    local_4 = *(int *)(iVar1 + 0x24) - ((DAT_00793534 - iVar2 < 0) - 1 & DAT_00793534 - iVar2);
    if (iVar2 < DAT_00793534) {
      iVar2 = DAT_00793534;
    }
    if (DAT_0056df34 < local_4 + iVar2) {
      local_4 = (DAT_0056df34 - iVar2) + 1;
    }
    if (0 < local_4) {
      do {
        FUN_004eb940(iVar2);
        iVar2 = iVar2 + 1;
        local_4 = local_4 + -1;
      } while (local_4 != 0);
    }
  }
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

