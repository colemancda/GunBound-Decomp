/* FUN_00503e10 - 0x00503e10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00503e10(void)

{
  byte bVar1;
  uint uVar2;
  int unaff_ESI;
  int unaff_EDI;
  
  uVar2 = 0;
  do {
    bVar1 = (byte)uVar2;
    if (*(char *)(uVar2 + unaff_EDI) == '\0') break;
    bVar1 = bVar1 + 1;
    *(char *)(uVar2 + unaff_ESI) = *(char *)(uVar2 + unaff_EDI);
    uVar2 = (uint)bVar1;
  } while (bVar1 < 0xc);
  *(byte *)(unaff_ESI + 0xd) = bVar1;
  *(undefined1 *)((uint)bVar1 + unaff_ESI) = 0;
  return;
}

