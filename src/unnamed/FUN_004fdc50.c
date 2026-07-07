/* FUN_004fdc50 - 0x004fdc50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004fdc50(void)

{
  int in_EAX;
  byte bVar1;
  uint uVar2;
  int unaff_ESI;
  
  uVar2 = 0;
  do {
    bVar1 = (byte)uVar2;
    if (*(char *)(uVar2 + unaff_ESI) == '\0') break;
    bVar1 = bVar1 + 1;
    *(char *)(uVar2 + in_EAX) = *(char *)(uVar2 + unaff_ESI);
    uVar2 = (uint)bVar1;
  } while (bVar1 < 0x10);
  *(byte *)(in_EAX + 0x11) = bVar1;
  *(undefined1 *)((uint)bVar1 + in_EAX) = 0;
  return;
}

