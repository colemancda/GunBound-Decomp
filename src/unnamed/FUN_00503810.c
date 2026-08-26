/* FUN_00503810 - 0x00503810 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-08-25): `lea eax,[esp+0xe8]` at 0x501afd, which under
 * FUN_00501770's -0x4990 frame constant is -0x48a8 -- a slot that function
 * does not declare, because it is INSIDE one that it does: `char local_48ba
 * [82]` runs from -0x48ba to -0x4869, so -0x48a8 is local_48ba + 0x12.  That
 * array is a name key record (its +0x11 is the length byte the lines above
 * the call fill in), so EAX is the payload just past the key.
 */
#include "ghidra_types.h"


void FUN_00503810(int regEsi,int regEax)

{
  byte bVar1;
  uint uVar2;
  
  uVar2 = 0;
  do {
    bVar1 = (byte)uVar2;
    if (*(char *)(uVar2 + regEsi) == '\0') break;
    bVar1 = bVar1 + 1;
    *(char *)(uVar2 + regEax) = *(char *)(uVar2 + regEsi);
    uVar2 = (uint)bVar1;
  } while (bVar1 < 8);
  *(byte *)(regEax + 9) = bVar1;
  *(undefined1 *)((uint)bVar1 + regEax) = 0;
  return;
}

