/* FUN_004e6b50 - 0x004e6b50 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004e6b50(void)

{
  uintptr_t uVar1;
  void *unaff_ESI;
  
  *(undefined4 *)((int)unaff_ESI + 0x3bc) = 0;
  *(undefined4 *)((int)unaff_ESI + 0x3b8) = 0;
  uVar1 = __beginthread(FUN_004f47e0,0,unaff_ESI);
  *(uintptr_t *)((int)unaff_ESI + 4) = uVar1;
  if (uVar1 != 0) {
    Sleep(0);
  }
  return;
}

