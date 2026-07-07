/* FUN_004d24f0 - 0x004d24f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004d24f0(void)

{
  int iVar1;
  int unaff_EDI;
  
  iVar1 = *(int *)(unaff_EDI + 0x84e0);
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 0x22c) = 1;
    if (*(SOCKET *)(iVar1 + 0x24) != 0xffffffff) {
      closesocket(*(SOCKET *)(iVar1 + 0x24));
    }
    *(undefined4 *)(iVar1 + 0x24) = 0xffffffff;
    *(undefined1 *)(iVar1 + 0x22a) = 0;
    *(undefined1 *)(unaff_EDI + 0x84e5) = 0;
  }
  return;
}

