/* FUN_004e7430 - 0x004e7430 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004e7430(void)

{
  int iVar1;
  int unaff_ESI;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(unaff_ESI + 0x18);
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 *)(unaff_ESI + 0x13c) = 0;
  *(undefined4 *)(unaff_ESI + 0x140) = 0;
  *(undefined4 *)(unaff_ESI + 0x138) = 0;
  puVar2 = (undefined4 *)(unaff_ESI + 0x42de0);
  for (iVar1 = 0x400; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 *)(unaff_ESI + 0x40bd0) = 0;
  *(undefined4 *)(unaff_ESI + 0x40bd4) = 0;
  *(undefined4 *)(unaff_ESI + 0x44de4) = 0;
  *(undefined4 *)(unaff_ESI + 0x44de8) = 0;
  InterlockedExchange((LONG *)(unaff_ESI + 0x44de0),0);
  *(undefined4 *)(unaff_ESI + 0x454c4) = 0xffffffff;
  *(undefined4 *)(unaff_ESI + 0x454c8) = 0xffffffff;
  *(undefined4 *)(unaff_ESI + 0x454cc) = 0xffffffff;
  *(undefined4 *)(unaff_ESI + 0x454d0) = 0xffffffff;
  *(undefined4 *)(unaff_ESI + 0x454d4) = 0xffffffff;
  *(undefined4 *)(unaff_ESI + 0x454d8) = 0xffffffff;
  *(undefined4 *)(unaff_ESI + 0x454dc) = 0xffffffff;
  *(undefined4 *)(unaff_ESI + 0x454e0) = 0xffffffff;
  return;
}

