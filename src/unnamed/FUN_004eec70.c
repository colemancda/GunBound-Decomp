/* FUN_004eec70 - 0x004eec70 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_004eec70(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int unaff_EBX;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  if (*(int *)(unaff_EBX + 0xa4) < 0) {
    *(undefined4 *)(unaff_EBX + 0xa4) = 0;
  }
  uVar2 = *(uint *)(unaff_EBX + 0xa4);
  if ((int)uVar2 < *(int *)(unaff_EBX + 0xa0)) {
    uVar2 = ((int)uVar2 < 0) - 1 & uVar2;
    puVar4 = *(undefined4 **)(unaff_EBX + 0x9c);
    puVar5 = *(undefined4 **)(unaff_EBX + 0x98);
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
    iVar1 = ReadXFSEntryByte(*(undefined4 *)(unaff_EBX + 0x50),
                             *(int *)(unaff_EBX + 0x98) + *(int *)(unaff_EBX + 0xa4));
    if (iVar1 == -1) {
      *(undefined4 *)(unaff_EBX + 0xa0) = 0;
      return 0;
    }
    *(int *)(unaff_EBX + 0xa4) = *(int *)(unaff_EBX + 0xa4) + iVar1;
    *(undefined4 *)(unaff_EBX + 0x9c) = *(undefined4 *)(unaff_EBX + 0x98);
  }
  return 1;
}

