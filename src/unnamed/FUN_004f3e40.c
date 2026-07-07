/* FUN_004f3e40 - 0x004f3e40 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004f3e40(void)

{
  undefined1 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = &DAT_007921b0;
  for (iVar2 = 0x400; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  puVar1 = (undefined1 *)FUN_004f3dc0();
  DAT_00792190 = puVar1;
  *puVar1 = 0;
  *(undefined4 *)(puVar1 + 0x70) = 0;
  *(undefined4 *)(puVar1 + 0x74) = 0;
  *(undefined4 *)(puVar1 + 0x7c) = 0;
  *(undefined4 *)(puVar1 + 0x78) = 0xfe967699;
  return;
}

