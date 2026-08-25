/* FUN_005037d0 - 0x005037d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ESI and EDI RECOVERED (2026-08-25) from the single site in FUN_00501770, under the
 * -0x4990 frame constant that function's earlier recoveries established and
 * that four independent slots agree on: `lea esi,[esp+0xb2]` = &local_48de and
 * `lea edi,[esp+0x4c]` = &local_4944.
 */
#include "ghidra_types.h"


void FUN_005037d0(int regEsi,int regEdi)

{
  byte bVar1;
  uint uVar2;
  
  uVar2 = 0;
  do {
    bVar1 = (byte)uVar2;
    if (*(char *)(uVar2 + regEdi) == '\0') break;
    bVar1 = bVar1 + 1;
    *(char *)(uVar2 + regEsi) = *(char *)(uVar2 + regEdi);
    uVar2 = (uint)bVar1;
  } while (bVar1 < 0x14);
  *(byte *)(regEsi + 0x15) = bVar1;
  *(undefined1 *)((uint)bVar1 + regEsi) = 0;
  return;
}

