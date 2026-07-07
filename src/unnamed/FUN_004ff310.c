/* FUN_004ff310 - 0x004ff310 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_004ff310(void)

{
  int iVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  int unaff_EDI;
  
  iVar4 = 0;
  uVar3 = 0;
  if (*(char *)(unaff_EDI + 0x11) != '\0') {
    do {
      iVar1 = _toupper((int)*(char *)(uVar3 + unaff_EDI));
      iVar4 = iVar4 * 0x21 + iVar1;
      bVar2 = (char)uVar3 + 1;
      uVar3 = (uint)bVar2;
    } while (bVar2 < *(byte *)(unaff_EDI + 0x11));
  }
  return iVar4;
}

