/* FUN_004ea670 - 0x004ea670 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_004ea670(void)

{
  int iVar1;
  int unaff_ESI;
  uint uVar2;
  
  for (uVar2 = *(uint *)(unaff_ESI + 0xf6ac); uVar2 < 0x273;
      uVar2 = *(uint *)(unaff_ESI + 0xece4 + uVar2 * 4)) {
    if (*(char *)(unaff_ESI + 0xf6b2) == '\0') {
      iVar1 = FUN_004ea120();
      uVar2 = uVar2 + iVar1;
    }
    else {
      *(char *)(unaff_ESI + 0xf6b2) = *(char *)(unaff_ESI + 0xf6b2) + -1;
      if (*(short *)(unaff_ESI + 0xf6b0) < 0) {
        uVar2 = uVar2 + 1;
      }
      *(short *)(unaff_ESI + 0xf6b0) = *(short *)(unaff_ESI + 0xf6b0) * 2;
    }
  }
  FUN_004ea580(uVar2 - 0x273);
  return uVar2 - 0x273;
}

