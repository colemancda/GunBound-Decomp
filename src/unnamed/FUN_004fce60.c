/* FUN_004fce60 - 0x004fce60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_004fce60(void)

{
  short sVar1;
  int unaff_EBX;
  int iVar2;
  int unaff_EDI;
  
  iVar2 = 0;
  if (0 < *(int *)(unaff_EDI + 0x280) + 1) {
    do {
      sVar1 = DecodeCipherBlock(iVar2 + unaff_EBX);
      if (sVar1 != 1) {
        return 0;
      }
      iVar2 = iVar2 + 0x10;
    } while (iVar2 < *(int *)(unaff_EDI + 0x280) + 1);
  }
  return 1;
}

